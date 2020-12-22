/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:21 by grinko            #+#    #+#             */
/*   Updated: 2020/12/22 16:28:59 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	malloc_interface(t_map *map)
{
	int i;

	i = -1;
	while (++i < 22)
		map->inter_tex[i] = (t_image *)malloc(sizeof(t_image));
	get_inter_textures(map);
	i = 0;
	while (++i < 22)
	{
		map->inter_tex[i]->img = SDL_ConvertSurfaceFormat(map->inter_tex[i]->img, SDL_PIXELFORMAT_BGRA32, 0);
		init_texture(map->inter_tex[i]->img, &(map->inter_tex[i]->s), &(map->inter_tex[i]->pixb), &(map->inter_tex[i]->strb));
		map->inter_tex[i]->active = 0;
	}
	map->inter_tex[3]->active = 1;
	map->inter_tex[6]->active = 1;
}

void	malloc_block_texture(t_map *map)
{
	int i;

	i = -1;
	map->remove = malloc(sizeof(t_removeinfo*)); ///
	map->remove->x = malloc(sizeof(int *) * 10); /// 
	map->remove->y = malloc(sizeof(int *) * 10); ////
	while (++i < 4)
		map->block_tex[i] = (t_image *)malloc(sizeof(t_image));
	get_block_textures(map);
	i = -1;
	while (++i < 4)
	{
		map->block_tex[i]->img = SDL_ConvertSurfaceFormat(map->block_tex[i]->img, SDL_PIXELFORMAT_BGRA32, 0);
		init_texture(map->block_tex[i]->img, &(map->block_tex[i]->s), &(map->block_tex[i]->pixb), &(map->block_tex[i]->strb));
		map->block_tex[i]->active = 0;
	}
}

void	malloc_floorsky_texture(t_map *map)
{
	int i;

	i = -1;
	while (++i < 13)
		map->floorsky_tex[i] = (t_image *)malloc(sizeof(t_image));
	get_floorsky_textures(map);
	i = -1;
	while (++i < 13)
	{
		map->floorsky_tex[i]->img = SDL_ConvertSurfaceFormat(map->floorsky_tex[i]->img, SDL_PIXELFORMAT_BGRA32, 0);
		init_texture(map->floorsky_tex[i]->img, &(map->floorsky_tex[i]->s), &(map->floorsky_tex[i]->pixb), &(map->floorsky_tex[i]->strb));
		map->floorsky_tex[i]->active = 0;
	}
}

void	malloc_wall_texture(t_map *map)
{
	int i;

	i = -1;
	while (++i < 20)
		map->wall_tex[i] = (t_image *)malloc(sizeof(t_image));
	get_wall_textures(map);
	i = -1;
	while (++i < 20)
	{
		map->wall_tex[i]->img = SDL_ConvertSurfaceFormat(map->wall_tex[i]->img, SDL_PIXELFORMAT_BGRA32, 0);
		init_texture(map->wall_tex[i]->img, &(map->wall_tex[i]->s), &(map->wall_tex[i]->pixb), &(map->wall_tex[i]->strb));
		map->wall_tex[i]->active = 0;
	}
}

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
		map->liquid_tex[i]->img = SDL_ConvertSurfaceFormat(map->liquid_tex[i]->img, SDL_PIXELFORMAT_BGRA32, 0);
		init_texture(map->liquid_tex[i]->img, &(map->liquid_tex[i]->s), &(map->liquid_tex[i]->pixb), &(map->liquid_tex[i]->strb));
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
		map->enemy_tex[i]->img = SDL_ConvertSurfaceFormat(map->enemy_tex[i]->img, SDL_PIXELFORMAT_BGRA32, 0);
		init_texture(map->enemy_tex[i]->img, &(map->enemy_tex[i]->s), &(map->enemy_tex[i]->pixb), &(map->enemy_tex[i]->strb));
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
		map->player_tex[i]->img = SDL_ConvertSurfaceFormat(map->player_tex[i]->img, SDL_PIXELFORMAT_BGRA32, 0);
		init_texture(map->player_tex[i]->img, &(map->player_tex[i]->s), &(map->player_tex[i]->pixb), &(map->player_tex[i]->strb));
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
		map->gun_tex[i]->img = SDL_ConvertSurfaceFormat(map->gun_tex[i]->img, SDL_PIXELFORMAT_BGRA32, 0);
		init_texture(map->gun_tex[i]->img, &(map->gun_tex[i]->s), &(map->gun_tex[i]->pixb), &(map->gun_tex[i]->strb));
		map->gun_tex[i]->active = 0;
	}
}

void	malloc_door_texture(t_map *map)
{
	int i;

	i = -1;
	while (++i < 10)
		map->door_tex[i] = (t_image *)malloc(sizeof(t_image));
	get_door_textures(map);
	i = -1;
	while (++i < 10)
	{
		map->door_tex[i]->img = SDL_ConvertSurfaceFormat(map->door_tex[i]->img, SDL_PIXELFORMAT_BGRA32, 0);
		init_texture(map->door_tex[i]->img, &(map->door_tex[i]->s), &(map->door_tex[i]->pixb), &(map->door_tex[i]->strb));
		map->door_tex[i]->active = 0;
	}
}