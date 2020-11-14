//------------------------------------------------------------------------
//  LINEDEF PATHS
//------------------------------------------------------------------------
//
//  Eureka DOOM Editor
//
//  Copyright (C) 2001-2016 Andrew Apted
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
#include "e_main.h"
#include "e_objects.h"
#include "e_path.h"
#include "m_game.h"
#include "r_grid.h"
#include "r_render.h"
#include "w_rawdef.h"

#include "ui_window.h"
#include "ui_misc.h"


typedef enum
{
	SLP_Normal = 0,

	SLP_SameTex  = (1 << 1),  // require lines have same textures
	SLP_OneSided = (1 << 2),  // only handle one-sided lines
}
select_lines_in_path_flag_e;


static bool MatchingTextures(int index1, int index2)
{
	LineDef *L1 = LineDefs[index1];
	LineDef *L2 = LineDefs[index2];

	// lines with no sidedefs only match each other
	if (! L1->Right() || ! L2->Right())
		return L1->Right() == L2->Right();

	// determine texture to match from first line
	int texture = 0;

	if (! L1->TwoSided())
	{
		texture = L1->Right()->mid_tex;
	}
	else
	{
		int f_diff = L1->Left()->SecRef()->floorh - L1->Right()->SecRef()->floorh;
		int c_diff = L1->Left()->SecRef()->ceilh  - L1->Right()->SecRef()->ceilh;

		if (f_diff == 0 && c_diff != 0)
			texture = (c_diff > 0) ? L1->Left()->upper_tex : L1->Right()->upper_tex;
		else
			texture = (f_diff < 0) ? L1->Left()->lower_tex : L1->Right()->lower_tex;
	}

	// match texture with other line

	if (! L2->TwoSided())
	{
		return (L2->Right()->mid_tex == texture);
	}
	else
	{
		int f_diff = L2->Left()->SecRef()->floorh - L2->Right()->SecRef()->floorh;
		int c_diff = L2->Left()->SecRef()->ceilh  - L2->Right()->SecRef()->ceilh;

		if (c_diff != 0)
			if (texture == ((c_diff > 0) ? L2->Left()->upper_tex : L2->Right()->upper_tex))
				return true;

		if (f_diff != 0)
			if (texture == ((f_diff < 0) ? L2->Left()->lower_tex : L2->Right()->lower_tex))
				return true;

		return false;
	}
}


bool OtherLineDef(int L, int V, int *L_other, int *V_other,
                  int match, int start_L)
{
	*L_other = -1;
	*V_other = -1;

	for (int n = 0 ; n < NumLineDefs ; n++)
	{
		if (n == L)
			continue;

		if ((match & SLP_OneSided) && ! LineDefs[n]->OneSided())
			continue;

		for (int k = 0 ; k < 2 ; k++)
		{
			int v1 = LineDefs[n]->start;
			int v2 = LineDefs[n]->end;

			if (k == 1)
				std::swap(v1, v2);

			if (v1 != V)
				continue;

			if ((match & SLP_SameTex) && ! MatchingTextures(start_L, n))
				continue;

			if (*L_other >= 0)  // There is a fork in the path. Stop here.
				return false;

			*L_other = n;
			*V_other = v2;
		}
	}

	return (*L_other >= 0);
}


//
// This routine looks for all linedefs other than 'L' which use
// the vertex 'V'.  If there are none or more than one, the search
// stops there and nothing else happens.  If there is exactly one,
// then it is added to the selection and we continue from the new
// linedef and vertex.
//
static void SelectLinesInHalfPath(int L, int V, selection_c& seen, int match)
{
	int start_L = L;

	for (;;)
	{
		int L_other, V_other;

		// does not exist or is forky
		if (! OtherLineDef(L, V, &L_other, &V_other, match, start_L))
			break;

		// already seen?
		if (seen.get(L_other))
			break;

		seen.set(L_other);

		L = L_other;
		V = V_other;
	}
}


//
// select/unselect all linedefs in a non-forked path.
//
void CMD_LIN_SelectPath(void)
{
	// determine starting linedef
	if (edit.highlight.is_nil())
	{
		Beep("No highlighted line");
		return;
	}

	bool fresh_sel = Exec_HasFlag("/fresh");

	int match = 0;

	if (Exec_HasFlag("/onesided")) match |= SLP_OneSided;
	if (Exec_HasFlag("/sametex"))  match |= SLP_SameTex;

	int start_L = edit.highlight.num;

	if ((match & SLP_OneSided) && ! LineDefs[start_L]->OneSided())
		return;

	bool unset_them = false;

	if (!fresh_sel && edit.Selected->get(start_L))
		unset_them = true;

	selection_c seen(OBJ_LINEDEFS);

	seen.set(start_L);

	SelectLinesInHalfPath(start_L, LineDefs[start_L]->start, seen, match);
	SelectLinesInHalfPath(start_L, LineDefs[start_L]->end,   seen, match);

	Editor_ClearErrorMode();

	if (fresh_sel)
		Selection_Clear();

	if (unset_them)
		edit.Selected->unmerge(seen);
	else
		edit.Selected->merge(seen);

	 RedrawMap();
}


//------------------------------------------------------------------------

#define PLAYER_STEP_H	24

static bool GrowContiguousSectors(selection_c &seen)
{
	// returns TRUE when some new sectors got added

	bool changed = false;

	bool can_walk    = Exec_HasFlag("/can_walk");
	bool allow_doors = Exec_HasFlag("/doors");

	bool do_floor_h   = Exec_HasFlag("/floor_h");
	bool do_floor_tex = Exec_HasFlag("/floor_tex");
	bool do_ceil_h    = Exec_HasFlag("/ceil_h");
	bool do_ceil_tex  = Exec_HasFlag("/ceil_tex");

	bool do_light   = Exec_HasFlag("/light");
	bool do_tag     = Exec_HasFlag("/tag");
	bool do_special = Exec_HasFlag("/special");

	for (int n = 0 ; n < NumLineDefs ; n++)
	{
		LineDef *L = LineDefs[n];

		if (! L->TwoSided())
			continue;

		int sec1 = L->Right()->sector;
		int sec2 = L-> Left()->sector;

		if (sec1 == sec2)
			continue;

		Sector *S1 = Sectors[sec1];
		Sector *S2 = Sectors[sec2];

		// skip closed doors
		if (! allow_doors && (S1->floorh >= S1->ceilh || S2->floorh >= S2->ceilh))
			continue;

		if (can_walk)
		{
			if (L->flags & MLF_Blocking)
				continue;

			// too big a step?
			if (abs(S1->floorh - S2->floorh) > PLAYER_STEP_H)
				continue;

			// player wouldn't fit vertically?
			int f_max = MAX(S1->floorh, S2->floorh);
			int c_min = MIN(S1-> ceilh, S2-> ceilh);

			if (c_min - f_max < Misc_info.player_h)
			{
				// ... but allow doors
				if (! (allow_doors && (S1->floorh == S1->ceilh || S2->floorh == S2->ceilh)))
					continue;
			}
		}

		/* perform match */

		if (do_floor_h && (S1->floorh != S2->floorh)) continue;
		if (do_ceil_h  && (S1->ceilh  != S2->ceilh))  continue;

		if (do_floor_tex && (S1->floor_tex != S2->floor_tex)) continue;
		if (do_ceil_tex  && (S1->ceil_tex  != S2->ceil_tex))  continue;

		if (do_light   && (S1->light != S2->light)) continue;
		if (do_tag     && (S1->tag   != S2->tag  )) continue;
		if (do_special && (S1->type  != S2->type))  continue;

		// check if only one of the sectors is part of current set
		// (doing this _AFTER_ the matches since this can be a bit slow)
		bool got1 = seen.get(sec1);
		bool got2 = seen.get(sec2);

		if (got1 == got2)
			continue;

		seen.set(got1 ? sec2 : sec1);

		changed = true;
	}

	return changed;
}


//
// select/unselect a contiguous group of sectors.
//
void CMD_SEC_SelectGroup(void)
{
	// determine starting sector
	if (edit.highlight.is_nil())
	{
		Beep("No highlighted sector");
		return;
	}

	bool fresh_sel = Exec_HasFlag("/fresh");

	int start_sec = edit.highlight.num;

	bool unset_them = false;

	if (!fresh_sel && edit.Selected->get(start_sec))
		unset_them = true;

	selection_c seen(OBJ_SECTORS);

	seen.set(start_sec);

	while (GrowContiguousSectors(seen))
	{ }


	Editor_ClearErrorMode();

	if (fresh_sel)
		Selection_Clear();

	if (unset_them)
		edit.Selected->unmerge(seen);
	else
		edit.Selected->merge(seen);

	 RedrawMap();
}


//------------------------------------------------------------------------


void GoToSelection()
{
	if (edit.render3d)
		Render3D_Enable(false);

	double x1, y1, x2, y2;
	Objs_CalcBBox(edit.Selected, &x1, &y1, &x2, &y2);

	double mid_x = (x1 + x2) / 2;
	double mid_y = (y1 + y2) / 2;

	grid.MoveTo(mid_x, mid_y);

	// zoom out until selected objects fit on screen
	for (int loop = 0 ; loop < 30 ; loop++)
	{
		int eval = main_win->canvas->ApproxBoxSize(x1, y1, x2, y2);

		if (eval <= 0)
			break;

		grid.AdjustScale(-1);
	}

	// zoom in when bbox is very small (say < 20% of window)
	for (int loop = 0 ; loop < 30 ; loop++)
	{
		if (grid.Scale >= 1.0)
			break;

		int eval = main_win->canvas->ApproxBoxSize(x1, y1, x2, y2);

		if (eval >= 0)
			break;

		grid.AdjustScale(+1);
	}

	RedrawMap();
}


void GoToErrors()
{
	edit.error_mode = true;

	GoToSelection();
}


//
// centre the map around the object and zoom in if necessary
//
void GoToObject(const Objid& objid)
{
	Selection_Clear();

	edit.Selected->set(objid.num);

	GoToSelection();
}


void CMD_JumpToObject(void)
{
	int total = NumObjects(edit.mode);

	if (total <= 0)
	{
		Beep("No objects!");
		return;
	}

	UI_JumpToDialog *dialog = new UI_JumpToDialog(NameForObjectType(edit.mode), total - 1);

	int num = dialog->Run();

	delete dialog;

	if (num < 0)	// cancelled
		return;

	// this is guaranteed by the dialog
	SYS_ASSERT(num < total);

	GoToObject(Objid(edit.mode, num));
}


void CMD_NextObject()
{
	if (edit.Selected->count_obj() != 1)
	{
		Beep("Next: need a single object");
		return;
	}

	int num = edit.Selected->find_first();

	if (num >= NumObjects(edit.mode))
	{
		Beep("Next: no more objects");
		return;
	}

	num += 1;

	GoToObject(Objid(edit.mode, num));
}


void CMD_PrevObject()
{
	if (edit.Selected->count_obj() != 1)
	{
		Beep("Prev: need a single object");
		return;
	}

	int num = edit.Selected->find_first();

	if (num <= 0)
	{
		Beep("Prev: no more objects");
		return;
	}

	num -= 1;

	GoToObject(Objid(edit.mode, num));
}


void CMD_PruneUnused(void)
{
	selection_c used_secs (OBJ_SECTORS);
	selection_c used_sides(OBJ_SIDEDEFS);
	selection_c used_verts(OBJ_VERTICES);

	for (int i = 0 ; i < NumLineDefs ; i++)
	{
		const LineDef * L = LineDefs[i];

		used_verts.set(L->start);
		used_verts.set(L->end);

		if (L->left >= 0)
		{
			used_sides.set(L->left);
			used_secs.set(L->Left()->sector);
		}

		if (L->right >= 0)
		{
			used_sides.set(L->right);
			used_secs.set(L->Right()->sector);
		}
	}

	used_secs .frob_range(0, NumSectors -1, BOP_TOGGLE);
	used_sides.frob_range(0, NumSideDefs-1, BOP_TOGGLE);
	used_verts.frob_range(0, NumVertices-1, BOP_TOGGLE);

	int num_secs  = used_secs .count_obj();
	int num_sides = used_sides.count_obj();
	int num_verts = used_verts.count_obj();

	if (num_verts == 0 && num_sides == 0 && num_secs == 0)
	{
		Beep("Nothing to prune");
		return;
	}

	BA_Begin();
	BA_Message("pruned %d objects", num_secs + num_sides + num_verts);

	DeleteObjects(&used_sides);
	DeleteObjects(&used_secs);
	DeleteObjects(&used_verts);

	BA_End();
}


//------------------------------------------------------------------------

bool sound_propagation_invalid;

static std::vector<byte> sound_prop_vec;
static std::vector<byte> sound_temp1_vec;
static std::vector<byte> sound_temp2_vec;

static int sound_start_sec;


static void CalcPropagation(std::vector<byte>& vec, bool ignore_doors)
{
	bool changes;

	for (int k = 0 ; k < NumSectors ; k++)
		vec[k] = 0;

	vec[sound_start_sec] = 2;

	do
	{
		changes = false;

		for (int n = 0 ; n < NumLineDefs ; n++)
		{
			const LineDef *L = LineDefs[n];

			if (! L->TwoSided())
				continue;

			int sec1 = L->WhatSector(SIDE_RIGHT);
			int sec2 = L->WhatSector(SIDE_LEFT);

			SYS_ASSERT(sec1 >= 0);
			SYS_ASSERT(sec2 >= 0);

			// check for doors
			if (!ignore_doors &&
				(MIN(Sectors[sec1]->ceilh,  Sectors[sec2]->ceilh) <=
				 MAX(Sectors[sec1]->floorh, Sectors[sec2]->floorh)))
			{
				continue;
			}

			int val1 = vec[sec1];
			int val2 = vec[sec2];

			int new_val = MAX(val1, val2);

			if (L->flags & MLF_SoundBlock)
				new_val -= 1;

			if (new_val > val1 || new_val > val2)
			{
				if (new_val > val1) vec[sec1] = new_val;
				if (new_val > val2) vec[sec2] = new_val;

				changes = true;
			}
		}

	} while (changes);
}


static void CalcFinalPropagation()
{
	for (int s = 0 ; s < NumSectors ; s++)
	{
		int t1 = sound_temp1_vec[s];
		int t2 = sound_temp2_vec[s];

		if (t1 != t2)
		{
			if (t1 == 0 || t2 == 0)
			{
				sound_prop_vec[s] = PGL_Maybe;
				continue;
			}

			t1 = MIN(t1, t2);
		}

		switch (t1)
		{
			case 0: sound_prop_vec[s] = PGL_Never;   break;
			case 1: sound_prop_vec[s] = PGL_Level_1; break;
			case 2: sound_prop_vec[s] = PGL_Level_2; break;
		}
	}
}


const byte * SoundPropagation(int start_sec)
{
	if ((int)sound_prop_vec.size() != NumSectors)
	{
		sound_prop_vec .resize(NumSectors);
		sound_temp1_vec.resize(NumSectors);
		sound_temp2_vec.resize(NumSectors);

		sound_propagation_invalid = true;
	}

	if (sound_propagation_invalid ||
		sound_start_sec != start_sec)
	{
		// cannot used cached data, recompute it

		sound_start_sec = start_sec;
		sound_propagation_invalid = false;

		CalcPropagation(sound_temp1_vec, false);
		CalcPropagation(sound_temp2_vec, true);

		CalcFinalPropagation();
	}

	return &sound_prop_vec[0];
}

//--- editor settings ---
// vi:ts=4:sw=4:noexpandtab
