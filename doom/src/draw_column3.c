/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_column3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:31:45 by skaren            #+#    #+#             */
/*   Updated: 2021/02/09 16:20:04 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			brute_draw_column_3_2(t_wolf *wolf,\
t_data_column *d)
{
	if (d->flag == 1)
	{
		d->count = (int)(round(wolf->p->\
		walls[d->dist->number_wall[d->j]].length));
		d->koof = (wolf->p->walls[d->dist->\
		number_wall[d->j]].length) / d->count;
		d->tex_1 = (wolf->p->walls[d->dist->\
		number_wall[d->j]].length / d->count) * d->koof;
		d->pos = d->dist->offsetx[d->j]\
		* wolf->p->walls[d->dist->number_wall[d->j]].length;
		d->fractpart = modf((d->pos / d->tex_1), &d->intpart);
		d->flag = 0;
	}
}

void			brute_draw_column_3_3(t_wolf *wolf,\
t_point point, t_data_column *d)
{
	if (point.x == W / 2 && H / 2 < d->size && H / 2 > d->begin_y)
	{
		if (wolf->bon->flag_guns == 2 &&\
		wolf->p->walls[d->dist->number_wall[d->j]].type_flag\
		== 3 && wolf->p->walls[d->dist->number_wall[d->j]].active == 1)
		{
			wolf->p->walls[d->dist->number_wall[d->j]].active = 0;
			wolf->bon->score++;
		}
	}
}
