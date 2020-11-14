//------------------------------------------------------------------------
//  DEFAULT PROPERTIES
//------------------------------------------------------------------------
//
//  Eureka DOOM Editor
//
//  Copyright (C) 2007-2016 Andrew Apted
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

#include "main.h"
#include "ui_window.h"

#include "e_main.h"
#include "e_cutpaste.h"
#include "m_config.h"	// gui_scheme
#include "m_game.h"
#include "r_render.h"
#include "w_rawdef.h"
#include "w_texture.h"


#define HIDE_BG  (gui_scheme == 2 ? FL_DARK3 : FL_DARK1)


UI_DefaultProps::UI_DefaultProps(int X, int Y, int W, int H) :
	Fl_Group(X, Y, W, H, NULL)
{
	box(FL_FLAT_BOX);


	Fl_Button *hide_button = new Fl_Button(X + 14, Y + 14, 22, 22, "X");
	hide_button->color(HIDE_BG, HIDE_BG);
	hide_button->labelsize(14);
	hide_button->callback(hide_callback, this);


	Fl_Box *title = new Fl_Box(X + 60, Y + 10, W - 70, 30, "Default Properties");
	title->align(FL_ALIGN_LEFT | FL_ALIGN_INSIDE);
	title->labelsize(22);

	Y += 35; H -= 35;
	X += 6;  W -= 12;


	// ---- LINEDEF TEXTURES ------------

	Y += 32;

	w_pic = new UI_Pic(X+W-76,   Y, 64, 64);
	w_pic->callback(tex_callback, this);
	w_pic->AllowHighlight(true);

	Y += 20;

	w_tex = new UI_DynInput(X+68,   Y, 108, 24, "Wall: ");
	w_tex->callback(tex_callback, this);
	w_tex->callback2(dyntex_callback, this);
	w_tex->when(FL_WHEN_RELEASE | FL_WHEN_ENTER_KEY);

	Y += w_tex->h() + 50;


	// ---- SECTOR PROPS --------------

	c_pic = new UI_Pic(X+W-76, Y+2,  64, 64);
	f_pic = new UI_Pic(X+W-76, Y+78, 64, 64);

	c_pic->callback(flat_callback, this);
	f_pic->callback(flat_callback, this);

	f_pic->AllowHighlight(true);
	c_pic->AllowHighlight(true);


	c_tex = new UI_DynInput(X+68, Y, 108, 24, "Ceiling: ");
	c_tex->align(FL_ALIGN_LEFT);
	c_tex->callback(flat_callback, this);
	c_tex->callback2(dyntex_callback, this);
	c_tex->when(FL_WHEN_RELEASE | FL_WHEN_ENTER_KEY);

	Y += c_tex->h() + 3;


	ceil_h = new Fl_Int_Input(X+68, Y, 64, 24, "");
	ceil_h->align(FL_ALIGN_LEFT);
	ceil_h->callback(height_callback, this);
	ceil_h->when(FL_WHEN_RELEASE | FL_WHEN_ENTER_KEY);



	ce_down = new Fl_Button(X+24,    Y+1, 30, 22, "-");
	ce_up   = new Fl_Button(X+68+68, Y+1, 30, 22, "+");

	ce_down->labelfont(FL_HELVETICA_BOLD);
	ce_up  ->labelfont(FL_HELVETICA_BOLD);
	ce_down->labelsize(16);
	ce_up  ->labelsize(16);

	ce_down->callback(button_callback, this);
	ce_up  ->callback(button_callback, this);


	Y += ceil_h->h() + 8;

	floor_h = new Fl_Int_Input(X+68, Y, 64, 24, "");
	floor_h->align(FL_ALIGN_LEFT);
	floor_h->callback(height_callback, this);
	floor_h->when(FL_WHEN_RELEASE | FL_WHEN_ENTER_KEY);


	fl_down = new Fl_Button(X+24,    Y+1, 30, 22, "-");
	fl_up   = new Fl_Button(X+68+68, Y+1, 30, 22, "+");

	fl_down->labelfont(FL_HELVETICA_BOLD);
	fl_up  ->labelfont(FL_HELVETICA_BOLD);
	fl_down->labelsize(16);
	fl_up  ->labelsize(16);

	fl_down->callback(button_callback, this);
	fl_up  ->callback(button_callback, this);

	Y += floor_h->h() + 3;


	f_tex = new UI_DynInput(X+68, Y, 108, 24, "Floor:   ");
	f_tex->align(FL_ALIGN_LEFT);
	f_tex->callback(flat_callback, this);
	f_tex->callback2(dyntex_callback, this);
	f_tex->when(FL_WHEN_RELEASE | FL_WHEN_ENTER_KEY);

	Y += f_tex->h() + 8;


	light = new Fl_Int_Input(X+68, Y, 64, 24, "Light:   ");
	light->align(FL_ALIGN_LEFT);
	light->callback(height_callback, this);
	light->when(FL_WHEN_RELEASE | FL_WHEN_ENTER_KEY);

	Y += light->h() + 40;


	// ---- THING PROPS --------------

	thing = new UI_DynInput(X+60, Y+20, 64, 24, "Thing: ");
	thing->align(FL_ALIGN_LEFT);
	thing->callback(thing_callback, this);
	thing->callback2(dynthing_callback, this);
	thing->when(FL_WHEN_RELEASE | FL_WHEN_ENTER_KEY);
	thing->type(FL_INT_INPUT);

	th_desc = new Fl_Output(X+60, Y+80-26, 122, 24);

	th_sprite = new UI_Pic(X+W-90, Y, 80,80, "Sprite");
	th_sprite->callback(thing_callback, this);


	resizable(NULL);

	end();
}


UI_DefaultProps::~UI_DefaultProps()
{ }


void UI_DefaultProps::hide_callback(Fl_Widget *w, void *data)
{
	main_win->HideSpecialPanel();
}


void UI_DefaultProps::SetIntVal(Fl_Int_Input *w, int value)
{
	char buffer[64];
	snprintf(buffer, sizeof(buffer), "%d", value);
	w->value(buffer);
}


void UI_DefaultProps::UpdateThingDesc()
{
	const thingtype_t *info = M_GetThingType(default_thing);

	th_desc->value(info->desc);
	th_sprite->GetSprite(default_thing, FL_DARK2);
}


void UI_DefaultProps::SetThing(int number)
{
	default_thing = number;

	thing->value(Int_TmpStr(default_thing));

	UpdateThingDesc();
}


const char * UI_DefaultProps::Normalize_and_Dup(UI_DynInput *w)
{
	const char *normalized = StringDup(NormalizeTex(w->value()));

	w->value(normalized);

	return normalized;
}


void UI_DefaultProps::tex_callback(Fl_Widget *w, void *data)
{
	UI_DefaultProps *box = (UI_DefaultProps *)data;

	if (w == box->w_pic)
	{
		UI_Pic * pic = (UI_Pic *) w;

		pic->Selected(! pic->Selected());

		if (pic->Selected())
			main_win->BrowserMode('T');

		return;
	}

	if (w == box->w_tex)
	{
		default_wall_tex = Normalize_and_Dup(box->w_tex);
	}

	box->w_pic->GetTex(box->w_tex->value());
}


void UI_DefaultProps::flat_callback(Fl_Widget *w, void *data)
{
	UI_DefaultProps *box = (UI_DefaultProps *)data;

	if (w == box->f_pic ||
		w == box->c_pic)
	{
		UI_Pic * pic = (UI_Pic *) w;

		pic->Selected(! pic->Selected());

		if (pic->Selected())
			main_win->BrowserMode('F');

		return;
	}

	if (w == box->f_tex)
		default_floor_tex = Normalize_and_Dup(box->f_tex);

	if (w == box->c_tex)
		default_ceil_tex = Normalize_and_Dup(box->c_tex);

	box->f_pic->GetFlat(box->f_tex->value());
	box->c_pic->GetFlat(box->c_tex->value());
}


void UI_DefaultProps::dyntex_callback(Fl_Widget *w, void *data)
{
	UI_DefaultProps *box = (UI_DefaultProps *)data;

	if (w == box->w_tex)
	{
		box->w_pic->GetTex(box->w_tex->value());
	}
	else if (w == box->f_tex)
	{
		box->f_pic->GetFlat(box->f_tex->value());
	}
	else if (w == box->c_tex)
	{
		box->c_pic->GetFlat(box->c_tex->value());
	}
}


void UI_DefaultProps::button_callback(Fl_Widget *w, void *data)
{
	UI_DefaultProps *box = (UI_DefaultProps *)data;

	keycode_t mod = Fl::event_state() & MOD_ALL_MASK;

	int diff = 8;

	if (mod & MOD_SHIFT)
		diff = 1;
	else if (mod & MOD_COMMAND)
		diff = 64;

	if (w == box->fl_up)
		default_floor_h += diff;

	if (w == box->fl_down)
		default_floor_h -= diff;

	if (w == box->ce_up)
		default_ceil_h += diff;

	if (w == box->ce_down)
		default_ceil_h -= diff;

	box->SetIntVal(box->floor_h, default_floor_h);
	box->SetIntVal(box-> ceil_h, default_ceil_h);
}


void UI_DefaultProps::height_callback(Fl_Widget *w, void *data)
{
	UI_DefaultProps *box = (UI_DefaultProps *)data;

	default_floor_h = atoi(box->floor_h->value());
	default_ceil_h  = atoi(box-> ceil_h->value());
	default_light_level = atoi(box->light->value());
}


void UI_DefaultProps::thing_callback(Fl_Widget *w, void *data)
{
	UI_DefaultProps *box = (UI_DefaultProps *)data;

	if (w == box->th_sprite)
	{
		main_win->BrowserMode('O');
		return;
	}

	default_thing = atoi(box->thing->value());

	box->UpdateThingDesc();
}


void UI_DefaultProps::dynthing_callback(Fl_Widget *w, void *data)
{
	UI_DefaultProps *box = (UI_DefaultProps *)data;

	int value = atoi(box->thing->value());

	const thingtype_t *info = M_GetThingType(value);

	box->th_desc->value(info->desc);
	box->th_sprite->GetSprite(value, FL_DARK2);
}


void UI_DefaultProps::LoadValues()
{
	w_tex->value(default_wall_tex);
	f_tex->value(default_floor_tex);
	c_tex->value(default_ceil_tex);

	w_pic->GetTex (w_tex->value());
	f_pic->GetFlat(f_tex->value());
	c_pic->GetFlat(c_tex->value());

	SetIntVal(floor_h, default_floor_h);
	SetIntVal( ceil_h, default_ceil_h);
	SetIntVal(  light, default_light_level);

	thing->value(Int_TmpStr(default_thing));

	UpdateThingDesc();
}


void UI_DefaultProps::CB_Copy(int sel_pics)
{
	const char *name = NULL;

	switch (sel_pics)
	{
		case 1: name = f_tex->value(); break;
		case 2: name = c_tex->value(); break;
		case 4: name = w_tex->value(); break;

		default:
			Beep("multiple textures");
			return;
	}

	if (sel_pics & 4)
		Texboard_SetTex(name);
	else
		Texboard_SetFlat(name);
}


void UI_DefaultProps::CB_Paste(int sel_pics)
{
	if (sel_pics & 1)
	{
		f_tex->value(BA_GetString(Texboard_GetFlatNum()));
		f_tex->do_callback();
	}

	if (sel_pics & 2)
	{
		c_tex->value(BA_GetString(Texboard_GetFlatNum()));
		c_tex->do_callback();
	}

	if (sel_pics & 4)
	{
		w_tex->value(BA_GetString(Texboard_GetTexNum()));
		w_tex->do_callback();
	}
}


void UI_DefaultProps::CB_Delete(int sel_pics)
{
	// we abuse the delete function to turn sector ceilings into sky

	if (sel_pics & 1)
	{
		f_tex->value(Misc_info.sky_flat);
		f_tex->do_callback();
	}

	if (sel_pics & 2)
	{
		c_tex->value(Misc_info.sky_flat);
		c_tex->do_callback();
	}
}


bool UI_DefaultProps::ClipboardOp(char op)
{
	int sel_pics =	(f_pic->Selected() ? 1 : 0) |
					(c_pic->Selected() ? 2 : 0) |
					(w_pic->Selected() ? 4 : 0);

	if (sel_pics == 0)
	{
		sel_pics =	(f_pic->Highlighted() ? 1 : 0) |
					(c_pic->Highlighted() ? 2 : 0) |
					(w_pic->Highlighted() ? 4 : 0);
	}

	if (sel_pics == 0)
		return false;

	switch (op)
	{
		case 'c':
			CB_Copy(sel_pics);
			break;

		case 'v':
			CB_Paste(sel_pics);
			break;

		case 'x':
			Beep("cannot cut that");
			break;

		case 'd':
			CB_Delete(sel_pics);
			break;
	}

	return true;
}


void UI_DefaultProps::BrowsedItem(char kind, int number, const char *name, int e_state)
{
	if (kind == 'O')
	{
		SetThing(number);
		return;
	}

	if (! (kind == 'T' || kind == 'F'))
		return;

	int sel_pics =	(f_pic->Selected() ? 1 : 0) |
					(c_pic->Selected() ? 2 : 0) |
					(w_pic->Selected() ? 4 : 0);

	if (sel_pics == 0)
	{
		if (kind == 'T')
			sel_pics = 4;
		else
			sel_pics = (e_state & FL_BUTTON3) ? 2 : 1;
	}


	if (sel_pics & 1)
	{
		f_tex->value(name);
		f_tex->do_callback();
	}
	if (sel_pics & 2)
	{
		c_tex->value(name);
		c_tex->do_callback();
	}
	if (sel_pics & 4)
	{
		w_tex->value(name);
		w_tex->do_callback();
	}
}


void UI_DefaultProps::UnselectPics()
{
	w_pic->Unhighlight();
	f_pic->Unhighlight();
	c_pic->Unhighlight();

	w_pic->Selected(false);
	f_pic->Selected(false);
	c_pic->Selected(false);
}


//------------------------------------------------------------------------


bool Props_ParseUser(const char ** tokens, int num_tok)
{
	// syntax is:  default  <prop>  <value>
	if (num_tok < 3)
		return false;

	if (strcmp(tokens[0], "default") != 0)
		return false;

	if (strcmp(tokens[1], "floor_h") == 0)
		default_floor_h = atoi(tokens[2]);

	if (strcmp(tokens[1], "ceil_h") == 0)
		default_ceil_h = atoi(tokens[2]);

	if (strcmp(tokens[1], "light_level") == 0)
		default_light_level = atoi(tokens[2]);

	if (strcmp(tokens[1], "thing") == 0)
		default_thing = atoi(tokens[2]);

	if (strcmp(tokens[1], "floor_tex") == 0)
		default_floor_tex = StringDup(tokens[2]);

	if (strcmp(tokens[1], "ceil_tex") == 0)
		default_ceil_tex = StringDup(tokens[2]);

	if (strcmp(tokens[1], "mid_tex") == 0)
		default_wall_tex = StringDup(tokens[2]);

	return true;
}


void Props_WriteUser(FILE *fp)
{
	fprintf(fp, "\n");

	fprintf(fp, "default floor_h %d\n", default_floor_h);
	fprintf(fp, "default ceil_h %d\n",  default_ceil_h);
	fprintf(fp, "default light_level %d\n",  default_light_level);
	fprintf(fp, "default thing %d\n",  default_thing);

	fprintf(fp, "default mid_tex \"%s\"\n",   StringTidy(default_wall_tex,  "\""));
	fprintf(fp, "default floor_tex \"%s\"\n", StringTidy(default_floor_tex, "\""));
	fprintf(fp, "default ceil_tex \"%s\"\n",  StringTidy(default_ceil_tex,  "\""));
}


void Props_LoadValues()
{
	if (main_win)
		main_win->props_box->LoadValues();
}


//--- editor settings ---
// vi:ts=4:sw=4:noexpandtab
