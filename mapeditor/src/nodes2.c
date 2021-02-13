/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 20:27:45 by grinko            #+#    #+#             */
/*   Updated: 2021/02/13 20:14:39 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

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
	a->texture->texture_name[0] = NULL;
	a->texture->texture_name[1] = NULL;
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

	cur = NULL;
	n = n_cr(&(t_info){map->x_c, map->y_c, x, y}, 0);
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

	pixel = 0;
	if (x < WIDTH && y < HEIGHT && x >= 0 && y >= 0)
	{
		pixel = (x * map->inter_tex[0]->pixb) + (y * map->inter_tex[0]->strb);
		draw_color(map, pixel, color);
	}
}

void	zerotem(t_map *map)
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
