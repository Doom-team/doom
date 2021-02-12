/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_dist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:03:44 by ahusk             #+#    #+#             */
/*   Updated: 2021/02/12 16:03:45 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

float			calc_x(t_float2 player, float angle, t_wall wall, float *py)
{
	float b1;
	float x;
	float k2;
	float b2;

	b1 = player.y - tanf(angle) * player.x;
	if (angle == RAD_90 || angle == RAD_270)
	{
		x = player.x;
		k2 = 1.f * (wall.y2 - wall.y1) / (wall.x2 - wall.x1);
		b2 = wall.y1 - k2 * wall.x1;
		*py = k2 * x + b2;
		return (x);
	}
	if (wall.vert)
		x = wall.x1;
	else
	{
		k2 = 1.f * (wall.y2 - wall.y1) / (wall.x2 - wall.x1);
		b2 = wall.y1 - k2 * wall.x1;
		x = (b2 - b1) / (tanf(angle) - k2);
	}
	*py = tanf(angle) * x + b1;
	return (x);
}

float			calc_dist(t_float2 player, t_wall wall,
	t_distance *v, t_helper *h)
{
	float px;
	float py;

	if (!crossing(player, h->angle, wall))
		return (-1.);
	py = 0;
	px = calc_x(player, h->angle, wall, &py);
	if (h->angle < RAD_90 || h->angle > RAD_270)
	{
		if (px < player.x)
			return (-1.);
	}
	else if (h->angle == RAD_90 || h->angle == RAD_270)
	{
		if (px != player.x)
			return (-1.);
	}
	else if (px > player.x)
		return (-1.);
	v->coords[h->j].x = px;
	v->coords[h->j].y = py;
	px = vector_len(player.x, player.y, px, py);
	if (px < 0.001)
		return (-1.);
	return (px);
}

float			calc_dist_without_v(t_float2 player, float angle, t_wall wall)
{
	float px;
	float py;

	if (!crossing(player, angle, wall))
		return (-1.);
	py = 0;
	px = calc_x(player, angle, wall, &py);
	if (angle < RAD_90 || angle > RAD_270)
	{
		if (px < player.x)
			return (-1.);
	}
	else if (angle == RAD_90 || angle == RAD_270)
	{
		if (px != player.x)
			return (-1.);
		if (angle == RAD_90 && py < player.y)
			return (-1.);
		if (angle == RAD_270 && py > player.y)
			return (-1.);
	}
	else if (px > player.x)
		return (-1.);
	px = vector_len(player.x, player.y, px, py);
	return (px);
}

void			calculate_distance(t_wolf *wolf, t_way *d, t_helper *h)
{
	t_float2	player;
	float		dist;
	float		tmp;

	player.x = wolf->player->x;
	player.y = wolf->player->y;
	dist = MAXFLOAT;
	tmp = -1;
	while (++h->x < wolf->p->count_walls)
	{
		if (wolf->p->walls[h->x].type_flag >= 3 || !wolf->p->walls[h->x].active)
			continue;
		tmp = calc_dist_without_v(player, h->angle, wolf->p->walls[h->x]);
		if (tmp != -1. && tmp < dist)
		{
			dist = tmp;
			h->j = h->x;
		}
	}
	d->dist = dist;
	if (h->j != -1)
		d->wall = wolf->p->walls[h->j];
}
