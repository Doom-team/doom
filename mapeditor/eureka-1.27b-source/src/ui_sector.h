//------------------------------------------------------------------------
//  SECTOR PANEL
//------------------------------------------------------------------------
//
//  Eureka DOOM Editor
//
//  Copyright (C) 2007-2018 Andrew Apted
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

#ifndef __EUREKA_UI_SECTOR_H__
#define __EUREKA_UI_SECTOR_H__


class UI_SectorBox : public Fl_Group
{
private:
	int obj;
	int count;

public:
	UI_Nombre *which;

	UI_DynInput   *type;
	Fl_Output    *desc;
	Fl_Button    *choose;

	Fl_Int_Input *light;
	Fl_Int_Input *tag;

	Fl_Button *fresh_tag;
	Fl_Button *lt_down, *lt_up;

	Fl_Int_Input *ceil_h;
	Fl_Int_Input *floor_h;

	Fl_Button *ce_down, *ce_up;
	Fl_Button *fl_down, *fl_up;

	UI_DynInput *c_tex;
	UI_Pic      *c_pic;

	UI_DynInput *f_tex;
	UI_Pic      *f_pic;

	Fl_Int_Input *headroom;

	enum
	{
		HEADROOM_BUTTONS = 6
	};

	Fl_Button * hd_buttons[HEADROOM_BUTTONS];

	// Boom generalized sectors

	Fl_Box    * bm_title;
	Fl_Choice * bm_damage;

	Fl_Check_Button * bm_secret;
	Fl_Check_Button * bm_friction;
	Fl_Check_Button * bm_wind;

public:
	UI_SectorBox(int X, int Y, int W, int H, const char *label = NULL);
	virtual ~UI_SectorBox();

public:
	void SetObj(int _index, int _count);

	int GetObj() const { return obj; }

	// call this if the thing was externally changed.
	// -1 means "all fields"
	void UpdateField(int field = -1);

	void UpdateTotal();

	void UpdateGameInfo();

	// see ui_window.h for description of these two methods
	bool ClipboardOp(char op);
	void BrowsedItem(char kind, int number, const char *name, int e_state);

	void UnselectPics();

private:
	void CB_Copy(int parts);
	void CB_Paste(int parts, int new_tex);
	void CB_Cut(int parts);

	// returns either zero or a combination of PART_FLOOR and PART_CEIL
	int GetSelectedPics() const;
	int GetHighlightedPics() const;

	void SetFlat(const char *name, int parts);
	void SetSectorType(int new_type);

	void InstallFlat(const char *name, int parts);
	void InstallSectorType(int mask, int value);

	void FreshTag();

	static void   height_callback(Fl_Widget *, void *);
	static void headroom_callback(Fl_Widget *, void *);

	static void     tex_callback(Fl_Widget *, void *);
	static void  dyntex_callback(Fl_Widget *, void *);
	static void    type_callback(Fl_Widget *, void *);
	static void dyntype_callback(Fl_Widget *, void *);

	static void   light_callback(Fl_Widget *, void *);
	static void     tag_callback(Fl_Widget *, void *);
	static void  button_callback(Fl_Widget *, void *);
};

#endif  /* __EUREKA_UI_SECTOR_H__ */

//--- editor settings ---
// vi:ts=4:sw=4:noexpandtab
