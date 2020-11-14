//------------------------------------------------------------------------
//  BROWSER for TEXTURES / FLATS / THINGS
//------------------------------------------------------------------------
//
//  Eureka DOOM Editor
//
//  Copyright (C) 2007-2019 Andrew Apted
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

#ifndef __EUREKA_UI_BROWSER_H__
#define __EUREKA_UI_BROWSER_H__

#include <map>
#include <string>


class Browser_Button;


class Browser_Item : public Fl_Group
{
private:

public:
	std::string desc;
	std::string real_name;	// for textures and flats only

	int number;

	char kind;  // generally matches browser kind: T/F/O/S/L
	char category;

	int recent_idx;

	Browser_Button * button;

	UI_Pic *pic;

public:
	// this constructor makes a simple text button
	Browser_Item(int X, int Y, int W, int H,
	             const char *_desc, const char *_realname,
				 int _num, char _kind, char _category);

	// this constructor makes a picture with a text label below it
	Browser_Item(int X, int Y, int W, int H,
	             const char * _desc, const char *_realname,
				 int _num, char _kind, char _category,
	             int pic_w, int pic_h, UI_Pic *_pic);

	virtual ~Browser_Item();

	bool MatchName(const char *name) const;

public:
	static void texture_callback(Fl_Widget *w, void *data);
	static void    flat_callback(Fl_Widget *w, void *data);
	static void   thing_callback(Fl_Widget *w, void *data);
	static void    line_callback(Fl_Widget *w, void *data);
	static void  sector_callback(Fl_Widget *w, void *data);

private:
};


class UI_Browser_Box : public Fl_Group
{
private:
	char kind;

	Fl_Choice *category;
	Fl_Input  *search;

	Fl_Check_Button *alpha;
	Fl_Check_Button *pics;

	Fl_Check_Button *do_tex;
	Fl_Check_Button *do_flats;

	UI_Scroll *scroll;

	bool pic_mode;

	char cat_letters[64];

public:
	UI_Browser_Box(int X, int Y, int W, int H, const char *label, char _kind);
	virtual ~UI_Browser_Box();

	/* FLTK method */
	void resize(int X, int Y, int W, int H);

public:
	void Populate();

	void SetCategories(const char *cats, const char *letters);

	void CycleCategory(int dir);
	void ToggleRecent(bool force_recent);
	void ClearSearchBox();
	void Scroll(int delta);

	char GetKind() const { return kind; }

	// ensure the given texture or type/special is visible
	void JumpToTex(const char *tex_name);
	void JumpToValue(int value);

	void RecentUpdate();

	bool ParseUser(const char ** tokens, int num_tok);
	void WriteUser(FILE *fp);

private:
	// adjust the widgets in the Fl_Scroll based on current search
	// parameters.  Returns true if something changed.
	bool Filter(bool force_update = false);

	void Sort();

	bool SearchMatch(Browser_Item *item) const;

	void Populate_Images(char imkind, std::map<std::string, Img_c *> & img_list);
	void Populate_Sprites();

	void Populate_ThingTypes();
	void Populate_LineTypes();
	void Populate_SectorTypes();

	bool Recent_UpdateItem(Browser_Item *item);

	bool CategoryByLetter(char letter);

	static void category_callback(Fl_Widget *w, void *data);
	static void   search_callback(Fl_Widget *w, void *data);

	static void   hide_callback(Fl_Widget *w, void *data);
	static void  repop_callback(Fl_Widget *w, void *data);
	static void   sort_callback(Fl_Widget *w, void *data);
};


class UI_Generalized_Page;


class UI_Generalized_Box : public Fl_Group
{
private:
	// overall kind of line (DOOR, LIFT, etc...)
	Fl_Choice * category;

	// this is shown when not in Boom mode
	Fl_Box * no_boom;

	enum
	{
		MAX_PAGES = 16
	};

	UI_Generalized_Page * pages[MAX_PAGES];

	int num_pages;

	int in_update;

public:
	UI_Generalized_Box(int X, int Y, int W, int H, const char *label);
	virtual ~UI_Generalized_Box();

	void Populate();

	void UpdateGenType(int line_type);

private:
	void CreatePages();

	int ComputeType() const;

	static void hide_callback(Fl_Widget *w, void *data);
	static void  cat_callback(Fl_Widget *w, void *data);
	static void edit_callback(Fl_Widget *w, void *data);
};


class UI_Browser : public Fl_Group
{
	/* this widget basically just contains all the browser boxes,
	 * and controls which one is visible at any time.
	 */

private:
	UI_Browser_Box *browsers[5];

	UI_Generalized_Box *gen_box;

	enum
	{
		ACTIVE_GENERALIZED = 5
	};

 	// currently active browser box (may be hidden though)
	int active;

public:
	UI_Browser(int X, int Y, int W, int H, const char *label = NULL);
	virtual ~UI_Browser();

public:
	void Populate();

	void SetActive(int new_active);

	char GetMode() const;
	void ChangeMode(char new_mode);
	void NewEditMode(obj_type_e edit_mode);

	// ensure the given texture or type/special is visible
	void JumpToTex(const char *tex_name);
	void JumpToValue(int value);

	// dir is +1 or -1, or 0 to set the category to "ALL"
	void CycleCategory(int dir);
	void ToggleRecent(bool force_recent = false);

	void ClearSearchBox();

	void Scroll(int delta);

	// recently used textures (etc) has changed
	void RecentUpdate();

	// for the generalized box
	void UpdateGenType(int line_type);

	bool ParseUser(const char ** tokens, int num_tok);
	void WriteUser(FILE *fp);

private:
//	static void mode_callback(Fl_Widget *w, void *data);
};


bool Browser_ParseUser(const char ** tokens, int num_tok);
void Browser_WriteUser(FILE *fp);

#endif  /* __EUREKA_UI_BROWSER_H__ */

//--- editor settings ---
// vi:ts=4:sw=4:noexpandtab
