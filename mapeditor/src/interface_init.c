/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:13 by grinko            #+#    #+#             */
/*   Updated: 2021/02/13 16:02:35 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	init_texture(SDL_Surface *tex, unsigned char **s,
						unsigned char *pixb, int *strb)
{
	*s = (unsigned char*)(tex->pixels);
	*pixb = (tex->format->BytesPerPixel);
	*strb = (tex->pitch);
}

void	errors_init(t_map *map)
{
	map->remove = malloc(sizeof(t_removeinfo*));
	map->remove->x = malloc(sizeof(int *));
	map->remove->y = malloc(sizeof(int *));
	if (!map->music[0] || !map->music[1] || !map->music[2] || !map->music[3] ||
		!map->fontclasic || !map->fontdoom || !map->remove || !map->remove->x ||
		!map->remove->y)
		error("Init Error!");
}

void	init_all2(t_map *map)
{
	map->objnum = 0;
	map->plus_objects = 0;
	if (!(map->font = (t_image *)malloc(sizeof(t_image))))
		error("ERM!");
	if (!(map->tem = malloc(sizeof(t_tempnod))))
		error("ERM!");
	if (!(map->ha = malloc(sizeof(t_shit))))
		error("ERM!");
	map->stirsgroup = 1;
	map->floorstr = NULL;
	map->ceilingstr = NULL;
	map->objects = NULL;
	map->stairsoutput = NULL;
	map->stairstr = NULL;
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	map->musicflag = 0;
	map->musicoutput = 0;
	map->music[0] = Mix_LoadMUS("../textures/music/m1.mp3");
	map->music[1] = Mix_LoadMUS("../textures/music/m2.mp3");
	map->music[2] = Mix_LoadMUS("../textures/music/m3.mp3");
	map->music[3] = Mix_LoadMUS("../textures/music/m4.mp3");
	map->fontclasic = TTF_OpenFont("/textures/fonts/classic.ttf", 32);
	map->fontdoom = TTF_OpenFont("/textures/fonts/doom.ttf", 32);
	errors_init(map);
}

int		init_all(t_map *map)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	if (TTF_Init() == -1 || !IMG_Init(IMG_INIT_JPG))
		error("SLD Error");
	if (!(map->win = SDL_CreateWindow("Mapeditor", 200, 200,
		WIDTH, HEIGHT, SDL_WINDOW_SHOWN)))
		error("Window Error!");
	init_interface(map);
	map->click = 0;
	map->nod = NULL;
	map->tmpnod = NULL;
	map->wclick = 25;
	map->whclick = 5;
	map->tmpclick = 0;
	map->stclick = 1;
	map->showactive = 0;
	map->change_x = 0;
	map->change_y = 0;
	map->errorflag = 0;
	map->index_tex = -1;
	map->validflag = 0;
	map->index_wall = -1;
	map->exitflag = 0;
	init_all2(map);
	return (1);
}

void	init_interface(t_map *map)
{
	malloc_interface(map);
	malloc_block_texture(map);
	malloc_wall_texture(map);
	malloc_floorsky_texture(map);
	malloc_liquid_texture(map);
	malloc_player_texture(map);
	malloc_enemy_texture(map);
	malloc_gun_texture(map);
	malloc_door_texture(map);
}
