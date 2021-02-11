/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:13 by grinko            #+#    #+#             */
/*   Updated: 2021/02/11 15:39:34 by grinko           ###   ########.fr       */
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

void	init_all2(t_map *map)
{
	map->tmpfloor_x = -1;
	map->tmpfloor_y = -1;
	map->stirsgroup = 1;
	if (!(map->tem = malloc(sizeof(t_tempnod))))
		error("ERM!");
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
	map->music[2] = Mix_LoadMUS("../textures/music/m1.mp3");
	map->music[3] = Mix_LoadMUS("../textures/music/m2.mp3");
	map->fontclasic = TTF_OpenFont("/textures/fonts/classic.ttf", 32);
	map->fontdoom = TTF_OpenFont("/textures/fonts/doom.ttf", 32);
}

int		init_all(t_map *map)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	if (!(map->win = SDL_CreateWindow("Mapeditor", 200, 200,
		WIDTH, HEIGHT, SDL_WINDOW_SHOWN)))
		error("Window Error!");
	init_interface(map);
	map->click = 0;
	map->nod = NULL;
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
	map->floor_x = -1;
	map->floor_y = -1;
	if (!(map->font = (t_image *)malloc(sizeof(t_image))))
		error("ERM!");
	init_all2(map);
	return (1);
}

void	init_interface(t_map *map)
{
	malloc_interface(map);
	malloc_cursor(map);
	malloc_block_texture(map);
	malloc_wall_texture(map);
	malloc_floorsky_texture(map);
	malloc_liquid_texture(map);
	malloc_player_texture(map);
	malloc_enemy_texture(map);
	malloc_gun_texture(map);
	malloc_door_texture(map);
}
