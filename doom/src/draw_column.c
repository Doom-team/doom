/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:31:45 by skaren            #+#    #+#             */
/*   Updated: 2021/02/09 16:20:04 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			draw_column(t_wolf *wolf, t_point point, int count_distance)
{
	t_data_column			d;

	d.dist = wolf->player->distance[count_distance];
	d.j = -1;
	brute_draw_column(wolf, point, count_distance, &d);
	cut_ctage(wolf, point, count_distance, &d);
	while (++d.j < d.stage.count)
	{
		wolf->helper.j = d.j;
		wolf->helper.x = point.x;
		floorcast_up(wolf, wolf->player->distance[count_distance],\
		count_distance, d.sub_stage);
	}
	if (d.dist->number_wall[d.j] < 0 &&\
	d.dist->number_wall[d.j] > wolf->p->count_walls - 1)
		return ;
	brute_draw_column_1(wolf, point, count_distance, &d);
	brute_draw_column_2(wolf, point, count_distance, &d);
}

void			brute_draw_column(t_wolf *wolf,\
t_point point, int count_distance, t_data_column *d)
{
	while (++d->j < d->dist->count)
	{
		d->temp_y = ceilf((wolf->player->dist_to_canvas) /\
		wolf->player->distance[count_distance]->dist[d->j]);
		d->temp_y = (H - d->temp_y) / 2;
		d->size = H - d->temp_y;
		d->temp_y = d->size - ceilf((wolf->p->walls[d->dist->\
		number_wall[d->j]].h / 5.0f * wolf->player->dist_to_canvas) /\
		wolf->player->distance[count_distance]->dist[d->j]);
		if (wolf->p->walls[d->dist->number_wall[d->j]].active != 1)
			continue;
		brute_draw_column_1_1(wolf, point, count_distance, d);
		if (d->dist->number_wall[d->j] < 0 &&\
		d->dist->number_wall[d->j] > wolf->p->count_walls - 1)
			return ;
		d->begin_y = d->temp_y;
		d->len = d->size - d->begin_y;
		d->tex_2 = d->len / (wolf->p->walls[d->dist->number_wall[d->j]].h\
		/ 5.0f);
		d->flag = 1;
		d->temp_y--;
		brute_draw_column_3(wolf, point, count_distance, d);
	}
}

void			brute_draw_column_1(t_wolf *wolf,\
t_point point, int count_distance, t_data_column *d)
{
	d->j = 0;
	d->temp_y = ceilf((wolf->player->dist_to_canvas)\
	/ wolf->player->distance[count_distance]->dist[d->j]);
	d->temp_y = (H - d->temp_y) / 2;
	d->size = H - d->temp_y;
	d->temp_y = d->size - ceilf((wolf->p->walls[d->dist->number_wall[d->j]].h\
	/ 5.0f * wolf->player->dist_to_canvas) / wolf->player->\
	distance[count_distance]->dist[d->j]);
	d->begin_y = d->temp_y;
	d->len = d->size - d->begin_y;
	d->tex_2 = d->len / (wolf->p->walls[d->dist->number_wall[d->j]].h / 5.0f);
	d->flag = 1;
	d->temp_y--;
}

void			brute_draw_column_2_1(t_wolf *wolf,\
t_point point, int count_distance, t_data_column *d)
{
	brute_draw_column_2_2(wolf, point, count_distance, d);
	if ((d->temp_y - wolf->player->dir_y > 0 &&\
	d->temp_y - wolf->player->dir_y < H))
	{
		d->offsety = (float)(d->temp_y - d->begin_y) / (d->size - d->begin_y);
		d->pos_y = d->len * d->offsety;
		d->fractpart_2 = modf(d->pos_y / d->tex_2, &d->intpart_2);
		d->color = get_pixel(wolf->p->walls[d->dist->number_wall[d->j]].\
		texture1, wolf->p->walls[d->dist->number_wall[d->j]].texture1->w\
		* d->fractpart, d->fractpart_2 * wolf->p->walls[d->dist->\
		number_wall[d->j]].texture1->h);
		if (d->color != 0)
			set_pixel(wolf->surface, point.x, d->temp_y - wolf->player->dir_y,\
			d->color);
	}
}

void			brute_draw_column_2(t_wolf *wolf,\
t_point point, int count_distance, t_data_column *d)
{
	while (++d->temp_y < d->size)
	{
		if (wolf->p->walls[d->dist->number_wall[d->j]].active != 1)
			break ;
		if (d->temp_y - wolf->player->dir_y > H)
			break ;
		if (d->temp_y - wolf->player->dir_y < -H - 2)
		{
			d->temp_y = -H - 1 + wolf->player->dir_y;
			continue;
		}
		if (d->temp_y - wolf->player->dir_y < 0 ||\
		d->temp_y - wolf->player->dir_y > H)
			continue;
		brute_draw_column_2_1(wolf, point, count_distance, d);
	}
}
