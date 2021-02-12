/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_angle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 14:22:52 by ahusk             #+#    #+#             */
/*   Updated: 2021/02/12 14:22:55 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		search_angle_helper1(float *dist, float *angle, t_wolf *wolf,
										t_wall w)
{
	*dist = sqrtf(powf((w.realx - wolf->player->x), 2)
		+ powf((w.realy - wolf->player->y), 2));
	if (w.realx - wolf->player->x > 0
		&& w.realy - wolf->player->y < 0)
		*angle = asinf((wolf->player->y - w.realy)
			/ *dist);
	else if (w.realx - wolf->player->x < 0
		&& w.realy - wolf->player->y < 0)
		*angle = asinf((w.realy - wolf->player->y)
			/ *dist) + RAD_180;
	else if (w.realx - wolf->player->x < 0
		&& w.realy - wolf->player->y > 0)
		*angle = asinf((w.realy - wolf->player->y)
			/ *dist) + RAD_180;
	else if (w.realx - wolf->player->x > 0
		&& w.realy - wolf->player->y > 0)
		*angle = asinf((wolf->player->y - w.realy)
			/ *dist) + RAD_360;
}

static void		search_angle_helper2(float dist, int i, t_wolf *wolf, t_wall w)
{
	if (w.type_flag == 3 && dist < wolf->player->dist_mon)
	{
		wolf->player->dist_mon = dist;
		wolf->player->indx_mon = i;
	}
	if (w.type_flag >= 4 && w.type_flag <= 9 &&
		dist < wolf->player->dist_obj && dist <= 1.)
	{
		wolf->player->dist_obj = dist;
		wolf->player->indx_obj = i;
	}
}

float			search_angle(t_wall w, t_wolf *wolf, int i)
{
	float	dist;
	float	angle;

	angle = 0.f;
	if (w.type_flag == 2)
	{
		dist = fabs((w.y1 - w.y2) * wolf->player->x + (w.x2 - w.x1) *
			wolf->player->y + w.x1 * w.y2 - w.x2 * w.y1);
		dist /= sqrtf(powf(w.y1 - w.y2, 2) + powf(w.x1 - w.x2, 2));
		if (dist < wolf->player->dist_obj && dist <= 1.)
		{
			wolf->player->dist_obj = dist;
			wolf->player->indx_obj = i;
		}
		return (angle);
	}
	search_angle_helper1(&dist, &angle, wolf, w);
	search_angle_helper2(dist, i, wolf, w);
	return (angle);
}
