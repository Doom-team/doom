/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 16:10:33 by wendell           #+#    #+#             */
/*   Updated: 2020/10/19 14:55:31 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

double	dxdy(t_doom *dm, int b)
{
	if (b)
	{
		if (dm->ray_x == 0)
			return (0);
		else if (dm->ray_y == 0)
			return (1);
		else
			return (fabs(1 / dm->ray_y));
	}
	else
	{
		if (dm->ray_y == 0)
			return (0);
		else if (dm->ray_x == 0)
			return (1);
		else
			return (fabs(1 / dm->ray_x));
	}
}

t_dda	initdda(t_doom *dm)
{
	t_dda dda;

	dda.dx = dxdy(dm, 0);
	dda.dy = dxdy(dm, 1);
	if (dm->ray_x < 0)
	{
		dda.step_x = -1;
		dda.side_x = (dm->ppos_x - dm->map_x) * dda.dx;
	}
	else
	{
		dda.step_x = 1;
		dda.side_x = (dm->map_x + 1.0 - dm->ppos_x) * dda.dx;
	}
	if (dm->ray_y < 0)
	{
		dda.step_y = -1;
		dda.side_y = (dm->ppos_y - dm->map_y) * dda.dy;
	}
	else
	{
		dda.step_y = 1;
		dda.side_y = (dm->map_y + 1.0 - dm->ppos_y) * dda.dy;
	}
	return (dda);
}

double	dda_ret(t_doom *dm, t_dda dda)
{
	if (dm->side)
	{
		if (dda.step_y > 0)
			dm->ntex = 3;
		else
			dm->ntex = 2;
	}
	else
	{
		if (dda.step_x > 0)
			dm->ntex = 1;
		else
			dm->ntex = 0;
	}
	if (dm->side == 0)
		return ((dm->map_x - dm->ppos_x +
		(1.0 - dda.step_x) / 2.0) / dm->ray_x);
	else
		return ((dm->map_y - dm->ppos_y +
		(1.0 - dda.step_y) / 2.0) / dm->ray_y);
}

double	dda(t_doom *dm)
{
	t_dda dda;

	dda = initdda(dm);
	dda.hit = 0;
	dda.blck = 0;
	while (dda.hit == 0)
	{
		if (dda.blck == 1)
		{
			if (dda.side_x < dda.side_y)
			{
				dda.side_x += dda.dx;
				dm->map_x += dda.step_x;
				dm->side = 0;
			}
			else
			{
				dda.side_y += dda.dy;
				dm->map_y += dda.step_y;
				dm->side = 1;
			}
		}
		if (dda.side_x < dda.side_y)
		{
			dda.side_x += dda.dx;
			dm->map_x += dda.step_x;
			dm->side = 0;
		}
		else
		{
			dda.side_y += dda.dy;
			dm->map_y += dda.step_y;
			dm->side = 1;
		}
		if (dm->map[dm->map_x][dm->map_y] == 2)
			dda.blck = 1;
		if (dm->map[dm->map_x][dm->map_y] == 0)
			dda.blck = 0;
		if (dm->map[dm->map_x][dm->map_y] == 1)
			dda.hit = 1;
	}
	return (dda_ret(dm, dda));
}

double	calc_d(int i, t_doom *dm)
{
	double camera_x;
	double dist;

	camera_x = 2 * i / (double)(WIDTH) - 1;
	dm->ray_x = dm->dir_x + dm->cam_x * camera_x;
	dm->ray_y = dm->dir_y + dm->cam_y * camera_x;
	dm->map_x = (int)dm->ppos_x;
	dm->map_y = (int)dm->ppos_y;
	dist = dda(dm);
	if (dm->side == 0)
		dm->wall_x = dm->ppos_y + dist * dm->ray_y;
	else
		dm->wall_x = dm->ppos_x + dist * dm->ray_x;
	dm->wall_x -= floor(dm->wall_x);
	dm->tex_x = (int)(dm->wall_x * (double)(dm->wl_tex[dm->ntex]->w));
	return (dist);
}
