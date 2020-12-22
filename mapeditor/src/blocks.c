/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:36:42 by grinko            #+#    #+#             */
/*   Updated: 2020/12/22 13:45:40 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

// void remove_square(t_map *map)
// {
// 	find_remove(map, map->remove->x[0], map->remove->y[0]);
// 	find_remove(map, map->remove->x[1], map->remove->y[1]);
// 	find_remove(map, map->remove->x[2], map->remove->y[2]);
// 	find_remove(map, map->remove->x[3], map->remove->y[3]);
// }

// void remove_pentagon(t_map *map)
// {
// 	find_remove(map, map->remove->x[0], map->remove->y[0]);
// 	find_remove(map, map->remove->x[1], map->remove->y[1]);
// 	find_remove(map, map->remove->x[2], map->remove->y[2]);
// 	find_remove(map, map->remove->x[3], map->remove->y[3]);
// 	find_remove(map, map->remove->x[4], map->remove->y[4]);
// }

void remove_blocks(t_map *map)
{
	int i;
	int tmp;

	i = -1;
	if (map->block_tex[0]->active)
		tmp = 4;
	else if (map->block_tex[1]->active)
		tmp = 5;
	else if (map->block_tex[2]->active)
		tmp = 7;
	else if (map->block_tex[3]->active)
		tmp = 8;
	while (++i < tmp)
	{
		//printf("i: %d\n", i);
		//printf("i: %d, x: %d, y: %d\n", i, map->remove->x[i], map->remove->y[i]);
		find_remove(map, map->remove->x[i], map->remove->y[i]);
	}
}


void square(t_map *map, int x, int y)
{
	add_my_node(map, map->remove->x[0] = (x - 25) - map->wclick, map->remove->y[0] =  (y - 25) - map->wclick, (x + 25) + map->wclick, (y - 25) - map->wclick);
	add_my_node(map, map->remove->x[1] =  (x - 25) - map->wclick, map->remove->y[1] = (y - 25) - map->wclick, (x - 25) - map->wclick, (y + 25) + map->wclick);
	add_my_node(map, map->remove->x[2] =  (x + 25) + map->wclick, map->remove->y[2] = (y - 25) - map->wclick, (x + 25) + map->wclick, (y + 25) + map->wclick);
	add_my_node(map, map->remove->x[3] =  (x - 25) - map->wclick, map->remove->y[3] = (y + 25) + map->wclick, (x + 25) + map->wclick, (y + 25) + map->wclick);
}

void pentagon(t_map *map, int x, int y)
{
	add_my_node(map, map->remove->x[0] = (x - 45) - map->wclick, map->remove->y[0] = (y - 25) - map->wclick, x, (y - 75) - map->wclick); ///     ----
	add_my_node(map, map->remove->x[1] = (x - 45) - map->wclick, map->remove->y[1] = (y - 25) - map->wclick, (x - 35) - map->wclick, (y + 25) + map->wclick); ///     ----
	add_my_node(map, map->remove->x[2] = (x - 35) - map->wclick, map->remove->y[2] = (y + 25) + map->wclick, (x + 35) + map->wclick, (y + 25) + map->wclick); ///     ----
	add_my_node(map, map->remove->x[3] = (x + 35) + map->wclick, map->remove->y[3] = (y + 25) + map->wclick, (x + 45) + map->wclick, (y - 25) - map->wclick); ///     ----
	add_my_node(map, map->remove->x[4] = (x + 45) + map->wclick, map->remove->y[4] = (y - 25) - map->wclick, x, (y - 75) - map->wclick); ///     ----

}


void hexagon(t_map *map, int x, int y)
{
	add_my_node(map, map->remove->x[0] = (x - 20) - map->wclick, map->remove->y[0] = (y - 50) - map->wclick, (x + 20) + map->wclick, (y - 50) - map->wclick); ///     ----
	add_my_node(map, map->remove->x[1] = (x - 50) - map->wclick, map->remove->y[1] = y, (x - 20) - map->wclick, (y - 50) - map->wclick); /// /
	add_my_node(map, map->remove->x[2] = (x - 50) - map->wclick, map->remove->y[2] = y , (x - 20) - map->wclick, (y + 50) + map->wclick); //  \         //
	add_my_node(map, map->remove->x[3] = (x + 50) + map->wclick, map->remove->y[3] = y, (x + 20) + map->wclick, (y - 50) - map->wclick); //            \ //
	add_my_node(map, map->remove->x[4] = (x + 50) + map->wclick, map->remove->y[4] = y, (x + 20) + map->wclick, (y + 50) + map->wclick); //            /
	add_my_node(map, map->remove->x[5] = (x - 20) - map->wclick, map->remove->y[5] = (y + 50) + map->wclick, (x + 20) + map->wclick, (y + 50) + map->wclick); /// 	----
}

void octagon(t_map *map, int x, int y)
{
	add_my_node(map, map->remove->x[0] = (x - 30) - map->wclick, map->remove->y[0] = (y - 50) - map->wclick, (x + 30) + map->wclick, (y - 50) - map->wclick); ///     ----
	add_my_node(map, map->remove->x[1] = (x - 50) - map->wclick, map->remove->y[1] = (y - 25) - map->wclick, (x - 30) - map->wclick, (y - 50) - map->wclick); ///     /
	add_my_node(map, map->remove->x[2] = (x - 50) - map->wclick, map->remove->y[2] = (y - 25) - map->wclick, (x - 50) - map->wclick, (y + 25) + map->wclick); ///     |
	add_my_node(map, map->remove->x[3] = (x - 50) - map->wclick, map->remove->y[3] = (y + 25) + map->wclick, (x - 30) - map->wclick, (y + 50) + map->wclick); ///     \ //

	add_my_node(map, map->remove->x[4] = (x - 30) - map->wclick, map->remove->y[4] = (y + 50) + map->wclick, (x + 30) + map->wclick, (y + 50) + map->wclick);//        ----
	add_my_node(map, map->remove->x[5] = (x + 30) + map->wclick, map->remove->y[5] = (y - 50) - map->wclick, (x + 50) + map->wclick, (y - 25) - map->wclick); ///     \ //
	add_my_node(map, map->remove->x[6] = (x + 50) + map->wclick, map->remove->y[6] = (y - 25) - map->wclick, (x + 50) + map->wclick, (y + 25) + map->wclick); ///     |
	add_my_node(map, map->remove->x[7] = (x + 50) + map->wclick, map->remove->y[7] = (y + 25) + map->wclick, (x + 30) + map->wclick, (y + 50) + map->wclick); ///     /
}


void add_my_node(t_map *map, int x1, int y1, int x2, int y2)
{
	t_nod *n;
	t_nod *cur;

	n = n_cr(x1 - map->z_x, y1 - map->z_y, x2 - map->z_x, y2 - map->z_y);
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