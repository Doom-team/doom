/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column_fly.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:31:45 by skaren            #+#    #+#             */
/*   Updated: 2021/02/09 16:20:04 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

// void			draw_column_fly(t_wolf *wolf, t_point point, int count_distance)
// {
// 	t_data_column			d;

// 	d.dist = wolf->player->distance[count_distance];
// 	d.j = -1;
// 	d.flagg = 0;
// 	brute_column_fly(wolf, point, count_distance, &d);
// 	cut_ctage(wolf, point, count_distance, &d);
// 	while (++d.j < d.stage.count)
// 		floorcast_up_fly(wolf, wolf->player->distance[count_distance],\
// 		point.x, count_distance, d.sub_stage, d.j);
// 	upper_level_draw(wolf, point, count_distance, &d);
// }

// void			upper_level_draw(t_wolf *wolf,\
// t_point point, int count_distance, t_data_column *d)
// {
// 	if (d->stage.count % 2 == 0)
// 	{
// 		if (upper_level_draw_1(wolf, point, count_distance, d))
// 			return ;
// 		while (++d->temp_y < d->size)
// 		{
// 			if (wolf->p->walls[d->dist->number_wall[d->j]].active != 1)
// 				break ;
// 			if (d->temp_y - (wolf->player->dir_y +\
// 			fly_correction_from_dist(wolf, d->j, count_distance)) > H)
// 				break ;
// 			if (d->temp_y - (wolf->player->dir_y +\
// 			fly_correction_from_dist(wolf, d->j, count_distance)) < -H - 2)
// 			{
// 				d->temp_y = -H - 1 + (wolf->player->dir_y +\
// 				fly_correction_from_dist(wolf, d->j, count_distance));
// 				continue;
// 			}
// 			if ((d->temp_y - wolf->player->dir_y >= 0 && d->temp_y -\
// 			wolf->player->dir_y < H) && (wolf->z_buff[point.x + (d->temp_y -\
// 			wolf->player->dir_y) * W] == true))
// 				continue;
// 			upper_level_draw_2(wolf, point, count_distance, d);
// 		}
// 	}
// }

// void			upper_level_draw_2(t_wolf *wolf,\
// t_point point, int count_distance, t_data_column *d)
// {
// 	upper_level_draw_3(wolf, point, count_distance, d);
// 	if (d->temp_y - (wolf->player->dir_y + fly_correction_from_dist(wolf, d->j,\
// 	count_distance)) > 0 && d->temp_y - (wolf->player->dir_y +\
// 	fly_correction_from_dist(wolf, d->j, count_distance)) < H)
// 	{
// 		d->offsety = (float)(d->temp_y - d->begin_y) / (d->size - d->begin_y);
// 		d->pos_y = d->len * d->offsety;
// 		d->fractpart_2 = modf(d->pos_y / d->tex_2, &d->intpart_2);
// 		d->color = get_pixel(wolf->p->walls[d->dist->number_wall[d->j]].\
// 		texture1, wolf->p->walls[d->dist->number_wall[d->j]].texture1->w\
// 		* d->fractpart, d->fractpart_2 * wolf->p->walls[d->dist->\
// 		number_wall[d->j]].texture1->h);
// 		if (d->color != 0)
// 			set_pixel(wolf->surface, point.x, d->temp_y - (wolf->player->dir_y\
// 			+ fly_correction_from_dist(wolf, d->j, count_distance)), d->color);
// 	}
// }

// int				upper_level_draw_1(t_wolf *wolf,\
// t_point point, int count_distance, t_data_column *d)
// {
// 	d->j = d->dist->count - 1;
// 	if (d->j == -1)
// 		return (1);
// 	d->temp_y = ceilf((wolf->player->dist_to_canvas) /\
// 	wolf->player->distance[count_distance]->dist[d->j]);
// 	d->temp_y = (H - d->temp_y) / 2;
// 	d->size = H - d->temp_y;
// 	d->temp_y = d->size - ceilf((wolf->p->walls[d->dist->number_wall[d->j]].h /\
// 	5.0f * wolf->player->dist_to_canvas) /\
// 	wolf->player->distance[count_distance]->dist[d->j]);
// 	if (d->dist->number_wall[d->j] < 0 &&\
// 	d->dist->number_wall[d->j] > wolf->p->count_walls - 1)
// 		return (1);
// 	d->begin_y = d->temp_y;
// 	d->len = d->size - d->begin_y;
// 	d->tex_2 = d->len / (wolf->p->walls[d->dist->number_wall[d->j]].h / 5.0f);
// 	d->flag = 1;
// 	d->temp_y--;
// 	return (0);
// }

// void			cut_ctage(t_wolf *wolf,\
// t_point point, int count_distance, t_data_column *d)
// {
// 	int	i;

// 	d->sub_stage.count = d->stage.count;
// 	d->j = 0;
// 	while (d->j < d->stage.count)
// 	{
// 		i = 0;
// 		while (++i < 4)
// 		{
// 			if (d->sub_stage.dist[d->j] == d->sub_stage.dist[d->j + i])
// 			{
// 				d->sub_stage.y1[d->j] = 0.f;
// 				d->sub_stage.y2[d->j] = 0.f;
// 				d->sub_stage.dist[d->j] = 0.f;
// 				d->sub_stage.h[d->j] = 0;
// 			}
// 		}
// 		d->j++;
// 	}
// 	d->j = -1;
// }
