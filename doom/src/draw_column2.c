/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:31:45 by skaren            #+#    #+#             */
/*   Updated: 2021/02/09 16:20:04 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			brute_draw_column_2_2(t_wolf *wolf,\
t_data_column *d)
{
	if (d->flag == 1)
	{
		d->count = (int)\
		(round(wolf->p->walls[d->dist->number_wall[d->j]].length));
		d->koof = (wolf->p->walls[d->dist->number_wall[d->j]].length)\
		/ d->count;
		d->tex_1 = (wolf->p->walls[d->dist->number_wall[d->j]].length\
		/ d->count) * d->koof;
		d->pos = d->dist->offsetx[d->j] *\
		wolf->p->walls[d->dist->number_wall[d->j]].length;
		d->fractpart = modf((d->pos / d->tex_1), &d->intpart);
		d->flag = 0;
	}
}

void			brute_draw_column_1_2(t_wolf *wolf,\
int count_distance, t_data_column *d)
{
	if (d->stage.dist[wolf->p->walls[d->dist->number_wall[d->j]].\
	squad_stage - 1] == 0)
		d->stage.dist[wolf->p->walls[d->dist->number_wall[d->j]].\
		squad_stage - 1] = wolf->player->distance[count_distance]->dist[d->j];
	else if (wolf->player->distance[count_distance]->dist[d->j]\
	< d->stage.dist[wolf->p->walls[d->dist->number_wall[d->j]].squad_stage - 1])
		d->stage.dist[wolf->p->walls[d->dist->number_wall[d->j]].\
		squad_stage - 1] = wolf->player->distance[count_distance]->dist[d->j];
	if (d->stage.y2[wolf->p->walls[d->dist->number_wall[d->j]].\
	squad_stage - 1] < d->temp_y)
	{
		d->stage.y2[wolf->p->walls[d->dist->number_wall[d->j]].\
		squad_stage - 1] = d->temp_y;
		d->stage.y1[wolf->p->walls[d->dist->number_wall[d->j]].\
		squad_stage - 1] = -1;
	}
	else if (d->stage.y1[wolf->p->walls[d->dist->number_wall[d->j]].\
	squad_stage - 1] < d->temp_y)
		d->stage.y1[wolf->p->walls\
		[d->dist->number_wall[d->j]].squad_stage - 1] = d->temp_y;
}

void			brute_draw_column_1_1(t_wolf *wolf,\
int count_distance, t_data_column *d)
{
	if (wolf->p->walls[d->dist->number_wall[d->j]].type_flag == 1)
	{
		brute_draw_column_1_2(wolf, count_distance, d);
		if (d->stage.y2[wolf->p->walls\
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

void			brute_draw_column_3_1(t_wolf *wolf,\
t_point point, t_data_column *d)
{
	if (d->temp_y - wolf->player->dir_y >\
	0 && d->temp_y - wolf->player->dir_y < H)
	{
		d->offsety = (float)(d->temp_y - d->begin_y) / (d->size - d->begin_y);
		d->pos_y = d->len * d->offsety;
		d->fractpart_2 = modf(d->pos_y / d->tex_2, &d->intpart_2);
		d->color = get_pixel(wolf->p->walls[d->dist->number_wall[d->j]].\
		texture1, wolf->p->walls[d->dist->number_wall[d->j]].texture1->w\
		* d->fractpart, d->fractpart_2 * wolf->p->walls[d->dist->\
		number_wall[d->j]].texture1->h);
		if (d->color != 0)
		{
			set_pixel(wolf->surface, point.x,\
			d->temp_y - wolf->player->dir_y, d->color);
			wolf->z_buff[point.x + (d->temp_y -\
			wolf->player->dir_y) * W] = true;
		}
		brute_draw_column_3_3(wolf, point, d);
	}
}

void			brute_draw_column_3(t_wolf *wolf,\
t_point point, t_data_column *d)
{
	while (++d->temp_y < d->size)
	{
		if (d->temp_y - wolf->player->dir_y > H)
			break ;
		if (d->temp_y - wolf->player->dir_y < -H - 2)
		{
			d->temp_y = -H - 1 + wolf->player->dir_y;
			continue;
		}
		if ((d->temp_y - wolf->player->dir_y >= 0\
		&& d->temp_y - wolf->player->dir_y < H)\
		&& (wolf->z_buff[point.x + (d->temp_y\
		- wolf->player->dir_y) * W] == true))
			continue;
		brute_draw_column_3_2(wolf, d);
		brute_draw_column_3_1(wolf, point, d);
	}
}
