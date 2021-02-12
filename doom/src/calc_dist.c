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

static void		calculate_distance_help(float *dist, int *j, float tmp, int i)
{
	if (tmp != -1. && tmp < *dist)
	{
		*dist = tmp;
		*j = i;
	}
}

void			calculate_distance(t_wolf *wolf, float angle, t_way *d)
{
	t_float2	player;
	float		dist;
	float		tmp;
	int			i;
	int			j;

	j = -1;
	player.x = wolf->player->x;
	player.y = wolf->player->y;
	dist = MAXFLOAT;
	tmp = -1;
	i = -1;
	while (++i < wolf->p->count_walls)
	{
		if (wolf->p->walls[i].type_flag >= 3 || !wolf->p->walls[i].active)
			continue;
		tmp = calc_dist_without_v(player, angle, wolf->p->walls[i]);
		calculate_distance_help(&dist, &j, tmp, i);
	}
	d->dist = dist;
	if (j != -1)
		d->wall = wolf->p->walls[j];
}
