/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 20:27:45 by grinko            #+#    #+#             */
/*   Updated: 2020/12/20 18:11:36 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"
#include <math.h>

int nod_len(t_nod *nod)
{
	t_nod *n;
	int i;

	n = nod;
	i = 0;
	while (n)
	{
		i++;
		n = n->nxt;
	}
	return(i);
}

t_nod	*n_cr(short x1, short y1, short x2, short y2)
{
	t_nod *a;

	a = (t_nod*)malloc(sizeof(t_nod));
	a->texture = (t_texinfo*)malloc(sizeof(t_texinfo));
	a->texture->texture_name[0] = malloc(sizeof(char) * 100);
	a->texture->texture_name[1] = malloc(sizeof(char) * 100);
	a->texture->floor_name = malloc(sizeof(char) * 100);
	a->texture->ceiling_name = malloc(sizeof(char) * 100);
	a->texture->type_name = malloc(sizeof(char) * 100);
	a->texture->texture_name[0] = NULL;
	a->texture->texture_name[1] = NULL;
	a->texture->floor_name = NULL;
	a->texture->ceiling_name = NULL;
	a->texture->type_name = NULL;
	a->x1 = x1;
	a->y1 = y1;
	a->x2 = x2;
	a->y2 = y2;
	a->nxt = NULL;
	return (a);
}



void add_node(t_map *map, int x, int y)
{
	t_nod *n;
	t_nod *cur;

	n = n_cr(map->x_c - map->z_x, map->y_c  - map->z_y, x - map->z_x, y - map->z_y);
	n->index = nod_len(map->nod);
	n->wallh = map->whclick;
	if (map->nod == NULL)
	{
		map->nod = n;
		return;
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

void draw_gr(t_map *map, int x, int y, t_color color)
{
	int pixel;

	if (x < WIDTH && y < HEIGHT)
	{
		pixel = (x * map->inter_tex[0]->pixb) + (y * map->inter_tex[0]->strb);
		draw_color(map, pixel, color);
	}
}

void draw_node(t_map *map, t_nod *n)
{
	int x1;
	int y1;
	int x2;
	int y2;

	int dx;
	int dy;
	int er;
	int de;

	int i;
	int j;

	int diry;
	int di;

	if (n)
	{
		x1 = n->x1 + map->z_x;
		x2 = n->x2 + map->z_x;
		if (x1 < 0 && x2 < 0)
			return;
		y1 = n->y1 + map->z_y;
		y2 = n->y2 + map->z_y;
		dx = abs(x1 - x2);
		dy = abs(y1 - y2);
		er = 0;
		de = dy + 1;
		j = y1;
		i = x1;
		di = 0;
		
		if (dx > dy)
		{
			i = x1;
			j = y1;
			di = (x2 - x1) / dx;
			diry = y2 - y1;
			de = dy + 1;
			if (diry > 0)
				diry = 1;
			if (diry < 0)
				diry = -1;
			
			while (i != x2)
			{
				draw_gr(map, i, j, GREEN);
				er += de;
				if (er >= dx + 1)
				{
					j += diry;
					er = er - (dx + 1);
				}
				i += di;
			}
		}
		else if (dy != 0)
		{
			i = y1;
			j = x1;
			di = (y2 - y1) / dy;
			diry = x2 - x1;
			de = dx + 1;
			if (diry > 0)
				diry = 1;
			if (diry < 0)
				diry = -1;
			
			while (i != y2)
			{
				draw_gr(map, j, i, GREEN);
				er += de;
				if (er >= dy + 1)
				{
					j += diry;
					er = er - (dy + 1);
				}
				i += di;
			}
		}
		bigdot(map, x1, y1, RED);
		bigdot(map, x2, y2, RED);
	}
}

void draw_nodes(t_map *map)
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

int sq(int x1, int y1, int x2, int y2)
{
	return ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void	find_coord(t_map *map, int *x, int *y)
{
	int x1;
	int y1;
	int abs1;
	int abs2;
	t_nod *nod;

	nod = map->nod;
	x1 = *x + 10;
	y1 = *y + 10;
	abs1 = 200;
	if (!nod)
		return ;
	while (nod)
	{
		if (abs((nod->x1 + map->z_x) - *x) < 10 && abs((nod->y1 + map->z_y) - *y) < 10)
		{
			abs2 = sq(*x, *y, nod->x1 + map->z_x, nod->y1 + map->z_y);
			if (abs2 < abs1)
			{
				abs1 = abs2;
				x1 = nod->x1 + map->z_x;
				y1 = nod->y1 + map->z_y;
			}
		}
		if (abs((nod->x2 + map->z_x) - *x) < 10 && abs((nod->y2 + map->z_y) - *y) < 10)
		{
			abs2 = sq(*x, *y, nod->x2 + map->z_x, nod->y2 + map->z_y);
			if (abs2 < abs1)
			{
				abs1 = abs2;
				x1 = nod->x2 + map->z_x;
				y1 = nod->y2 + map->z_y;
			}
		}
		nod = nod->nxt;
	}
	if (abs1 < 200)
	{
		*x = x1;
		*y = y1;
	}
}
