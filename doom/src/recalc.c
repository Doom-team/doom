/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recalc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:07:41 by ahusk             #+#    #+#             */
/*   Updated: 2021/02/12 16:07:42 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			recalc3(t_wolf *wolf)
{
	if (wolf->player->rght_d->wall.squad_stage ==
		wolf->player->left_d->wall.squad_stage &&
		wolf->player->rght_d->wall.squad_stage == 0)
		wolf->player->inside_step = 0;
	else if (wolf->player->left_d->wall.squad_stage ==
		wolf->player->down_d->wall.squad_stage &&
		wolf->player->left_d->wall.squad_stage == 0)
		wolf->player->inside_step = 0;
}

void			recalc2(t_wolf *wolf)
{
	if (wolf->player->up_d->wall.squad_stage ==
		wolf->player->rght_d->wall.squad_stage &&
		wolf->player->up_d->wall.squad_stage == 0)
		wolf->player->inside_step = 0;
	else if (wolf->player->up_d->wall.squad_stage ==
		wolf->player->left_d->wall.squad_stage &&
		wolf->player->up_d->wall.squad_stage == 0)
		wolf->player->inside_step = 0;
	else if (wolf->player->rght_d->wall.squad_stage ==
		wolf->player->down_d->wall.squad_stage &&
		wolf->player->rght_d->wall.squad_stage == 0)
		wolf->player->inside_step = 0;
	else
		recalc3(wolf);
}

void			recalc(t_wolf *wolf)
{
	int r;
	int l;
	int u;
	int d;

	calculate_distance(wolf, RAD_0, wolf->player->rght_d);
	calculate_distance(wolf, RAD_90, wolf->player->up_d);
	calculate_distance(wolf, RAD_180, wolf->player->left_d);
	calculate_distance(wolf, RAD_270, wolf->player->down_d);
	r = wolf->player->rght_d->wall.squad_stage;
	l = wolf->player->left_d->wall.squad_stage;
	u = wolf->player->up_d->wall.squad_stage;
	d = wolf->player->down_d->wall.squad_stage;
	if (r == l && u == r && r != 0)
		wolf->player->inside_step = wolf->player->rght_d->wall.h * UP_LENGTH;
	else if (r == l && d == r && r != 0)
		wolf->player->inside_step = wolf->player->rght_d->wall.h * UP_LENGTH;
	else if (u == d && r == u && u != 0)
		wolf->player->inside_step = wolf->player->up_d->wall.h * UP_LENGTH;
	else if (u == d && l == u && u != 0)
		wolf->player->inside_step = wolf->player->up_d->wall.h * UP_LENGTH;
	else if (u == d && u == 0)
		wolf->player->inside_step = 0;
	else
		recalc2(wolf);
}
