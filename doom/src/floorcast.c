/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaren <skaren@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:31:45 by skaren            #+#    #+#             */
/*   Updated: 2021/02/09 16:20:04 by skaren           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static	void	floorcast_up_helper(t_floot_up *stage, t_data_floor *d, int j)
{
	d->tmp = stage->y2[j];
	stage->y2[j] = H;
	stage->y1[j] = d->tmp;
	d->temp_y = stage->y1[j];
}

int				floorcast_up_escape(t_wolf *wolf, t_floot_up *stage,
				t_data_floor *d, int j)
{
	if ((stage->y1[j] == 0 && stage->y2[j] == 0))
		return (1);
	if (stage->y1[j] == 0 && stage->y2[j] != 0)
		floorcast_up_helper(stage, d, j);
	else if (stage->y1[j] == -1 && stage->y2[j] != 0)
	{
		stage->y1[j] = stage->y2[j];
		if (stage->count % 2 == 0 && j - 1 >= 0
			&& stage->h[j] < stage->h[j - 1])
			floorcast_up_helper(stage, d, j);
		else
			return (1);
	}
	else
		stage->y2[j] -= wolf->player->dir_y;
	return (0);
}

static void		floor_text(t_wolf *wolf, t_data_floor *d,\
t_distance *dist, int cy[2])
{
	d->curr_dist = (H - wolf->player->fly) /\
	(2.0 * (cy[1] + wolf->player->fly) - (H - wolf->player->fly));
	d->weight = d->curr_dist / (dist->dist[wolf->player->\
	distance[cy[0]]->count - 1] / (d->cof));
	d->curr_floorx = d->weight * (dist->coords[wolf->player->\
	distance[cy[0]]->count - 1].x /\
	(d->cof)) + (1.0 - d->weight) * (wolf->player->x / (d->cof));
	d->curr_floory = d->weight * (dist->coords[wolf->player->\
	distance[cy[0]]->count - 1].y\
	/ (d->cof)) + (1.0 - d->weight) * (wolf->player->y / (d->cof));
	d->textx = (int)(d->curr_floorx * wolf->p->floor_texture->w * d->cof)\
	% wolf->p->floor_texture->w;
	d->texty = (int)(d->curr_floory * wolf->p->floor_texture->h * d->cof)\
	% wolf->p->floor_texture->h;
}

void			floorcast(t_wolf *wolf, t_distance *dist, t_point point,\
int count_distance)
{
	t_data_floor	d;
	int				cy[2];
	int				y;

	y = H - point.y;
	d.cof = cof_size_displ();
	d.temp_y = y - (wolf->player->dir_y +\
	diry_correction_from_fly(wolf->player->fly));
	cy[0] = count_distance;
	while (d.temp_y < H)
	{
		cy[1] = y;
		floor_text(wolf, &d, dist, cy);
		if (d.textx > 0 && d.texty > 0)
		{
			if (d.temp_y >= H / 2 - (wolf->player->dir_y - 1) && d.temp_y < H)
			{
				d.color = get_pixel(wolf->p->floor_texture, d.textx, d.texty);
				set_pixel(wolf->surface, point.x, d.temp_y, d.color);
			}
		}
		d.temp_y++;
		y++;
	}
}
