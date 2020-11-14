//------------------------------------------------------------------------
//  GAME DEFINITION
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

#include <map>
#include <algorithm>

#include "im_color.h"
#include "m_config.h"
#include "m_game.h"
#include "e_things.h"


#define UNKNOWN_THING_RADIUS  16
#define UNKNOWN_THING_COLOR   fl_rgb_color(0,255,255)


misc_info_t      Misc_info;
port_features_t  Features;


// all the game and port definitions and previously loaded
static std::map<std::string, GameInfo_c *> loaded_game_defs;
static std::map<std::string, PortInfo_c *> loaded_port_defs;

// the information being loaded for PURPOSE_GameInfo / PortInfo
// TODO : move into parser_state_c
static GameInfo_c *loading_Game;
static PortInfo_c *loading_Port;


std::map<char, linegroup_t *>    line_groups;
std::map<char, thinggroup_t *>   thing_groups;
std::map<char, texturegroup_t *> texture_groups;

std::map<int, linetype_t *>   line_types;
std::map<int, sectortype_t *> sector_types;
std::map<int, thingtype_t *>  thing_types;

std::map<std::string, char> texture_categories;
std::map<std::string, char> flat_categories;


//
// BOOM Generalized Lines
//
generalized_linetype_t gen_linetypes[MAX_GEN_NUM_TYPES];

int num_gen_linetypes;

// variables which are "set" in def files
static std::map< std::string, std::string > parse_vars;


GameInfo_c::GameInfo_c(std::string _name) :
	name(_name), base_game()
{ }

GameInfo_c::~GameInfo_c()
{ }


PortInfo_c::PortInfo_c(std::string _name) :
	name(_name),
	formats(0),
	supported_games(),
	udmf_namespace()
{ }

PortInfo_c::~PortInfo_c()
{ }

void PortInfo_c::AddSupportedGame(const char *game)
{
	if (! SupportsGame(game))
		supported_games.push_back(std::string(game));
}

bool PortInfo_c::SupportsGame(const char *game) const
{
	for (size_t i = 0 ; i < supported_games.size() ; i++)
		if (y_stricmp(supported_games[i].c_str(), game) == 0)
			return true;

	return false;
}


static void M_FreeAllDefinitions()
{
	// TODO: prevent memory leak, delete contents of these maps

    line_groups.clear();
    line_types.clear();
    sector_types.clear();

    thing_groups.clear();
    thing_types.clear();

	texture_groups.clear();
	texture_categories.clear();
	flat_categories.clear();
}


//
//  this is called each time the full set of definitions
//  (game, port, resource files) are loaded.
//
void M_ClearAllDefinitions()
{
	M_FreeAllDefinitions();

	memset(&Misc_info, 0, sizeof(Misc_info));
	memset(&Features,  0, sizeof(Features));

	Misc_info.player_r = 16;
	Misc_info.player_h = 56;
	Misc_info.view_height = 41;
	Misc_info.min_dm_starts = 4;
	Misc_info.max_dm_starts = 10;

	// reset generalized types
	memset(gen_linetypes, 0, sizeof(gen_linetypes));
	num_gen_linetypes = 0;
}


void M_PrepareConfigVariables()
{
	parse_vars.clear();

	switch (Level_format)
	{
		case MAPF_Doom:
			parse_vars[std::string("$MAP_FORMAT")] = std::string("DOOM");
			break;

		case MAPF_Hexen:
			parse_vars[std::string("$MAP_FORMAT")] = std::string("HEXEN");
			break;

		case MAPF_UDMF:
			parse_vars[std::string("$MAP_FORMAT")] = std::string("UDMF");
			break;

		default: break;
	}

	if (! Udmf_namespace.empty())
	{
		parse_vars[std::string("$UDMF_NAMESPACE")] = Udmf_namespace;
	}

	if (Game_name)
	{
		parse_vars[std::string("$GAME_NAME")] = std::string(Game_name);

		if (M_CanLoadDefinitions("games", Game_name))
		{
			const char *base_game = M_GetBaseGame(Game_name);
			parse_vars[std::string("$BASE_GAME")] = std::string(base_game);
		}
	}

	if (Port_name)
	{
		parse_vars[std::string("$PORT_NAME")] = std::string(Port_name);
	}
}



static short ParseThingdefFlags(const char *s)
{
	short flags = 0;

	if (strchr(s, 'i')) flags |= THINGDEF_INVIS;
	if (strchr(s, 'c')) flags |= THINGDEF_CEIL;
	if (strchr(s, 'l')) flags |= THINGDEF_LIT;
	if (strchr(s, 'n')) flags |= THINGDEF_PASS;
	if (strchr(s, 'v')) flags |= THINGDEF_VOID;
	if (strchr(s, 't')) flags |= THINGDEF_TELEPT;

	return flags;
}


static void ParseColorDef(char ** argv, int argc)
{
	if (y_stricmp(argv[0], "sky") == 0)
	{
		Misc_info.sky_color = atoi(argv[1]);
	}
	else if (y_stricmp(argv[0], "wall") == 0)
	{
		Misc_info.wall_colors[0] = atoi(argv[1]);
		Misc_info.wall_colors[1] = atoi(argv[(argc < 2) ? 1 : 2]);
	}
	else if (y_stricmp(argv[0], "floor") == 0)
	{
		Misc_info.floor_colors[0] = atoi(argv[1]);
		Misc_info.floor_colors[1] = atoi(argv[(argc < 2) ? 1 : 2]);
	}
	else if (y_stricmp(argv[0], "invis") == 0)
	{
		Misc_info.invis_colors[0] = atoi(argv[1]);
		Misc_info.invis_colors[1] = atoi(argv[(argc < 2) ? 1 : 2]);
	}
	else if (y_stricmp(argv[0], "missing") == 0)
	{
		Misc_info.missing_color = atoi(argv[1]);
	}
	else if (y_stricmp(argv[0], "unknown_tex") == 0)
	{
		Misc_info.unknown_tex = atoi(argv[1]);
	}
	else if (y_stricmp(argv[0], "unknown_flat") == 0)
	{
		Misc_info.unknown_flat = atoi(argv[1]);
	}
	else if (y_stricmp(argv[0], "unknown_thing") == 0)
	{
		Misc_info.unknown_thing = atoi(argv[1]);
	}
	else
	{
		LogPrintf("unknown color keyword: '%s'\n", argv[0]);
	}
}


static map_format_bitset_t ParseMapFormats(char ** argv, int argc)
{
	map_format_bitset_t result = 0;

	for ( ; argc > 0 ; argv++, argc--)
	{
		if (y_stricmp(argv[0], "DOOM") == 0)
			result |= (1 << MAPF_Doom);

		else if (y_stricmp(argv[0], "HEXEN") == 0)
			result |= (1 << MAPF_Hexen);

		else if (y_stricmp(argv[0], "UDMF") == 0)
			result |= (1 << MAPF_UDMF);

		else
			FatalError("Unknown map format '%s' in definition file.\n", argv[0]);
	}

	return result;
}


static void ParseClearKeywords(char ** argv, int argc)
{
	for ( ; argc > 0 ; argv++, argc--)
	{
		if (y_stricmp(argv[0], "lines") == 0)
		{
			line_groups.clear();
			line_types.clear();
		}
		else if (y_stricmp(argv[0], "sectors") == 0)
		{
			sector_types.clear();
		}
		else if (y_stricmp(argv[0], "things") == 0)
		{
			thing_groups.clear();
			thing_types.clear();
		}
		else if (y_stricmp(argv[0], "textures") == 0)
		{
			texture_groups.clear();
			texture_categories.clear();

			flat_categories.clear();
		}
		else
			FatalError("Unknown clear keyword '%s' in definition file.\n", argv[0]);
	}
}


static void ParseFeatureDef(char ** argv, int argc)
{
	if (y_stricmp(argv[0], "gen_types") == 0)
	{
		Features.gen_types = atoi(argv[1]);
	}
	else if (y_stricmp(argv[0], "gen_sectors") == 0)
	{
		Features.gen_sectors = atoi(argv[1]);
	}
	else if (y_stricmp(argv[0], "img_png") == 0)
	{
		Features.img_png = atoi(argv[1]);
	}
	else if (y_stricmp(argv[0], "tx_start") == 0)
	{
		Features.tx_start = atoi(argv[1]);
	}
	else if (y_stricmp(argv[0], "coop_dm_flags") == 0)
	{
		Features.coop_dm_flags = atoi(argv[1]);
	}
	else if (y_stricmp(argv[0], "friend_flag") == 0)
	{
		Features.friend_flag = atoi(argv[1]);
	}
	else if (y_stricmp(argv[0], "pass_through") == 0)
	{
		Features.pass_through = atoi(argv[1]);
	}
	else if (y_stricmp(argv[0], "3d_midtex") == 0)
	{
		Features.midtex_3d = atoi(argv[1]);
	}
	else if (y_stricmp(argv[0], "strife_flags") == 0)
	{
		Features.strife_flags = atoi(argv[1]);
	}
	else if (y_stricmp(argv[0], "medusa_fixed") == 0)
	{
		Features.medusa_fixed = atoi(argv[1]);
	}
	else if (y_stricmp(argv[0], "lax_sprites") == 0)
	{
		Features.lax_sprites = atoi(argv[1]);
	}
	else if (y_stricmp(argv[0], "no_need_players") == 0)
	{
		Features.no_need_players = atoi(argv[1]);
	}
	else if (y_stricmp(argv[0], "tag_666") == 0)
	{
		Features.tag_666 = atoi(argv[1]);
	}
	else if (y_stricmp(argv[0], "mix_textures_flats") == 0)
	{
		Features.mix_textures_flats = atoi(argv[1]);
	}
	else if (y_stricmp(argv[0], "extra_floors") == 0)
	{
		Features.extra_floors = atoi(argv[1]);
	}
	else if (y_stricmp(argv[0], "slopes") == 0)
	{
		Features.slopes = atoi(argv[1]);
	}
	else
	{
		LogPrintf("unknown feature keyword: '%s'\n", argv[0]);
	}
}


static const char * FindDefinitionFile(const char *folder, const char *name)
{
	static char filename[FL_PATH_MAX];

	for (int pass = 0 ; pass < 2 ; pass++)
	{
		const char *base_dir = (pass == 0) ? home_dir : install_dir;

		if (! base_dir)
			continue;

		snprintf(filename, sizeof(filename), "%s/%s/%s.ugh", base_dir, folder, name);

		DebugPrintf("  trying: %s\n", filename);

		if (FileExists(filename))
			return filename;
	}

	return NULL;
}


bool M_CanLoadDefinitions(const char *folder, const char *name)
{
	const char * filename = FindDefinitionFile(folder, name);

	return (filename != NULL);
}


//
// Loads a definition file.  The ".ugh" extension is added.
// Will try the "common" folder if not found in the given one.
//
// Examples: "games" + "doom2"
//           "ports" + "edge"
//
void M_LoadDefinitions(const char *folder, const char *name)
{
	// this is for error messages & debugging
	char prettyname[256];
	snprintf(prettyname, sizeof(prettyname), "%s/%s.ugh", folder, name);

	LogPrintf("Loading Definitions : %s\n", prettyname);

	const char * filename = FindDefinitionFile(folder, name);

	if (! filename)
		FatalError("Cannot find definition file: %s\n", prettyname);

	DebugPrintf("  found at: %s\n", filename);

	M_ParseDefinitionFile(PURPOSE_Normal, filename, folder, prettyname);
}


typedef enum
{
	PCOND_NONE		= 0,
	PCOND_Reading	= 1,
	PCOND_Skipping	= 2

} parsing_condition_e;

typedef struct
{
	parsing_condition_e cond;
	int start_line;

public:
	void Toggle()
	{
		cond = (cond == PCOND_Reading) ? PCOND_Skipping : PCOND_Reading;
	}

} parsing_cond_state_t;


#define MAX_TOKENS  30   /* tokens per line */

#define MAX_INCLUDE_LEVEL  10

class parser_state_c
{
public:
	// current line number
	int lineno;

	// filename for error messages (lacks the directory)
	const char *fname;

	// buffer containing the raw line
	char readbuf [512];

	// buffer storing the tokens
	char tokenbuf[512];

	// the line parsed into tokens
	int    argc;
	char * argv[MAX_TOKENS];

	// state for handling if/else/endif
	std::vector<parsing_cond_state_t> cond_stack;

	// BOOM generalized linedef stuff
	int current_gen_line;

public:
	parser_state_c() :
		lineno(0), fname(NULL), argc(0),
		cond_stack(),
		current_gen_line(-1)
	{
		memset(readbuf, 0, sizeof(readbuf));
		memset(argv,    0, sizeof(argv));
	}

	bool HaveAnySkipping() const
	{
		for (size_t i = 0 ; i < cond_stack.size() ; i++)
			if (cond_stack[i].cond == PCOND_Skipping)
				return true;

		return false;
	}
};


static const char *const bad_arg_count =
		"%s(%d): directive \"%s\" takes %d parameters\n";


static void M_TokenizeLine(parser_state_c *pst)
{
	// break the line into whitespace-separated tokens.
	// whitespace can be enclosed in double quotes.

	const char	*src  = pst->readbuf;
	char		*dest = pst->tokenbuf;

	bool		in_token = false;
	bool		quoted   = false;

	pst->argc = 0;

	for ( ; ; src++)
	{
		if (*src == 0 || *src == '\n')
		{
			if (in_token)
				*dest = 0;
			break;
		}

		if (*src == '"')
		{
			quoted = !quoted;
			continue;
		}

		// found a comment?   [ we allow # in the middle of a token ]
		if (*src == '#' && !in_token && !quoted)
			break;

		// beginning a new token?
		if (!in_token && (quoted || !isspace(*src)))
		{
			if (pst->argc >= MAX_TOKENS)
				FatalError("%s(%d): more than %d tokens on the line\n",
							pst->fname, pst->lineno, MAX_TOKENS);

			in_token = true;

			pst->argv[pst->argc++] = dest;

			*dest++ = *src;
			continue;
		}

		// whitespace will end a token (unless quoted)
		if (isspace(*src) && in_token && !quoted)
		{
			in_token = false;
			*dest++  = 0;
			continue;
		}

		// normal token character?
		if (in_token)
			*dest++ = *src;
	}

	if (quoted)
		FatalError("%s(%d): unmatched double quote\n", pst->fname, pst->lineno);
}


static void M_ParseNormalLine(parser_state_c *pst)
{
	char **argv  = pst->argv;
	int    nargs = pst->argc - 1;


	// these are handled by other passes
	if (y_stricmp(argv[0], "base_game") == 0 ||
		y_stricmp(argv[0], "map_formats") == 0 ||
		y_stricmp(argv[0], "supported_games") == 0 ||
		y_stricmp(argv[0], "udmf_namespace") == 0)
	{
		return;
	}


	if (y_stricmp(argv[0], "player_size") == 0)
	{
		if (nargs != 3)
			FatalError(bad_arg_count, pst->fname, pst->lineno, argv[0], 1);

		Misc_info.player_r    = atoi(argv[1]);
		Misc_info.player_h    = atoi(argv[2]);
		Misc_info.view_height = atoi(argv[3]);
	}
	else if (y_stricmp(argv[0], "sky_color") == 0)  // back compat
	{
		if (nargs != 1)
			FatalError(bad_arg_count, pst->fname, pst->lineno, argv[0], 1);

		Misc_info.sky_color = atoi(argv[1]);
	}
	else if (y_stricmp(argv[0], "sky_flat") == 0)
	{
		if (nargs != 1)
			FatalError(bad_arg_count, pst->fname, pst->lineno, argv[0], 1);

		if (strlen(argv[1]) >= sizeof(Misc_info.sky_flat))
			FatalError("%s(%d): sky_flat name is too long\n", pst->fname, pst->lineno);

		strcpy(Misc_info.sky_flat, argv[1]);
	}
	else if (y_stricmp(argv[0], "color") == 0)
	{
		if (nargs < 2)
			FatalError(bad_arg_count, pst->fname, pst->lineno, argv[0], 2);

		ParseColorDef(pst->argv + 1, nargs);
	}
	else if (y_stricmp(argv[0], "feature") == 0)
	{
		if (nargs < 2)
			FatalError(bad_arg_count, pst->fname, pst->lineno, argv[0], 2);

		ParseFeatureDef(pst->argv + 1, nargs);
	}
	else if (y_stricmp(argv[0], "default_textures") == 0)
	{
		if (nargs != 3)
			FatalError(bad_arg_count, pst->fname, pst->lineno, argv[0], 3);

		default_wall_tex	= StringDup(argv[1]);
		default_floor_tex	= StringDup(argv[2]);
		default_ceil_tex	= StringDup(argv[3]);
	}
	else if (y_stricmp(argv[0], "default_thing") == 0)
	{
		if (nargs != 1)
			FatalError(bad_arg_count, pst->fname, pst->lineno, argv[0], 1);

		default_thing = atoi(argv[1]);
	}
	else if (y_stricmp(argv[0], "linegroup") == 0 ||
			 y_stricmp(argv[0], "spec_group") == 0)
	{
		if (nargs != 2)
			FatalError(bad_arg_count, pst->fname, pst->lineno, argv[0], 2);

		linegroup_t * lg = new linegroup_t;

		lg->group = argv[1][0];
		lg->desc  = StringDup(argv[2]);

		line_groups[lg->group] = lg;
	}

	else if (y_stricmp(argv[0], "line") == 0 ||
			 y_stricmp(argv[0], "special") == 0)
	{
		if (nargs < 3)
			FatalError(bad_arg_count, pst->fname, pst->lineno, argv[0], 3);

		linetype_t * info = new linetype_t;

		memset(info->args, 0, sizeof(info->args));

		int number = atoi(argv[1]);

		info->group = argv[2][0];
		info->desc  = StringDup(argv[3]);

		int arg_count = MIN(nargs - 3, 5);
		for (int i = 0 ; i < arg_count ; i++)
		{
			if (argv[4 + i][0] != '-')
				info->args[i] = StringDup(argv[4 + i]);
		}

		if (line_groups.find( info->group) == line_groups.end())
		{
			LogPrintf("%s(%d): unknown line group '%c'\n",
					pst->fname, pst->lineno,  info->group);
		}
		else
			line_types[number] = info;
	}

	else if (y_stricmp(argv[0], "sector") == 0)
	{
		if (nargs != 2)
			FatalError(bad_arg_count, pst->fname, pst->lineno, argv[0], 2);

		int number = atoi(argv[1]);

		sectortype_t *info = new sectortype_t;

		info->desc = StringDup(argv[2]);

		sector_types[number] = info;
	}

	else if (y_stricmp(argv[0], "thinggroup") == 0)
	{
		if (nargs != 3)
			FatalError(bad_arg_count, pst->fname, pst->lineno, argv[0], 3);

		thinggroup_t * tg = new thinggroup_t;

		tg->group = argv[1][0];
		tg->color = ParseColor(argv[2]);
		tg->desc  = StringDup(argv[3]);

		thing_groups[tg->group] = tg;
	}

	else if (y_stricmp(argv[0], "thing") == 0)
	{
		if (nargs < 6)
			FatalError(bad_arg_count, pst->fname, pst->lineno, argv[0], 6);

		thingtype_t * info = new thingtype_t;

		int number = atoi(argv[1]);

		info->group  = argv[2][0];
		info->flags  = ParseThingdefFlags(argv[3]);
		info->radius = atoi(argv[4]);
		info->sprite = StringDup(argv[5]);
		info->desc   = StringDup(argv[6]);
		info->scale  = (nargs >= 7) ? atof(argv[7]) : 1.0;

		memset(info->args, 0, sizeof(info->args));

		int arg_count = MIN(nargs - 7, 5);
		for (int i = 0 ; i < arg_count ; i++)
		{
			if (argv[8 + i][0] != '-')
				info->args[i] = StringDup(argv[8 + i]);
		}

		if (thing_groups.find(info->group) == thing_groups.end())
		{
			LogPrintf("%s(%d): unknown thing group '%c'\n",
					pst->fname, pst->lineno, info->group);
		}
		else
		{
			info->color = thing_groups[info->group]->color;

			thing_types[number] = info;
		}
	}

	else if (y_stricmp(argv[0], "texturegroup") == 0)
	{
		if (nargs != 2)
			FatalError(bad_arg_count, pst->fname, pst->lineno, argv[0], 2);

		texturegroup_t * tg = new texturegroup_t;

		tg->group = argv[1][0];
		tg->desc  = StringDup(argv[2]);

		texture_groups[tg->group] = tg;
	}

	else if (y_stricmp(argv[0], "texture") == 0)
	{
		if (nargs != 2)
			FatalError(bad_arg_count, pst->fname, pst->lineno, argv[0], 2);

		char group = argv[1][0];
		std::string name = std::string(argv[2]);

		if (texture_groups.find(tolower(group)) == texture_groups.end())
		{
			LogPrintf("%s(%d): unknown texture group '%c'\n",
					  pst->fname, pst->lineno, group);
		}
		else
			texture_categories[name] = group;
	}

	else if (y_stricmp(argv[0], "flat") == 0)
	{
		if (nargs != 2)
			FatalError(bad_arg_count, pst->fname, pst->lineno, argv[0], 2);

		char group = argv[1][0];
		std::string name = std::string(argv[2]);

		if (texture_groups.find(tolower(group)) == texture_groups.end())
		{
			LogPrintf("%s(%d): unknown texture group '%c'\n",
						pst->fname, pst->lineno, group);
		}
		else
			flat_categories[name] = group;
	}

	else if (y_stricmp(argv[0], "gen_line") == 0)
	{
		if (nargs != 4)
			FatalError(bad_arg_count, pst->fname, pst->lineno, argv[0], 4);

		pst->current_gen_line = num_gen_linetypes;
		num_gen_linetypes++;

		if (num_gen_linetypes > MAX_GEN_NUM_TYPES)
			FatalError("%s(%d): too many gen_line definitions\n", pst->fname, pst->lineno);

		generalized_linetype_t *def = &gen_linetypes[pst->current_gen_line];

		def->key = argv[1][0];

		// use strtol() to support "0x" notation
		def->base   = static_cast<int>(strtol(argv[2], NULL, 0));
		def->length = static_cast<int>(strtol(argv[3], NULL, 0));

		def->name = StringDup(argv[4]);
		def->num_fields = 0;
	}

	else if (y_stricmp(argv[0], "gen_field") == 0)
	{
		if (nargs < 5)
			FatalError(bad_arg_count, pst->fname, pst->lineno, argv[0], 5);

		if (pst->current_gen_line < 0)
			FatalError("%s(%d): gen_field used outside of a gen_line definition\n", pst->fname, pst->lineno);

		generalized_linetype_t *def = &gen_linetypes[pst->current_gen_line];

		generalized_field_t *field = &def->fields[def->num_fields];

		def->num_fields++;
		if (def->num_fields > MAX_GEN_NUM_FIELDS)
			FatalError("%s(%d): too many fields in gen_line definition\n", pst->fname, pst->lineno);

		field->bits  = atoi(argv[1]);
		field->shift = atoi(argv[2]);

		field->mask  = ((1 << field->bits) - 1) << field->shift;

		field->default_val = atoi(argv[3]);

		field->name = StringDup(argv[4]);

		// grab the keywords
		field->num_keywords = MIN(nargs - 4, MAX_GEN_FIELD_KEYWORDS);

		for (int i = 0 ; i < field->num_keywords ; i++)
		{
			field->keywords[i] = StringDup(argv[5 + i]);
		}
	}
	else if (y_stricmp(argv[0], "clear") == 0)
	{
		if (nargs < 1)
			FatalError(bad_arg_count, pst->fname, pst->lineno, argv[0], 2);

		ParseClearKeywords(pst->argv + 1, nargs);
	}

/*  FIXME

	else
	{
		FatalError("%s(%d): unknown directive: %.32s\n",
				   pst->fname, pst->lineno, argv[0]);
	}
*/
}


static void M_ParseGameInfoLine(parser_state_c *pst)
{
	char **argv  = pst->argv;
	int    nargs = pst->argc - 1;

	if (y_stricmp(argv[0], "map_formats") == 0 ||
		y_stricmp(argv[0], "supported_games") == 0 ||
		y_stricmp(argv[0], "udmf_namespace") == 0)
	{
		FatalError("%s(%d): %s can only be used in port definitions\n",
			pst->fname, pst->lineno, argv[0]);
	}

	if (y_stricmp(argv[0], "base_game") == 0)
	{
		if (nargs < 1)
			FatalError(bad_arg_count, pst->fname, pst->lineno, argv[0], 1);

		// TODO memory leak
		loading_Game->base_game = StringLower(argv[1]);
	}
}


static void M_ParsePortInfoLine(parser_state_c *pst)
{
	char **argv  = pst->argv;
	int    nargs = pst->argc - 1;

	if (y_stricmp(argv[0], "base_game") == 0)
	{
		FatalError("%s(%d): %s can only be used in game definitions\n",
			pst->fname, pst->lineno, argv[0]);
	}

	if (y_stricmp(argv[0], "supported_games") == 0)
	{
		if (nargs < 1)
			FatalError(bad_arg_count, pst->fname, pst->lineno, argv[0], 1);

		for (argv++ ; nargs > 0 ; argv++, nargs--)
		{
			// TODO memory leak
			loading_Port->AddSupportedGame(StringLower(*argv));
		}
	}
	else if (y_stricmp(argv[0], "map_formats") == 0)
	{
		if (nargs < 1)
			FatalError(bad_arg_count, pst->fname, pst->lineno, argv[0], 1);

		loading_Port->formats = ParseMapFormats(argv + 1, nargs);
	}
	else if (y_stricmp(argv[0], "udmf_namespace") == 0)
	{
		if (nargs != 1)
			FatalError(bad_arg_count, pst->fname, pst->lineno, argv[0], 1);

		// want to preserve the case here
		loading_Port->udmf_namespace = argv[1];
	}
}


static bool M_ParseConditional(parser_state_c *pst)
{
	// returns the result of the "IF" test, true or false.

	char **argv  = pst->argv + 1;
	int    nargs = pst->argc - 1;

	bool op_is  = (nargs >= 3 && y_stricmp(argv[1], "is")  == 0);
	bool op_not = (nargs >= 3 && y_stricmp(argv[1], "not") == 0);

	if (op_is || op_not)
	{
		if (strlen(argv[0]) < 2 || argv[0][0] != '$')
			FatalError("%s(%d): expected variable in if statement\n",
						pst->fname, pst->lineno, argv[2]);

		// tokens are stored in pst->tokenbuf, so this is OK
		y_strupr(argv[0]);

		std::string var_value = parse_vars[std::string(argv[0])];

		// test multiple values, only need one to succeed
		for (int i = 2 ; i < nargs ; i++)
			if (y_stricmp(var_value.c_str(), argv[i]) == 0)
				return op_is;

		return op_not;
	}

	FatalError("%s(%d): syntax error in if statement\n", pst->fname, pst->lineno);
	return false;
}


void M_ParseSetVar(parser_state_c *pst)
{
	char **argv  = pst->argv + 1;
	int    nargs = pst->argc - 1;

	if (nargs != 2)
		FatalError(bad_arg_count, pst->fname, pst->lineno, pst->argv[0], 1);

	if (strlen(argv[0]) < 2 || argv[0][0] != '$')
		FatalError("%s(%d): variable name too short or lacks '$' prefix\n",
					pst->fname, pst->lineno);

	// tokens are stored in pst->tokenbuf, so this is OK
	y_strupr(argv[0]);

	parse_vars[std::string(argv[0])] = std::string(argv[1]);
}


//
//  this is main function for parsing a definition file.
//
//  when purpose is PURPOSE_GameInfo or PURPOSE_PortInfo, then
//  only minimal parsing occurs, in particular the "include", "set"
//  and "if".."endif" directives are NOT handled.
//
void M_ParseDefinitionFile(parse_purpose_e purpose,
						   const char *filename,
						   const char *folder,
						   const char *prettyname,
						   int include_level)
{
	if (! folder)
		folder = "common";

	if (! prettyname)
		prettyname = fl_filename_name(filename);


	parser_state_c parser_state;

	// this is a bit silly, but makes it easier to move code around
	parser_state_c *pst = &parser_state;

	pst->fname = prettyname;


	// read the definition file, line by line

	FILE *fp = fopen(filename, "r");
	if (! fp)
		FatalError("Cannot open %s: %s\n", filename, strerror(errno));

	while (M_ReadTextLine(pst->readbuf, sizeof(pst->readbuf), fp))
	{
		pst->lineno += 1;

		M_TokenizeLine(pst);

		// skip empty lines and comments
		if (pst->argc == 0)
			continue;

		int nargs = pst->argc - 1;


		// handle conditionals: if...else...endif

		if (y_stricmp(pst->argv[0], "if") == 0)
		{
			parsing_cond_state_t cst;

			cst.cond = M_ParseConditional(pst) ? PCOND_Reading : PCOND_Skipping;
			cst.start_line = pst->lineno;

			pst->cond_stack.push_back(cst);
			continue;
		}
		else if (y_stricmp(pst->argv[0], "else") == 0)
		{
			if (pst->cond_stack.empty())
				FatalError("%s(%d): else without if\n", pst->fname, pst->lineno);

			// toggle the mode
			pst->cond_stack.back().Toggle();
			continue;
		}
		else if (y_stricmp(pst->argv[0], "endif") == 0)
		{
			if (pst->cond_stack.empty())
				FatalError("%s(%d): endif without if\n", pst->fname, pst->lineno);

			pst->cond_stack.pop_back();
			continue;
		}


		// skip lines when ANY if statement is in skip mode
		if (pst->HaveAnySkipping())
			continue;


		// handle setting variables
		if (y_stricmp(pst->argv[0], "set") == 0)
		{
			M_ParseSetVar(pst);
			continue;
		}


		// handle includes
		if (y_stricmp(pst->argv[0], "include") == 0)
		{
			if (nargs != 1)
				FatalError(bad_arg_count, pst->fname, pst->lineno, pst->argv[0], 1);

			if (include_level >= MAX_INCLUDE_LEVEL)
				FatalError("%s(%d): Too many includes (check for a loop)\n",
							pst->fname, pst->lineno);

			const char * new_folder = folder;
			const char * new_name = FindDefinitionFile(new_folder, pst->argv[1]);

			// if not found, check the common/ folder
			if (! new_name && strcmp(folder, "common") != 0)
			{
				new_folder = "common";
				new_name = FindDefinitionFile(new_folder, pst->argv[1]);
			}

			if (! new_name)
				FatalError("%s(%d): Cannot find include file: %s.ugh\n",
							pst->fname, pst->lineno, pst->argv[1]);

			M_ParseDefinitionFile(purpose, new_name, new_folder,
								  NULL /* prettyname */,
								  include_level + 1);
			continue;
		}


		if (purpose == PURPOSE_GameInfo)
		{
			M_ParseGameInfoLine(pst);
			continue;
		}
		else if (purpose == PURPOSE_PortInfo)
		{
			M_ParsePortInfoLine(pst);
			continue;
		}


		// handle everything else
		M_ParseNormalLine(pst);
	}

	// check for an unterminated conditional
	if (! pst->cond_stack.empty())
	{
		FatalError("%s(%d): Missing endif statement\n", pst->fname,
			pst->cond_stack.back().start_line);
	}

	fclose(fp);
}


GameInfo_c * M_LoadGameInfo(const char *game)
{
	// already loaded?
	std::map<std::string, GameInfo_c *>::iterator IT;
	IT = loaded_game_defs.find(std::string(game));

	if (IT != loaded_game_defs.end())
		return IT->second;

	const char * filename = FindDefinitionFile("games", game);
	if (! filename)
		return NULL;

	loading_Game = new GameInfo_c(game);

	M_ParseDefinitionFile(PURPOSE_GameInfo, filename, "games", NULL);

	if (loading_Game->base_game.empty())
	{
		FatalError("Game definition for '%s' does not set base_game\n", game);
	}

	loaded_game_defs[game] = loading_Game;
	return loading_Game;
}


PortInfo_c * M_LoadPortInfo(const char *port)
{
	std::map<std::string, PortInfo_c *>::iterator IT;
	IT = loaded_port_defs.find(std::string(port));

	if (IT != loaded_port_defs.end())
		return IT->second;

	const char * filename = FindDefinitionFile("ports", port);
	if (! filename)
		return NULL;

	loading_Port = new PortInfo_c(port);

	M_ParseDefinitionFile(PURPOSE_PortInfo, filename, "ports", NULL);

	// default is to support both Doom and Doom2
	if (loading_Port->supported_games.empty())
	{
		loading_Port->supported_games.push_back(std::string("doom"));
		loading_Port->supported_games.push_back(std::string("doom2"));
	}

	loaded_port_defs[port] = loading_Port;
	return loading_Port;
}


//------------------------------------------------------------------------


static void scanner_add_file(const char *name, int flags, void *priv_dat)
{
	std::vector<const char*> * list = (std::vector<const char*> *) priv_dat;

//	DebugPrintf("  file [%s] flags:%d\n", name, flags);

	if (flags & (SCAN_F_IsDir | SCAN_F_Hidden))
		return;

	if (! MatchExtension(name, "ugh"))
		return;

	list->push_back(ReplaceExtension(name, NULL));
}


struct DefName_CMP_pred
{
	inline bool operator() (const char *A, const char *B) const
	{
		return y_stricmp(A, B) < 0;
	}
};

void M_CollectKnownDefs(const char *folder, std::vector<const char *> & list)
{
	std::vector<const char *> temp_list;

	static char path[FL_PATH_MAX];

//	DebugPrintf("M_CollectKnownDefs for: %d\n", folder);

	snprintf(path, sizeof(path), "%s/%s", install_dir, folder);
	ScanDirectory(path, scanner_add_file, & temp_list);

	snprintf(path, sizeof(path), "%s/%s", home_dir, folder);
	ScanDirectory(path, scanner_add_file, & temp_list);

	std::sort(temp_list.begin(), temp_list.end(), DefName_CMP_pred());

	// transfer to passed list, removing duplicates as we go
	unsigned int pos;

	for (pos = 0 ; pos < temp_list.size() ; pos++)
	{
		if (pos + 1 < temp_list.size() &&
			y_stricmp(temp_list[pos], temp_list[pos + 1]) == 0)
		{
			StringFree(temp_list[pos]);
			continue;
		}

		list.push_back(temp_list[pos]);
	}
}


const char * M_GetBaseGame(const char *game)
{
	GameInfo_c *ginfo = M_LoadGameInfo(game);
	SYS_ASSERT(ginfo);

	return ginfo->base_game.c_str();
}


map_format_bitset_t M_DetermineMapFormats(const char *game, const char *port)
{
	PortInfo_c *pinfo = M_LoadPortInfo(port);
	if (pinfo && pinfo->formats != 0)
		return pinfo->formats;

	// a bit hacky, maybe should do it a better way...
	if (strcmp(game, "hexen") == 0)
		return (1 << MAPF_Hexen);

	return (1 << MAPF_Doom);
}


bool M_CheckPortSupportsGame(const char *base_game, const char *port)
{
	if (strcmp(port, "vanilla") == 0)
	{
		// Vanilla means the engine that comes with the game, hence
		// it supports everything.
		return true;
	}

	PortInfo_c *pinfo = M_LoadPortInfo(port);
	if (! pinfo)
		return false;

	return pinfo->SupportsGame(base_game);
}


// find all the ports which support the given base game..
//
// result will be '|' separated (ready for Fl_Choice::add)
// returns the empty string when nothing found.
// The result should be freed with StringFree().
//
// will also find an existing name, storing its index in 'exist_val'
// (when not found, the value in 'exist_val' is not changed at all)

const char * M_CollectPortsForMenu(const char *base_game, int *exist_val, const char *exist_name)
{
	std::vector<const char *> list;

	M_CollectKnownDefs("ports", list);

	if (list.empty())
		return StringDup("");

	// determine final length
	int length = 2 + (int)list.size();
	unsigned int i;

	for (i = 0 ; i < list.size() ; i++)
		length += strlen(list[i]);

	char * result = StringNew(length);
	result[0] = 0;

	int entry_id = 0;

	for (i = 0 ; i < list.size() ; i++)
	{
		if (! M_CheckPortSupportsGame(base_game, list[i]))
			continue;

		if (result[0])
			strcat(result, "|");

		strcat(result, list[i]);

		if (y_stricmp(list[i], exist_name) == 0)
			*exist_val = entry_id;

		entry_id++;
	}

//	DebugPrintf( "RESULT = '%s'\n", result);

	return result;
}


//------------------------------------------------------------------------


bool is_sky(const char *flat)
{
	return (y_stricmp(Misc_info.sky_flat, flat) == 0);
}

bool is_null_tex(const char *tex)
{
	return tex[0] == '-';
}

bool is_special_tex(const char *tex)
{
	return tex[0] == '#';
}


const sectortype_t * M_GetSectorType(int type)
{
	std::map<int, sectortype_t *>::iterator SI;

	SI = sector_types.find(type);

	if (SI != sector_types.end())
		return SI->second;

	static sectortype_t dummy_type =
	{
		"UNKNOWN TYPE"
	};

	return &dummy_type;
}


const linetype_t * M_GetLineType(int type)
{
	std::map<int, linetype_t *>::iterator LI;

	LI = line_types.find(type);

	if (LI != line_types.end())
		return LI->second;

	static linetype_t dummy_type =
	{
		0, "UNKNOWN TYPE"
	};

	return &dummy_type;
}


const thingtype_t * M_GetThingType(int type)
{
	std::map<int, thingtype_t *>::iterator TI;

	TI = thing_types.find(type);

	if (TI != thing_types.end())
		return TI->second;

	static thingtype_t dummy_type =
	{
		0, 0, UNKNOWN_THING_RADIUS, 1.0f,
		"UNKNOWN TYPE", "NULL",
		UNKNOWN_THING_COLOR
	};

	return &dummy_type;
}


char M_GetTextureType(const char *name)
{
	std::map<std::string, char>::iterator TI;

	TI = texture_categories.find(name);

	if (TI != texture_categories.end())
		return TI->second;

	return '-';  // the OTHER category
}


char M_GetFlatType(const char *name)
{
	std::map<std::string, char>::iterator TI;

	TI = flat_categories.find(name);

	if (TI != flat_categories.end())
		return TI->second;

	return '-';  // the OTHER category
}


static bool LineCategory_IsUsed(char group)
{
	std::map<int, linetype_t *>::iterator IT;

	for (IT = line_types.begin() ; IT != line_types.end() ; IT++)
	{
		linetype_t *info = IT->second;
		if (info->group == group)
			return true;
	}

	return false;
}


static bool ThingCategory_IsUsed(char group)
{
	std::map<int, thingtype_t *>::iterator IT;

	for (IT = thing_types.begin() ; IT != thing_types.end() ; IT++)
	{
		thingtype_t *info = IT->second;
		if (info->group == group)
			return true;
	}

	return false;
}


static bool TextureCategory_IsUsed(char group)
{
	std::map<std::string, char>::iterator IT;

	for (IT = texture_categories.begin() ; IT != texture_categories.end() ; IT++)
		if (IT->second == group)
			return true;

	return false;
}


static bool FlatCategory_IsUsed(char group)
{
	std::map<std::string, char>::iterator IT;

	for (IT = flat_categories.begin() ; IT != flat_categories.end() ; IT++)
		if (IT->second == group)
			return true;

	return false;
}


const char *M_LineCategoryString(char *letters)
{
	static char buffer[2000];

	int L_index = 0;

	// the "ALL" category is always first
	strcpy(buffer, "ALL");
	letters[L_index++] = '*';

	std::map<char, linegroup_t *>::iterator IT;

	for (IT = line_groups.begin() ; IT != line_groups.end() ; IT++)
	{
		linegroup_t *G = IT->second;

		// the "Other" category is always at the end
		if (G->group == '-')
			continue;

		if (! LineCategory_IsUsed(G->group))
			continue;

		// FIXME: potential for buffer overflow here
		strcat(buffer, "|");
		strcat(buffer, G->desc);

		letters[L_index++] = IT->first;
	}

	strcat(buffer, "|Other");

	letters[L_index++] = '-';
	letters[L_index++] = 0;

	return buffer;
}


const char *M_ThingCategoryString(char *letters)
{
	static char buffer[2000];

	int L_index = 0;

	// these common categories are always first
	strcpy(buffer, "ALL|RECENT");
	letters[L_index++] = '*';
	letters[L_index++] = '^';

	std::map<char, thinggroup_t *>::iterator IT;

	for (IT = thing_groups.begin() ; IT != thing_groups.end() ; IT++)
	{
		thinggroup_t *G = IT->second;

		// the "Other" category is always at the end
		if (G->group == '-')
			continue;

		if (! ThingCategory_IsUsed(G->group))
			continue;

		// FIXME: potential for buffer overflow here
		strcat(buffer, "|");
		strcat(buffer, G->desc);

		letters[L_index++] = IT->first;
	}

	strcat(buffer, "|Other");

	letters[L_index++] = '-';
	letters[L_index++] = 0;

	return buffer;
}


const char *M_TextureCategoryString(char *letters, bool do_flats)
{
	static char buffer[2000];

	int L_index = 0;

	// these common categories are always first
	strcpy(buffer, "ALL|RECENT");
	letters[L_index++] = '*';
	letters[L_index++] = '^';

	std::map<char, texturegroup_t *>::iterator IT;

	for (IT = texture_groups.begin() ; IT != texture_groups.end() ; IT++)
	{
		texturegroup_t *G = IT->second;

		// the "Other" category is always at the end
		if (G->group == '-')
			continue;

		if (do_flats && !FlatCategory_IsUsed(G->group))
			continue;

		if (!do_flats && !TextureCategory_IsUsed(G->group))
			continue;

		// FIXME: potential for buffer overflow here
		strcat(buffer, "|");
		strcat(buffer, G->desc);

		letters[L_index++] = IT->first;
	}

	strcat(buffer, "|Other");

	letters[L_index++] = '-';
	letters[L_index++] = 0;

	return buffer;
}


//--- editor settings ---
// vi:ts=4:sw=4:noexpandtab
