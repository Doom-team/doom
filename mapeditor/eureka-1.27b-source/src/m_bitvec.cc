//------------------------------------------------------------------------
//  BIT VECTORS
//------------------------------------------------------------------------
//
//  Eureka DOOM Editor
//
//  Copyright (C) 2001-2015 Andrew Apted
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

#include "main.h"

#include "m_bitvec.h"


bitvec_c::bitvec_c(int n_elements) : num_elem(n_elements)
{
	SYS_ASSERT(n_elements > 0);

	int total = (num_elem / 8) + 1;

	d = new byte[total];

	clear_all();
}


bitvec_c::~bitvec_c()
{
	delete[] d;
}


void bitvec_c::resize(int n_elements)
{
	SYS_ASSERT(n_elements > 0);

	int old_elem  = num_elem;
	int old_total = (num_elem / 8) + 1;
	int new_total = (n_elements / 8) + 1;

	byte * old_d = d;

	// don't bother re-allocating unless shrinking by a large amount
	if (num_elem/2 < n_elements && n_elements < num_elem)
	{
		num_elem = n_elements;
		return;
	}

	num_elem = n_elements;

	d = new byte[new_total];

	// copy existing values
	memcpy(d, old_d, MIN(old_total, new_total));

	delete[] old_d;

	if (new_total > old_total)
		memset(d+old_total, 0, new_total - old_total);

	// make sure the bits near the old top are clear
	for (int i = 0 ; i < 8 ; i++)
	{
		if (old_elem + i < num_elem)
			raw_clear(old_elem + i);
	}
}


bool bitvec_c::get(int n) const
{
	SYS_ASSERT(n >= 0);

	if (n >= num_elem)
		return 0;

	return raw_get(n);
}


void bitvec_c::set(int n)
{
	SYS_ASSERT(n >= 0);

	while (n >= num_elem)
	{
		resize(num_elem * 3 / 2 + 16);
	}

	raw_set(n);
}


void bitvec_c::clear(int n)
{
	SYS_ASSERT(n >= 0);

	if (n >= num_elem)
		return;

	raw_clear(n);
}


void bitvec_c::toggle(int n)
{
	if (get(n))
		clear(n);
	else
		set(n);
}


void bitvec_c::frob(int n, sel_op_e op)
{
	switch (op)
	{
		case BOP_ADD: set(n); break;
		case BOP_REMOVE: clear(n); break;
		default: toggle(n); break;
	}
}


void bitvec_c::set_all()
{
	int total = (num_elem / 8) + 1;

	// Note: this will set some extra bits (over num_elem).
	//       the get() functions (etc) make sure to never use them.

	memset(d, 0xFF, total);
}


void bitvec_c::clear_all()
{
	int total = (num_elem / 8) + 1;

	memset(d, 0, total);
}


void bitvec_c::toggle_all()
{
	int total = (num_elem / 8) + 1;

	byte *pos   = d;
	byte *p_end = d + total;

	while (pos < p_end)
		*pos++ ^= 0xFF;
}


//--- editor settings ---
// vi:ts=4:sw=4:noexpandtab
