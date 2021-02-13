/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:36:42 by grinko            #+#    #+#             */
/*   Updated: 2021/02/13 17:30:49 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	octagon(t_map *map, int x, int y)
{
	add_my_node(map, &(t_info){map->remove->x[0] = (x - 30) - map->wclick,
		map->remove->y[0] = (y - 50) - map->wclick,
			(x + 30) + map->wclick, (y - 50) - map->wclick}, 0);
	add_my_node(map, &(t_info){map->remove->x[1] = (x - 50) - map->wclick,
		map->remove->y[1] = (y - 25) - map->wclick,
			(x - 30) - map->wclick, (y - 50) - map->wclick}, 0);
	add_my_node(map, &(t_info){map->remove->x[2] = (x - 50) - map->wclick,
		map->remove->y[2] = (y - 25) - map->wclick,
			(x - 50) - map->wclick, (y + 25) + map->wclick}, 0);
	add_my_node(map, &(t_info){map->remove->x[3] = (x - 50) - map->wclick,
		map->remove->y[3] = (y + 25) + map->wclick,
			(x - 30) - map->wclick, (y + 50) + map->wclick}, 0);
	add_my_node(map, &(t_info){map->remove->x[4] = (x - 30) - map->wclick,
		map->remove->y[4] = (y + 50) + map->wclick,
			(x + 30) + map->wclick, (y + 50) + map->wclick}, 0);
	add_my_node(map, &(t_info){map->remove->x[5] = (x + 30) + map->wclick,
		map->remove->y[5] = (y - 50) - map->wclick,
			(x + 50) + map->wclick, (y - 25) - map->wclick}, 0);
	add_my_node(map, &(t_info){map->remove->x[6] = (x + 50) + map->wclick,
		map->remove->y[6] = (y - 25) - map->wclick,
			(x + 50) + map->wclick, (y + 25) + map->wclick}, 0);
	add_my_node(map, &(t_info){map->remove->x[7] = (x + 50) + map->wclick,
		map->remove->y[7] = (y + 25) + map->wclick,
			(x + 30) + map->wclick, (y + 50) + map->wclick}, 0);
}

void	admn(t_map *map, t_nod *n, t_nod *cur)
{
	n->index = nod_len(map->nod);
	n->wallh = map->whclick;
	if (map->nod == NULL)
	{
		map->nod = n;
		return ;
	}
	else
	{
		cur = map->nod;
		while (cur->nxt)
			cur = cur->nxt;
		cur->nxt = n;
	}
}

void	add_my_node(t_map *map, t_info *info, int type)
{
	t_nod *n;
	t_nod *cur;

	n = n_cr(&(t_info){info->x, info->y, info->w, info->h}, type);
	if (type)
	{
		n->index = nod_len(map->tmpnod);
		n->wallh = map->whclick;
		if (map->tmpnod == NULL)
		{
			map->tmpnod = n;
			return ;
		}
		else
		{
			cur = map->tmpnod;
			while (cur->nxt)
				cur = cur->nxt;
			cur->nxt = n;
		}
	}
	else
		admn(map, n, cur);
}

void	made_blocks(t_map *map, int x, int y)
{
	if (map->block_tex[0]->active)
		square(map, x, y);
	if (map->block_tex[1]->active)
		pentagon(map, x, y);
	if (map->block_tex[2]->active)
		hexagon(map, x, y);
	if (map->block_tex[3]->active)
		octagon(map, x, y);
}
