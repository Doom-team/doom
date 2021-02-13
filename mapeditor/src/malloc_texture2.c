/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_texture2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:21 by grinko            #+#    #+#             */
/*   Updated: 2021/02/13 16:04:31 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	malloc_liquid_texture(t_map *map)
{
	int i;

	i = -1;
	while (++i < 4)
	{
		map->liquid_tex[i] = (t_image *)malloc(sizeof(t_image));
		if (!map->liquid_tex[i])
			error("Malloc Error");
	}
	get_liquid_textures(map);
	i = -1;
	while (++i < 4)
	{
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
	{
		map->enemy_tex[i] = (t_image *)malloc(sizeof(t_image));
		if (!map->enemy_tex[i])
			error("Malloc Error");
	}
	get_enemy_textures(map);
	i = -1;
	while (++i < 5)
	{
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
	{
		map->player_tex[i] = (t_image *)malloc(sizeof(t_image));
		if (!map->player_tex[i])
			error("Malloc Error");
	}
	get_player_textures(map);
	i = -1;
	while (++i < 3)
	{
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
	{
		map->gun_tex[i] = (t_image *)malloc(sizeof(t_image));
		if (!map->gun_tex[i])
			error("Malloc Error");
	}
	get_gun_textures(map);
	i = -1;
	while (++i < 6)
	{
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
	{
		map->door_tex[i] = (t_image *)malloc(sizeof(t_image));
		if (!map->door_tex[i])
			error("Malloc Error");
	}
	get_door_textures(map);
	i = -1;
	while (++i < 11)
	{
		init_texture(map->door_tex[i]->img, &(map->door_tex[i]->s),
			&(map->door_tex[i]->pixb), &(map->door_tex[i]->strb));
		map->door_tex[i]->active = 0;
	}
}
