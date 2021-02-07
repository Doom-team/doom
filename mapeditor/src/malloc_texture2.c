/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_texture2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gordey <gordey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:21 by grinko            #+#    #+#             */
/*   Updated: 2021/02/07 20:55:49 by gordey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	malloc_liquid_texture(t_map *map)
{
	int i;

	i = -1;
	while (++i < 4)
		map->liquid_tex[i] = (t_image *)malloc(sizeof(t_image));
	get_liquid_textures(map);
	i = -1;
	while (++i < 4)
	{
		map->liquid_tex[i]->img = SDL_ConvertSurfaceFormat(
			map->liquid_tex[i]->img, SDL_PIXELFORMAT_BGRA32, 0);
		init_texture(map->liquid_tex[i]->img, &(map->liquid_tex[i]->s),
			&(map->liquid_tex[i]->pixb), &(map->liquid_tex[i]->strb));
		map->liquid_tex[i]->active = 0;
	}
}

void	malloc_enemy_texture(t_map *map)
{
	int i;

	i = -1;
	while (++i < 5)
		map->enemy_tex[i] = (t_image *)malloc(sizeof(t_image));
	get_enemy_textures(map);
	i = -1;
	while (++i < 5)
	{
		map->enemy_tex[i]->img = SDL_ConvertSurfaceFormat(
			map->enemy_tex[i]->img, SDL_PIXELFORMAT_BGRA32, 0);
		init_texture(map->enemy_tex[i]->img, &(map->enemy_tex[i]->s),
			&(map->enemy_tex[i]->pixb), &(map->enemy_tex[i]->strb));
		map->enemy_tex[i]->active = 0;
	}
}

void	malloc_player_texture(t_map *map)
{
	int i;

	i = -1;
	while (++i < 3)
		map->player_tex[i] = (t_image *)malloc(sizeof(t_image));
	get_player_textures(map);
	i = -1;
	while (++i < 3)
	{
		map->player_tex[i]->img = SDL_ConvertSurfaceFormat(
			map->player_tex[i]->img, SDL_PIXELFORMAT_BGRA32, 0);
		init_texture(map->player_tex[i]->img, &(map->player_tex[i]->s),
			&(map->player_tex[i]->pixb), &(map->player_tex[i]->strb));
		map->player_tex[i]->active = 0;
	}
}

void	malloc_gun_texture(t_map *map)
{
	int i;

	i = -1;
	while (++i < 6)
		map->gun_tex[i] = (t_image *)malloc(sizeof(t_image));
	get_gun_textures(map);
	i = -1;
	while (++i < 6)
	{
		map->gun_tex[i]->img = SDL_ConvertSurfaceFormat(
			map->gun_tex[i]->img, SDL_PIXELFORMAT_BGRA32, 0);
		init_texture(map->gun_tex[i]->img, &(map->gun_tex[i]->s),
			&(map->gun_tex[i]->pixb), &(map->gun_tex[i]->strb));
		map->gun_tex[i]->active = 0;
	}
}

void	malloc_door_texture(t_map *map)
{
	int i;

	i = -1;
	while (++i < 11)
		map->door_tex[i] = (t_image *)malloc(sizeof(t_image));
	get_door_textures(map);
	i = -1;
	while (++i < 11)
	{
		map->door_tex[i]->img = SDL_ConvertSurfaceFormat(
			map->door_tex[i]->img, SDL_PIXELFORMAT_BGRA32, 0);
		init_texture(map->door_tex[i]->img, &(map->door_tex[i]->s),
			&(map->door_tex[i]->pixb), &(map->door_tex[i]->strb));
		map->door_tex[i]->active = 0;
	}
}
