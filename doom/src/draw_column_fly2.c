/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column_fly2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:31:45 by skaren            #+#    #+#             */
/*   Updated: 2021/02/09 16:20:04 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			brute_column_fly(t_wolf *wolf,\
t_point point, int count_distance, t_data_column *d)
{
	while (++d->j < d->dist->count)
	{
		d->temp_y = ceilf((wolf->player->dist_to_canvas)\
		/ wolf->player->distance[count_distance]->dist[d->j]);
		d->temp_y = (H - d->temp_y) / 2;
		d->size = H - d->temp_y;
		d->temp_y = d->size - ceilf((wolf->p->walls[d->dist->\
		number_wall[d->j]].h / 5.0f * wolf->player->dist_to_canvas)\
		/ wolf->player->distance[count_distance]->dist[d->j]);
		if (wolf->p->walls[d->dist->number_wall[d->j]].active != 1)
			continue;
		brute_column_fly_1(wolf, count_distance, d);
		if (d->dist->number_wall[d->j] < 0 &&\
		d->dist->number_wall[d->j] > wolf->p->count_walls - 1)
			return ;
		brute_column_fly_2(wolf, point, count_distance, d);
	}
}

void			brute_column_fly_2(t_wolf *wolf,\
t_point point, int count_distance, t_data_column *d)
{
	d->begin_y = d->temp_y;
	d->len = d->size - d->begin_y;
	d->tex_2 = d->len / (wolf->p->walls[d->dist->number_wall[d->j]].h / 5.0f);
	d->flag = 1;
	d->temp_y--;
	while (++d->temp_y < d->size)
	{
		if (d->temp_y - (wolf->player->dir_y +\
		fly_correction_from_dist(wolf, d->j, count_distance)) > H)
			break ;
		if (d->temp_y - (wolf->player->dir_y +\
		fly_correction_from_dist(wolf, d->j, count_distance)) < -H - 2)
		{
			d->temp_y = -H - 1 + (wolf->player->dir_y +\
			fly_correction_from_dist(wolf, d->j, count_distance));
			continue;
		}
		if ((d->temp_y - wolf->player->dir_y >= 0 && d->temp_y - wolf->player->\
		dir_y < H) && (wolf->z_buff[point.x + (d->temp_y - wolf->player->dir_y)\
		* W] == true))
			continue;
		brute_column_fly_2_1(wolf, point, count_distance, d);
	}
}

void			brute_column_fly_2_1(t_wolf *wolf,\
t_point point, int count_distance, t_data_column *d)
{
	if (d->flag == 1)
	{
		d->count =\
		(int)(round(wolf->p->walls[d->dist->number_wall[d->j]].length));
		d->koof =\
		(wolf->p->walls[d->dist->number_wall[d->j]].length) / d->count;
		d->tex_1 = (wolf->p->walls[d->dist->number_wall[d->j]].length /\
		d->count) * d->koof;
		d->pos = d->dist->offsetx[d->j]\
		* wolf->p->walls[d->dist->number_wall[d->j]].length;
		d->fractpart = modf((d->pos / d->tex_1), &d->intpart);
		d->flag = 0;
	}
	brute_column_fly_2_2(wolf, point, count_distance, d);
}

void			brute_column_fly_2_2(t_wolf *wolf,\
t_point point, int count_distance, t_data_column *d)
{
	if (d->temp_y - (wolf->player->dir_y + fly_correction_from_dist(\
	wolf, d->j, count_distance)) > 0 && d->temp_y - (wolf->player->\
	dir_y + fly_correction_from_dist(wolf, d->j, count_distance)) < H)
	{
		d->offsety = (float)(d->temp_y - d->begin_y) / (d->size - d->begin_y);
		d->pos_y = d->len * d->offsety;
		d->fractpart_2 = modf(d->pos_y / d->tex_2, &d->intpart_2);
		d->color = get_pixel(wolf->p->walls[d->dist->number_wall[d->j]].\
		texture1, wolf->p->walls[d->dist->number_wall[d->j]].texture1->w\
		* d->fractpart, d->fractpart_2 * wolf->p->walls[d->dist->\
		number_wall[d->j]].texture1->h);
		if (d->color != 0)
			set_pixel(wolf->surface, point.x, d->temp_y - (wolf->player->dir_y\
			+ fly_correction_from_dist(wolf, d->j, count_distance)), d->color);
		if (point.x == W / 2 && H / 2 < d->size && H / 2 > d->begin_y)
		{
			if (wolf->bon->flag_guns == 2 && wolf->p->walls[d->dist->\
			number_wall[d->j]].type_flag == 3 && wolf->p->walls\
			[d->dist->number_wall[d->j]].active == 1)
			{
				wolf->p->walls[d->dist->number_wall[d->j]].active = 0;
				wolf->bon->score++;
			}
		}
	}
}

void			brute_column_fly_1(t_wolf *wolf,\
int count_distance, t_data_column *d)
{
	if (wolf->p->walls[d->dist->number_wall[d->j]].type_flag == 1)
	{
		brute_column_fly_1_1(wolf, count_distance, d);
		if (d->stage.y2[wolf->p->walls[d->dist->number_wall[d->j]].\
		squad_stage - 1] != 0 && d->stage.y1[wolf->p->walls\
		[d->dist->number_wall[d->j]].squad_stage - 1] != 0)
		{
			d->stage.h[wolf->p->walls[d->dist->number_wall[d->j]].\
			squad_stage - 1] = wolf->p->walls[d->dist->number_wall[d->j]].h;
			d->sub_stage.h[d->stage.count] = d->stage.h\
			[wolf->p->walls[d->dist->number_wall[d->j]].squad_stage - 1];
			d->sub_stage.y1[d->stage.count] = d->stage.y1\
			[wolf->p->walls[d->dist->number_wall[d->j]].squad_stage - 1];
			d->sub_stage.y2[d->stage.count] = d->stage.y2\
			[wolf->p->walls[d->dist->number_wall[d->j]].squad_stage - 1];
			d->sub_stage.dist[d->stage.count] = d->stage.dist\
			[wolf->p->walls[d->dist->number_wall[d->j]].squad_stage - 1];
			d->stage.count++;
		}
	}
}
