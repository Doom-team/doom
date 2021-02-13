/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudo_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:31:45 by skaren            #+#    #+#             */
/*   Updated: 2021/02/12 02:49:52 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			upper_level_draw_3(t_wolf *wolf,\
t_point point, int count_distance, t_data_column *d)
{
	if (d->flag == 1)
	{
		d->count =\
		(int)(round(wolf->p->walls[d->dist->number_wall[d->j]].length));
		d->koof = (wolf->p->walls[d->dist->number_wall[d->j]].length) /\
		d->count;
		d->tex_1 = (wolf->p->walls[d->dist->number_wall[d->j]].length /\
		d->count) * d->koof;
		d->pos = d->dist->offsetx[d->j] *\
		wolf->p->walls[d->dist->number_wall[d->j]].length;
		d->fractpart = modf((d->pos / d->tex_1), &d->intpart);
		d->flag = 0;
	}
}

void			draw_sky(t_wolf *wolf, int x, int y)
{
	int		i;
	int		to_draw;
	int		to_draw_x;

	i = -1;
	if (y < 0)
		y = 0;
	if (y > H)
		y = H;
	while (++i < H)
	{
		to_draw = i;
		to_draw_x = x;
		while (to_draw + (int)wolf->sdl->skybox_offset_y >
			wolf->p->sky_texture->h - 1)
			to_draw -= wolf->p->sky_texture->h;
		while (to_draw_x + (int)wolf->sdl->skybox_offset >
			wolf->p->sky_texture->w)
			to_draw_x -= wolf->p->sky_texture->w;
		set_pixel(wolf->surface, x, i,
			get_pixel(wolf->p->sky_texture, to_draw_x +
				(int)wolf->sdl->skybox_offset, to_draw +
					(int)wolf->sdl->skybox_offset_y));
	}
}
