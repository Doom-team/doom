/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcast_up.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 12:06:53 by ahusk             #+#    #+#             */
/*   Updated: 2021/02/12 12:06:54 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			floorcast_up(t_wolf *wolf, t_distance *dist, int x,
						int count_distance, t_floot_up stage, int j)
{
	t_data_floor	d;

	if (floorcast_up_escape(wolf, &stage, &d, j))
		return ;
	d.cof = cof_size_displ();
	d.cof_h = -0.4 * stage.h[j] + 1;
	d.temp_y = stage.y1[j] - wolf->player->dir_y;
	d.y = stage.y1[j];
	while (d.temp_y < stage.y2[j])
	{
		if (d.temp_y >= 0 && d.temp_y <= H)
		{
			d.curr_dist = H / (2.0 * d.y - H);
			d.weight = d.curr_dist /
				(dist->dist[wolf->player->distance[count_distance]->count - 1]
					/ (d.cof * d.cof_h));
			d.curr_floorx = d.weight *
				(dist->coords[wolf->player->distance[count_distance]->count - 1].x
					/ (d.cof * d.cof_h)) + (1.0 - d.weight) * (wolf->player->x
						/ (d.cof * d.cof_h));
			d.curr_floory = d.weight *
				(dist->coords[wolf->player->distance[count_distance]->count - 1].y
					/ (d.cof * d.cof_h)) + (1.0 - d.weight) * (wolf->player->y /
						(d.cof * d.cof_h));
			d.textx = (int)(d.curr_floorx *
				wolf->p->floor_texture->w * d.cof * d.cof_h)
					% wolf->p->floor_texture->w;
			d.texty = (int)(d.curr_floory *
				wolf->p->floor_texture->h * d.cof * d.cof_h)
					% wolf->p->floor_texture->h;
			if (d.textx > 0 && d.texty > 0)
			{
				d.color = get_pixel(wolf->p->floor_texture, d.textx, d.texty);
				set_pixel(wolf->surface, x, d.temp_y, d.color);
			}
		}
		d.temp_y++;
		d.y++;
	}
}
