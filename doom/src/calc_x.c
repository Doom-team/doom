/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:29:52 by ahusk             #+#    #+#             */
/*   Updated: 2021/02/12 17:29:53 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		calc_x_helper(float *k2, float *b2, t_wall wall)
{
	*k2 = 1.f * (wall.y2 - wall.y1) / (wall.x2 - wall.x1);
	*b2 = wall.y1 - *k2 * wall.x1;
}

float			calc_x(t_float2 player, float angle, t_wall wall, float *py)
{
	float k1;
	float b1;
	float x;
	float k2;
	float b2;

	k1 = tanf(angle);
	b1 = player.y - k1 * player.x;
	if (angle == RAD_90 || angle == RAD_270)
	{
		x = player.x;
		calc_x_helper(&k2, &b2, wall);
		*py = k2 * x + b2;
		return (x);
	}
	if (wall.vert)
		x = wall.x1;
	else
	{
		calc_x_helper(&k2, &b2, wall);
		x = (b2 - b1) / (k1 - k2);
	}
	*py = k1 * x + b1;
	return (x);
}
