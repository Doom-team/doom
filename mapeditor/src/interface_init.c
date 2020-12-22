/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:13 by grinko            #+#    #+#             */
/*   Updated: 2020/12/22 16:29:54 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void init_texture(SDL_Surface *tex, unsigned char **s, unsigned char *pixb, int *strb)
{
	*s = (unsigned char*)(tex->pixels);
	*pixb = (tex->format->BytesPerPixel);
	*strb = (tex->pitch);
}

int		init_all(t_map *map)
{
	int i;

	i = -1;
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
	if (!(map->win = SDL_CreateWindow("Mapeditor", 200, 200, WIDTH, HEIGHT, SDL_WINDOW_SHOWN)))
		return (0);
	init_interface(map);
	map->z_x = WIDTH / 2;
	map->z_y = HEIGHT / 2;
	map->click = 0;
	map->nod = NULL;
	map->wclick = 25;
	map->whclick = 5;
	map->tmpclick = 0;
	map->showactive = 0;

	map->change_x = 0;
	map->change_y = 0;
	// map->change_plus = 0;
	map->index_tex = -1;
	map->validflag = 0;
	map->index_wall = -1;
	map->floor_x = -1;
	map->floor_y = -1;
	map->tmpfloor_x = -1;
	map->tmpfloor_y = -1;
	map->floorstr = malloc(sizeof(char **) * 10);
	map->ceilingstr = malloc(sizeof(char **) * 10);
	while (++i < 9)
	{
		map->floorstr[i] = NULL;
		map->ceilingstr[i] = NULL;
	}
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