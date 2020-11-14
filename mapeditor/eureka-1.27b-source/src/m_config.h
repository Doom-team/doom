//------------------------------------------------------------------------
//  CONFIG FILE
//------------------------------------------------------------------------
//
//  Eureka DOOM Editor
//
//  Copyright (C) 2001-2018 Andrew Apted
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

#ifndef __EUREKA_M_CONFIG_H__
#define __EUREKA_M_CONFIG_H__

#include "im_color.h"

/* ==== CONFIG VARIABLES ==================== */

extern const char *default_port;
extern int default_edit_mode;

extern bool auto_load_recent;
extern bool begin_maximized;
extern bool map_scroll_bars;

extern bool leave_offsets_alone;
extern bool same_mode_clears_selection;

extern bool swap_sidedefs;
extern bool show_full_one_sided;
extern bool sidedef_add_del_buttons;

extern int gui_scheme;
extern int gui_color_set;
extern rgb_color_t gui_custom_bg;
extern rgb_color_t gui_custom_ig;
extern rgb_color_t gui_custom_fg;

extern int panel_gamma;

extern int  minimum_drag_pixels;
extern int  highlight_line_info;
extern int  new_sector_size;
extern int  sector_render_default;
extern int   thing_render_default;

extern int  grid_style;
extern int  grid_default_mode;
extern bool grid_default_snap;
extern int  grid_default_size;
extern bool grid_hide_in_free_mode;
extern bool grid_snap_indicator;
extern int  grid_ratio_high;
extern int  grid_ratio_low;

extern rgb_color_t dotty_axis_col;
extern rgb_color_t dotty_major_col;
extern rgb_color_t dotty_minor_col;
extern rgb_color_t dotty_point_col;

extern rgb_color_t normal_axis_col;
extern rgb_color_t normal_main_col;
extern rgb_color_t normal_flat_col;
extern rgb_color_t normal_small_col;

extern int backup_max_files;
extern int backup_max_space;

extern bool browser_small_tex;
extern bool browser_combine_tex;

extern int floor_bump_small;
extern int floor_bump_medium;
extern int floor_bump_large;

extern int light_bump_small;
extern int light_bump_medium;
extern int light_bump_large;

extern int  render_pixel_aspect;
extern int  render_far_clip;
extern bool render_high_detail;
extern bool render_lock_gravity;
extern bool render_missing_bright;
extern bool render_unknown_bright;

extern rgb_color_t transparent_col;

extern bool bsp_on_save;
extern bool bsp_fast;
extern bool bsp_warnings;
extern int  bsp_split_factor;

extern bool bsp_gl_nodes;
extern bool bsp_force_v5;
extern bool bsp_force_zdoom;
extern bool bsp_compressed;


/* ==== FUNCTIONS ==================== */

int M_ParseConfigFile();
int M_WriteConfigFile();

int M_ParseDefaultConfigFile();

void M_ParseEnvironmentVars();
void M_ParseCommandLine(int argc, const char *const *argv, int pass);

void M_PrintCommandLineOptions(FILE *fp);


// returns true if ok, false on EOF or error
bool M_ReadTextLine(char *buf, size_t size, FILE *fp);


// returns number of tokens, zero for comment, negative on error
int M_ParseLine(const char *line, const char ** tokens, int max_tok, int do_strings);
void M_FreeLine(const char ** tokens, int num_tok);

// user state persistence (stuff like camera pos, grid settings, ...)
bool M_LoadUserState();
bool M_SaveUserState();

void M_DefaultUserState();

#endif  /* __EUREKA_M_CONFIG_H__ */

//--- editor settings ---
// vi:ts=4:sw=4:noexpandtab
