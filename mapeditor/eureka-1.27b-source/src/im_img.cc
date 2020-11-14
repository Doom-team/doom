//------------------------------------------------------------------------
//  IMAGES
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

#include "im_img.h"
#include "m_game.h"

#ifndef NO_OPENGL
// need this for GL_UNSIGNED_INT_8_8_8_8_REV
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#else
#include "GL/glext.h"
#endif
#endif


static int missing_tex_color;
static int unknown_tex_color;
static int special_tex_color;
static int unknown_flat_color;
static int unknown_sprite_color;

static Img_c * missing_tex_image;
static Img_c * unknown_tex_image;
static Img_c * special_tex_image;
static Img_c * unknown_flat_image;
static Img_c * unknown_sprite_image;

static Img_c * digit_font_11x14;
static Img_c * digit_font_14x19;

#define DIGIT_FONT_COLOR   RGB_MAKE(68, 221, 255)


inline rgb_color_t IM_PixelToRGB(img_pixel_t p)
{
	if (p & IS_RGB_PIXEL)
	{
		byte r = IMG_PIXEL_RED(p)   << 3;
		byte g = IMG_PIXEL_GREEN(p) << 3;
		byte b = IMG_PIXEL_BLUE(p)  << 3;

		return RGB_MAKE(r, g, b);
	}
	else
	{
		byte r = raw_palette[p][0];
		byte g = raw_palette[p][1];
		byte b = raw_palette[p][2];

		return RGB_MAKE(r, g, b);
	}
}


//
// default constructor, creating a null image
//
Img_c::Img_c() : pixels(NULL), w(0), h(0), gl_tex(0)
{ }


//
// a constructor with dimensions
//
Img_c::Img_c(int width, int height, bool _dummy) :
	pixels(NULL), w(0), h(0), gl_tex(0)
{
	resize(width, height);
}


//
// destructor
//
Img_c::~Img_c()
{
	delete []pixels;
}


//
//  return a const pointer on the buffer.
//  if the image is null, return a NULL pointer.
//
const img_pixel_t *Img_c::buf() const
{
	return pixels;
}


//
// return a writable pointer on the buffer.
// if the image is null, return a NULL pointer.
//
img_pixel_t *Img_c::wbuf()
{
	return pixels;
}


//
// clear the image to fully transparent
//
void Img_c::clear()
{
	if (pixels)
	{
		img_pixel_t *dest = pixels;
		img_pixel_t *dest_end = dest + (w * h);

		for ( ; dest < dest_end ; dest++)
			*dest = TRANS_PIXEL;
	}
}


//
// resize the image.  if either dimension is zero,
// the image becomes a null image.
//
void Img_c::resize(int new_width, int new_height)
{
	if (new_width == w && new_height == h)
		return;

	// unallocate old buffer
	if (pixels)
	{
		delete[] pixels;
		pixels = NULL;
	}

	// Is it a null image ?
	if (new_width == 0 || new_height == 0)
	{
		w = h = 0;
		return;
	}

	// Allocate new buffer
	w = new_width;
	h = new_height;

	pixels = new img_pixel_t[w * h + 10];  // Some slack

	clear();
}


void Img_c::compose(Img_c *other, int x, int y)
{
	int W = width();
	int H = height();

	int OW = other->width();
	int OH = other->height();

	for (int oy = 0 ; oy < OH ; oy++)
	{
		int iy = y + oy;
		if (iy < 0 || iy >= H)
			continue;

		const img_pixel_t *src = other->buf() + oy * OW;
		img_pixel_t *dest = wbuf() + iy * W;

		for (int ox = 0 ; ox < OW ; ox++, src++)
		{
			int ix = x + ox;
			if (ix < 0 || ix >= W)
				continue;

			if (*src != TRANS_PIXEL)
				dest[ix] = *src;
		}
	}
}


//
// make a game image look vaguely like a spectre
//
Img_c * Img_c::spectrify() const
{
	Img_c *omg = new Img_c(width(), height());

	int invis_start = Misc_info.invis_colors[0];
	int invis_len   = Misc_info.invis_colors[1] - invis_start + 1;

	if (invis_len < 1)
		invis_len = 1;

	int W = width();
	int H = height();

	const img_pixel_t *src = buf();

	img_pixel_t *dest = omg->wbuf();

	for (int y = 0 ; y < H ; y++)
	for (int x = 0 ; x < W ; x++)
	{
		img_pixel_t pix = src[y * W + x];

		if (pix != TRANS_PIXEL)
			pix = invis_start + (rand() >> 4) % invis_len;

		dest[y * W + x] = pix;
	}

	return omg;
}


//
//  scale a game image, returning a new one.
//
//  the implementation is very simplistic and not optimized.
//
//  andrewj: turned into a method, but untested...
//
Img_c * Img_c::scale_img(double scale) const
{
	int iwidth  = width();
	int owidth  = (int) (width()  * scale + 0.5);
	int oheight = (int) (height() * scale + 0.5);

	Img_c *omg = new Img_c(owidth, oheight);

	const img_pixel_t *const ibuf = buf();
	img_pixel_t       *const obuf = omg->wbuf();

	if (true)
	{
		img_pixel_t *orow = obuf;
		int *ix = new int[owidth];
		for (int ox = 0; ox < owidth; ox++)
			ix[ox] = (int) (ox / scale);
		const int *const ix_end = ix + owidth;
		for (int oy = 0; oy < oheight; oy++)
		{
			int iy = (int) (oy / scale);
			const img_pixel_t *const irow = ibuf + iwidth * iy;
			for (const int *i = ix; i < ix_end; i++)
				*orow++ = irow[*i];
		}
		delete[] ix;
	}

	return omg;
}


//
// copy the image, remapping pixels in the range 'src1..src2' to the
// range 'targ1..targ2'.
//
// TODO : make it work with RGB pixels (find nearest in palette).
//
Img_c * Img_c::color_remap(int src1, int src2, int targ1, int targ2) const
{
	SYS_ASSERT( src1 <=  src2);
	SYS_ASSERT(targ1 <= targ2);

	Img_c *omg = new Img_c(width(), height());

	int W = width();
	int H = height();

	const img_pixel_t *src = buf();

	img_pixel_t *dest = omg->wbuf();

	for (int y = 0 ; y < H ; y++)
	for (int x = 0 ; x < W ; x++)
	{
		img_pixel_t pix = src[y * W + x];

		if (src1 <= pix && pix <= src2)
		{
			int diff = pix - src1;

			pix = targ1 + diff * (targ2 - targ1 + 1) / (src2 - src1 + 1);
		}

		dest[y * W + x] = pix;
	}

	return omg;
}


bool Img_c::has_transparent() const
{
	int W = width();
	int H = height();

	const img_pixel_t *src = buf();

	for (int y = 0 ; y < H ; y++)
	for (int x = 0 ; x < W ; x++)
	{
		if (src[y * W + x] == TRANS_PIXEL)
			return true;
	}

	return false;
}


void Img_c::test_make_RGB()
{
	int W = width();
	int H = height();

	img_pixel_t *src = wbuf();

	for (int y = 0 ; y < H ; y++)
	for (int x = 0 ; x < W ; x++)
	{
		img_pixel_t pix = src[y * W + x];

		if (pix != TRANS_PIXEL && ! (pix & IS_RGB_PIXEL))
		{
			const rgb_color_t col = IM_PixelToRGB(pix);

			byte r = RGB_RED(col)   >> 3;
			byte g = RGB_GREEN(col) >> 3;
			byte b = RGB_BLUE(col)  >> 3;

			src[y * W + x] = IMG_PIXEL_MAKE_RGB(r, g, b);
		}
	}
}


#ifdef NO_OPENGL

void Img_c::load_gl() {}
void Img_c::unload_gl(bool can_delete) {}
void Img_c::bind_gl() {}

#else

void Img_c::load_gl()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &gl_tex);
	glBindTexture(GL_TEXTURE_2D, gl_tex);

	// construct a power-of-two sized bottom-up RGBA image
	int tw = RoundPOW2(w);
	int th = RoundPOW2(h);

	byte *rgba = new byte[tw * th * 4];

	memset(rgba, 0, (size_t)(tw * th * 4));

	bool has_trans = has_transparent();

	int ex = has_trans ? w : tw;
	int ey = has_trans ? h : th;

	int x, y;

	for (y = 0 ; y < ey ; y++)
	{
		// invert source Y for OpenGL
		int sy = h - 1 - y;
		if (sy < 0)
			sy += h;

		for (x = 0 ; x < ex ; x++)
		{
			int sx = x;
			if (sx >= w)
				sx = x - w;

			// convert pixel to RGBA
			const img_pixel_t pix = buf()[sy*w + sx];

			if (pix != TRANS_PIXEL)
			{
				byte r, g, b;

				IM_DecodePixel(pix, r, g, b);

				byte *dest = rgba + (y*tw + x) * 4;

				dest[0] = b;
				dest[1] = g;
				dest[2] = r;
				dest[3] = 255;
			}
		}
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0 /* mip */,
		GL_RGBA8, tw, th, 0 /* border */,
		GL_BGRA_EXT, GL_UNSIGNED_INT_8_8_8_8_REV, rgba);

	delete[] rgba;
}


void Img_c::unload_gl(bool can_delete)
{
	if (can_delete && gl_tex != 0)
	{
		glDeleteTextures(1, &gl_tex);
	}

	gl_tex = 0;
}


void Img_c::bind_gl()
{
	// create the GL texture if we haven't already
	if (gl_tex == 0)
	{
		// this will do a glBindTexture
		load_gl();
		return;
	}

	glBindTexture(GL_TEXTURE_2D, gl_tex);
}

#endif

//------------------------------------------------------------------------


void IM_ResetDummyTextures()
{
	missing_tex_color  = -1;
	unknown_tex_color  = -1;
	special_tex_color  = -1;
	unknown_flat_color = -1;
	unknown_sprite_color = -1;
}


void IM_UnloadDummyTextures()
{
	bool can_delete = false;

	if (missing_tex_image)
		missing_tex_image->unload_gl(can_delete);

	if (unknown_tex_image)
		unknown_tex_image->unload_gl(can_delete);

	if (special_tex_image)
		special_tex_image->unload_gl(can_delete);

	if (unknown_flat_image)
		unknown_flat_image->unload_gl(can_delete);

	if (unknown_sprite_image)
		unknown_sprite_image->unload_gl(can_delete);

	if (digit_font_11x14)
		digit_font_11x14->unload_gl(can_delete);

	if (digit_font_14x19)
		digit_font_14x19->unload_gl(can_delete);
}


static const byte unknown_graphic[16 * 16] =
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,
	0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,
	0,0,1,1,1,1,0,0,0,0,0,1,1,1,0,0,
	0,0,0,1,1,0,0,0,0,0,0,1,1,1,0,0,
	0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,
	0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,
	0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,
	0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};


static const byte missing_graphic[16 * 16] =
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,
	0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,
	0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};


static Img_c * IM_CreateDummyTex(const byte *data, int bg, int fg)
{
	Img_c *omg = new Img_c(64, 64, true);

	img_pixel_t *obuf = omg->wbuf();

	for (int y = 0 ; y < 64 ; y++)
	for (int x = 0 ; x < 64 ; x++)
	{
		obuf[y * 64 + x] = data[((y/2) & 15 ) * 16 + ((x/2) & 15)] ? fg : bg;
	}

	return omg;
}


Img_c * IM_MissingTex()
{
	if (! missing_tex_image || missing_tex_color != Misc_info.missing_color)
	{
		missing_tex_color = Misc_info.missing_color;

		if (missing_tex_image)
			delete missing_tex_image;

		missing_tex_image = IM_CreateDummyTex(missing_graphic, missing_tex_color, 0);
	}

	return missing_tex_image;
}


Img_c * IM_UnknownTex()
{
	if (! unknown_tex_image || unknown_tex_color != Misc_info.unknown_tex)
	{
		unknown_tex_color = Misc_info.unknown_tex;

		if (unknown_tex_image)
			delete unknown_tex_image;

		unknown_tex_image = IM_CreateDummyTex(unknown_graphic, unknown_tex_color, 0);
	}

	return unknown_tex_image;
}


Img_c * IM_SpecialTex()
{
	if (special_tex_color < 0)
	{
		special_tex_color = W_FindPaletteColor(192, 0, 192);

		if (special_tex_image)
		{
			delete special_tex_image;
			special_tex_image = NULL;
		}
	}

	if (! special_tex_image)
		special_tex_image = IM_CreateDummyTex(unknown_graphic, special_tex_color,
			W_FindPaletteColor(255, 255, 255));

	return special_tex_image;
}


Img_c * IM_UnknownFlat()
{
	if (! unknown_flat_image || unknown_flat_color != Misc_info.unknown_flat)
	{
		unknown_flat_color = Misc_info.unknown_flat;

		if (unknown_flat_image)
			delete unknown_flat_image;

		unknown_flat_image = IM_CreateDummyTex(unknown_graphic, unknown_flat_color, 0);
	}

	return unknown_flat_image;
}


Img_c * IM_UnknownSprite()
{
	int unk_col = Misc_info.unknown_thing;
	if (unk_col == 0)
		unk_col = Misc_info.unknown_tex;

	if (! unknown_sprite_image || unknown_sprite_color != unk_col)
	{
		unknown_sprite_color = unk_col;

		if (unknown_sprite_image)
			delete unknown_sprite_image;

		unknown_sprite_image = new Img_c(64, 64, true);

		img_pixel_t *obuf = unknown_sprite_image->wbuf();

		for (int y = 0 ; y < 64 ; y++)
		for (int x = 0 ; x < 64 ; x++)
		{
			obuf[y * 64 + x] = unknown_graphic[(y/4) * 16 + (x/4)] ? unknown_sprite_color : TRANS_PIXEL;
		}
	}

	return unknown_sprite_image;
}


Img_c * IM_CreateFromText(int W, int H, const char **text, const rgb_color_t *palette, int pal_size)
{
	Img_c *result = new Img_c(W, H);

	result->clear();

	// translate colors to current palette
	byte *conv_palette = new byte[pal_size];

	for (int c = 0 ; c < pal_size ; c++)
		conv_palette[c] = W_FindPaletteColor(RGB_RED(palette[c]), RGB_GREEN(palette[c]), RGB_BLUE(palette[c]));

	for (int y = 0 ; y < H ; y++)
	for (int x = 0 ; x < W ; x++)
	{
		int ch = text[y][x] & 0x7f;

		if (ch == ' ')
			continue;  // leave transparent

		if (ch < 'a' || ch >= 'a' + pal_size)
			BugError("Bad character (dec #%d) in built-in image.\n", ch);

		result->wbuf() [y * W + x] = conv_palette[ch - 'a'];
	}

	delete[] conv_palette;

	return result;
}


static Img_c * IM_CreateFont(int W, int H, const char **text,
							 const int *intensities, int ity_size,
							 rgb_color_t color)
{
	Img_c *result = new Img_c(W, H);

	result->clear();

	for (int y = 0 ; y < H ; y++)
	for (int x = 0 ; x < W ; x++)
	{
		int ch = text[y][x] & 0x7f;

		if (ch == ' ')
			continue;  // leave transparent

		if (ch < 'a' || ch >= 'a' + ity_size)
			BugError("Bad character (dec #%d) in built-in font.\n", ch);

		int ity = intensities[ch - 'a'];

		int r = (RGB_RED(color)   * ity) >> 11;
		int g = (RGB_GREEN(color) * ity) >> 11;
		int b = (RGB_BLUE(color)  * ity) >> 11;

		result->wbuf() [y * W + x] = IMG_PIXEL_MAKE_RGB(r, g, b);
	}

	return result;
}


Img_c * IM_ConvertRGBImage(Fl_RGB_Image *src)
{
	int W  = src->w();
	int H  = src->h();
	int D  = src->d();
	int LD = src->ld();

	LD += W;

	const byte * data = (const byte *) src->array;

	if (! data)
		return NULL;

	if (! (D == 3 || D == 4))
		return NULL;

	Img_c *img = new Img_c(W, H);

	for (int y = 0 ; y < H ; y++)
	for (int x = 0 ; x < W ; x++)
	{
		const byte *src_pix = data + (y * LD + x) * D;

		int r = src_pix[0];
		int g = src_pix[1];
		int b = src_pix[2];
		int a = (D == 3) ? 255 : src_pix[3];

		img_pixel_t dest_pix = TRANS_PIXEL;

		if (a & 128)
		{
			// TODO : a preference to palettize it
			// dest_pix = W_FindPaletteColor(r, g, b);

			dest_pix = IMG_PIXEL_MAKE_RGB(r >> 3, g >> 3, b >> 3);
		}

		img->wbuf() [ y * W + x ] = dest_pix;
	}

	return img;
}


Img_c * IM_ConvertTGAImage(const rgba_color_t * data, int W, int H)
{
	Img_c *img = new Img_c(W, H);

	img_pixel_t *dest = img->wbuf();

	for (int i = W * H ; i > 0 ; i--, data++, dest++)
	{
		if (RGBA_ALPHA(*data) & 128)
		{
			byte r = RGB_RED(  *data) >> 3;
			byte g = RGB_GREEN(*data) >> 3;
			byte b = RGB_BLUE( *data) >> 3;

			*dest = IMG_PIXEL_MAKE_RGB(r, g, b);
		}
		else
		{
			*dest = TRANS_PIXEL;
		}
	}

	return img;
}


//------------------------------------------------------------------------

//
// eight basic arrow sprites, made by Andrew Apted, public domain.
//

/* XPM */
const char * arrow_0_xpm[] =
{
	"12 12 2 1",
	" 	c None",
	"1	c #000000",
	"      1     ",
	"      11    ",
	"      111   ",
	"      1111  ",
	"      11111 ",
	"111111111111",
	"111111111111",
	"      11111 ",
	"      1111  ",
	"      111   ",
	"      11    ",
	"      1     "
};

/* XPM */
const char * arrow_45_xpm[] =
{
	"12 12 2 1",
	" 	c None",
	"1	c #000000",
	"            ",
	"   11111111 ",
	"    1111111 ",
	"     111111 ",
	"      11111 ",
	"     111111 ",
	"    111 111 ",
	"   111   11 ",
	"  111     1 ",
	" 111        ",
	" 11         ",
	"            "
};

/* XPM */
const char * arrow_90_xpm[] =
{
	"12 12 2 1",
	" 	c None",
	"1	c #000000",
	"     11     ",
	"    1111    ",
	"   111111   ",
	"  11111111  ",
	" 1111111111 ",
	"111111111111",
	"     11     ",
	"     11     ",
	"     11     ",
	"     11     ",
	"     11     ",
	"     11     "
};

/* XPM */
const char * arrow_135_xpm[] =
{
	"12 12 2 1",
	" 	c None",
	"1	c #000000",
	"            ",
	" 11111111   ",
	" 1111111    ",
	" 111111     ",
	" 11111      ",
	" 111111     ",
	" 111 111    ",
	" 11   111   ",
	" 1     111  ",
	"        111 ",
	"         11 ",
	"            "
};

/* XPM */
const char * arrow_180_xpm[] =
{
	"12 12 2 1",
	" 	c None",
	"1	c #000000",
	"     1      ",
	"    11      ",
	"   111      ",
	"  1111      ",
	" 11111      ",
	"111111111111",
	"111111111111",
	" 11111      ",
	"  1111      ",
	"   111      ",
	"    11      ",
	"     1      "
};

/* XPM */
const char * arrow_225_xpm[] =
{
	"12 12 2 1",
	" 	c None",
	"1	c #000000",
	"            ",
	"         11 ",
	"        111 ",
	" 1     111  ",
	" 11   111   ",
	" 111 111    ",
	" 111111     ",
	" 11111      ",
	" 111111     ",
	" 1111111    ",
	" 11111111   ",
	"            "
};

/* XPM */
const char * arrow_270_xpm[] =
{
	"12 12 2 1",
	" 	c None",
	"1	c #000000",
	"     11     ",
	"     11     ",
	"     11     ",
	"     11     ",
	"     11     ",
	"     11     ",
	"111111111111",
	" 1111111111 ",
	"  11111111  ",
	"   111111   ",
	"    1111    ",
	"     11     "
};

/* XPM */
const char * arrow_315_xpm[] =
{
	"12 12 2 1",
	" 	c None",
	"1	c #000000",
	"            ",
	" 11         ",
	" 111        ",
	"  111     1 ",
	"   111   11 ",
	"    111 111 ",
	"     111111 ",
	"      11111 ",
	"     111111 ",
	"    1111111 ",
	"   11111111 ",
	"            "
};


//------------------------------------------------------------------------

//
// This dog sprite was sourced from OpenGameArt.org
// Authors are 'Benalene' and 'qudobup' (users on the OGA site).
// License is CC-BY 3.0 (Creative Commons Attribution license).
//

static const rgb_color_t dog_palette[] =
{
	0x302020ff,
	0x944921ff,
	0x000000ff,
	0x844119ff,
	0x311800ff,
	0x4A2400ff,
	0x633119ff,
};


static const char *dog_image_text[] =
{
	"       aaaa                                 ",
	"      abbbba                                ",
	"     abbbbbba                               ",
	" aaaabcbbbbbda                              ",
	"aeedbbbfbbbbda                              ",
	"aegdddbbdbbdbbaaaaaaaaaaaaaaaaa           a ",
	"affggddbgddgbccceeeeeeeeeeeeeeeaa        aba",
	" affgggdfggfccceeeeeeeeeeeeeefffgaaa   aaba ",
	"  afffaafgecccefffffffffffffffggggddaaabbba ",
	"   aaa  aeeccggggffffffffffffggddddbbbbbaa  ",
	"         accbdddggfffffffffffggdbbbbbbba    ",
	"          aabbdbddgfffffffffggddbaaaaaa     ",
	"            abbbbdddfffffffggdbbba          ",
	"            abbbbbbdddddddddddbbba          ",
	"           aeebbbbbbbbaaaabbbbbbbba         ",
	"           aeebbbbbaaa    aeebbbbbba        ",
	"          afebbbbaa       affeebbbba        ",
	"         agfbbbaa         aggffabbbba       ",
	"        agfebba           aggggaabbba       ",
	"      aadgfabba            addda abba       ",
	"     abbddaabbbaa           adddaabba       ",
	"    abbbba  abbbba          adbbaabba       ",
	"     aaaa    abbba         abbba  abba      ",
	"              aaa         abbba   abba      ",
	"                         abbba   abbba      ",
	"                          aaa     aaa       "
};


Img_c * IM_CreateDogSprite()
{
	return IM_CreateFromText(44, 26, dog_image_text, dog_palette, 7);
}


//------------------------------------------------------------------------

Img_c * IM_CreateLightSprite()
{
	int W = 11;
	int H = 11;

	Img_c *result = new Img_c(W, H);

	result->clear();

	for (int y = 0 ; y < H ; y++)
	for (int x = 0 ; x < W ; x++)
	{
		byte pix = TRANS_PIXEL;

		if (true) // x > 0 && x < W-1 && y > 0 && y < H-1)
		{
			float dx = (W - 2*x) / (float)W;
			float dy = (H - 2*y) / (float)H;

			float dist = sqrt((dx) * (dx) + (dy) * (dy));

			float ity = 1.0 / (dist + 0.5) / (dist + 0.5);

			if (ity < 0.5)
				continue;

			ity = (ity - 0.4) / (1.0 - 0.4);

			int r = 255 * ity;
			int g = 235 * ity;
			int b = 90  * ity;

			pix = W_FindPaletteColor(r, g, b);
		}

		result->wbuf() [ y * W + x ] = pix;
	}

	return result;
}


Img_c * IM_CreateMapSpotSprite(int base_r, int base_g, int base_b)
{
	int W = 32;
	int H = 32;

	Img_c *result = new Img_c(W, H);

	result->clear();

	for (int y = 4 ; y < H ; y++)
	for (int x = 0 ; x < W ; x++)
	{
		byte pix = TRANS_PIXEL;

		int cx1 = y/2;
		int cx2 = W - y/2;

		if (cx1 <= x && x <= cx2)
		{
			float dx = MIN(x - cx1, cx2 - x);
			//float dy = MIN(abs(y - 4), abs(y - W));

			float ity = 0.3 + dx / 14.0;
			if (ity > 1.0) ity = 1.0;

			int r = base_r * ity;
			int g = base_g * ity;
			int b = base_b * ity;

			pix = W_FindPaletteColor(r, g, b);
		}

		result->wbuf() [ y * W + x ] = pix;
	}

	return result;
}


//------------------------------------------------------------------------

/* a digit-only font, in two sizes */

static const int digit_font_intensities[] =
{
	0x00, 0x16, 0x24, 0x32, 0x3f,
	0x4c, 0x58, 0x65, 0x72, 0x7e,
	0x8b, 0x98, 0xa4, 0xb0, 0xbc,
	0xc9, 0xd6, 0xe2, 0xef, 0xfc,
};


static const char *digit_11x14_text[] =
{
	"                                                                                                                                                 aaaaaaa  ",
	"  aaaaaaa    aaaaaa     aaaaaaaa    aaaaaaa     aaaaa    aaaaaaa     aaaaaa    aaaaaaaa   aaaaaaa    aaaaaaa                                     agqspda  ",
	"  agqspda    alprga     aeorsoca    apsspfa    aalrga    aprrrka    aanssna    afrrrrqa   ajrsqha   aajrspca                                    aaqogqoa  ",
	" aaqogqoa    aontha     ahojirna    amiiqpa    aertha    asmkkga   aanrjika    adkkkpqa  aasnfora   adsmgqoa     aaaa                           afteaitaa ",
	" afteaitaa   aaatha     aaaaamqa    aaaakra   aaomtha    ashaaaa   absiaaaa    aaaaarma  adtcahta   aksaajsaa    ahfa                           agtcagtba ",
	" ajsaaatga     atha        aaooa     ahjqna   ahratha    asrqmaa   agtmrpfa       agtea  aarnhopa   akraajtda    arma                           aarlanqaa ",
	" akraaatha     atha       aajtha     aqssha  aaqjathaa   ankmsna   ajtqjpraa      anqaa  aaktssiaa  aftjaptga    ajga                 aaaaaa     ajtssha  ",
	" aksaaatga     atha      aagskaa     aaanra  akqeetiba   aaaalsa   ajthactga     aarla   aftialsba  aalstotca    aaaa                 amrrla     aadhcaa  ",
	" agtcagtba     atha     aaermaa    aaaaagta  antttttka  aaaaajsa   afteaatha     ahtca   aksaaatga   aaaajsaa    aaaa       aaaa      agjjfa      aaaaa   ",
	" aarlanqaa   aaathaa    acroaaaa   afhaanra  aaaaathaa  aegacpqa   aarmaksba     aopaa   agthaktba   agadrna     amia       anha      aaaaaa              ",
	"  ajtssha    aqtttsa    ajttttra   ahtstsia      atha   ahtstrga    aisrtlaa     aska    aantrtmaa   arstpba     arma       aska                          ",
	"  aadhcaa    aaaaaaa    aaaaaaaa   aabhgaaa      aaaa   aachfaaa    aachcaa      aaaa     aadhdaa    abhfaaa     aaaa       aaaa                          ",
	"   aaaaa                            aaaaa                aaaaa       aaaaa                 aaaaa     aaaaa                                                ",
	"                                                                                                                                                          "
};


static const char *digit_14x19_text[] =
{
	"                                                                                                                                                                                          aaaaaa    ",
	"    aaaaaa         aaaaa       aaaaaaa       aaaaaaa          aaaaa     aaaaaaaaa        aaaaaa     aaaaaaaaaa      aaaaaa        aaaaaa                                                 aadklgaa   ",
	"   aadklgaa     aaaafhca      aacjlkeaa     aadjlkfaa         adhga     adhhhhhhaa      aagllhaa    afhhhhhhga     aafklhaaa     aaglleaa                                               aajstttnaa  ",
	"  aajstttnaa    agqsttja      ansttttlaa    altttttoaa       aaqtra     akttttttda     aaottttna    aqttttttsa    aanttttqda    aaottttlaa                                              adssjgqtja  ",
	"  adssjgqtja    ajtrrtja      arqlilstia    alokikrtma      aakttra     aktommmmba    aaotpjjnma    akmmmmntpa    aktrigotoa    altqhirtha                                              amtkaaetqa  ",
	"  amtkaaetqa    acbamtja      afaaaajtoa    aaaaaaetqa      acsosra     aktjaaaaaa    ahtpaaaaaa    aaaaaamtka    aotgaaarsa    arsdaaftpa      aaaaa                                   aptcaaaqsa  ",
	"  aqtbaaaqtaa   aaaamtja      aaa  actpa         aasqa     aansdsra     aktjaaaa      anthaaaaa         aarsba    aptcaaarsa    atqaaaarsaa     adlia                                   altlaaftqa  ",
	"  arraaaaotga      amtja           aitna      aaaamtma     aftmasra     aktpqpkaa     aqsfoqohaa        agtpaa    aktmaahtpa    atqaaaartea     agtpa                                   abssljrtia  ",
	"  asqa  antia      amtja          aaqtga      aorstnaa    aapraasra     aktssttqaa    arsssrttja        antja     aantrqsqda    assaaadstha     afsoa                                   aahstttlaa  ",
	"  asqa  amtja      amtja         aantnaa      aorstqda    ajtjaasra     agiaafqtma    astrdaissaa      aarsaa     aanssstqea    aotoabpttia     aaaaa                     aaaaaaaa       aaaijdaa   ",
	"  asqa  antia      amtja        aaltpaa       aaaaltpa   aarpaaasraaa   aaaaaaetra    astjaaaotia      ahtoa      antnaaisqaa   adrttttqtga                               ahqqqqda         aaaaa    ",
	"  arraaaaotga      amtja       aajtrca           aaqsa   aitqppptspja        aarsa    artea amtka      aotia      arsaaaaotfa   aablongptba                               airrrrda                  ",
	"  aptcaaaqsaa      amtja      aahsreaa      aaa  aaqta   aisssssttsma   aaa  aassa    aotga antka     aassaa      asraaaantia    aaaaaasraa     aaaaa         aaaaa       aaaaaaaa                  ",
	"  altlaaftqa     aaamtjaaa    afssgaaaaa    abaaaaessa   aaaaaaasraaa   abaaaajtpa    aktmaaaqtea     aitoa       arseaaaqtfa   aaaaaamtma      ackha         aekga                                 ",
	"  abssljrtia     aooqtpona    aqtqooooma    aqpmknstma         asra     aqplknttia    aartmjotpaa     aotha       amtrkjotqaa   aiplkotraa      agtpa         aktna                                 ",
	"  aahstttlaa     attttttra    arttttttqa    apttttsmaa         asra     apttttskaa     agrtttpda      asraa       aaottttqfa    aittttpea       agtpa         aktna                                 ",
	"   aaaijdaa      aaaaaaaaa    aaaaaaaaaa    aadijibaa          aaaa     aadijhaaa      aaahjfaaa      aaaa         aadjjfaaa    aacijfaaa       aaaaa         aaaaa                                 ",
	"     aaaaa                                   aaaaaaa                     aaaaaa          aaaaa                      aaaaaa       aaaaaa                                                             ",
	"                                                                                                                                                                                                    ",
};


Img_c * IM_DigitFont_11x14()
{
	if (! digit_font_11x14)
	{
		digit_font_11x14 = IM_CreateFont(11*14, 14, digit_11x14_text,
										 digit_font_intensities, 20,
										 DIGIT_FONT_COLOR);
	}
	return digit_font_11x14;
}

Img_c * IM_DigitFont_14x19()
{
	if (! digit_font_14x19)
	{
		digit_font_14x19 = IM_CreateFont(14*14, 19, digit_14x19_text,
										 digit_font_intensities, 20,
										 DIGIT_FONT_COLOR);
	}
	return digit_font_14x19;
}

//--- editor settings ---
// vi:ts=4:sw=4:noexpandtab
