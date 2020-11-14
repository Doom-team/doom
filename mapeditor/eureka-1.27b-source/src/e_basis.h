//------------------------------------------------------------------------
//  BASIC OBJECT HANDLING
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

#ifndef __EUREKA_E_BASIS_H__
#define __EUREKA_E_BASIS_H__

class crc32_c;


//
// DESIGN NOTES
//
// Every field in these structures are a plain 'int'.  This is a
// design decision aiming to simplify the logic and code for undo
// and redo.
//
// Strings are represented as offsets into a string table, where
// fetching the actual (read-only) string is fast, but adding new
// strings is slow (with the current code).
//
// These structures are always ensured to have valid fields, e.g.
// the LineDef vertex numbers are OK, the SideDef sector number is
// valid, etc.  For LineDefs, the left and right fields can contain
// -1 to mean "no sidedef", but note that a missing right sidedef
// can cause problems or crashes when playing the map in DOOM.
//


// a fixed-point coordinate with 12 bits of fractional part.
typedef int fixcoord_t;

#define  FROM_COORD(fx)  ((double)(fx) / 4096.0)
#define    TO_COORD(db)  ((fixcoord_t) I_ROUND((db) * 4096.0))

#define INT_TO_COORD(i)  ((fixcoord_t) ((i) << 12))
#define COORD_TO_INT(i)  ((int) ((i) / 4096))

fixcoord_t MakeValidCoord(double x);


typedef enum
{
	SIDE_RIGHT = +1,
	SIDE_LEFT  = -1
}
side_ref_e;


// See objid.h for obj_type_e (OBJ_THINGS etc)


class Thing
{
public:
	fixcoord_t raw_x;
	fixcoord_t raw_y;

	int angle;
	int type;
	int options;

	// Hexen stuff
	fixcoord_t raw_h;

	int tid;
	int special;
	int arg1, arg2, arg3, arg4, arg5;

	enum { F_X, F_Y, F_ANGLE, F_TYPE, F_OPTIONS,
	       F_H, F_TID, F_SPECIAL,
		   F_ARG1, F_ARG2, F_ARG3, F_ARG4, F_ARG5 };

public:
	Thing() : raw_x(0), raw_y(0), angle(0), type(0), options(0),
			  raw_h(0), tid(0), special(0),
			  arg1(0), arg2(0), arg3(0), arg4(0), arg5(0)
	{ }

	inline double x() const
	{
		return FROM_COORD(raw_x);
	}
	inline double y() const
	{
		return FROM_COORD(raw_y);
	}
	inline double h() const
	{
		return FROM_COORD(raw_h);
	}

	// these handle rounding to integer in non-UDMF mode
	void SetRawX(double x) { raw_x = MakeValidCoord(x); }
	void SetRawY(double y) { raw_y = MakeValidCoord(y); }
	void SetRawH(double h) { raw_h = MakeValidCoord(h); }

	void SetRawXY(double x, double y)
	{
		SetRawX(x);
		SetRawY(y);
	}

	void RawCopy(const Thing *other)
	{
		raw_x = other->raw_x;
		raw_y = other->raw_y;
		raw_h = other->raw_h;

		angle = other->angle;
		type = other->type;
		options = other->options;
		tid = other->tid;
		special = other->special;

		arg1 = other->arg1;
		arg2 = other->arg2;
		arg3 = other->arg3;
		arg4 = other->arg4;
		arg5 = other->arg5;
	}

	int Arg(int which /* 1..5 */) const
	{
		if (which == 1) return arg1;
		if (which == 2) return arg2;
		if (which == 3) return arg3;
		if (which == 4) return arg4;
		if (which == 5) return arg5;

		return 0;
	}
};


class Vertex
{
public:
	fixcoord_t raw_x;
	fixcoord_t raw_y;

	enum { F_X, F_Y };

public:
	Vertex() : raw_x(0), raw_y(0)
	{ }

	inline double x() const
	{
		return FROM_COORD(raw_x);
	}
	inline double y() const
	{
		return FROM_COORD(raw_y);
	}

	// these handle rounding to integer in non-UDMF mode
	void SetRawX(double x) { raw_x = MakeValidCoord(x); }
	void SetRawY(double y) { raw_y = MakeValidCoord(y); }

	void SetRawXY(double x, double y)
	{
		SetRawX(x);
		SetRawY(y);
	}

	void RawCopy(const Vertex *other)
	{
		raw_x = other->raw_x;
		raw_y = other->raw_y;
	}

	bool Matches(fixcoord_t ox, fixcoord_t oy) const
	{
		return (raw_x == ox) && (raw_y == oy);
	}

	bool Matches(const Vertex *other) const
	{
		return (raw_x == other->raw_x) && (raw_y == other->raw_y);
	}
};


class Sector
{
public:
	int floorh;
	int ceilh;
	int floor_tex;
	int ceil_tex;
	int light;
	int type;
	int tag;

	enum { F_FLOORH, F_CEILH, F_FLOOR_TEX, F_CEIL_TEX, F_LIGHT, F_TYPE, F_TAG };

public:
	Sector() : floorh(0), ceilh(0), floor_tex(0), ceil_tex(0),
			   light(0), type(0), tag(0)
	{ }

	void RawCopy(const Sector *other)
	{
		floorh = other->floorh;
		ceilh  = other->ceilh;
		floor_tex = other->floor_tex;
		ceil_tex  = other->ceil_tex;
		light  = other->light;
		type   = other->type;
		tag    = other->tag;
	}

	const char *FloorTex() const;
	const char *CeilTex() const;

	int HeadRoom() const
	{
		return ceilh - floorh;
	}

	void SetDefaults();
};


class SideDef
{
public:
	int x_offset;
	int y_offset;
	int upper_tex;
	int mid_tex;
	int lower_tex;
	int sector;

	enum { F_X_OFFSET, F_Y_OFFSET, F_UPPER_TEX, F_MID_TEX, F_LOWER_TEX, F_SECTOR };

public:
	SideDef() : x_offset(0), y_offset(0), upper_tex(0), mid_tex(0),
				lower_tex(0), sector(0)
	{ }

	void RawCopy(const SideDef *other)
	{
		x_offset  = other->x_offset;
		y_offset  = other->y_offset;
		upper_tex = other->upper_tex;
		mid_tex   = other->mid_tex;
		lower_tex = other->lower_tex;
		sector    = other->sector;
	}

	const char *UpperTex() const;
	const char *MidTex()   const;
	const char *LowerTex() const;

	Sector *SecRef() const;

	// use new_tex when >= 0, otherwise use default_wall_tex
	void SetDefaults(bool two_sided, int new_tex = -1);
};


class LineDef
{
public:
	int start;
	int end;
	int right;
	int left;

	int flags;
	int type;
	int tag;

	// Hexen stuff  [NOTE: tag is 'arg1']
	int arg2;
	int arg3;
	int arg4;
	int arg5;

	enum { F_START, F_END, F_RIGHT, F_LEFT,
	       F_FLAGS, F_TYPE, F_TAG,
		   F_ARG2, F_ARG3, F_ARG4, F_ARG5 };

public:
	LineDef() : start(0), end(0), right(-1), left(-1),
				flags(0), type(0), tag(0),
				arg2(0), arg3(0), arg4(0), arg5(0)
	{ }

	void RawCopy(const LineDef *other)
	{
		start = other->start;
		end   = other->end;
		right = other->right;
		left  = other->left;
		flags = other->flags;

		type  = other->type;
		tag   = other->tag;   // arg1
		arg2  = other->arg2;
		arg3  = other->arg3;
		arg4  = other->arg4;
		arg5  = other->arg5;
	}

	Vertex *Start() const;
	Vertex *End()   const;

	// remember: these two can return NULL!
	SideDef *Right() const;
	SideDef *Left()  const;

	bool TouchesVertex(int v_num) const
	{
		return (start == v_num) || (end == v_num);
	}

	bool TouchesCoord(fixcoord_t tx, fixcoord_t ty) const
	{
		return Start()->Matches(tx, ty) || End()->Matches(tx, ty);
	}

	bool TouchesSector(int sec_num) const;

	bool NoSided() const
	{
		return (right < 0) && (left < 0);
	}

	bool OneSided() const
	{
		return (right >= 0) && (left < 0);
	}

	bool TwoSided() const
	{
		return (right >= 0) && (left >= 0);
	}

	// side is either SIDE_LEFT or SIDE_RIGHT
	int WhatSector(int side) const;
	int WhatSideDef(int side) const;

	double CalcLength() const;

	bool IsZeroLength() const
	{
		return (Start()->raw_x == End()->raw_x) && (Start()->raw_y == End()->raw_y);
	}

	bool IsSelfRef() const;

	bool IsHorizontal() const
	{
		return (Start()->raw_y == End()->raw_y);
	}

	bool IsVertical() const
	{
		return (Start()->raw_x == End()->raw_x);
	}

	int Arg(int which /* 1..5 */) const
	{
		if (which == 1) return tag;
		if (which == 2) return arg2;
		if (which == 3) return arg3;
		if (which == 4) return arg4;
		if (which == 5) return arg5;

		return 0;
	}
};


extern std::vector<Thing *>   Things;
extern std::vector<Vertex *>  Vertices;
extern std::vector<Sector *>  Sectors;
extern std::vector<SideDef *> SideDefs;
extern std::vector<LineDef *> LineDefs;

extern std::vector<byte>  HeaderData;
extern std::vector<byte>  BehaviorData;
extern std::vector<byte>  ScriptsData;


#define NumThings     ((int)Things.size())
#define NumVertices   ((int)Vertices.size())
#define NumSectors    ((int)Sectors.size())
#define NumSideDefs   ((int)SideDefs.size())
#define NumLineDefs   ((int)LineDefs.size())

int NumObjects(obj_type_e type);

#define is_thing(n)    ((n) >= 0 && (n) < NumThings  )
#define is_vertex(n)   ((n) >= 0 && (n) < NumVertices)
#define is_sector(n)   ((n) >= 0 && (n) < NumSectors )
#define is_sidedef(n)  ((n) >= 0 && (n) < NumSideDefs)
#define is_linedef(n)  ((n) >= 0 && (n) < NumLineDefs)

const char * NameForObjectType(obj_type_e type, bool plural = false);


/* BASIS API */

// begin a group of operations that will become a single undo/redo
// step.  Any stored _redo_ steps will be forgotten.  The BA_New,
// BA_Delete, BA_Change and BA_Message functions must only be called
// between BA_Begin() and BA_End() pairs.
void BA_Begin();

// finish a group of operations.
void BA_End();

// abort the group of operations -- the undo/redo history is not
// modified and any changes since BA_Begin() are undone except
// when 'keep_changes' is true.
void BA_Abort(bool keep_changes = false);

// assign a message to the current operation.
// this can be called multiple times.
void BA_Message(const char *msg = NULL, ...);

void BA_MessageForSel(const char *verb, selection_c *list, const char *suffix = "");

// create a new object, returning its objnum.  It is safe to
// directly set the new object's fields after calling BA_New().
int BA_New(obj_type_e type);

// deletes the given object, and in certain cases other types of
// objects bound to it (e.g. deleting a vertex will cause all
// bound linedefs to also be deleted).
void BA_Delete(obj_type_e type, int objnum);

// change a field of an existing object.  If the value was the
// same as before, nothing happens and false is returned.
// Otherwise returns true.
bool BA_Change(obj_type_e type, int objnum, byte field, int value);

// attempt to undo the last normal or redo operation.  Returns
// false if the undo history is empty.
bool BA_Undo();

// attempt to re-do the last undo operation.  Returns false if
// there is no stored redo steps.
bool BA_Redo();

// add this string to the basis string table (if it doesn't
// already exist) and return its integer offset.
int BA_InternaliseString(const char *str);
int BA_InternaliseShortStr(const char *str, int max_len);

// get the string from the basis string table.
const char * BA_GetString(int offset);

// clear everything (before loading a new level).
void BA_ClearAll();

// compute a checksum for the current level
void BA_LevelChecksum(crc32_c& crc);


/* HELPERS */

bool BA_ChangeTH(int thing, byte field, int value);
bool BA_ChangeVT(int vert,  byte field, int value);
bool BA_ChangeSEC(int sec,  byte field, int value);
bool BA_ChangeSD(int side,  byte field, int value);
bool BA_ChangeLD(int line,  byte field, int value);
bool BA_ChangeRAD(int rad,  byte field, int value);


#endif  /* __EUREKA_E_BASIS_H__ */

//--- editor settings ---
// vi:ts=4:sw=4:noexpandtab
