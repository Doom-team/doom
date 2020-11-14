//------------------------------------------------------------------------
//  WAD Reading / Writing
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

#include "main.h"

#include <algorithm>

#include "lib_adler.h"
#include "w_rawdef.h"
#include "w_wad.h"


Wad_file * game_wad;
Wad_file * edit_wad;

std::vector<Wad_file *> master_dir;

// UDMF support is unfinished and hence disabled by default.
bool udmf_testing = false;


#define MAX_LUMPS_IN_A_LEVEL	21


//------------------------------------------------------------------------
//  LUMP Handling
//------------------------------------------------------------------------

Lump_c::Lump_c(Wad_file *_par, const char *_nam, int _start, int _len) :
	parent(_par), l_start(_start), l_length(_len)
{
	name = StringDup(_nam);

	SYS_ASSERT(name);

	// ensure lump name is uppercase
	y_strupr((char *)name);
}


Lump_c::Lump_c(Wad_file *_par, const struct raw_wad_entry_s *entry) :
	parent(_par)
{
	// handle the entry name, which can lack a terminating NUL
	char buffer[10];
	strncpy(buffer, entry->name, 8);
	buffer[8] = 0;

	name = StringDup(buffer);

	l_start  = LE_U32(entry->pos);
	l_length = LE_U32(entry->size);

//	DebugPrintf("new lump '%s' @ %d len:%d\n", name, l_start, l_length);

	if (l_length == 0)
		l_start = 0;
}


Lump_c::~Lump_c()
{
	StringFree(name);
}


void Lump_c::MakeEntry(struct raw_wad_entry_s *entry)
{
	W_StoreString(entry->name, name, sizeof(entry->name));

	entry->pos  = LE_U32(l_start);
	entry->size = LE_U32(l_length);
}


void Lump_c::Rename(const char *new_name)
{
	StringFree(name);

	name = StringDup(new_name);
	SYS_ASSERT(name);

	// ensure lump name is uppercase
	y_strupr((char *)name);
}


bool Lump_c::Seek(int offset)
{
	SYS_ASSERT(offset >= 0);

	return (fseek(parent->fp, l_start + offset, SEEK_SET) == 0);
}


bool Lump_c::Read(void *data, int len)
{
	SYS_ASSERT(data && len > 0);

	return (fread(data, len, 1, parent->fp) == 1);
}


bool Lump_c::GetLine(char *buffer, size_t buf_size)
{
	int cur_pos = (int)ftell(parent->fp);

	if (cur_pos < 0)
		return false;

	cur_pos -= l_start;

	if (cur_pos >= l_length)
		return false;  // EOF

	char *dest = buffer;
	char *dest_end = buffer + buf_size - 1;

	for (; cur_pos < l_length && dest < dest_end ; cur_pos++)
	{
		*dest++ = fgetc(parent->fp);

		if (dest[-1] == '\n')
			break;

		if (ferror(parent->fp))
			return false;

		if (feof(parent->fp))
			break;
	}

	*dest = 0;

	return true;  // OK
}


bool Lump_c::Write(const void *data, int len)
{
	SYS_ASSERT(data && len > 0);

	l_length += len;

	return (fwrite(data, len, 1, parent->fp) == 1);
}


void Lump_c::Printf(const char *msg, ...)
{
	static char buffer[FL_PATH_MAX];

	va_list args;

	va_start(args, msg);
	vsnprintf(buffer, sizeof(buffer), msg, args);
	va_end(args);

	buffer[sizeof(buffer) - 1] = 0;

	Write(buffer, (int)strlen(buffer));
}


bool Lump_c::Finish()
{
	if (l_length == 0)
		l_start = 0;

	return parent->FinishLump(l_length);
}


//------------------------------------------------------------------------
//  WAD Reading Interface
//------------------------------------------------------------------------

Wad_file::Wad_file(const char *_name, char _mode, FILE * _fp) :
	mode(_mode), fp(_fp), kind('P'),
	total_size(0), directory(),
	dir_start(0), dir_count(0), dir_crc(0),
	levels(), patches(), sprites(), flats(), tx_tex(),
	begun_write(false), insert_point(-1)
{
	filename = StringDup(_name);
}

Wad_file::~Wad_file()
{
	LogPrintf("Closing WAD file: %s\n", filename);

	fclose(fp);

	// free the directory
	for (short k = 0 ; k < NumLumps() ; k++)
		delete directory[k];

	directory.clear();

	StringFree(filename);
}


Wad_file * Wad_file::Open(const char *filename, char mode)
{
	SYS_ASSERT(mode == 'r' || mode == 'w' || mode == 'a');

	if (mode == 'w')
		return Create(filename, mode);

	LogPrintf("Opening WAD file: %s\n", filename);

	FILE *fp = NULL;

retry:
	fp = fopen(filename, (mode == 'r' ? "rb" : "r+b"));

	if (! fp)
	{
		// mimic the fopen() semantics
		if (mode == 'a' && errno == ENOENT)
			return Create(filename, mode);

		// if file is read-only, open in 'r' mode instead
		if (mode == 'a' && (errno == EACCES || errno == EROFS))
		{
			LogPrintf("Open r/w failed, trying again in read mode...\n");
			mode = 'r';
			goto retry;
		}

		int what = errno;
		LogPrintf("Open failed: %s\n", strerror(what));
		return NULL;
	}

	Wad_file *w = new Wad_file(filename, mode, fp);

	// determine total size (seek to end)
	if (fseek(fp, 0, SEEK_END) != 0)
		FatalError("Error determining WAD size.\n");

	w->total_size = (int)ftell(fp);

	DebugPrintf("total_size = %d\n", w->total_size);

	if (w->total_size < 0)
		FatalError("Error determining WAD size.\n");

	if (! w->ReadDirectory())
	{
		delete w;
		LogPrintf("Open wad failed (reading directory)\n");
		return NULL;
	}

	w->DetectLevels();
	w->ProcessNamespaces();

	return w;
}


Wad_file * Wad_file::Create(const char *filename, char mode)
{
	LogPrintf("Creating new WAD file: %s\n", filename);

	FILE *fp = fopen(filename, "w+b");
	if (! fp)
		return NULL;

	Wad_file *w = new Wad_file(filename, mode, fp);

	// write out base header
	raw_wad_header_t header;

	memset(&header, 0, sizeof(header));
	memcpy(header.ident, "PWAD", 4);

	fwrite(&header, sizeof(header), 1, fp);
	fflush(fp);

	w->total_size = (int)sizeof(header);

	return w;
}


bool Wad_file::Validate(const char *filename)
{
	FILE *fp = fopen(filename, "rb");

	if (! fp)
		return false;

	raw_wad_header_t header;

	if (fread(&header, sizeof(header), 1, fp) != 1)
	{
		fclose(fp);
		return false;
	}

	if (! ( header.ident[1] == 'W' &&
			header.ident[2] == 'A' &&
			header.ident[3] == 'D'))
	{
		fclose(fp);
		return false;
	}

	fclose(fp);

	return true;  // OK
}


static int WhatLevelPart(const char *name)
{
	if (y_stricmp(name, "THINGS")   == 0) return 1;
	if (y_stricmp(name, "LINEDEFS") == 0) return 2;
	if (y_stricmp(name, "SIDEDEFS") == 0) return 3;
	if (y_stricmp(name, "VERTEXES") == 0) return 4;
	if (y_stricmp(name, "SECTORS")  == 0) return 5;

	return 0;
}

static bool IsLevelLump(const char *name)
{
	if (y_stricmp(name, "SEGS")     == 0) return true;
	if (y_stricmp(name, "SSECTORS") == 0) return true;
	if (y_stricmp(name, "NODES")    == 0) return true;
	if (y_stricmp(name, "REJECT")   == 0) return true;
	if (y_stricmp(name, "BLOCKMAP") == 0) return true;
	if (y_stricmp(name, "BEHAVIOR") == 0) return true;
	if (y_stricmp(name, "SCRIPTS")  == 0) return true;

	return WhatLevelPart(name) != 0;
}

static bool IsGLNodeLump(const char *name)
{
	if (y_strnicmp(name, "GL_", 3) == 0 ) return true;

	return false;
}


Lump_c * Wad_file::GetLump(short index)
{
	SYS_ASSERT(0 <= index && index < NumLumps());
	SYS_ASSERT(directory[index]);

	return directory[index];
}


Lump_c * Wad_file::FindLump(const char *name)
{
	for (short k = 0 ; k < NumLumps() ; k++)
		if (y_stricmp(directory[k]->name, name) == 0)
			return directory[k];

	return NULL;  // not found
}

short Wad_file::FindLumpNum(const char *name)
{
	for (short k = 0 ; k < NumLumps() ; k++)
		if (y_stricmp(directory[k]->name, name) == 0)
			return k;

	return -1;  // not found
}


short Wad_file::LevelLookupLump(short lev_num, const char *name)
{
	short start = LevelHeader(lev_num);

	// determine how far past the level marker (MAP01 etc) to search
	short finish = LevelLastLump(lev_num);

	for (short k = start+1 ; k <= finish ; k++)
	{
		SYS_ASSERT(0 <= k && k < NumLumps());

		if (y_stricmp(directory[k]->name, name) == 0)
			return k;
	}

	return -1;  // not found
}


short Wad_file::LevelFind(const char *name)
{
	for (short k = 0 ; k < (int)levels.size() ; k++)
	{
		short index = levels[k];

		SYS_ASSERT(0 <= index && index < NumLumps());
		SYS_ASSERT(directory[index]);

		if (y_stricmp(directory[index]->name, name) == 0)
			return k;
	}

	return -1;  // not found
}


short Wad_file::LevelLastLump(short lev_num)
{
	short start = LevelHeader(lev_num);

	int count = 1;

	// UDMF level?
	if (y_stricmp(directory[start+1]->name, "TEXTMAP") == 0)
	{
		while (count < MAX_LUMPS_IN_A_LEVEL && start+count < NumLumps())
		{
			if (y_stricmp(directory[start+count]->name, "ENDMAP") == 0)
			{
				count++;
				break;
			}

			count++;
		}

		return start + count - 1;
	}

	// standard DOOM or HEXEN format
	while (count < MAX_LUMPS_IN_A_LEVEL &&
		   start+count < NumLumps() &&
		   (IsLevelLump(directory[start+count]->name) ||
		    IsGLNodeLump(directory[start+count]->name)) )
	{
		count++;
	}

	return start + count - 1;
}


short Wad_file::LevelFindByNumber(int number)
{
	// sanity check
	if (number <= 0 || number > 99)
		return -1;

	char buffer[16];
	short index;

	 // try MAP## first
	snprintf(buffer, sizeof(buffer), "MAP%02d", number);

	index = LevelFind(buffer);
	if (index >= 0)
		return index;

	// otherwise try E#M#
	snprintf(buffer, sizeof(buffer), "E%dM%d", MAX(1, number / 10), number % 10);

	index = LevelFind(buffer);
	if (index >= 0)
		return index;

	return -1;  // not found
}


short Wad_file::LevelFindFirst()
{
	if (levels.size() > 0)
		return 0;
	else
		return -1;  // none
}


short Wad_file::LevelHeader(short lev_num)
{
	SYS_ASSERT(0 <= lev_num && lev_num < LevelCount());

	return levels[lev_num];
}


map_format_e Wad_file::LevelFormat(short lev_num)
{
	int start = LevelHeader(lev_num);

	if (y_stricmp(directory[start+1]->name, "TEXTMAP") == 0)
		return MAPF_UDMF;

	if (start + LL_BEHAVIOR < (int)NumLumps())
	{
		const char *name = GetLump(start + LL_BEHAVIOR)->Name();

		if (y_stricmp(name, "BEHAVIOR") == 0)
			return MAPF_Hexen;
	}

	return MAPF_Doom;
}


Lump_c * Wad_file::FindLumpInNamespace(const char *name, char group)
{
	short k;

	switch (group)
	{
		case 'P':
			for (k = 0 ; k < (short)patches.size() ; k++)
				if (y_stricmp(directory[patches[k]]->name, name) == 0)
					return directory[patches[k]];
			break;

		case 'S':
			for (k = 0 ; k < (short)sprites.size() ; k++)
				if (y_stricmp(directory[sprites[k]]->name, name) == 0)
					return directory[sprites[k]];
			break;

		case 'F':
			for (k = 0 ; k < (short)flats.size() ; k++)
				if (y_stricmp(directory[flats[k]]->name, name) == 0)
					return directory[flats[k]];
			break;

		default:
			BugError("FindLumpInNamespace: bad group '%c'\n", group);
	}

	return NULL; // not found!
}


bool Wad_file::ReadDirectory()
{
	rewind(fp);

	raw_wad_header_t header;

	if (fread(&header, sizeof(header), 1, fp) != 1)
	{
		LogPrintf("Error reading WAD header.\n");
		return false;
	}

	kind = header.ident[0];

	dir_start = LE_S32(header.dir_start);
	dir_count = LE_S32(header.num_entries);

	if (dir_count < 0 || dir_count > 32000)
	{
		LogPrintf("Bad WAD header, too many entries (%d)\n", dir_count);
		return false;
	}

	crc32_c checksum;

	if (fseek(fp, dir_start, SEEK_SET) != 0)
	{
		LogPrintf("Error seeking to WAD directory.\n");
		return false;
	}

	for (short i = 0 ; i < dir_count ; i++)
	{
		raw_wad_entry_t entry;

		if (fread(&entry, sizeof(entry), 1, fp) != 1)
		{
			LogPrintf("Error reading entry in WAD directory.\n");
			return false;
		}

		// update the checksum with each _RAW_ entry
		checksum.AddBlock((u8_t *) &entry, sizeof(entry));

		Lump_c *lump = new Lump_c(this, &entry);

		// check if entry is valid
		// [ the total_size value was computed in parent function ]
		if (lump->l_length != 0)
		{
			const int max_size = 99999999;

			if (lump->l_length < 0 || lump->l_start < 0 ||
				lump->l_length >= max_size ||
				lump->l_start > total_size ||
				lump->l_start + lump->l_length > total_size)
			{
				LogPrintf("WARNING: clearing lump '%s' with invalid position (%d+%d > %d)\n",
						lump->name, lump->l_start, lump->l_length, total_size);

				lump->l_start = 0;
				lump->l_length = 0;
			}
		}

		directory.push_back(lump);
	}

	dir_crc = checksum.raw;

	DebugPrintf("Loaded directory. crc = %08x\n", dir_crc);
	return true;
}


void Wad_file::DetectLevels()
{
	// Determine what lumps in the wad are level markers, based on
	// the lumps which follow it.  Store the result in the 'levels'
	// vector.  The test here is rather lax, as I'm told certain
	// wads exist with a non-standard ordering of level lumps.

	for (short k = 0 ; k+1 < NumLumps() ; k++)
	{
		int part_mask  = 0;
		int part_count = 0;

		// check for UDMF levels
		if (udmf_testing && y_stricmp(directory[k+1]->name, "TEXTMAP") == 0)
		{
			levels.push_back(k);
			DebugPrintf("Detected level : %s (UDMF)\n", directory[k]->name);
			continue;
		}

		// check whether the next four lumps are level lumps
		for (short i = 1 ; i <= 4 ; i++)
		{
			if (k+i >= NumLumps())
				break;

			int part = WhatLevelPart(directory[k+i]->name);

			if (part == 0)
				break;

			// do not allow duplicates
			if (part_mask & (1 << part))
				break;

			part_mask |= (1 << part);
			part_count++;
		}

		if (part_count == 4)
		{
			levels.push_back(k);

			DebugPrintf("Detected level : %s\n", directory[k]->name);
		}
	}

	// sort levels into alphabetical order
	// (mainly for the 'N' next map and 'P' prev map commands)

	SortLevels();
}


void Wad_file::SortLevels()
{
	std::sort(levels.begin(), levels.end(), level_name_CMP_pred(this));
}


static bool IsDummyMarker(const char *name)
{
	// matches P1_START, F3_END etc...

	if (strlen(name) < 3)
		return false;

	if (! strchr("PSF", toupper(name[0])))
		return false;

	if (! isdigit(name[1]))
		return false;

	if (y_stricmp(name+2, "_START") == 0 ||
	    y_stricmp(name+2, "_END") == 0)
		return true;

	return false;
}


void Wad_file::ProcessNamespaces()
{
	char active = 0;

	for (short k = 0 ; k < NumLumps() ; k++)
	{
		const char *name = directory[k]->name;

		// skip the sub-namespace markers
		if (IsDummyMarker(name))
			continue;

		if (y_stricmp(name, "P_START") == 0 || y_stricmp(name, "PP_START") == 0)
		{
			if (active && active != 'P')
				LogPrintf("WARNING: missing %c_END marker.\n", active);

			active = 'P';
			continue;
		}
		else if (y_stricmp(name, "P_END") == 0 || y_stricmp(name, "PP_END") == 0)
		{
			if (active != 'P')
				LogPrintf("WARNING: stray P_END marker found.\n");

			active = 0;
			continue;
		}

		if (y_stricmp(name, "S_START") == 0 || y_stricmp(name, "SS_START") == 0)
		{
			if (active && active != 'S')
				LogPrintf("WARNING: missing %c_END marker.\n", active);

			active = 'S';
			continue;
		}
		else if (y_stricmp(name, "S_END") == 0 || y_stricmp(name, "SS_END") == 0)
		{
			if (active != 'S')
				LogPrintf("WARNING: stray S_END marker found.\n");

			active = 0;
			continue;
		}

		if (y_stricmp(name, "F_START") == 0 || y_stricmp(name, "FF_START") == 0)
		{
			if (active && active != 'F')
				LogPrintf("WARNING: missing %c_END marker.\n", active);

			active = 'F';
			continue;
		}
		else if (y_stricmp(name, "F_END") == 0 || y_stricmp(name, "FF_END") == 0)
		{
			if (active != 'F')
				LogPrintf("WARNING: stray F_END marker found.\n");

			active = 0;
			continue;
		}

		if (y_stricmp(name, "TX_START") == 0)
		{
			if (active && active != 'T')
				LogPrintf("WARNING: missing %c_END marker.\n", active);

			active = 'T';
			continue;
		}
		else if (y_stricmp(name, "TX_END") == 0)
		{
			if (active != 'T')
				LogPrintf("WARNING: stray TX_END marker found.\n");

			active = 0;
			continue;
		}

		if (active)
		{
			if (directory[k]->Length() == 0)
			{
				LogPrintf("WARNING: skipping empty lump %s in %c_START\n",
						  name, active);
				continue;
			}

//			DebugPrintf("Namespace %c lump : %s\n", active, name);

			switch (active)
			{
				case 'P': patches.push_back(k); break;
				case 'S': sprites.push_back(k); break;
				case 'F': flats.  push_back(k); break;
				case 'T': tx_tex. push_back(k); break;

				default:
					BugError("ProcessNamespaces: active = 0x%02x\n", (int)active);
			}
		}
	}

	if (active)
		LogPrintf("WARNING: Missing %c_END marker (at EOF)\n", active);
}


bool Wad_file::WasExternallyModified()
{
	if (fseek(fp, 0, SEEK_END) != 0)
		FatalError("Error determining WAD size.\n");

	if (total_size != (int)ftell(fp))
		return true;

	rewind(fp);

	raw_wad_header_t header;

	if (fread(&header, sizeof(header), 1, fp) != 1)
		FatalError("Error reading WAD header.\n");

	if (dir_start != LE_S32(header.dir_start) ||
		dir_count != LE_S32(header.num_entries))
		return true;

	fseek(fp, dir_start, SEEK_SET);

	crc32_c checksum;

	for (short i = 0 ; i < dir_count ; i++)
	{
		raw_wad_entry_t entry;

		if (fread(&entry, sizeof(entry), 1, fp) != 1)
			FatalError("Error reading WAD directory.\n");

		checksum.AddBlock((u8_t *) &entry, sizeof(entry));

	}

	DebugPrintf("New CRC : %08x\n", checksum.raw);

	return (dir_crc != checksum.raw);
}


//------------------------------------------------------------------------
//  WAD Writing Interface
//------------------------------------------------------------------------

void Wad_file::BeginWrite()
{
	if (mode == 'r')
		BugError("Wad_file::BeginWrite() called on read-only file\n");

	if (begun_write)
		BugError("Wad_file::BeginWrite() called again without EndWrite()\n");

	// put the size into a quantum state
	total_size = 0;

	begun_write = true;
}


void Wad_file::EndWrite()
{
	if (! begun_write)
		BugError("Wad_file::EndWrite() called without BeginWrite()\n");

	begun_write = false;

	WriteDirectory();

	// reset the insertion point
	insert_point = -1;
}


void Wad_file::RenameLump(short index, const char *new_name)
{
	SYS_ASSERT(begun_write);
	SYS_ASSERT(0 <= index && index < NumLumps());

	Lump_c *lump = directory[index];
	SYS_ASSERT(lump);

	lump->Rename(new_name);
}


void Wad_file::RemoveLumps(short index, short count)
{
	SYS_ASSERT(begun_write);
	SYS_ASSERT(0 <= index && index < NumLumps());
	SYS_ASSERT(directory[index]);

	short i;

	for (i = 0 ; i < count ; i++)
	{
		delete directory[index + i];
	}

	for (i = index ; i+count < NumLumps() ; i++)
		directory[i] = directory[i+count];

	directory.resize(directory.size() - (size_t)count);

	// fix various arrays containing lump indices
	FixGroup(levels,  index, 0, count);
	FixGroup(patches, index, 0, count);
	FixGroup(sprites, index, 0, count);
	FixGroup(flats,   index, 0, count);
	FixGroup(tx_tex,  index, 0, count);

	// reset the insertion point
	insert_point = -1;
}


void Wad_file::RemoveLevel(short lev_num)
{
	SYS_ASSERT(begun_write);
	SYS_ASSERT(0 <= lev_num && lev_num < LevelCount());

	short start  = LevelHeader(lev_num);
	short finish = LevelLastLump(lev_num);

	// NOTE: FixGroup() will remove the entry in levels[]

	RemoveLumps(start, finish - start + 1);
}


void Wad_file::RemoveGLNodes(short lev_num)
{
	SYS_ASSERT(begun_write);
	SYS_ASSERT(0 <= lev_num && lev_num < LevelCount());

	short start  = LevelHeader(lev_num);
	short finish = LevelLastLump(lev_num);

	start++;

	while (start <= finish &&
		   IsLevelLump(directory[start]->name))
	{
		start++;
	}

	short count = 0;

	while (start+count <= finish &&
		   IsGLNodeLump(directory[start+count]->name))
	{
		count++;
	}

	if (count > 0)
		RemoveLumps(start, count);
}


void Wad_file::RemoveZNodes(short lev_num)
{
	SYS_ASSERT(begun_write);
	SYS_ASSERT(0 <= lev_num && lev_num < LevelCount());

	short start  = LevelHeader(lev_num);
	short finish = LevelLastLump(lev_num);

	for ( ; start <= finish ; start++)
	{
		if (y_stricmp(directory[start]->name, "ZNODES") == 0)
		{
			RemoveLumps(start, 1);
			break;
		}
	}
}


void Wad_file::FixGroup(std::vector<short>& group, short index,
                        short num_added, short num_removed)
{
	bool did_remove = false;

	for (short k = 0 ; k < (short)group.size() ; k++)
	{
		if (group[k] < index)
			continue;

		if (group[k] < index + num_removed)
		{
			group[k] = -1;
			did_remove = true;
			continue;
		}

		group[k] += num_added;
		group[k] -= num_removed;
	}

	if (did_remove)
	{
		std::vector<short>::iterator ENDP;
		ENDP = std::remove(group.begin(), group.end(), (short)-1);
		group.erase(ENDP, group.end());
	}
}


Lump_c * Wad_file::AddLump(const char *name, int max_size)
{
	SYS_ASSERT(begun_write);

	begun_max_size = max_size;

	int start = PositionForWrite(max_size);

	Lump_c *lump = new Lump_c(this, name, start, 0);

	// check if the insert_point is still valid
	if (insert_point >= NumLumps())
		insert_point = -1;

	if (insert_point >= 0)
	{
		// fix various arrays containing lump indices
		FixGroup(levels,  insert_point, 1, 0);
		FixGroup(patches, insert_point, 1, 0);
		FixGroup(sprites, insert_point, 1, 0);
		FixGroup(flats,   insert_point, 1, 0);
		FixGroup(tx_tex,  insert_point, 1, 0);

		directory.insert(directory.begin() + insert_point, lump);

		insert_point++;
	}
	else  // add to end
	{
		directory.push_back(lump);
	}

	return lump;
}


void Wad_file::RecreateLump(Lump_c *lump, int max_size)
{
	SYS_ASSERT(begun_write);

	begun_max_size = max_size;

	int start = PositionForWrite(max_size);

	lump->l_start  = start;
	lump->l_length = 0;
}


Lump_c * Wad_file::AddLevel(const char *name, int max_size, short *lev_num)
{
	int actual_point = insert_point;

	if (actual_point < 0 || actual_point > NumLumps())
		actual_point = NumLumps();

	Lump_c * lump = AddLump(name, max_size);

	if (lev_num)
	{
		*lev_num = (short)levels.size();
	}

	levels.push_back(actual_point);

	return lump;
}


void Wad_file::InsertPoint(short index)
{
	// this is validated on usage
	insert_point = index;
}


int Wad_file::HighWaterMark()
{
	int offset = (int)sizeof(raw_wad_header_t);

	for (short k = 0 ; k < NumLumps() ; k++)
	{
		Lump_c *lump = directory[k];

		// ignore zero-length lumps (their offset could be anything)
		if (lump->Length() <= 0)
			continue;

		int l_end = lump->l_start + lump->l_length;

		l_end = ((l_end + 3) / 4) * 4;

		if (offset < l_end)
			offset = l_end;
	}

	return offset;
}


int Wad_file::FindFreeSpace(int length)
{
	length = ((length + 3) / 4) * 4;

	// collect non-zero length lumps and sort by their offset
	std::vector<Lump_c *> sorted_dir;

	for (short k = 0 ; k < NumLumps() ; k++)
	{
		Lump_c *lump = directory[k];

		if (lump->Length() > 0)
			sorted_dir.push_back(lump);
	}

	std::sort(sorted_dir.begin(), sorted_dir.end(), Lump_c::offset_CMP_pred());


	int offset = (int)sizeof(raw_wad_header_t);

	for (unsigned int k = 0 ; k < sorted_dir.size() ; k++)
	{
		Lump_c *lump = sorted_dir[k];

		int l_start = lump->l_start;
		int l_end   = lump->l_start + lump->l_length;

		l_end = ((l_end + 3) / 4) * 4;

		if (l_end <= offset)
			continue;

		if (l_start >= offset + length)
			continue;

		// the lump overlapped the current gap, so bump offset

		offset = l_end;
	}

	return offset;
}


int Wad_file::PositionForWrite(int max_size)
{
	int want_pos;

	if (max_size <= 0)
		want_pos = HighWaterMark();
	else
		want_pos = FindFreeSpace(max_size);

	// determine if position is past end of file
	// (difference should only be a few bytes)
	//
	// Note: doing this for every new lump may be a little expensive,
	//       but trying to optimise it away will just make the code
	//       needlessly complex and hard to follow.

	if (fseek(fp, 0, SEEK_END) < 0)
		FatalError("Error seeking to new write position.\n");

	total_size = (int)ftell(fp);

	if (total_size < 0)
		FatalError("Error seeking to new write position.\n");

	if (want_pos > total_size)
	{
		if (want_pos >= total_size + 8)
			FatalError("Internal Error: lump positions are beyond end of file\n(%d > %d)\n",
				want_pos, total_size);

		WritePadding(want_pos - total_size);
	}
	else if (want_pos == total_size)
	{
		/* ready to write */
	}
	else
	{
		if (fseek(fp, want_pos, SEEK_SET) < 0)
			FatalError("Error seeking to new write position.\n");
	}

	DebugPrintf("POSITION FOR WRITE: %d  (total_size %d)\n", want_pos, total_size);

	return want_pos;
}


bool Wad_file::FinishLump(int final_size)
{
	fflush(fp);

	// sanity check
	if (begun_max_size >= 0)
		if (final_size > begun_max_size)
			BugError("Internal Error: wrote too much in lump (%d > %d)\n",
					 final_size, begun_max_size);

	int pos = (int)ftell(fp);

	if (pos & 3)
	{
		WritePadding(4 - (pos & 3));
	}

	fflush(fp);
	return true;
}


int Wad_file::WritePadding(int count)
{
	static byte zeros[8] = { 0,0,0,0,0,0,0,0 };

	SYS_ASSERT(1 <= count && count <= 8);

	fwrite(zeros, count, 1, fp);

	return count;
}


//
// IDEA : Truncate file to "total_size" after writing the directory.
//
//        On Linux / MacOSX, this can be done as follows:
//                 - fflush(fp)   -- ensure STDIO has empty buffers
//                 - ftruncate(fileno(fp), total_size);
//                 - freopen(fp)
//
//        On Windows:
//                 - instead of ftruncate, use _chsize() or _chsize_s()
//                   [ investigate what the difference is.... ]
//


void Wad_file::WriteDirectory()
{
	dir_start = PositionForWrite();
	dir_count = NumLumps();

	DebugPrintf("WriteDirectory...\n");
	DebugPrintf("dir_start:%d  dir_count:%d\n", dir_start, dir_count);

	crc32_c checksum;

	for (short k = 0 ; k < dir_count ; k++)
	{
		Lump_c *lump = directory[k];
		SYS_ASSERT(lump);

		raw_wad_entry_t entry;

		lump->MakeEntry(&entry);

		// update the CRC
		checksum.AddBlock((u8_t *) &entry, sizeof(entry));

		if (fwrite(&entry, sizeof(entry), 1, fp) != 1)
			FatalError("Error writing WAD directory.\n");
	}

	dir_crc = checksum.raw;
	DebugPrintf("dir_crc: %08x\n", dir_crc);

	fflush(fp);

	total_size = (int)ftell(fp);
	DebugPrintf("total_size: %d\n", total_size);

	if (total_size < 0)
		FatalError("Error determining WAD size.\n");

	// update header at start of file

	rewind(fp);

	raw_wad_header_t header;

	memcpy(header.ident, (kind == 'I') ? "IWAD" : "PWAD", 4);

	header.dir_start   = LE_U32(dir_start);
	header.num_entries = LE_U32(dir_count);

	if (fwrite(&header, sizeof(header), 1, fp) != 1)
		FatalError("Error writing WAD header.\n");

	fflush(fp);
}


bool Wad_file::Backup(const char *new_filename)
{
	fflush(fp);

	return FileCopy(PathName(), new_filename);
}


//------------------------------------------------------------------------
//  GLOBAL API
//------------------------------------------------------------------------


Lump_c * W_FindLump(const char *name)
{
	for (short i = (int)master_dir.size()-1 ; i >= 0 ; i--)
	{
		Lump_c *L = master_dir[i]->FindLump(name);
		if (L)
			return L;
	}

	return NULL;  // not found
}


Lump_c * W_FindSpriteLump(const char *name)
{
	for (short i = (int)master_dir.size()-1 ; i >= 0 ; i--)
	{
		Lump_c *L = master_dir[i]->FindLumpInNamespace(name, 'S');
		if (L)
			return L;
	}

	return NULL;  // not found
}


Lump_c * W_FindPatchLump(const char *name)
{
	for (short i = (int)master_dir.size()-1 ; i >= 0 ; i--)
	{
		Lump_c *L = master_dir[i]->FindLumpInNamespace(name, 'P');
		if (L)
			return L;
	}

	// Fallback: try free-standing lumps
	Lump_c *L = W_FindLump(name);

	// TODO: verify lump is OK (size etc)
	if (L)
		return L;

	return NULL;  // not found
}


int W_LoadLumpData(Lump_c *lump, byte ** buf_ptr)
{
	// include an extra byte, used to NUL-terminate a text buffer
	*buf_ptr = new byte[lump->Length() + 1];

	if (lump->Length() > 0)
	{
		if (! lump->Seek() ||
			! lump->Read(*buf_ptr, lump->Length()))
			FatalError("W_LoadLumpData: read error loading lump.\n");
	}

	(*buf_ptr)[lump->Length()] = 0;

	return lump->Length();
}


void W_FreeLumpData(byte ** buf_ptr)
{
	if (*buf_ptr)
	{
		delete[] *buf_ptr;
		*buf_ptr = NULL;
	}
}


//------------------------------------------------------------------------

void MasterDir_Add(Wad_file *wad)
{
	DebugPrintf("MasterDir: adding '%s'\n", wad->PathName());

	master_dir.push_back(wad);
}


void MasterDir_Remove(Wad_file *wad)
{
	DebugPrintf("MasterDir: removing '%s'\n", wad->PathName());

	std::vector<Wad_file *>::iterator ENDP;

	ENDP = std::remove(master_dir.begin(), master_dir.end(), wad);

	master_dir.erase(ENDP, master_dir.end());
}


void MasterDir_CloseAll()
{
	while (master_dir.size() > 0)
	{
		Wad_file *wad = master_dir.back();

		master_dir.pop_back();

		delete wad;
	}
}


int W_FilenameAbsCompare(const char *A, const char *B)
{
	static char A_buffer[FL_PATH_MAX];
	static char B_buffer[FL_PATH_MAX];

	fl_filename_absolute(A_buffer, sizeof(A_buffer), A);
	fl_filename_absolute(B_buffer, sizeof(B_buffer), B);

	return y_stricmp(A_buffer, B_buffer);
}


void W_StoreString(char *buf, const char *str, size_t buflen)
{
	memset(buf, 0, buflen);

	for (size_t i = 0 ; i < buflen && str[i] ; i++)
		buf[i] = str[i];
}


bool MasterDir_HaveFilename(const char *chk_path)
{
	for (unsigned int k = 0 ; k < master_dir.size() ; k++)
	{
		const char *wad_path = master_dir[k]->PathName();

		if (W_FilenameAbsCompare(wad_path, chk_path) == 0)
			return true;
	}

	return false;
}


//--- editor settings ---
// vi:ts=4:sw=4:noexpandtab
