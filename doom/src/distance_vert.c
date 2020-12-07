/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_vert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:18:12 by clala             #+#    #+#             */
/*   Updated: 2020/10/18 18:35:13 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		init_vert(t_player *p, t_float2 *b, t_float2 *diff, float angle)
{
	b->x = floorf((float)p->x / CUBE) * CUBE;
	b->x = angle > RAD_270 || angle < RAD_90 ? b->x + CUBE : b->x;
	b->y = p->y + (p->x - b->x) * tanf(angle);
	diff->y = CUBE * tanf(angle);
	if (angle > RAD_270 && angle < RAD_360)
	{
		diff->y = -diff->y;
		diff->x = CUBE;
	}
	else if (angle > RAD_90 && angle < RAD_180)
	{
		diff->y = diff->y;
		diff->x = -CUBE;
	}
	else if (angle > RAD_0 && angle < RAD_90)
	{
		diff->y = (-diff->y);
		diff->x = CUBE;
	}
	else
	{
		diff->y = diff->y;
		diff->x = -CUBE;
	}
}

static int		calc_vert(t_wolf *wolf, t_float2 *b,
t_distance *dist, float angle)
{
	if (angle < RAD_270 && angle > RAD_90 &&
		ft_strchr(WALLSET, wolf->map->map[((int)b->y / CUBE) \
		* wolf->map->w + ((int)(b->x - 1) / CUBE)]))
	{
		dist->dist = fabsf((wolf->player->x - b->x) / cosf(angle));
		dist->offsetx = (int)b->y % CUBE;
		dist->tex = wolf->sdl->sides_mode ? 'w' : \
			wolf->map->map[((int)b->y / CUBE) \
			* wolf->map->w + ((int)(b->x - 1) / CUBE)];
		return (1);
	}
	else if (ft_strchr(WALLSET, wolf->map->map[((int)b->y / CUBE) \
		* wolf->map->w + ((int)b->x / CUBE)]))
	{
		dist->dist = fabsf((wolf->player->x - b->x) / cosf(angle));
		dist->offsetx = (int)b->y % CUBE;
		dist->tex = wolf->sdl->sides_mode ? 'e' : \
			wolf->map->map[((int)b->y / CUBE) \
			* wolf->map->w + ((int)b->x / CUBE)];
		return (1);
	}
	return (0);
}

t_distance		*find_vertical_intersection(t_wolf *wolf,
float angle, t_distance *dist)
{
	t_float2	b;
	t_float2	diff;

	init_vert(wolf->player, &b, &diff, angle);
	while (b.y > -1 && b.y < wolf->map->h_pix &&
		b.x > -1 && b.x < wolf->map->w_pix)
	{
		if (calc_vert(wolf, &b, dist, angle))
			break ;
		b.x += diff.x;
		b.y += diff.y;
	}
	dist->coords = b;
	return (dist);
}
