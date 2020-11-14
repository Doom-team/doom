//------------------------------------------------------------------------
//  TEXTURES / FLATS / SPRITES
//------------------------------------------------------------------------
//
//  Eureka DOOM Editor
//
//  Copyright (C) 2001-2020 Andrew Apted
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

#include <map>
#include <algorithm>
#include <string>

#include "m_game.h"      /* yg_picture_format */
#include "w_loadpic.h"
#include "w_rawdef.h"
#include "w_texture.h"


//----------------------------------------------------------------------
//    TEXTURE HANDLING
//----------------------------------------------------------------------


std::map<std::string, Img_c *> textures;
std::map<std::string, Img_c *> flats;

// textures which can cause the Medusa Effect in vanilla/chocolate DOOM
static std::map<std::string, int> medusa_textures;


static void DeleteTex(const std::map<std::string, Img_c *>::value_type& P)
{
	delete P.second;
}

static void W_ClearTextures()
{
	std::for_each(textures.begin(), textures.end(), DeleteTex);

	textures.clear();

	medusa_textures.clear();
}


static void W_AddTexture(const char *name, Img_c *img, bool is_medusa)
{
	// free any existing one with the same name

	std::string tex_str = name;

	std::map<std::string, Img_c *>::iterator P = textures.find(tex_str);

	if (P != textures.end())
	{
		delete P->second;

		P->second = img;
	}
	else
	{
		textures[tex_str] = img;
	}

	medusa_textures[tex_str] = is_medusa ? 1 : 0;
}


static bool CheckTexturesAreStrife(byte *tex_data, int tex_length, int num_tex,
								   bool skip_first)
{
	// we follow the ZDoom logic here: check ALL the texture entries
	// assuming DOOM format, and if any have a patch_count of zero or
	// the last two bytes of columndir are non-zero then assume Strife.

	const s32_t *tex_data_s32 = (const s32_t *)tex_data;

	for (int n = skip_first ? 1 : 0 ; n < num_tex ; n++)
	{
		int offset = LE_S32(tex_data_s32[1 + n]);

		// ignore invalid offsets here  [ caught later ]
		if (offset < 4 * num_tex || offset >= tex_length)
			continue;

		const raw_texture_t *raw = (const raw_texture_t *)(tex_data + offset);

		if (LE_S16(raw->patch_count) <= 0)
			return true;

		if (raw->column_dir[1] != 0)
			return true;
	}

	return false;
}


static void LoadTextureEntry_Strife(byte *tex_data, int tex_length, int offset,
									byte *pnames, int pname_size, bool skip_first)
{
	const raw_strife_texture_t *raw = (const raw_strife_texture_t *)(tex_data + offset);

	// create the new image
	int width  = LE_U16(raw->width);
	int height = LE_U16(raw->height);

	DebugPrintf("Texture [%.8s] : %dx%d\n", raw->name, width, height);

	if (width == 0 || height == 0)
		FatalError("W_LoadTextures: Texture '%.8s' has zero size\n", raw->name);

	Img_c *img = new Img_c(width, height, false);
	bool is_medusa = false;

	// apply all the patches
	int num_patches = LE_S16(raw->patch_count);

	if (! num_patches)
		FatalError("W_LoadTextures: Texture '%.8s' has no patches\n", raw->name);

	const raw_strife_patchdef_t *patdef = (const raw_strife_patchdef_t *) & raw->patches[0];

	if (num_patches >= 2)
		is_medusa = true;

	for (int j = 0 ; j < num_patches ; j++, patdef++)
	{
		int xofs = LE_S16(patdef->x_origin);
		int yofs = LE_S16(patdef->y_origin);
		int pname_idx = LE_U16(patdef->pname);

		if (yofs < 0)
			yofs = 0;

		if (pname_idx >= pname_size)
		{
			LogPrintf("Invalid pname in texture '%.8s'\n", raw->name);
			continue;
		}

		char picname[16];
		memcpy(picname, pnames + 8*pname_idx, 8);
		picname[8] = 0;

		Lump_c *lump = W_FindPatchLump(picname);

		if (! lump ||
			! LoadPicture(*img, lump, picname, xofs, yofs))
		{
			LogPrintf("texture '%.8s': patch '%.8s' not found.\n", raw->name, picname);
		}
	}

	// store the new texture
	char namebuf[16];
	memcpy(namebuf, raw->name, 8);
	namebuf[8] = 0;

	W_AddTexture(namebuf, img, is_medusa);
}


static void LoadTextureEntry_DOOM(byte *tex_data, int tex_length, int offset,
								  byte *pnames, int pname_size, bool skip_first)
{
	const raw_texture_t *raw = (const raw_texture_t *)(tex_data + offset);

	// create the new image
	int width  = LE_U16(raw->width);
	int height = LE_U16(raw->height);

	DebugPrintf("Texture [%.8s] : %dx%d\n", raw->name, width, height);

	if (width == 0 || height == 0)
		FatalError("W_LoadTextures: Texture '%.8s' has zero size\n", raw->name);

	Img_c *img = new Img_c(width, height, false);
	bool is_medusa = false;

	// apply all the patches
	int num_patches = LE_S16(raw->patch_count);

	if (! num_patches)
		FatalError("W_LoadTextures: Texture '%.8s' has no patches\n", raw->name);

	const raw_patchdef_t *patdef = (const raw_patchdef_t *) & raw->patches[0];

	// andrewj: this is not strictly correct, the Medusa Effect is only
	//          triggered when multiple patches occupy a single column of
	//          the texture.  But checking for that is a major pain since
	//          we don't know the width of each patch here....
	if (num_patches >= 2)
		is_medusa = true;

	for (int j = 0 ; j < num_patches ; j++, patdef++)
	{
		int xofs = LE_S16(patdef->x_origin);
		int yofs = LE_S16(patdef->y_origin);
		int pname_idx = LE_U16(patdef->pname);

		// AYM 1998-08-08: Yes, that's weird but that's what Doom
		// does. Without these two lines, the few textures that have
		// patches with negative y-offsets (BIGDOOR7, SKY1, TEKWALL1,
		// TEKWALL5 and a few others) would not look in the texture
		// viewer quite like in Doom. This should be mentioned in
		// the UDS, by the way.
		if (yofs < 0)
			yofs = 0;

		if (pname_idx >= pname_size)
		{
			LogPrintf("Invalid pname in texture '%.8s'\n", raw->name);
			continue;
		}

		char picname[16];
		memcpy(picname, pnames + 8*pname_idx, 8);
		picname[8] = 0;

//DebugPrintf("-- %d patch [%s]\n", j, picname);
		Lump_c *lump = W_FindPatchLump(picname);

		if (! lump ||
			! LoadPicture(*img, lump, picname, xofs, yofs))
		{
			LogPrintf("texture '%.8s': patch '%.8s' not found.\n", raw->name, picname);
		}
	}

	// store the new texture
	char namebuf[16];
	memcpy(namebuf, raw->name, 8);
	namebuf[8] = 0;

	W_AddTexture(namebuf, img, is_medusa);
}


static void LoadTexturesLump(Lump_c *lump, byte *pnames, int pname_size,
                             bool skip_first)
{
	// TODO : verify size word at front of PNAMES ??

	// skip size word at front of PNAMES
	pnames += 4;

	pname_size /= 8;

	// load TEXTUREx data into memory for easier processing
	byte *tex_data;

	int tex_length = W_LoadLumpData(lump, &tex_data);

	// at the front of the TEXTUREx lump are some 4-byte integers
	s32_t *tex_data_s32 = (s32_t *)tex_data;

	int num_tex = LE_S32(tex_data_s32[0]);

	// it seems having a count of zero is valid
	if (num_tex == 0)
	{
		W_FreeLumpData(&tex_data);
		return;
	}

	if (num_tex < 0 || num_tex > (1<<20))
		FatalError("W_LoadTextures: TEXTURE1/2 lump is corrupt, bad count.\n");

	bool is_strife = CheckTexturesAreStrife(tex_data, tex_length, num_tex, skip_first);

	// Note: we skip the first entry (e.g. AASHITTY) which is not really
    //       usable (in the DOOM engine the #0 texture means "do not draw").

	for (int n = skip_first ? 1 : 0 ; n < num_tex ; n++)
	{
		int offset = LE_S32(tex_data_s32[1 + n]);

		if (offset < 4 * num_tex || offset >= tex_length)
			FatalError("W_LoadTextures: TEXTURE1/2 lump is corrupt, bad offset.\n");

		if (is_strife)
			LoadTextureEntry_Strife(tex_data, tex_length, offset, pnames, pname_size, skip_first);
		else
			LoadTextureEntry_DOOM(tex_data, tex_length, offset, pnames, pname_size, skip_first);
	}

	W_FreeLumpData(&tex_data);
}


void W_LoadTextures_TX_START(Wad_file *wf)
{
	for (int k = 0 ; k < (int)wf->tx_tex.size() ; k++)
	{
		Lump_c *lump = wf->GetLump(wf->tx_tex[k]);

		char img_fmt = W_DetectImageFormat(lump);
		const char *name = lump->Name();
		Img_c *img = NULL;

		DebugPrintf("TX_TEX %d : '%s' type=%c\n", k, name, img_fmt ? img_fmt : '?');

		switch (img_fmt)
		{
			case 'd': /* Doom patch */
				img = new Img_c();
				if (! LoadPicture(*img, lump, name, 0, 0))
				{
					delete img;
					img = NULL;
				}
				break;

			case 'p': /* PNG */
				img = LoadImage_PNG(lump, name);
				break;

			case 't': /* TGA */
				img = LoadImage_TGA(lump, name);
				break;

			case 'j': /* JPEG */
				img = LoadImage_JPEG(lump, name);
				break;

			case 0:
				LogPrintf("Unknown texture format in '%s' lump\n", name);
				break;

			default:
				LogPrintf("Unsupported texture format in '%s' lump\n", lump->Name());
				break;
		}

		// if we successfully loaded the texture, add it
		if (img)
		{
			W_AddTexture(name, img, false /* is_medusa */);
		}
	}
}


void W_LoadTextures()
{
	W_ClearTextures();

	for (int i = 0 ; i < (int)master_dir.size() ; i++)
	{
		LogPrintf("Loading Textures from WAD #%d\n", i+1);

		Lump_c *pnames   = master_dir[i]->FindLump("PNAMES");
		Lump_c *texture1 = master_dir[i]->FindLump("TEXTURE1");
		Lump_c *texture2 = master_dir[i]->FindLump("TEXTURE2");

		// Note that we _require_ the PNAMES lump to exist along
		// with the TEXTURE1/2 lump which uses it.  Probably a
		// few wads exist which lack the PNAMES lump (relying on
		// the one in the IWAD), however this practice is too
		// error-prone (using the wrong IWAD will break it),
		// so I think supporting it is a bad idea.  -- AJA

		if (pnames)
		{
			byte *pname_data;
			int pname_size = W_LoadLumpData(pnames, &pname_data);

			if (texture1)
				LoadTexturesLump(texture1, pname_data, pname_size, true);

			if (texture2)
				LoadTexturesLump(texture2, pname_data, pname_size, false);

			W_FreeLumpData(&pname_data);
		}

		if (Features.tx_start)
		{
			W_LoadTextures_TX_START(master_dir[i]);
		}
	}
}


Img_c * W_GetTexture(const char *name, bool try_uppercase)
{
	if (is_null_tex(name))
		return NULL;

	if (strlen(name) == 0)
		return NULL;

	std::string t_str = name;
	std::map<std::string, Img_c *>::iterator P = textures.find(t_str);

	if (P != textures.end())
		return P->second;

	if (try_uppercase)
	{
		return W_GetTexture(NormalizeTex(name), false);
	}

	if (Features.mix_textures_flats)
	{
		std::map<std::string, Img_c *>::iterator P = flats.find(t_str);

		if (P != flats.end())
			return P->second;
	}

	return NULL;
}


int W_GetTextureHeight(const char *name)
{
	Img_c *img = W_GetTexture(name);

	if (! img)
		return 128;

	return img->height();
}


bool W_TextureIsKnown(const char *name)
{
	if (is_null_tex(name) || is_special_tex(name))
		return true;

	if (strlen(name) == 0)
		return false;

	std::string t_str = name;
	std::map<std::string, Img_c *>::iterator P = textures.find(t_str);

	if (P != textures.end())
		return true;

	if (Features.mix_textures_flats)
	{
		std::map<std::string, Img_c *>::iterator P = flats.find(t_str);

		if (P != flats.end())
			return true;
	}

	return false;
}


bool W_TextureCausesMedusa(const char *name)
{
	std::string t_str = name;

	std::map<std::string, int>::iterator P = medusa_textures.find(t_str);

	return (P != medusa_textures.end() && P->second > 0);
}


const char *NormalizeTex(const char *name)
{
	if (name[0] == 0)
		return "-";

	static char buffer[WAD_TEX_NAME+1];

	memset(buffer, 0, sizeof(buffer));

	for (size_t i = 0 ; i < WAD_TEX_NAME && name[i]; i++)
	{
		buffer[i] = name[i];

		// remove double quotes
		if (buffer[i] == '"')
			buffer[i] = '_';
		else
			buffer[i] = toupper(buffer[i]);
	}

	return buffer;
}


//----------------------------------------------------------------------
//    FLAT HANDLING
//----------------------------------------------------------------------

static void DeleteFlat(const std::map<std::string, Img_c *>::value_type& P)
{
	delete P.second;
}


static void W_ClearFlats()
{
	std::for_each(flats.begin(), flats.end(), DeleteFlat);

	flats.clear();
}


static void W_AddFlat(const char *name, Img_c *img)
{
	// find any existing one with same name, and free it

	std::string flat_str = name;

	std::map<std::string, Img_c *>::iterator P = flats.find(flat_str);

	if (P != flats.end())
	{
		delete P->second;

		P->second = img;
	}
	else
	{
		flats[flat_str] = img;
	}
}


static Img_c * LoadFlatImage(const char *name, Lump_c *lump)
{
	// TODO: check size == 64*64

	Img_c *img = new Img_c(64, 64, false);

	int size = 64 * 64;

	byte *raw = new byte[size];

	if (! (lump->Seek() && lump->Read(raw, size)))
		FatalError("Error reading flat from WAD.\n");

	for (int i = 0 ; i < size ; i++)
	{
		img_pixel_t pix = raw[i];

		if (pix == TRANS_PIXEL)
			pix = trans_replace;

		img->wbuf() [i] = pix;
	}

	delete[] raw;

	return img;
}


void W_LoadFlats()
{
	W_ClearFlats();

	for (int i = 0 ; i < (int)master_dir.size() ; i++)
	{
		LogPrintf("Loading Flats from WAD #%d\n", i+1);

		Wad_file *wf = master_dir[i];

		for (int k = 0 ; k < (int)wf->flats.size() ; k++)
		{
			Lump_c *lump = wf->GetLump(wf->flats[k]);

			DebugPrintf("  Flat %d : '%s'\n", k, lump->Name());

			Img_c * img = LoadFlatImage(lump->Name(), lump);

			if (img)
				W_AddFlat(lump->Name(), img);
		}
	}
}


Img_c * W_GetFlat(const char *name, bool try_uppercase)
{
	std::string f_str = name;
	std::map<std::string, Img_c *>::iterator P = flats.find(f_str);

	if (P != flats.end())
		return P->second;

	if (Features.mix_textures_flats)
	{
		std::map<std::string, Img_c *>::iterator P = textures.find(f_str);

		if (P != textures.end())
			return P->second;
	}

	if (try_uppercase)
	{
		return W_GetFlat(NormalizeTex(name), false);
	}

	return NULL;
}


bool W_FlatIsKnown(const char *name)
{
	// sectors do not support "-" (but our code can make it)
	if (is_null_tex(name))
		return false;

	if (strlen(name) == 0)
		return false;

	std::string f_str = name;
	std::map<std::string, Img_c *>::iterator P = flats.find(f_str);

	if (P != flats.end())
		return true;

	if (Features.mix_textures_flats)
	{
		std::map<std::string, Img_c *>::iterator P = textures.find(f_str);

		if (P != textures.end())
			return true;
	}

	return false;
}


//----------------------------------------------------------------------
//    SPRITE HANDLING
//----------------------------------------------------------------------


// maps type number to an image
typedef std::map<int, Img_c *> sprite_map_t;

static sprite_map_t sprites;


static void DeleteSprite(const sprite_map_t::value_type& P)
{
	// Note that P.second can be NULL here
	delete P.second;
}

void W_ClearSprites()
{
	std::for_each(sprites.begin(), sprites.end(), DeleteSprite);

	sprites.clear();
}


// find sprite by prefix
Lump_c * Sprite_loc_by_root (const char *name)
{
	// first look for one in the sprite namespace (S_START..S_END),
	// only if that fails do we check the whole wad.

	char buffer[16];

	strcpy(buffer, name);

	if (strlen(buffer) == 4)
		strcat(buffer, "A");

	if (strlen(buffer) == 5)
		strcat(buffer, "0");

	Lump_c *lump = W_FindSpriteLump(buffer);

	if (! lump)
	{
		buffer[5] = '1';
		lump = W_FindSpriteLump(buffer);
	}

	if (! lump)
	{
		strcat(buffer, "D1");
		lump = W_FindSpriteLump(buffer);
	}

	if (lump)
		return lump;

	// check outside of the sprite namespace...

	if (! Features.lax_sprites)
		return NULL;

	strcpy(buffer, name);

	if (strlen(buffer) == 4)
		strcat(buffer, "A");

	if (strlen(buffer) == 5)
		strcat(buffer, "0");

	lump = W_FindLump(buffer);

	if (! lump)
	{
		buffer[5] = '1';
		lump = W_FindLump(buffer);
	}

	// TODO: verify lump is OK (size etc)
	if (lump)
	{
		LogPrintf("WARNING: using sprite '%s' outside of S_START..S_END\n", name);
	}

	return lump;
}


Img_c * W_GetSprite(int type)
{
	sprite_map_t::iterator P = sprites.find(type);

	if (P != sprites.end())
		return P->second;

	// sprite not in the list yet.  Add it.

	const thingtype_t *info = M_GetThingType(type);

	Img_c *result = NULL;

	if (strncmp(info->desc, "UNKNOWN", 7) == 0)
	{
		// leave as NULL
	}
	else if (y_stricmp(info->sprite, "_LYT") == 0)
	{
		result = IM_CreateLightSprite();
	}
	else if (y_stricmp(info->sprite, "_MSP") == 0)
	{
		result = IM_CreateMapSpotSprite(0, 255, 0);
	}
	else if (y_stricmp(info->sprite, "NULL") == 0)
	{
		result = IM_CreateMapSpotSprite(70, 70, 255);
	}
	else
	{
		Lump_c *lump = Sprite_loc_by_root(info->sprite);
		if (! lump)
		{
			// for the MBF dog, create our own sprite for it, since
			// it is defined in the Boom definition file and the
			// missing sprite looks ugly in the thing browser.

			if (y_stricmp(info->sprite, "DOGS") == 0)
				result = IM_CreateDogSprite();
			else
				LogPrintf("Sprite not found: '%s'\n", info->sprite);
		}
		else
		{
			result = new Img_c();

			if (! LoadPicture(*result, lump, info->sprite, 0, 0))
			{
				delete result;
				result = NULL;
			}
		}
	}

	// player color remapping
	// [ FIXME : put colors into game definition file ]
	if (result && info->group == 'p')
	{
		Img_c *new_img = NULL;

		switch (type)
		{
			case 1:
				// no change
				break;

			case 2:
				new_img = result->color_remap(0x70, 0x7f, 0x60, 0x6f);
				break;

			case 3:
				new_img = result->color_remap(0x70, 0x7f, 0x40, 0x4f);
				break;

			case 4:
				new_img = result->color_remap(0x70, 0x7f, 0x20, 0x2f);
				break;

			// blue for the extra coop starts
			case 4001:
			case 4002:
			case 4003:
			case 4004:
				new_img = result->color_remap(0x70, 0x7f, 0xc4, 0xcf);
				break;
		}

		if (new_img)
		{
			std::swap(result, new_img);
			delete new_img;
		}
	}

	// note that a NULL image is OK.  Our renderer will just ignore the
	// missing sprite.

	sprites[type] = result;
	return result;
}


//----------------------------------------------------------------------

static void UnloadTex(const std::map<std::string, Img_c *>::value_type& P)
{
	if (P.second != NULL)
		P.second->unload_gl(false);
}

static void UnloadFlat(const std::map<std::string, Img_c *>::value_type& P)
{
	if (P.second != NULL)
		P.second->unload_gl(false);
}

static void UnloadSprite(const sprite_map_t::value_type& P)
{
	if (P.second != NULL)
		P.second->unload_gl(false);
}

void W_UnloadAllTextures()
{
	std::for_each(textures.begin(), textures.end(), UnloadTex);
	std::for_each(   flats.begin(),    flats.end(), UnloadFlat);
	std::for_each( sprites.begin(),  sprites.end(), UnloadSprite);

	IM_UnloadDummyTextures();
}

//--- editor settings ---
// vi:ts=4:sw=4:noexpandtab
