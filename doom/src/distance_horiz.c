/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_horiz.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:17:24 by clala             #+#    #+#             */
/*   Updated: 2020/10/18 18:17:48 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		init_horiz(t_player *p, t_float2 *a,
t_float2 *diff, float angle)
{
	a->y = floorf((float)p->y / CUBE) * CUBE;
	a->y = angle > RAD_0 && angle < RAD_180 ? a->y : a->y + CUBE;
	a->x = p->x + (p->y - a->y) / tanf(angle);
	diff->x = CUBE / tanf(angle);
	if (angle > RAD_270 && angle < RAD_360)
	{
		diff->x = -diff->x;
		diff->y = CUBE;
	}
	else if (angle > RAD_90 && angle < RAD_180)
	{
		diff->x = diff->x;
		diff->y = -CUBE;
	}
	else if (angle > RAD_0 && angle < RAD_90)
	{
		diff->x = (diff->x);
		diff->y = -CUBE;
	}
	else
	{
		diff->x = -diff->x;
		diff->y = CUBE;
	}
}

static int		calc_horiz(t_wolf *wolf, t_float2 *a,
t_distance *dist, float angle)
{
	if (angle > RAD_0 && angle < RAD_180 &&
	ft_strchr(WALLSET, wolf->map->map[((int)(a->y - 1) / CUBE) \
		* wolf->map->w + ((int)a->x / CUBE)]))
	{
		dist->dist = fabsf((wolf->player->y - a->y) / sinf(angle));
		dist->offsetx = (int)a->x % CUBE;
		dist->tex = wolf->sdl->sides_mode ? 's' : \
			wolf->map->map[((int)(a->y - 1) / CUBE) * wolf->map->w \
			+ ((int)a->x / CUBE)];
		return (1);
	}
	else if (ft_strchr(WALLSET, wolf->map->map[((int)a->y / CUBE) \
		* wolf->map->w + ((int)a->x / CUBE)]))
	{
		dist->dist = fabsf((wolf->player->y - a->y) / sinf(angle));
		dist->offsetx = (int)a->x % CUBE;
		dist->tex = wolf->sdl->sides_mode ? 'n' : \
			wolf->map->map[((int)a->y / CUBE) * wolf->map->w \
			+ ((int)a->x / CUBE)];
		return (1);
	}
	return (0);
}

t_distance		*find_horizontal_intersection(t_wolf *wolf,
	float angle, t_distance *dist)
{
	t_float2	a;
	t_float2	diff;

	init_horiz(wolf->player, &a, &diff, angle);
	while (a.y > -1 && a.y < wolf->map->h_pix &&
		a.x > -1 && a.x < wolf->map->w_pix)
	{
		if (calc_horiz(wolf, &a, dist, angle))
			break ;
		a.x += diff.x;
		a.y += diff.y;
	}
	dist->coords = a;
	return (dist);
}
