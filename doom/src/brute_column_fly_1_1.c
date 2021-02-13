/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brute_column_fly_1_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 17:55:27 by ahusk             #+#    #+#             */
/*   Updated: 2021/02/12 17:55:28 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		brute_column_fly_1_1_help(t_data_column *d,
				t_wolf *wolf, int count_distance)
{
	if (d->stage.y1[wolf->p->walls[d->dist->number_wall[d->j]].squad_stage
		- 1] == -1)
		d->stage.y1[wolf->p->walls[d->dist->number_wall[d->j]].squad_stage
		- 1] =
		d->stage.y2[wolf->p->walls[d->dist->number_wall[d->j]].squad_stage
		- 1];
	d->stage.y2[wolf->p->walls[d->dist->number_wall[d->j]].squad_stage
		- 1] = d->temp_y - (wolf->player->dir_y +
			fly_correction_from_dist(wolf, d->j, count_distance));
}

void			brute_column_fly_1_1(t_wolf *wolf,
				int count_distance, t_data_column *d)
{
	if (d->stage.dist[wolf->p->walls[d->dist->number_wall[d->j]].squad_stage
		- 1] == 0)
	{
		d->flagg = 0;
		d->stage.dist[wolf->p->walls[d->dist->number_wall[d->j]].squad_stage
			- 1] = wolf->player->distance[count_distance]->dist[d->j];
	}
	if (d->stage.y2[wolf->p->walls[d->dist->number_wall[d->j]].squad_stage
		- 1] < d->temp_y - (fly_correction_from_dist(wolf, d->j,
			count_distance) + fly_correct_fuf(wolf))
		&& d->flagg != 1)
	{
		d->flagg = 1;
		d->stage.y2[wolf->p->walls[d->dist->number_wall[d->j]].squad_stage
			- 1] = d->temp_y - (fly_correction_from_dist(wolf, d->j,
				count_distance) + fly_correct_fuf(wolf));
		d->stage.y1[wolf->p->walls[d->dist->number_wall[d->j]].squad_stage
			- 1] = -1;
	}
	else if (d->stage.y1[wolf->p->walls[d->dist->number_wall[d->j]].squad_stage
		- 1] < d->temp_y - (fly_correction_from_dist(wolf, d->j,
			count_distance)))
		brute_column_fly_1_1_help(d, wolf, count_distance);
}
