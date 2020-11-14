//------------------------------------------------------------------------
//  TEXTURES / FLATS / SPRITES
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

#ifndef __EUREKA_W_TEXTURE_H__
#define __EUREKA_W_TEXTURE_H__

#include "im_img.h"

void W_LoadTextures();

// accepts "-", "#xxxx" or an existing texture name
bool W_TextureIsKnown(const char *name);

Img_c * W_GetTexture(const char *name, bool try_uppercase = false);

int  W_GetTextureHeight(const char *name);
bool W_TextureCausesMedusa(const char *name);

// this truncates the name to 8 chars, and makes it uppercase.
// [ result is a static buffer, copy if necessary! ]
const char *NormalizeTex(const char *name);


/* ---- FLATS ---- */

void W_LoadFlats();

// checks if the flat exists
bool W_FlatIsKnown(const char *name);

Img_c * W_GetFlat(const char *name, bool try_uppercase = false);


/* ---- SPRITES ---- */

void W_ClearSprites();

Img_c * W_GetSprite(int type);


/* ---- ALL ---- */

void W_UnloadAllTextures();


#endif  /* __EUREKA_W_TEXTURE_H__ */

//--- editor settings ---
// vi:ts=4:sw=4:noexpandtab
