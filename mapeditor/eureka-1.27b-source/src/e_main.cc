//------------------------------------------------------------------------
//  LEVEL MISC STUFF
//------------------------------------------------------------------------
//
//  Eureka DOOM Editor
//
//  Copyright (C) 2001-2019 Andrew Apted
//  Copyright (C) 1997-2003 Andr� Majorel et al
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//------------------------------------------------------------------------
//
//  Based on Yadex which incorporated code from DEU 5.21 that was put
//  in the public domain in 1994 by Rapha�l Quinet and Brendon Wyber.
//
//------------------------------------------------------------------------

#include "main.h"

#include "m_bitvec.h"
#include "m_game.h"
#include "e_hover.h"
#include "e_linedef.h"
#include "e_main.h"
#include "e_path.h"
#include "e_things.h"
#include "e_vertex.h"
#include "r_render.h"
#include "r_subdiv.h"
#include "w_rawdef.h"

#include "ui_window.h"


Editor_State_t  edit;


double Map_bound_x1 =  32767;   /* minimum X value of map */
double Map_bound_y1 =  32767;   /* minimum Y value of map */
double Map_bound_x2 = -32767;   /* maximum X value of map */
double Map_bound_y2 = -32767;   /* maximum Y value of map */

int MadeChanges;

static bool recalc_map_bounds;
static int  new_vertex_minimum;
static int  moved_vertex_count;

static selection_c * last_Sel;

extern bool sound_propagation_invalid;


// config items
int default_edit_mode = 3;  // Vertices

bool same_mode_clears_selection = false;

int sector_render_default = (int)SREND_Floor;
int  thing_render_default = 1;


//
// adjust zoom factor to make whole map fit in window
//
static void zoom_fit()
{
	if (NumVertices == 0)
		return;

	double xzoom = 1;
	double yzoom = 1;

	int ScrMaxX = main_win->canvas->w();
	int ScrMaxY = main_win->canvas->h();

	if (Map_bound_x1 < Map_bound_x2)
		xzoom = ScrMaxX / (Map_bound_x2 - Map_bound_x1);

	if (Map_bound_y1 < Map_bound_y2)
		yzoom = ScrMaxY / (Map_bound_y2 - Map_bound_y1);

	grid.NearestScale(MIN(xzoom, yzoom));

	grid.MoveTo((Map_bound_x1 + Map_bound_x2) / 2, (Map_bound_y1 + Map_bound_y2) / 2);
}


void ZoomWholeMap()
{
	if (MadeChanges)
		CalculateLevelBounds();

	zoom_fit();

	RedrawMap();
}


void RedrawMap()
{
	if (! main_win)
		return;

	UpdateHighlight();

	main_win->scroll->UpdateRenderMode();
	main_win->info_bar->UpdateSecRend();
	main_win->status_bar->redraw();
	main_win->canvas->redraw();
}


static void UpdatePanel()
{
	// -AJA- I think the highlighted object is always the same type as
	//       the current editing mode.  But do this check for safety.
	if (edit.highlight.valid() &&
		edit.highlight.type != edit.mode)
		return;


	// Choose object to show in right-hand panel:
	//   - the highlighted object takes priority
	//   - otherwise show the selection (first + count)
	//
	// It's a little more complicated since highlight may or may not
	// be part of the selection.

	int obj_idx   = edit.highlight.num;
	int obj_count = edit.Selected->count_obj();

	// the highlight is usually turned off when dragging, so compensate
	if (obj_idx < 0 && edit.action == ACT_DRAG)
		obj_idx = edit.dragged.num;

	if (obj_idx >= 0)
	{
		if (! edit.Selected->get(obj_idx))
			obj_count = 0;
	}
	else if (obj_count > 0)
	{
		// in linedef mode, we prefer showing a two-sided linedef
		if (edit.mode == OBJ_LINEDEFS && obj_count > 1)
			obj_idx = Selection_FirstLine(edit.Selected);
		else
			obj_idx = edit.Selected->find_first();
	}

	switch (edit.mode)
	{
		case OBJ_THINGS:
			main_win->thing_box->SetObj(obj_idx, obj_count);
			break;

		case OBJ_LINEDEFS:
			main_win->line_box->SetObj(obj_idx, obj_count);
			break;

		case OBJ_SECTORS:
			main_win->sec_box->SetObj(obj_idx, obj_count);
			break;

		case OBJ_VERTICES:
			main_win->vert_box->SetObj(obj_idx, obj_count);
			break;

		default: break;
	}
}


void UpdateDrawLine()
{
	if (edit.action != ACT_DRAW_LINE || edit.draw_from.is_nil())
		return;

	const Vertex *V = Vertices[edit.draw_from.num];

	double new_x = edit.map_x;
	double new_y = edit.map_y;

	if (grid.ratio > 0)
	{
		grid.RatioSnapXY(new_x, new_y, V->x(), V->y());
	}
	else if (edit.highlight.valid())
	{
		new_x = Vertices[edit.highlight.num]->x();
		new_y = Vertices[edit.highlight.num]->y();
	}
	else if (edit.split_line.valid())
	{
		new_x = edit.split_x;
		new_y = edit.split_y;
	}
	else
	{
		new_x = grid.SnapX(new_x);
		new_y = grid.SnapY(new_y);
	}

	edit.draw_to_x = new_x;
	edit.draw_to_y = new_y;

	// when drawing mode, highlight a vertex at the snap position
	if (grid.snap && edit.highlight.is_nil() && edit.split_line.is_nil())
	{
		int near_vert = Vertex_FindExact(TO_COORD(new_x), TO_COORD(new_y));
		if (near_vert >= 0)
		{
			edit.highlight = Objid(OBJ_VERTICES, near_vert);
		}
	}

	// never highlight the vertex we are drawing from
	if (edit.draw_from.valid() &&
		edit.draw_from == edit.highlight)
	{
		edit.highlight.clear();
	}
}


static void UpdateSplitLine(double map_x, double map_y)
{
	edit.split_line.clear();

	// splitting usually disabled while dragging stuff, EXCEPT a single vertex
	if (edit.action == ACT_DRAG && edit.dragged.is_nil())
		goto done;

	// in vertex mode, see if there is a linedef which would be split by
	// adding a new vertex.

	if (edit.mode == OBJ_VERTICES &&
		edit.pointer_in_window &&
	    edit.highlight.is_nil())
	{
		FindSplitLine(edit.split_line, edit.split_x, edit.split_y,
					  map_x, map_y, edit.dragged.num);

		// NOTE: OK if the split line has one of its vertices selected
		//       (that case is handled by Insert_Vertex)
	}

done:
	main_win->canvas->UpdateHighlight();
}


void UpdateHighlight()
{
	if (edit.render3d)
	{
		Render3D_UpdateHighlight();
		UpdatePanel();
		return;
	}

	// find the object to highlight
	edit.highlight.clear();

	// don't highlight when dragging, EXCEPT when dragging a single vertex
	if (edit.pointer_in_window &&
	    (edit.action != ACT_DRAG || (edit.mode == OBJ_VERTICES && edit.dragged.valid()) ))
	{
		GetNearObject(edit.highlight, edit.mode, edit.map_x, edit.map_y);

		// guarantee that we cannot drag a vertex onto itself
		if (edit.action == ACT_DRAG && edit.dragged.valid() &&
			edit.highlight.valid() && edit.dragged.num == edit.highlight.num)
		{
			edit.highlight.clear();
		}

		// if drawing a line and ratio lock is ON, only highlight a
		// vertex if it is *exactly* the right ratio.
		if (grid.ratio > 0 && edit.action == ACT_DRAW_LINE &&
			edit.mode == OBJ_VERTICES && edit.highlight.valid())
		{
			const Vertex *V = Vertices[edit.highlight.num];
			const Vertex *S = Vertices[edit.draw_from.num];

			double vx = V->x();
			double vy = V->y();

			grid.RatioSnapXY(vx, vy, S->x(), S->y());

			if (MakeValidCoord(vx) != V->raw_x ||
				MakeValidCoord(vy) != V->raw_y)
			{
				edit.highlight.clear();
			}
		}
	}

	UpdateSplitLine(edit.map_x, edit.map_y);
	UpdateDrawLine();

	main_win->canvas->UpdateHighlight();
	main_win->canvas->CheckGridSnap();

	UpdatePanel();
}


void Editor_ClearErrorMode()
{
	if (edit.error_mode)
	{
		Selection_Clear();
	}
}


void Editor_ChangeMode_Raw(obj_type_e new_mode)
{
	// keep selection after a "Find All" and user dismisses panel
	if (new_mode == edit.mode && main_win->isSpecialPanelShown())
		edit.error_mode = false;

	edit.mode = new_mode;

	Editor_ClearAction();
	Editor_ClearErrorMode();

	edit.highlight.clear();
	edit.split_line.clear();
}


void Editor_ChangeMode(char mode_char)
{
	obj_type_e  prev_type = edit.mode;

	// Set the object type according to the new mode.
	switch (mode_char)
	{
		case 't': Editor_ChangeMode_Raw(OBJ_THINGS);   break;
		case 'l': Editor_ChangeMode_Raw(OBJ_LINEDEFS); break;
		case 's': Editor_ChangeMode_Raw(OBJ_SECTORS);  break;
		case 'v': Editor_ChangeMode_Raw(OBJ_VERTICES); break;

		default:
			Beep("Unknown mode: %c\n", mode_char);
			return;
	}

	if (prev_type != edit.mode)
	{
		Selection_Push();

		main_win->NewEditMode(edit.mode);

		// convert the selection
		selection_c *prev_sel = edit.Selected;
		edit.Selected = new selection_c(edit.mode, true /* extended */);

		ConvertSelection(prev_sel, edit.Selected);
		delete prev_sel;
	}
	else if (main_win->isSpecialPanelShown())
	{
		// same mode, but this removes the special panel
		main_win->NewEditMode(edit.mode);
	}
	// -AJA- Yadex (DEU?) would clear the selection if the mode didn't
	//       change.  We optionally emulate that behavior here.
	else if (same_mode_clears_selection)
	{
		Selection_Clear();
	}

	RedrawMap();
}


//------------------------------------------------------------------------


void UpdateLevelBounds(int start_vert)
{
	for (int i = start_vert ; i < NumVertices ; i++)
	{
		const Vertex * V = Vertices[i];

		if (V->x() < Map_bound_x1) Map_bound_x1 = V->x();
		if (V->y() < Map_bound_y1) Map_bound_y1 = V->y();

		if (V->x() > Map_bound_x2) Map_bound_x2 = V->x();
		if (V->y() > Map_bound_y2) Map_bound_y2 = V->y();
	}
}

void CalculateLevelBounds()
{
	if (NumVertices == 0)
	{
		Map_bound_x1 = Map_bound_x2 = 0;
		Map_bound_y1 = Map_bound_y2 = 0;
		return;
	}

	Map_bound_x1 = 32767; Map_bound_x2 = -32767;
	Map_bound_y1 = 32767; Map_bound_y2 = -32767;

	UpdateLevelBounds(0);
}


void MapStuff_NotifyBegin()
{
	recalc_map_bounds  = false;
	new_vertex_minimum = -1;
	moved_vertex_count =  0;

	sound_propagation_invalid = true;
}

void MapStuff_NotifyInsert(obj_type_e type, int objnum)
{
	if (type == OBJ_VERTICES)
	{
		if (new_vertex_minimum < 0 || objnum < new_vertex_minimum)
			new_vertex_minimum = objnum;
	}
}

void MapStuff_NotifyDelete(obj_type_e type, int objnum)
{
	if (type == OBJ_VERTICES)
	{
		recalc_map_bounds = true;

		if (edit.action == ACT_DRAW_LINE &&
			edit.draw_from.num == objnum)
		{
			Editor_ClearAction();
		}
	}
}

void MapStuff_NotifyChange(obj_type_e type, int objnum, int field)
{
	if (type == OBJ_VERTICES)
	{
		// NOTE: for performance reasons we don't recalculate the
		//       map bounds when only moving a few vertices.
		moved_vertex_count++;

		const Vertex * V = Vertices[objnum];

		if (V->x() < Map_bound_x1) Map_bound_x1 = V->x();
		if (V->y() < Map_bound_y1) Map_bound_y1 = V->y();

		if (V->x() > Map_bound_x2) Map_bound_x2 = V->x();
		if (V->y() > Map_bound_y2) Map_bound_y2 = V->y();

		// TODO: only invalidate sectors touching vertex
		Subdiv_InvalidateAll();
	}

	if (type == OBJ_SIDEDEFS && field == SideDef::F_SECTOR)
		Subdiv_InvalidateAll();

	if (type == OBJ_LINEDEFS && (field == LineDef::F_LEFT || field == LineDef::F_RIGHT))
		Subdiv_InvalidateAll();

	if (type == OBJ_SECTORS && (field == Sector::F_FLOORH || field == Sector::F_CEILH))
		Subdiv_InvalidateAll();
}

void MapStuff_NotifyEnd()
{
	if (recalc_map_bounds || moved_vertex_count > 10)  // TODO: CONFIG
	{
		CalculateLevelBounds();
	}
	else if (new_vertex_minimum >= 0)
	{
		UpdateLevelBounds(new_vertex_minimum);
	}
}


//------------------------------------------------------------------------
//  ObjectBox Notification handling
//------------------------------------------------------------------------

static bool invalidated_totals;
static bool invalidated_panel_obj;
static bool changed_panel_obj;
static bool changed_recent_list;


void ObjectBox_NotifyBegin()
{
	invalidated_totals = false;
	invalidated_panel_obj = false;
	changed_panel_obj = false;
	changed_recent_list = false;
}


void ObjectBox_NotifyInsert(obj_type_e type, int objnum)
{
	invalidated_totals = true;

	if (type != edit.mode)
		return;

	if (objnum > main_win->GetPanelObjNum())
		return;

	invalidated_panel_obj = true;
}


void ObjectBox_NotifyDelete(obj_type_e type, int objnum)
{
	invalidated_totals = true;

	if (type != edit.mode)
		return;

	if (objnum > main_win->GetPanelObjNum())
		return;

	invalidated_panel_obj = true;
}


void ObjectBox_NotifyChange(obj_type_e type, int objnum, int field)
{
	if (type != edit.mode)
		return;

	if (objnum != main_win->GetPanelObjNum())
		return;

	changed_panel_obj = true;
}


void ObjectBox_NotifyEnd()
{
	if (invalidated_totals)
		main_win->UpdateTotals();

	if (invalidated_panel_obj)
	{
		main_win->InvalidatePanelObj();
	}
	else if (changed_panel_obj)
	{
		main_win->UpdatePanelObj();
	}

	if (changed_recent_list)
		main_win->browser->RecentUpdate();
}


//------------------------------------------------------------------------
//  Selection Notification, ETC
//------------------------------------------------------------------------

static bool invalidated_selection;
static bool invalidated_last_sel;


void Selection_NotifyBegin()
{
	invalidated_selection = false;
	invalidated_last_sel  = false;
}


void Selection_NotifyInsert(obj_type_e type, int objnum)
{
	if (type == edit.Selected->what_type() &&
		objnum <= edit.Selected->max_obj())
	{
		invalidated_selection = true;
	}

	if (last_Sel &&
		type == last_Sel->what_type() &&
		objnum <= last_Sel->max_obj())
	{
		invalidated_last_sel = true;
	}
}


void Selection_NotifyDelete(obj_type_e type, int objnum)
{
	if (objnum <= edit.Selected->max_obj())
	{
		invalidated_selection = true;
	}

	if (last_Sel &&
		type == last_Sel->what_type() &&
		objnum <= last_Sel->max_obj())
	{
		invalidated_last_sel = true;
	}
}


void Selection_NotifyChange(obj_type_e type, int objnum, int field)
{
	// field changes never affect the current selection
}


void Selection_NotifyEnd()
{
	if (invalidated_selection)
	{
		// this clears AND RESIZES the selection_c object
		edit.Selected->change_type(edit.mode);
	}

	if (invalidated_last_sel)
		Selection_InvalidateLast();
}


//
//  list the contents of a selection (for debugging)
//
void DumpSelection(selection_c * list)
{
	SYS_ASSERT(list);

	printf("Selection:");

	for (sel_iter_c it(list); ! it.done(); it.next())
		printf(" %d", *it);

	printf("\n");
}


void ConvertSelection(selection_c * src, selection_c * dest)
{
	if (src->what_type() == dest->what_type())
	{
		dest->merge(*src);
		return;
	}


	if (src->what_type() == OBJ_SECTORS && dest->what_type() == OBJ_THINGS)
	{
		for (int t = 0 ; t < NumThings ; t++)
		{
			const Thing *T = Things[t];

			Objid obj;
			GetNearObject(obj, OBJ_SECTORS, T->x(), T->y());

			if (! obj.is_nil() && src->get(obj.num))
			{
				dest->set(t);
			}
		}
		return;
	}


	if (src->what_type() == OBJ_SECTORS && dest->what_type() == OBJ_LINEDEFS)
	{
		for (int l = 0 ; l < NumLineDefs ; l++)
		{
			const LineDef *L = LineDefs[l];

			if ( (L->Right() && src->get(L->Right()->sector)) ||
				 (L->Left()  && src->get(L->Left()->sector)) )
			{
				dest->set(l);
			}
		}
		return;
	}


	if (src->what_type() == OBJ_SECTORS && dest->what_type() == OBJ_VERTICES)
	{
		for (int l = 0 ; l < NumLineDefs ; l++)
		{
			const LineDef *L = LineDefs[l];

			if ( (L->Right() && src->get(L->Right()->sector)) ||
				 (L->Left()  && src->get(L->Left()->sector)) )
			{
				dest->set(L->start);
				dest->set(L->end);
			}
		}
		return;
	}


	if (src->what_type() == OBJ_LINEDEFS && dest->what_type() == OBJ_SIDEDEFS)
	{
		for (sel_iter_c it(src); ! it.done(); it.next())
		{
			const LineDef *L = LineDefs[*it];

			if (L->Right()) dest->set(L->right);
			if (L->Left())  dest->set(L->left);
		}
		return;
	}

	if (src->what_type() == OBJ_SECTORS && dest->what_type() == OBJ_SIDEDEFS)
	{
		for (int n = 0 ; n < NumSideDefs ; n++)
		{
			const SideDef * SD = SideDefs[n];

			if (src->get(SD->sector))
				dest->set(n);
		}
		return;
	}


	if (src->what_type() == OBJ_LINEDEFS && dest->what_type() == OBJ_VERTICES)
	{
		for (sel_iter_c it(src); ! it.done(); it.next())
		{
			const LineDef *L = LineDefs[*it];

			dest->set(L->start);
			dest->set(L->end);
		}
		return;
	}


	if (src->what_type() == OBJ_VERTICES && dest->what_type() == OBJ_LINEDEFS)
	{
		// select all linedefs that have both ends selected
		for (int l = 0 ; l < NumLineDefs ; l++)
		{
			const LineDef *L = LineDefs[l];

			if (src->get(L->start) && src->get(L->end))
			{
				dest->set(l);
			}
		}
	}


	// remaining conversions are L->S and V->S

	if (dest->what_type() != OBJ_SECTORS)
		return;

	if (src->what_type() != OBJ_LINEDEFS && src->what_type() != OBJ_VERTICES)
		return;


	// step 1: select all sectors (except empty ones)
	int l;

	for (l = 0 ; l < NumLineDefs ; l++)
	{
		const LineDef *L = LineDefs[l];

		if (L->Right()) dest->set(L->Right()->sector);
		if (L->Left())  dest->set(L->Left()->sector);
	}

	// step 2: unselect any sectors if a component is not selected

	for (l = 0 ; l < NumLineDefs ; l++)
	{
		const LineDef *L = LineDefs[l];

		if (src->what_type() == OBJ_VERTICES)
		{
			if (src->get(L->start) && src->get(L->end))
				continue;
		}
		else
		{
			if (src->get(l))
				continue;
		}

		if (L->Right()) dest->clear(L->Right()->sector);
		if (L->Left())  dest->clear(L->Left()->sector);
	}
}


//
// Return the line to show in the LineDef panel from the selection.
// When the selection is a mix of one-sided and two-sided lines, then
// we want the first TWO-SIDED line.
//
// NOTE: this is slow, as it may need to search the whole list.
//
int Selection_FirstLine(selection_c *list)
{
	for (sel_iter_c it(list); ! it.done(); it.next())
	{
		const LineDef *L = LineDefs[*it];

		if (L->TwoSided())
			return *it;
	}

	// return first entry (a one-sided line)
	return list->find_first();
}


//
// This is a helper to handle performing an operation on the
// selection if it is non-empty, otherwise the highlight.
// Returns false if both selection and highlight are empty.
//
soh_type_e Selection_Or_Highlight()
{
	if (! edit.Selected->empty())
		return SOH_OK;

	if (edit.highlight.valid())
	{
		Selection_Add(edit.highlight);
		return SOH_Unselect;
	}

	return SOH_Empty;
}


//
// select all objects inside a given box
//
void SelectObjectsInBox(selection_c *list, int objtype, double x1, double y1, double x2, double y2)
{
	if (x2 < x1)
		std::swap(x1, x2);

	if (y2 < y1)
		std::swap(y1, y2);

	switch (objtype)
	{
		case OBJ_THINGS:
			for (int n = 0 ; n < NumThings ; n++)
			{
				const Thing *T = Things[n];

				double tx = T->x();
				double ty = T->y();

				if (x1 <= tx && tx <= x2 && y1 <= ty && ty <= y2)
				{
					list->toggle(n);
				}
			}
			break;

		case OBJ_VERTICES:
			for (int n = 0 ; n < NumVertices ; n++)
			{
				const Vertex *V = Vertices[n];

				double vx = V->x();
				double vy = V->y();

				if (x1 <= vx && vx <= x2 && y1 <= vy && vy <= y2)
				{
					list->toggle(n);
				}
			}
			break;

		case OBJ_LINEDEFS:
			for (int n = 0 ; n < NumLineDefs ; n++)
			{
				const LineDef *L = LineDefs[n];

				/* the two ends of the line must be in the box */
				if (x1 <= L->Start()->x() && L->Start()->x() <= x2 &&
				    y1 <= L->Start()->y() && L->Start()->y() <= y2 &&
				    x1 <= L->End()->x()   && L->End()->x() <= x2 &&
				    y1 <= L->End()->y()   && L->End()->y() <= y2)
				{
					list->toggle(n);
				}
			}
			break;

		case OBJ_SECTORS:
		{
			selection_c  in_sectors(OBJ_SECTORS);
			selection_c out_sectors(OBJ_SECTORS);

			for (int n = 0 ; n < NumLineDefs ; n++)
			{
				const LineDef *L = LineDefs[n];

				// Get the numbers of the sectors on both sides of the linedef
				int s1 = L->Right() ? L->Right()->sector : -1;
				int s2 = L->Left( ) ? L->Left() ->sector : -1;

				if (x1 <= L->Start()->x() && L->Start()->x() <= x2 &&
				    y1 <= L->Start()->y() && L->Start()->y() <= y2 &&
				    x1 <= L->End()->x()   && L->End()->x() <= x2 &&
				    y1 <= L->End()->y()   && L->End()->y() <= y2)
				{
					if (s1 >= 0) in_sectors.set(s1);
					if (s2 >= 0) in_sectors.set(s2);
				}
				else
				{
					if (s1 >= 0) out_sectors.set(s1);
					if (s2 >= 0) out_sectors.set(s2);
				}
			}

			for (int i = 0 ; i < NumSectors ; i++)
				if (in_sectors.get(i) && ! out_sectors.get(i))
					list->toggle(i);

			break;
		}
	}
}



void Selection_InvalidateLast()
{
	delete last_Sel;
	last_Sel = NULL;
}


void Selection_Push()
{
	if (edit.Selected->empty())
		return;

	if (last_Sel && last_Sel->test_equal(*edit.Selected))
		return;

	// OK copy it

	if (last_Sel)
		delete last_Sel;

	last_Sel = new selection_c(edit.Selected->what_type(), true);

	last_Sel->merge(*edit.Selected);
}


void Selection_Clear(bool no_save)
{
	if (! no_save)
		Selection_Push();

	// this always clears it
	edit.Selected->change_type(edit.mode);

	edit.error_mode = false;

	if (main_win)
		main_win->UnselectPics();

	RedrawMap();
}


void Selection_Add(Objid& obj)
{
	// validate the mode is correct
	if (obj.type != edit.mode)
		return;

	if (obj.parts == 0)
	{
		// ignore the add if object is already set.
		// [ since the selection may have parts, and we don't want to
		//   forget those parts ]
		if (! edit.Selected->get(obj.num))
			edit.Selected->set(obj.num);
		return;
	}

	byte cur = edit.Selected->get_ext(obj.num);

	cur = 1 | obj.parts;

	edit.Selected->set_ext(obj.num, cur);
}


void Selection_Remove(Objid& obj)
{
	if (obj.type != edit.mode)
		return;

	if (obj.parts == 0)
	{
		edit.Selected->clear(obj.num);
		return;
	}

	byte cur = edit.Selected->get_ext(obj.num);
	if (cur == 0)
		return;

	cur = 1 | (cur & ~obj.parts);

	// if we unset all the parts, then unset the object itself
	if (cur == 1)
		cur = 0;

	edit.Selected->set_ext(obj.num, cur);
}


void Selection_Toggle(Objid& obj)
{
	if (obj.type != edit.mode)
		return;

	if (obj.parts == 0)
	{
		edit.Selected->toggle(obj.num);
		return;
	}

	byte cur = edit.Selected->get_ext(obj.num);

	// if object was simply selected, then just clear it
	if (cur == 1)
	{
		edit.Selected->clear(obj.num);
		return;
	}

	cur = 1 | (cur ^ obj.parts);

	// if we toggled off all the parts, then unset the object itself
	if (cur == 1)
		cur = 0;

	edit.Selected->set_ext(obj.num, cur);
}


void Selection_Validate()
{
	int num_obj = NumObjects(edit.mode);

	if (edit.Selected->max_obj() >= num_obj)
	{
		edit.Selected->frob_range(num_obj, edit.Selected->max_obj(), BOP_REMOVE);

		Beep("BUG: invalid selection");
	}
}


void CMD_LastSelection()
{
	if (! last_Sel)
	{
		Beep("No last selection (or was invalidated)");
		return;
	}

	bool changed_mode = false;

	if (last_Sel->what_type() != edit.mode)
	{
		changed_mode = true;
		Editor_ChangeMode_Raw(last_Sel->what_type());
		main_win->NewEditMode(edit.mode);
	}

	std::swap(last_Sel, edit.Selected);

	// ensure everything is kosher
	Selection_Validate();

	if (changed_mode)
		GoToSelection();

	RedrawMap();
}


//------------------------------------------------------------------------
//  RECENTLY USED TEXTURES (etc)
//------------------------------------------------------------------------


// the containers for the textures (etc)
Recently_used  recent_textures;
Recently_used  recent_flats;
Recently_used  recent_things;


Recently_used::Recently_used() :
	size(0),
	keep_num(RECENTLY_USED_MAX - 2)
{
	memset(name_set, 0, sizeof(name_set));
}


Recently_used::~Recently_used()
{
	for (int i = 0 ; i < size ; i++)
	{
		StringFree(name_set[i]);
		name_set[i] = NULL;
	}
}


int Recently_used::find(const char *name)
{
	for (int k = 0 ; k < size ; k++)
		if (y_stricmp(name_set[k], name) == 0)
			return k;

	return -1;	// not found
}

int Recently_used::find_number(int val)
{
	char buffer[64];

	snprintf(buffer, sizeof(buffer), "%d", val);

	return find(buffer);
}


void Recently_used::insert(const char *name)
{
	// ignore '-' texture
	if (is_null_tex(name))
		return;

	// ignore empty strings to prevent potential problems
	if (strlen(name) == 0)
		return;

	int idx = find(name);

	// optimisation
	if (idx >= 0 && idx < 4)
		return;

	if (idx >= 0)
		erase(idx);

	push_front(name);

	// mark browser for later update
	// [ this method may be called very often by basis, too expensive to
	//   update the browser here ]
	changed_recent_list = true;
}

void Recently_used::insert_number(int val)
{
	char buffer[64];

	snprintf(buffer, sizeof(buffer), "%d", val);

	insert(buffer);
}


void Recently_used::erase(int index)
{
	SYS_ASSERT(0 <= index && index < size);

	StringFree(name_set[index]);

	size--;

	for ( ; index < size ; index++)
	{
		name_set[index] = name_set[index + 1];
	}

	name_set[index] = NULL;
}


void Recently_used::push_front(const char *name)
{
	if (size >= keep_num)
	{
		erase(keep_num - 1);
	}

	// shift elements up
	for (int k = size - 1 ; k >= 0 ; k--)
	{
		name_set[k + 1] = name_set[k];
	}

	name_set[0] = StringDup(name);

	size++;
}


void Recently_used::clear()
{
	size = 0;

	memset(name_set, 0, sizeof(name_set));
}


void RecUsed_ClearAll()
{
	recent_textures.clear();
	recent_flats   .clear();
	recent_things  .clear();

	if (main_win)
		main_win->browser->RecentUpdate();
}


/* --- Save and Restore --- */

void Recently_used::WriteUser(FILE *fp, char letter)
{
	for (int i = 0 ; i < size ; i++)
	{
		fprintf(fp, "recent_used %c \"%s\"\n", letter, StringTidy(name_set[i]));
	}
}


void RecUsed_WriteUser(FILE *fp)
{
	fprintf(fp, "\n");
	fprintf(fp, "recent_used clear\n");

	recent_textures.WriteUser(fp, 'T');
	recent_flats   .WriteUser(fp, 'F');
	recent_things  .WriteUser(fp, 'O');
}


bool RecUsed_ParseUser(const char ** tokens, int num_tok)
{
	if (strcmp(tokens[0], "recent_used") != 0 || num_tok < 2)
		return false;

	if (strcmp(tokens[1], "clear") == 0)
	{
		RecUsed_ClearAll();
		return true;
	}

	// syntax is:  recent_used  <kind>  <name>
	if (num_tok < 3)
		return false;

	switch (tokens[1][0])
	{
		case 'T':
			recent_textures.insert(tokens[2]);
			break;

		case 'F':
			recent_flats.insert(tokens[2]);
			break;

		case 'O':
			recent_things.insert(tokens[2]);
			break;

		default:
			// ignore it
			break;
	}

	if (main_win)
		main_win->browser->RecentUpdate();

	return true;
}


//------------------------------------------------------------------------


// this in e_commands.cc
void Editor_RegisterCommands();


void Editor_Init()
{
	switch (default_edit_mode)
	{
		case 1:  edit.mode = OBJ_LINEDEFS; break;
		case 2:  edit.mode = OBJ_SECTORS;  break;
		case 3:  edit.mode = OBJ_VERTICES; break;
		default: edit.mode = OBJ_THINGS;   break;
	}

	edit.render3d = false;

	Editor_DefaultState();

	Nav_Clear();

	edit.pointer_in_window = false;
	edit.map_x = 0;
	edit.map_y = 0;
	edit.map_z = -1;

	edit.Selected = new selection_c(edit.mode, true /* extended */);

	edit.highlight.clear();
	edit.split_line.clear();
	edit.clicked.clear();

	grid.Init();

	MadeChanges = 0;

	  Editor_RegisterCommands();
	Render3D_RegisterCommands();
}


void Editor_DefaultState()
{
	edit.action = ACT_NOTHING;
	edit.sticky_mod = 0;
	edit.is_panning = false;

	edit.dragged.clear();
	edit.draw_from.clear();

	edit.error_mode = false;
	edit.show_object_numbers = false;

	edit.sector_render_mode = sector_render_default;
	edit. thing_render_mode =  thing_render_default;
}


bool Editor_ParseUser(const char ** tokens, int num_tok)
{
	if (strcmp(tokens[0], "edit_mode") == 0 && num_tok >= 2)
	{
		Editor_ChangeMode(tokens[1][0]);
		return true;
	}

	if (strcmp(tokens[0], "render_mode") == 0 && num_tok >= 2)
	{
		edit.render3d = atoi(tokens[1]);
		RedrawMap();
		return true;
	}

	if (strcmp(tokens[0], "sector_render_mode") == 0 && num_tok >= 2)
	{
		edit.sector_render_mode = atoi(tokens[1]);
		RedrawMap();
		return true;
	}

	if (strcmp(tokens[0], "thing_render_mode") == 0 && num_tok >= 2)
	{
		edit.thing_render_mode = atoi(tokens[1]);
		RedrawMap();
		return true;
	}

	if (strcmp(tokens[0], "show_object_numbers") == 0 && num_tok >= 2)
	{
		edit.show_object_numbers = atoi(tokens[1]);
		RedrawMap();
		return true;
	}

	return false;
}


void Editor_WriteUser(FILE *fp)
{
	switch (edit.mode)
	{
		case OBJ_THINGS:   fprintf(fp, "edit_mode t\n"); break;
		case OBJ_LINEDEFS: fprintf(fp, "edit_mode l\n"); break;
		case OBJ_SECTORS:  fprintf(fp, "edit_mode s\n"); break;
		case OBJ_VERTICES: fprintf(fp, "edit_mode v\n"); break;

		default: break;
	}

	fprintf(fp, "render_mode %d\n", edit.render3d ? 1 : 0);
	fprintf(fp, "sector_render_mode %d\n", edit.sector_render_mode);
	fprintf(fp, "thing_render_mode %d\n",  edit.thing_render_mode);
	fprintf(fp, "show_object_numbers %d\n", edit.show_object_numbers ? 1 : 0);
}


//--- editor settings ---
// vi:ts=4:sw=4:noexpandtab
