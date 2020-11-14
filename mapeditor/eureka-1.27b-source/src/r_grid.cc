//------------------------------------------------------------------------
//  GRID STUFF
//------------------------------------------------------------------------
//
//  Eureka DOOM Editor
//
//  Copyright (C) 2001-2019 Andrew Apted
//  Copyright (C) 1997-2003 André Majorel et al
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
//  in the public domain in 1994 by Raphaël Quinet and Brendon Wyber.
//
//------------------------------------------------------------------------

#include "main.h"

#include "r_grid.h"
#include "e_main.h"
#include "ui_window.h"


Grid_State_c  grid;

// config items
int  grid_default_size = 64;
bool grid_default_snap = false;
int  grid_default_mode = 0;  // off

int  grid_style;  // 0 = squares, 1 = dotty
bool grid_hide_in_free_mode = false;
bool grid_snap_indicator = true;

int  grid_ratio_high = 3;  // custom ratio (high must be >= low)
int  grid_ratio_low  = 1;  // (low must be > 0)


Grid_State_c::Grid_State_c() :
	step(64 /* dummy */), snap(true),
	ratio(0), shown(true),
	orig_x(0.0), orig_y(0.0),
	Scale(1.0)
{ }

Grid_State_c::~Grid_State_c()
{ }


void Grid_State_c::Init()
{
	step = grid_default_size;

	if (step < 1)
		step = 1;

	if (step > grid_values[0])
		step = grid_values[0];

	shown = true;  // prevent a beep in AdjustStep

	AdjustStep(+1);

	if (grid_default_mode == 0)
	{
		shown = false;

		if (main_win)
			main_win->info_bar->SetGrid(-1);
	}
	else
	{
		shown = true;
	}

	snap = grid_default_snap;

	if (main_win)
		main_win->info_bar->UpdateSnap();
}


void Grid_State_c::MoveTo(double x, double y)
{
	// no change?
	if (fabs(x - orig_x) < 0.01 &&
	    fabs(y - orig_y) < 0.01)
		return;

	orig_x = x;
	orig_y = y;

	if (main_win)
	{
		main_win->scroll->AdjustPos();
		main_win->canvas->PointerPos();

		RedrawMap();
	}
}


void Grid_State_c::Scroll(double delta_x, double delta_y)
{
	MoveTo(orig_x + delta_x, orig_y + delta_y);
}


int Grid_State_c::ForceSnapX(double map_x) const
{
	return grid.step * round(map_x / (double)grid.step);
}

int Grid_State_c::ForceSnapY(double map_y) const
{
	return grid.step * round(map_y / (double)grid.step);
}


double Grid_State_c::SnapX(double map_x) const
{
	if (! snap || grid.step == 0)
		return map_x;

	return ForceSnapX(map_x);
}

double Grid_State_c::SnapY(double map_y) const
{
	if (! snap || grid.step == 0)
		return map_y;

	return ForceSnapY(map_y);
}


void Grid_State_c::RatioSnapXY(double& var_x, double& var_y,
							   double start_x, double start_y) const
{
	// snap first, otherwise we lose the ratio
	var_x = grid.SnapX(var_x);
	var_y = grid.SnapY(var_y);

	double dx = var_x - start_x;
	double dy = var_y - start_y;

	double len = MAX(abs(dx), abs(dy));

	int sign_x = (dx >= 0) ? +1 : -1;
	int sign_y = (dy >= 0) ? +1 : -1;

	double custom;

	switch (ratio)
	{
	case 0: // unlocked
		break;

	case 1: // 1:1 (45 degrees) + axis aligned
		if (fabs(dx) * 2 < fabs(dy))
		{
			var_x = start_x;
		}
		else if (fabs(dy) * 2 < fabs(dx))
		{
			var_y = start_y;
		}
		else
		{
			var_x = start_x + sign_x * len;
			var_y = start_y + sign_y * len;
		}
		break;

	case 2: // 2:1 + axis aligned
		if (fabs(dx) * 4 < fabs(dy))
		{
			var_x = start_x;
		}
		else if (fabs(dy) * 4 < fabs(dx))
		{
			var_y = start_y;
		}
		else if (fabs(dx) < fabs(dy))
		{
			var_x = start_x + sign_x * len * 0.5;
			var_y = start_y + sign_y * len;
		}
		else
		{
			var_x = start_x + sign_x * len;
			var_y = start_y + sign_y * len * 0.5;
		}
		break;

	case 3: // 4:1 + axis aligned
		if (fabs(dx) * 8 < fabs(dy))
		{
			var_x = start_x;
		}
		else if (fabs(dy) * 8 < fabs(dx))
		{
			var_y = start_y;
		}
		else if (fabs(dx) < fabs(dy))
		{
			var_x = start_x + sign_x * len * 0.25;
			var_y = start_y + sign_y * len;
		}
		else
		{
			var_x = start_x + sign_x * len;
			var_y = start_y + sign_y * len * 0.25;
		}
		break;

	case 4: // 8:1 + axis aligned
		if (fabs(dx) * 16 < fabs(dy))
		{
			var_x = start_x;
		}
		else if (fabs(dy) * 16 < fabs(dx))
		{
			var_y = start_y;
		}
		else if (fabs(dx) < fabs(dy))
		{
			var_x = start_x + sign_x * len * 0.125;
			var_y = start_y + sign_y * len;
		}
		else
		{
			var_x = start_x + sign_x * len;
			var_y = start_y + sign_y * len * 0.125;
		}
		break;

	case 5: // 5:4 + axis aligned
		if (fabs(dx) * 3 < fabs(dy))
		{
			var_x = start_x;
		}
		else if (fabs(dy) * 3 < fabs(dx))
		{
			var_y = start_y;
		}
		else if (fabs(dx) < fabs(dy))
		{
			var_x = start_x + sign_x * len * 0.8;
			var_y = start_y + sign_y * len;
		}
		else
		{
			var_x = start_x + sign_x * len;
			var_y = start_y + sign_y * len * 0.8;
		}
		break;

	case 6: // 7:4 + axis aligned
		if (fabs(dx) * 3 < fabs(dy))
		{
			var_x = start_x;
		}
		else if (fabs(dy) * 3 < fabs(dx))
		{
			var_y = start_y;
		}
		else if (fabs(dx) < fabs(dy))
		{
			var_x = start_x + sign_x * len * 4 / 7;
			var_y = start_y + sign_y * len;
		}
		else
		{
			var_x = start_x + sign_x * len;
			var_y = start_y + sign_y * len * 4 / 7;
		}
		break;

	default: // USER SETTING
		if (grid_ratio_low < 1)
			grid_ratio_low = 1;
		if (grid_ratio_high < grid_ratio_low)
			grid_ratio_high = grid_ratio_low;

		custom = (double)grid_ratio_low / (double)grid_ratio_high;

		if (custom > 0.1 && fabs(dx) < fabs(dy) * custom * 0.3)
		{
			var_x = start_x;
		}
		else if (custom > 0.1 && fabs(dy) < fabs(dx) * custom * 0.3)
		{
			var_y = start_y;
		}
		else if (fabs(dx) < fabs(dy))
		{
			var_x = start_x + sign_x * len * custom;
			var_y = start_y + sign_y * len;
		}
		else
		{
			var_x = start_x + sign_x * len;
			var_y = start_y + sign_y * len * custom;
		}
	}
}


int Grid_State_c::QuantSnapX(double map_x, bool want_furthest, int *dir) const
{
	if (OnGridX(map_x))
	{
		if (dir)
			*dir = 0;
		return map_x;
	}

	int new_x = ForceSnapX(map_x);

	if (dir)
	{
		if (new_x < map_x)
			*dir = -1;
		else
			*dir = +1;
	}

	if (! want_furthest)
		return new_x;

	if (new_x < map_x)
		return ForceSnapX(map_x + (step - 1));
	else
		return ForceSnapX(map_x - (step - 1));
}

int Grid_State_c::QuantSnapY(double map_y, bool want_furthest, int *dir) const
{
	// this is sufficient since the grid is always square

	return QuantSnapX(map_y, want_furthest, dir);
}


void Grid_State_c::NaturalSnapXY(double& var_x, double& var_y) const
{
	// this is only used by UI_Canvas::PointerPos()

	double nat_step = 1.0;

	while (nat_step * 2.0 <= Scale)
		nat_step = nat_step * 2.0;

	while (nat_step * 0.5 >= Scale)
		nat_step = nat_step * 0.5;

	var_x = round(var_x * nat_step) / nat_step;
	var_y = round(var_y * nat_step) / nat_step;
}


bool Grid_State_c::OnGridX(double map_x) const
{
	if (map_x < 0)
		map_x = -map_x;

	int map_x2 = (int)map_x;

	if (map_x != (double)map_x2)
		return false;

	return (map_x2 % step) == 0;
}

bool Grid_State_c::OnGridY(double map_y) const
{
	if (map_y < 0)
		map_y = -map_y;

	int map_y2 = (int)map_y;

	if (map_y != (double)map_y2)
		return false;

	return (map_y2 % step) == 0;
}

bool Grid_State_c::OnGrid(double map_x, double map_y) const
{
	return OnGridX(map_x) && OnGridY(map_y);
}


void Grid_State_c::RefocusZoom(double map_x, double map_y, float before_Scale)
{
	double dist_factor = (1.0 - before_Scale / Scale);

	orig_x += (map_x - orig_x) * dist_factor;
	orig_y += (map_y - orig_y) * dist_factor;

	if (main_win)
	{
		main_win->canvas->PointerPos();
		RedrawMap();
	}
}


const double Grid_State_c::scale_values[] =
{
	32.0, 16.0, 8.0, 6.0, 4.0,  3.0, 2.0, 1.5, 1.0,

	1.0 / 1.5, 1.0 / 2.0, 1.0 / 3.0,  1.0 / 4.0,
	1.0 / 6.0, 1.0 / 8.0, 1.0 / 16.0, 1.0 / 32.0,
	1.0 / 64.0
};


const int Grid_State_c::digit_scales[] =
{
	1, 3, 5, 7, 9, 11, 13, 14, 15  /* index into scale_values[] */
};

const int Grid_State_c::grid_values[] =
{
	1024, 512, 256, 192, 128, 64, 32, 16, 8, 4, 2,

	-1 /* OFF */,
};

#define NUM_SCALE_VALUES  18
#define NUM_GRID_VALUES   12


void Grid_State_c::RawSetScale(int i)
{
	SYS_ASSERT(0 <= i && i < NUM_SCALE_VALUES);

	Scale = scale_values[i];

	if (! main_win)
		return;

	main_win->scroll->AdjustPos();
	main_win->canvas->PointerPos();
	main_win->info_bar->SetScale(Scale);

	RedrawMap();
}


void Grid_State_c::RawSetStep(int i)
{
	SYS_ASSERT(0 <= i && i < NUM_GRID_VALUES);

	if (i == NUM_GRID_VALUES-1)  /* OFF */
	{
		shown = false;

		if (main_win)
			main_win->info_bar->SetGrid(-1);
	}
	else
	{
		shown = true;
		step  = grid_values[i];

		if (main_win)
			main_win->info_bar->SetGrid(step);
	}

	if (grid_hide_in_free_mode)
		SetSnap(shown);

	RedrawMap();
}


void Grid_State_c::ForceStep(int new_step)
{
	step  = new_step;
	shown = true;

	if (main_win)
		main_win->info_bar->SetGrid(step);

	if (grid_hide_in_free_mode)
		SetSnap(shown);

	RedrawMap();
}


void Grid_State_c::StepFromScale()
{
	int pixels_min = 16;

	int result = 0;

	for (int i = 0 ; i < NUM_GRID_VALUES-1 ; i++)
	{
		result = i;

		if (grid_values[i] * Scale / 2 < pixels_min)
			break;
	}

	if (step == grid_values[result])
		return; // no change

	step = grid_values[result];

	RedrawMap();
}


void Grid_State_c::AdjustStep(int delta)
{
	if (! shown)
	{
		Beep("Grid is off (cannot change step)");
		return;
	}

	int result = -1;

	if (delta > 0)
	{
		for (int i = NUM_GRID_VALUES-2 ; i >= 0 ; i--)
		{
			if (grid_values[i] > step)
			{
				result = i;
				break;
			}
		}
	}
	else // (delta < 0)
	{
		for (int i = 0 ; i < NUM_GRID_VALUES-1 ; i++)
		{
			if (grid_values[i] < step)
			{
				result = i;
				break;
			}
		}
	}

	// already at the extreme end?
	if (result < 0)
		return;

	RawSetStep(result);
}


void Grid_State_c::AdjustScale(int delta)
{
	int result = -1;

	if (delta > 0)
	{
		for (int i = NUM_SCALE_VALUES-1 ; i >= 0 ; i--)
		{
			if (scale_values[i] > Scale*1.01)
			{
				result = i;
				break;
			}
		}
	}
	else // (delta < 0)
	{
		for (int i = 0 ; i < NUM_SCALE_VALUES ; i++)
		{
			if (scale_values[i] < Scale*0.99)
			{
				result = i;
				break;
			}
		}
	}

	// already at the extreme end?
	if (result < 0)
		return;

	RawSetScale(result);
}


void Grid_State_c::RawSetShown(bool new_value)
{
	shown = new_value;

	if (! main_win)
		return;

	if (! shown)
	{
		main_win->info_bar->SetGrid(-1);
		RedrawMap();
		return;
	}

	// update the info-bar
	main_win->info_bar->SetGrid(step);

	RedrawMap();
}


void Grid_State_c::SetShown(bool enable)
{
	RawSetShown(enable);

	if (grid_hide_in_free_mode)
		SetSnap(enable);
}

void Grid_State_c::ToggleShown()
{
	SetShown(!shown);
}


void Grid_State_c::SetSnap(bool enable)
{
	if (snap == enable)
		return;

	snap = enable;

	if (grid_hide_in_free_mode && snap != shown)
		SetShown(snap);

	if (main_win)
		main_win->info_bar->UpdateSnap();

	RedrawMap();
}

void Grid_State_c::ToggleSnap()
{
	SetSnap(! snap);
}


void Grid_State_c::NearestScale(double want_scale)
{
	int best = 0;

	for (int i = 0 ; i < NUM_SCALE_VALUES ; i++)
	{
		best = i;

		if (scale_values[i] < want_scale * 1.1)
			break;
	}

	RawSetScale(best);
}


bool Grid_ParseUser(const char ** tokens, int num_tok)
{
	if (strcmp(tokens[0], "map_pos") == 0 && num_tok >= 4)
	{
		double x = atof(tokens[1]);
		double y = atof(tokens[2]);

		grid.MoveTo(x, y);

		double new_scale = atof(tokens[3]);

		grid.NearestScale(new_scale);

		RedrawMap();
		return true;
	}

	if (strcmp(tokens[0], "grid") == 0 && num_tok >= 4)
	{
		bool t_shown = atoi(tokens[1]) ? true : false;

		grid.step = atoi(tokens[3]);

		// tokens[2] was grid.mode, currently unused

		grid.RawSetShown(t_shown);

		RedrawMap();

		return true;
	}

	if (strcmp(tokens[0], "snap") == 0 && num_tok >= 2)
	{
		grid.snap = atoi(tokens[1]) ? true : false;

		if (main_win)
			main_win->info_bar->UpdateSnap();

		return true;
	}

	return false;
}


void Grid_WriteUser(FILE *fp)
{
	fprintf(fp, "map_pos %1.0f %1.0f %1.6f\n",
	        grid.orig_x,
			grid.orig_y,
			grid.Scale);

	fprintf(fp, "grid %d %d %d\n",
			grid.shown ? 1 : 0,
			grid_style ? 0 : 1,  /* was grid.mode, now unused */
			grid.step);

	fprintf(fp, "snap %d\n",
	        grid.snap ? 1 : 0);
}


//--- editor settings ---
// vi:ts=4:sw=4:noexpandtab
