/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:06:11 by ahusk             #+#    #+#             */
/*   Updated: 2021/02/12 16:06:12 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

float			vector_len(float x1, float y1, float x2, float y2)
{
	return (sqrt((float)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1))));
}

int				ifcrossing(t_float2 player, float angle, t_wall wall)
{
	float k;
	float b;

	k = tanf(angle);
	b = player.y - k * player.x;
	if (angle > RAD_180)
	{
		if ((wall.y1 > player.y && wall.y2 > player.y) ||
			(wall.x1 * k + b < wall.y1 && wall.x2 * k + b < wall.y2))
			return (0);
	}
	if (angle < RAD_90 || angle > RAD_270)
	{
		if ((wall.x1 < player.x && wall.x2 < player.x) || ((wall.y1 - b) /
			k > wall.x1 && (wall.y2 - b) / k > wall.x2))
			return (0);
	}
	else
	{
		if ((wall.x1 > player.x && wall.x2 > player.x) || ((wall.y1 - b) /
			k < wall.x1 && (wall.y2 - b) / k < wall.x2))
			return (0);
	}
	return (1);
}

int				crossing(t_float2 player, float angle, t_wall wall)
{
	float k;
	float b;

	k = tanf(angle);
	b = player.y - k * player.x;
	if (angle == RAD_90 || angle == RAD_270)
	{
		if ((player.x > wall.x1 && player.x < wall.x2) ||
			(player.x > wall.x2 && player.x < wall.x1))
			return (1);
		return (0);
	}
	if (!((wall.y1 - k * wall.x1 - b) * (wall.y2 - k * wall.x2 - b) < 0))
		return (0);
	if (angle < RAD_180)
	{
		if ((wall.y1 < player.y && wall.y2 < player.y) ||
			(wall.x1 * k + b > wall.y1 && wall.x2 * k + b > wall.y2))
			return (0);
	}
	return (ifcrossing(player, angle, wall));
}
