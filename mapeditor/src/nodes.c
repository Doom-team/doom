/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 20:27:45 by grinko            #+#    #+#             */
/*   Updated: 2021/02/09 18:41:44 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"
#include <math.h>

int		nod_len(t_nod *nod)
{
	t_nod	*n;
	int		i;

	n = nod;
	i = 0;
	while (n)
	{
		i++;
		n = n->nxt;
	}
	return (i);
}

t_nod	*n_cr(t_info *info, int type)
{
	t_nod *a;

	a = (t_nod*)malloc(sizeof(t_nod));
	a->texture = (t_texinfo*)malloc(sizeof(t_texinfo));
	a->texture->texture_name[0] = malloc(sizeof(char) * 100);
	// a->texture->texture_name[1] = malloc(sizeof(char) * 100);
	// a->texture->floor_name = malloc(sizeof(char) * 100);
	// a->texture->ceiling_name = malloc(sizeof(char) * 100);
	a->texture->type_name = malloc(sizeof(char) * 100);
	a->texture->texture_name[0] = NULL;
	//a->texture->texture_name[1] = NULL;
	//a->texture->floor_name = NULL;
	//a->texture->ceiling_name = NULL;
	a->texture->type_name = NULL;
	a->x1 = info->x;
	a->y1 = info->y;
	a->x2 = info->w;
	a->y2 = info->h;
	a->type = type;
	a->grnum = 0;
	a->nxt = NULL;
	return (a);
}

void	add_node(t_map *map, int x, int y)
{
	t_nod *n;
	t_nod *cur;

	n = n_cr(&(t_info){map->x_c , map->y_c ,
		x , y }, 0);
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
		{
			cur = cur->nxt;
		}
		cur->nxt = n;
	}
}

void	draw_gr(t_map *map, int x, int y, t_color color)
{
	int pixel;

	if (x < WIDTH && y < HEIGHT)
	{
		pixel = (x * map->inter_tex[0]->pixb) + (y * map->inter_tex[0]->strb);
		draw_color(map, pixel, color);
	}
}

void zerotem(t_map *map)
{
	map->tem->x1 = 0;
	map->tem->y1 = 0;
	map->tem->x2 = 0;
	map->tem->y2 = 0;
	map->tem->dx = 0;
	map->tem->dy = 0;
	map->tem->er = 0;
	map->tem->de = 0;
	map->tem->i = 0;
	map->tem->j = 0;
	map->tem->diry = 0;
	map->tem->di = 0;
}

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

void	two_n(t_map *map, t_color color)
{
	map->tem->i = map->tem->y1;
	map->tem->j = map->tem->x1;
	map->tem->di = (map->tem->y2 - map->tem->y1) / map->tem->dy;
	map->tem->diry = map->tem->x2 - map->tem->x1;
	map->tem->de = map->tem->dx + 1;
	if (map->tem->diry > 0)
		map->tem->diry = 1;
	if (map->tem->diry < 0)
		map->tem->diry = -1;
	while (map->tem->i != map->tem->y2)
	{
		draw_gr(map, map->tem->j, map->tem->i, color);
		map->tem->er += map->tem->de;
		if (map->tem->er >= map->tem->dy + 1)
		{
			map->tem->j += map->tem->diry;
			map->tem->er = map->tem->er - (map->tem->dy + 1);
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
	t_nod *n;

	n = map->nod;
	if (!n)
		return ;
	while (n)
	{
		//printf("index: %d\n", n->index);
		if (map->inter_tex[6]->active)
			n->texture->type_name = "w";
		draw_node(map, n);
		n = n->nxt;
	}
}

int		sq(int x1, int y1, int x2, int y2)
{
	return ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void find_help(t_nod *nod, t_info *inf, int *x, int *y)
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
	t_info *inf;
	t_nod	*nod;

	if (!nod)
		return ;
	if (!(inf = malloc(sizeof(inf))))
		error(ERM);
	nod = map->nod;
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
