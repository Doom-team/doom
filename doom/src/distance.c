/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:19:22 by skaren            #+#    #+#             */
/*   Updated: 2021/02/12 14:35:36 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		dist_to_wall_helper(t_distance *v, t_helper *h,
				float *tmp, t_wolf *wolf)
{
	v->number_wall[h->j] = h->x;
	v->offsetx[h->j] = sqrtf(powf(v->coords[h->j].x -
		wolf->p->walls[h->x].x1, 2)
		+ powf(v->coords[h->j].y - wolf->p->walls[h->x].y1, 2))
		/ wolf->p->walls[h->x].length;
	v->dist[h->j] = *tmp;
	h->j++;
	*tmp = -1.0f;
}

t_distance		*dist_to_wall(t_wolf *wolf,
float angle, int count_distance)
{
	t_distance	*v;
	t_float2	player;
	float		tmp;
	t_helper	h;

	tmp = -1.0f;
	h.x = -1;
	h.j = 0;
	v = wolf->player->distance_vert[count_distance];
	t_distance_clear(v);
	player.x = wolf->player->x;
	player.y = wolf->player->y;
	while (++h.x < wolf->p->count_walls)
	{
		tmp = calc_dist(player, angle, wolf->p->walls[h.x], v, h.j);
		if (tmp != -1.0f)
			dist_to_wall_helper(v, &h, &tmp, wolf);
	}
	v->count = h.j;
	if (wolf->player->fly < 0)
		buble_sort_fly(v);
	else
		buble_sort(v);
	return (v);
}
