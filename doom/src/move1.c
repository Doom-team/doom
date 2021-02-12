/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:32:04 by skaren            #+#    #+#             */
/*   Updated: 2021/02/12 13:15:49 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		falling(t_wolf *wolf)
{
	SDL_Event	event;
	int			dmg;

	if (wolf->player->inside_step > abs(wolf->player->fly))
	{
		while (abs(wolf->player->fly) < wolf->player->inside_step)
		{
			wolf->player->fly -= UP_LENGTH / 2;
			falling2(wolf, &event);
		}
	}
	else if (wolf->player->inside_step < abs(wolf->player->fly))
	{
		dmg = (wolf->player->inside_step + wolf->player->fly) / 60;
		while (abs(wolf->player->fly) > wolf->player->inside_step)
		{
			wolf->player->fly += UP_LENGTH / 4;
			falling2(wolf, &event);
		}
		if (dmg < -15)
			take_damage(wolf, abs(dmg) / 2);
	}
}

void		jump(t_wolf *wolf)
{
	int			i;
	int			dmg;
	SDL_Event	event;

	i = 0;
	wolf->player->in_jump = 1;
	while (i < 12)
	{
		wolf->player->fly -= UP_LENGTH / 6;
		jump2(wolf, &event, 1);
		i++;
	}
	dmg = (wolf->player->inside_step + wolf->player->fly) / 60;
	while (abs(wolf->player->fly) > wolf->player->inside_step &&
			wolf->player->fly < 0)
	{
		wolf->player->fly += UP_LENGTH / 3;
		jump2(wolf, &event, 0);
	}
	wolf->player->fly = -wolf->player->inside_step;
	if (dmg < -15)
		take_damage(wolf, abs(dmg) / 2);
	wolf->player->in_jump = 0;
}

void		calc_move3(t_wolf *wolf, t_way *way, float dy)
{
	if (way->dist > fabs(dy))
		wolf->player->y += dy * 0.8f;
	else if (way->wall.type_flag == 1 &&
		UP_LENGTH * way->wall.h +
			wolf->player->fly <= UP_LENGTH)
		wolf->player->y += dy;
	else if ((!way->wall.type_flag || way->wall.type_flag == 2) &&
		UP_LENGTH * way->wall.h + wolf->player->fly < UP_LENGTH)
		wolf->player->y += dy;
}

void		calc_move2(t_wolf *wolf, t_way *way, float dx)
{
	if (way->dist > fabs(dx))
		wolf->player->x += dx * 0.8f;
	else if (way->wall.type_flag == 1
		&& UP_LENGTH * way->wall.h +
			wolf->player->fly <= UP_LENGTH)
		wolf->player->x += dx;
	else if ((!way->wall.type_flag || way->wall.type_flag == 2) &&
		UP_LENGTH * way->wall.h + wolf->player->fly < UP_LENGTH)
		wolf->player->x += dx;
}

void		calc_move(t_wolf *wolf, float dy, float dx)
{
	if (wolf->player->flying)
	{
		wolf->player->x += dx * 0.8f;
		wolf->player->y += dy * 0.8f;
	}
	else
	{
		recalc(wolf);
		if (dx > 0)
			calc_move2(wolf, wolf->player->rght_d, dx);
		else if (dx < 0)
			calc_move2(wolf, wolf->player->left_d, dx);
		recalc(wolf);
		if (dy > 0)
			calc_move3(wolf, wolf->player->up_d, dy);
		else if (dy < 0)
			calc_move3(wolf, wolf->player->down_d, dy);
		recalc(wolf);
		if (!wolf->player->in_jump)
			falling(wolf);
	}
}
