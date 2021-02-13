/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_texture1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:21 by grinko            #+#    #+#             */
/*   Updated: 2021/02/13 20:22:59 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	malloc_interface(t_map *map)
{
	int				i;

	i = -1;
	while (++i < 22)
	{
		map->inter_tex[i] = (t_image *)malloc(sizeof(t_image));
		if (!map->inter_tex[i])
			error("Malloc Error");
	}
	get_inter_textures(map);
	i = 0;
	while (++i < 22)
	{
		init_texture(map->inter_tex[i]->img, &(map->inter_tex[i]->s),
			&(map->inter_tex[i]->pixb), &(map->inter_tex[i]->strb));
		map->inter_tex[i]->active = 0;
	}
	map->inter_tex[3]->active = 1;
	map->inter_tex[6]->active = 1;
}

void	malloc_block_texture(t_map *map)
{
	int i;

	i = -1;
	while (++i < 9)
	{
		map->block_tex[i] = (t_image *)malloc(sizeof(t_image));
		if (!map->block_tex[i])
			error("Malloc Error");
	}
	get_block_textures(map);
	i = -1;
	while (++i < 9)
	{
		init_texture(map->block_tex[i]->img, &(map->block_tex[i]->s),
			&(map->block_tex[i]->pixb), &(map->block_tex[i]->strb));
		map->block_tex[i]->active = 0;
	}
}

void	malloc_floorsky_texture(t_map *map)
{
	int i;

	i = -1;
	while (++i < 13)
	{
		map->floorsky_tex[i] = (t_image *)malloc(sizeof(t_image));
		if (!map->floorsky_tex[i])
			error("Malloc Error");
	}
	get_floorsky_textures(map);
	i = -1;
	while (++i < 13)
	{
		init_texture(map->floorsky_tex[i]->img, &(map->floorsky_tex[i]->s),
			&(map->floorsky_tex[i]->pixb), &(map->floorsky_tex[i]->strb));
		map->floorsky_tex[i]->active = 0;
	}
}

void	malloc_wall_texture(t_map *map)
{
	int i;

	i = -1;
	while (++i < 20)
	{
		map->wall_tex[i] = (t_image *)malloc(sizeof(t_image));
		if (!map->wall_tex[i])
			error("Malloc Error");
	}
	get_wall_textures(map);
	i = -1;
	while (++i < 20)
	{
		init_texture(map->wall_tex[i]->img, &(map->wall_tex[i]->s),
			&(map->wall_tex[i]->pixb), &(map->wall_tex[i]->strb));
		map->wall_tex[i]->active = 0;
	}
}

void	find_removestair(t_map *map, int x, int y)
{
	t_nod *tmp;
	t_nod *tmp2;
	t_nod *first;

	tmp = map->tmpnod;
	first = map->tmpnod;
	while (tmp)
	{
		if (((tmp->x1 == x) && (tmp->y1 == y)) ||
		((tmp->x2 == x) && (tmp->y2 == y)))
		{
			tmp2 = tmp;
			tmp = tmp->nxt;
			if (lstdelone(&map->tmpnod, tmp2))
				map->tmpnod = NULL;
		}
		else
			tmp = tmp->nxt;
	}
}
