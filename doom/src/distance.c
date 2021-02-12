/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:19:22 by skaren            #+#    #+#             */
/*   Updated: 2021/02/12 15:55:16 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		buble_sort_fly(t_distance *v, t_helper *h)
{
	float		of_temp;
	t_float2	cor_temp;

	while (++h->x < v->count - 1)
	{
		h->j = v->count;
		while (--h->j > h->x)
		{
			if (v->dist[h->x - 1] < v->dist[h->x])
			{
				h->angle = v->dist[h->j - 1];
				h->prikol = v->number_wall[h->j - 1];
				of_temp = v->offsetx[h->j - 1];
				cor_temp = v->coords[h->j - 1];
				v->dist[h->j - 1] = v->dist[h->j];
				v->number_wall[h->j - 1] = v->number_wall[h->j];
				v->offsetx[h->j - 1] = v->offsetx[h->j];
				v->coords[h->j - 1] = v->coords[h->j];
				v->dist[h->j] = h->angle;
				v->number_wall[h->j] = h->prikol;
				v->offsetx[h->j] = of_temp;
				v->coords[h->j] = cor_temp;
			}
		}
	}
}

static void		buble_sort(t_distance *v, t_helper *h)
{
	float		of_temp;
	t_float2	cor_temp;

	while (++h->x < v->count - 1)
	{
		h->j = v->count;
		while (--h->j > h->x)
		{
			if (v->dist[h->j - 1] > v->dist[h->j])
			{
				h->angle = v->dist[h->j - 1];
				h->prikol = v->number_wall[h->j - 1];
				of_temp = v->offsetx[h->j - 1];
				cor_temp = v->coords[h->j - 1];
				v->dist[h->j - 1] = v->dist[h->j];
				v->number_wall[h->j - 1] = v->number_wall[h->j];
				v->offsetx[h->j - 1] = v->offsetx[h->j];
				v->coords[h->j - 1] = v->coords[h->j];
				v->dist[h->j] = h->angle;
				v->number_wall[h->j] = h->prikol;
				v->offsetx[h->j] = of_temp;
				v->coords[h->j] = cor_temp;
			}
		}
	}
}

void			dist_to_ass(t_wolf *wolf, t_distance *v, int t)
{
	v->count = t;
	if (wolf->player->fly < 0)
		buble_sort_fly(v, &(t_helper){0, -1, 0, 0});
	else
		buble_sort(v, &(t_helper){0, -1, 0, 0});
}

static void		dist_to_wall_helper(t_distance *v, t_helper *h,
				t_wolf *wolf, float *tmp)
{
	v->number_wall[h->j] = h->x;
	v->offsetx[h->j] = sqrtf(powf(v->coords[h->j].x -
		wolf->p->walls[h->x].x1, 2) +
			powf(v->coords[h->j].y - wolf->p->walls[h->x].y1, 2)) /
				wolf->p->walls[h->x].length;
	v->dist[h->j] = *tmp;
	h->j++;
	*tmp = -1.0f;
}

t_distance		*dist_to_wall(t_wolf *wolf, t_helper *h)
{
	t_distance	*v;
	t_float2	player;
	float		tmp;

	tmp = -1.0f;
	v = wolf->player->distance_vert[h->prikol];
	t_distance_clear(v);
	player.x = wolf->player->x;
	player.y = wolf->player->y;
	while (h->x < wolf->p->count_walls)
	{
		tmp = calc_dist(player, wolf->p->walls[h->x], v,
			&(t_helper){h->j, 0, h->angle});
		if (tmp != -1.0f)
			dist_to_wall_helper(v, h, wolf, &tmp);
		h->x++;
	}
	dist_to_ass(wolf, v, h->j);
	return (v);
}
