/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stairs3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 10:51:15 by grinko            #+#    #+#             */
/*   Updated: 2021/02/12 03:02:11 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	stairarr1(t_map *map, t_info *cor, int i)
{
	if (i == 1)
	{
		map->remove->x[i - 1] = cor->x - map->ha->nx;
		map->remove->y[i - 1] = cor->y - map->ha->ny;
		map->remove->x[i] = cor->x + map->ha->nx;
		map->remove->y[i] = cor->y + map->ha->ny;
		map->remove->x[i + 1] = cor->x - map->ha->nx;
		map->remove->y[i + 1] = cor->y - map->ha->ny;
		map->remove->x[i + 2] = cor->w - map->ha->nx;
		map->remove->y[i + 2] = cor->h - map->ha->ny;
		map->remove->x[i + 3] = cor->x + map->ha->nx;
		map->remove->y[i + 3] = cor->y + map->ha->ny;
		map->remove->x[i + 4] = cor->w + map->ha->nx;
		map->remove->y[i + 4] = cor->h + map->ha->ny;
		map->remove->x[i + 5] = cor->w - map->ha->nx;
		map->remove->y[i + 5] = cor->h - map->ha->ny;
		map->remove->x[i + 6] = cor->w + map->ha->nx;
		map->remove->y[i + 6] = cor->h + map->ha->ny;
	}
	else
		stairarr2(map, cor, i);
}

void	remove_tool(t_map *map, int x, int y)
{
	int x1;
	int y1;

	x1 = x;
	y1 = y;
	find_coord(map, &x1, &y1);
	if (x1 != x || y1 != y)
		find_remove(map, x1, y1);
}

void	lstdelone2(t_nod **fd_lst, t_nod *fd, t_nod *file, t_nod *last)
{
	if (last)
		last->nxt = file->nxt;
	else
		*fd_lst = file->nxt;
	free(file);
}
