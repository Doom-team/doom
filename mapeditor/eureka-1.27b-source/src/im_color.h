//------------------------------------------------------------------------
//  COLORS
//------------------------------------------------------------------------
//
//  Eureka DOOM Editor
//
//  Copyright (C) 2001-2016 Andrew Apted
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

#ifndef __EUREKA_IM_COLOR_H__
#define __EUREKA_IM_COLOR_H__


typedef u32_t rgb_color_t;

#define RGB_RED(col)    ((col >> 24) & 255)
#define RGB_GREEN(col)  ((col >> 16) & 255)
#define RGB_BLUE(col)   ((col >>  8) & 255)

#define RGB_MAKE(r, g, b)  (((r) << 24) | ((g) << 16) | ((b) << 8))


// this is a version of rgb_color_t with an alpha channel
// [ currently only used by the TGA loading code ]
typedef u32_t rgba_color_t;
#define RGBA_ALPHA(col)   ((col) & 255)
#define RGBA_MAKE(r, g, b, a)  (((r) << 24) | ((g) << 16) | ((b) << 8) | (a))


extern int usegamma;

// the palette color closest to what TRANS_PIXEL really is
extern int trans_replace;


// this palette has the gamma setting applied
extern rgb_color_t palette[256];
extern rgb_color_t palette_medium[256];

extern byte raw_palette[256][3];

extern byte raw_colormap[32][256];

extern byte rgb555_gamma [32];
extern byte rgb555_medium[32];

extern int gammatable[5][256];


void W_UpdateGamma();

void W_LoadPalette();
void W_LoadColormap();

byte W_FindPaletteColor(int r, int g, int b);

void W_CreateBrightMap();

// make the color darker
rgb_color_t DarkerColor(rgb_color_t col);

rgb_color_t ParseColor(const char *str);

rgb_color_t SectorLightColor(int light);

int HashedPalColor(const char *name, const int *cols);


inline int R_DoomLightingEquation(int L, float dist)
{
	/* L in the range 0 to 256 */
	L >>= 2;

	int min_L = CLAMP(0, 36 - L, 31);

	int index = (59 - L) - int(1280 / MAX(1, dist));

	/* result is colormap index (0 bright .. 31 dark) */
	return CLAMP(min_L, index, 31);
}


//------------------------------------------------------------//


#define BLACK           FL_BLACK
#define BLUE            FL_BLUE
#define GREEN           FL_GREEN
#define CYAN            FL_CYAN
#define RED             FL_RED
#define MAGENTA         FL_MAGENTA
#define BROWN           FL_DARK_RED
#define YELLOW          fl_rgb_color(255,255,0)
#define WHITE           FL_WHITE

#define LIGHTGREY       fl_rgb_color(144,144,144)
#define DARKGREY        fl_rgb_color(80,80,80)

#define LIGHTBLUE       fl_rgb_color(128,128,255)
#define LIGHTGREEN      fl_rgb_color(128,255,128)
#define LIGHTCYAN       fl_rgb_color(128,255,255)
#define LIGHTRED        fl_rgb_color(255,128,128)
#define LIGHTMAGENTA    fl_rgb_color(255,128,255)

#define OBJECT_NUM_COL  fl_rgb_color(0x44, 0xdd, 0xff)
#define CLR_ERROR       fl_rgb_color(0xff, 0,    0)

#define SECTOR_TAG      fl_rgb_color(0x00, 0xff, 0x00)
#define SECTOR_TAGTYPE  fl_rgb_color(0x00, 0xe0, 0xe0)
#define SECTOR_TYPE     fl_rgb_color(0x00, 0x80, 0xff)

#define SEL_COL         fl_rgb_color(128,192,255)
#define SEL3D_COL       fl_rgb_color(128,255,128)
#define HI_COL          fl_rgb_color(255,255,0)
#define HI_AND_SEL_COL  fl_rgb_color(255,128,0)

#define THING_MODE_COL  fl_rgb_color(255,64,255)
#define LINE_MODE_COL   fl_rgb_color(0,160,255)
#define SECTOR_MODE_COL fl_rgb_color(255,255,0)
#define VERTEX_MODE_COL fl_rgb_color(0,255,128)


#endif  /* __EUREKA_IM_COLOR_H__ */

//--- editor settings ---
// vi:ts=4:sw=4:noexpandtab
