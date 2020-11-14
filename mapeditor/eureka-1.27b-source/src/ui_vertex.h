//------------------------------------------------------------------------
//  VERTEX PANEL
//------------------------------------------------------------------------
//
//  Eureka DOOM Editor
//
//  Copyright (C) 2007-2015 Andrew Apted
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

#ifndef __EUREKA_UI_VERTEX_H__
#define __EUREKA_UI_VERTEX_H__


class UI_VertexBox : public Fl_Group
{
private:
	int obj;
	int count;

public:
	UI_Nombre *which;

	Fl_Int_Input *pos_x;
	Fl_Int_Input *pos_y;

	Fl_Button *move_left;
	Fl_Button *move_right;
	Fl_Button *move_up;
	Fl_Button *move_down;

public:
	UI_VertexBox(int X, int Y, int W, int H, const char *label = NULL);
	virtual ~UI_VertexBox();

public:
	int handle(int event);
	// FLTK virtual method for handling input events.

public:
	void SetObj(int _index, int _count);

	int GetObj() const { return obj; }

	// call this if the vertex was externally changed.
	void UpdateField();

	void UpdateTotal();

private:
	static void x_callback(Fl_Widget *, void *);
	static void y_callback(Fl_Widget *, void *);
	static void button_callback(Fl_Widget *, void *);
};


#endif  /* __EUREKA_UI_VERTEX_H__ */

//--- editor settings ---
// vi:ts=4:sw=4:noexpandtab
