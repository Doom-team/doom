/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 20:27:45 by grinko            #+#    #+#             */
/*   Updated: 2021/02/12 08:30:29 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	one_n(t_map *map, t_color color)
{
	map->tem->i = map->tem->x1;
	map->tem->j = map->tem->y1;
	map->tem->di = (map->tem->x2 - map->tem->x1) / map->tem->dx;
	map->tem->diry = map->tem->y2 - map->tem->y1;
	map->tem->de = map->tem->dy + 1;
	if (map->tem->diry > 0)
		map->tem->diry = 1;
	if (map->tem->diry < 0)
		map->tem->diry = -1;
	while (map->tem->i != map->tem->x2)
	{
		draw_gr(map, map->tem->i, map->tem->j, color);
		map->tem->er += map->tem->de;
		if (map->tem->er >= map->tem->dx + 1)
		{
			map->tem->j += map->tem->diry;
			map->tem->er = map->tem->er - (map->tem->dx + 1);
		}
		map->tem->i += map->tem->di;
	}
}

void	draw_node(t_map *map, t_nod *n)
{
	zerotem(map);
	if (n)
	{
		map->tem->x1 = n->x1;
		map->tem->x2 = n->x2;
		if (map->tem->x1 < 0 && map->tem->x2 < 0)
			return ;
		map->tem->y1 = n->y1;
		map->tem->y2 = n->y2;
		map->tem->dx = abs(map->tem->x1 - map->tem->x2);
		map->tem->dy = abs(map->tem->y1 - map->tem->y2);
		map->tem->er = 0;
		map->tem->de = map->tem->dy + 1;
		map->tem->j = map->tem->y1;
		map->tem->i = map->tem->x1;
		map->tem->di = 0;
		if (map->tem->dx > map->tem->dy)
			one_n(map, GREEN);
		else if (map->tem->dy != 0)
			two_n(map, GREEN);
		bigdot(map, map->tem->x1, map->tem->y1, RED);
		bigdot(map, map->tem->x2, map->tem->y2, RED);
	}
}

void	draw_nodes(t_map *map)
{
	t_nod	*n;
	t_nod	*tmpn;
	int		i;

	i = -1;
	n = map->nod;
	tmpn = map->tmpnod;
	if (!n && !tmpn)
		return ;
	while (n)
	{
		if (map->inter_tex[6]->active)
			n->texture->type_name = "w";
		draw_node(map, n);
		n = n->nxt;
	}
	while (tmpn)
	{
		if (map->inter_tex[6]->active)
			tmpn->texture->type_name = "w";
		draw_node(map, tmpn);
		tmpn = tmpn->nxt;
	}
	while (++i <= map->objnum)
		bigdot(map, map->dots.x[i], map->dots.y[i], BLUE);
}

void	find_help(t_nod *nod, t_info *inf, int *x, int *y)
{
	if (abs((nod->x1) - *x) < 10 && abs((nod->y1) - *y) < 10)
	{
		inf->h = sq(*x, *y, nod->x1, nod->y1);
		if (inf->h < inf->w)
		{
			inf->w = inf->h;
			inf->x = nod->x1;
			inf->y = nod->y1;
		}
	}
	if (abs((nod->x2) - *x) < 10 && abs((nod->y2) - *y) < 10)
	{
		inf->h = sq(*x, *y, nod->x2, nod->y2);
		if (inf->h < inf->w)
		{
			inf->w = inf->h;
			inf->x = nod->x2;
			inf->y = nod->y2;
		}
	}
}

void	find_coord(t_map *map, int *x, int *y)
{
	t_info	*inf;
	t_nod	*nod;

	nod = map->nod;
	if (!nod)
		return ;
	if (!(inf = malloc(sizeof(inf))))
		error(ERM);
	inf->x = *x + 10;
	inf->y = *y + 10;
	inf->w = 200;
	while (nod)
	{
		find_help(nod, inf, x, y);
		nod = nod->nxt;
	}
	if (inf->w < 200)
	{
		*x = inf->x;
		*y = inf->y;
	}
	free(inf);
}
