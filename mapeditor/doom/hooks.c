/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 19:23:34 by wendell           #+#    #+#             */
/*   Updated: 2020/10/15 23:54:00 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	rot_l(t_doom *dm)
{
	rotate(dm, -10);
	tics(dm);
}

void	rot_r(t_doom *dm)
{
	rotate(dm, 10);
	tics(dm);
}

void	move_f(t_doom *dm)
{
	if (dm->map[(int)(dm->ppos_x + dm->dir_x /
	(10 - 3.01 * dm->sh))][(int)dm->ppos_y] != 1)
		dm->ppos_x += dm->dir_x / (10 - 3.01 * dm->sh);
	if (dm->map[(int)dm->ppos_x][(int)(dm->ppos_y + dm->dir_y /
	(10 - 3.01 * dm->sh))] != 1)
		dm->ppos_y += dm->dir_y / (10 - 3.01 * dm->sh);
	tics(dm);
}

void	move_b(t_doom *dm)
{
	if (dm->map[(int)(dm->ppos_x - dm->dir_x /
	(10 - 3.01 * dm->sh))][(int)dm->ppos_y] != 1)
		dm->ppos_x -= dm->dir_x / (10 - 3.01 * dm->sh);
	if (dm->map[(int)dm->ppos_x][(int)(dm->ppos_y - dm->dir_y /
	(10 - 3.01 * dm->sh))] != 1)
		dm->ppos_y -= dm->dir_y / (10 - 3.01 * dm->sh);
	tics(dm);
}

int		pkey(int key, t_doom *dm)
{
	if (key == 225)
		dm->sh = 1;
	if (key == 32)
	{
		dm->f = 1;
		tics(dm);
	}
	if (key == 109)
		dm->mp = !dm->mp;
	if (key == 27)
		ext(dm);
	if (key == 79)
		rot_l(dm);
	if (key == 80)
		rot_r(dm);
	if (key == 82)
		move_f(dm);
	if (key == 81)
		move_b(dm);
	draw(dm);
	dm->f = 0;
	return (0);
}
