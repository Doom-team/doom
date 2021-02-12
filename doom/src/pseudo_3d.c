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

void			brute_column_fly_1_1(t_wolf *wolf, t_point point, int count_distance, t_data_column *d)
{
	if (d->stage.dist[wolf->p->walls[d->dist->number_wall[d->j]].squad_stage - 1] == 0)
	{
		d->flagg = 0;
		d->stage.dist[wolf->p->walls[d->dist->number_wall[d->j]].squad_stage - 1] = wolf->player->distance[count_distance]->dist[d->j];
	}
	if (d->stage.y2[wolf->p->walls[d->dist->number_wall[d->j]].squad_stage - 1] < d->temp_y - (fly_correction_from_dist(wolf, d->j, count_distance) + fly_correct_fuf(wolf))
		&& d->flagg != 1)
	{
		d->flagg = 1;
		d->stage.y2[wolf->p->walls[d->dist->number_wall[d->j]].squad_stage - 1] = d->temp_y - (fly_correction_from_dist(wolf, d->j, count_distance) + fly_correct_fuf(wolf));
		d->stage.y1[wolf->p->walls[d->dist->number_wall[d->j]].squad_stage - 1] = -1;
	}
	else if (d->stage.y1[wolf->p->walls[d->dist->number_wall[d->j]].squad_stage - 1] < d->temp_y - (fly_correction_from_dist(wolf, d->j, count_distance)))
	{
		if (d->stage.y1[wolf->p->walls[d->dist->number_wall[d->j]].squad_stage - 1] == -1)
			d->stage.y1[wolf->p->walls[d->dist->number_wall[d->j]].squad_stage - 1] = d->stage.y2[wolf->p->walls[d->dist->number_wall[d->j]].squad_stage - 1];
		d->stage.y2[wolf->p->walls[d->dist->number_wall[d->j]].squad_stage - 1] = d->temp_y - (wolf->player->dir_y + fly_correction_from_dist(wolf, d->j, count_distance));
	}
}

void			floorcast_up_fly(t_wolf *wolf, t_distance *dist, int x, int count_distance, t_floot_up stage, int j)
{
	float	curr_dist;
	float	weight;
	float	curr_floorx;
	float	curr_floory;
	int		textx;
	int		texty;
	int		color;
	int		temp_y;
	int		y;
	int		tmp;
	float	cof;
	float	cof_h;

	if ((stage.y1[j] == 0 && stage.y2[j] == 0))
		return ;
	cof = cof_size_displ();
	cof_h = -0.4 * stage.h[j] + 1.0  + correct_cof_h(wolf) * stage.h[j];
	if (stage.y1[j] == 0 && stage.y2[j] != 0)
	{
		tmp = stage.y2[j];
		stage.y2[j] = H;
		stage.y1[j] = tmp;
		temp_y = stage.y1[j];
	}
	else if (stage.y1[j] == -1 && stage.y2[j] != 0)
	{
		stage.y1[j] = stage.y2[j];
		if (stage.count % 2 == 0)
		{
			tmp = stage.y2[j];
			stage.y2[j] = 0;
			stage.y1[j] = tmp;
			temp_y = stage.y1[j];
		}
		else
		{
			tmp = stage.y2[j];
			stage.y2[j] = H;
			stage.y1[j] = tmp;
			temp_y = stage.y1[j];
		}
	}
	temp_y = stage.y1[j] - (wolf->player->dir_y + diry_correction_from_fly(wolf->player->fly));
	y = stage.y1[j];
	while (temp_y < stage.y2[j])
	{
		if (temp_y >= 0 && temp_y <= H) 
		{
			curr_dist = (H - wolf->player->fly) / (2.0 * (y + wolf->player->fly) - (H - wolf->player->fly));

			weight = curr_dist / (dist->dist[wolf->player->distance[count_distance]->count - 1] / (cof * cof_h));
			
			curr_floorx = weight * (dist->coords[wolf->player->distance[count_distance]->count - 1].x / (cof * cof_h)) + (1.0 - weight) * (wolf->player->x / (cof * cof_h));
			curr_floory = weight * (dist->coords[wolf->player->distance[count_distance]->count - 1].y / (cof * cof_h)) + (1.0 - weight) * (wolf->player->y / (cof * cof_h));
			
			textx = (int)(curr_floorx * wolf->p->floor_texture->w * cof * cof_h) % wolf->p->floor_texture->w;
			texty = (int)(curr_floory * wolf->p->floor_texture->h * cof * cof_h) % wolf->p->floor_texture->h;

			if (textx > 0 && texty > 0)
			{
				color = get_pixel(wolf->p->floor_texture, textx, texty);
				set_pixel(wolf->surface, x, temp_y, color);
			}
		}
		temp_y++;
		y++;
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
		while (to_draw + (int)wolf->sdl->skybox_offset_y > wolf->p->sky_texture->h - 1)
			to_draw -= wolf->p->sky_texture->h;
		while (to_draw_x + (int)wolf->sdl->skybox_offset > wolf->p->sky_texture->w)
			to_draw_x -= wolf->p->sky_texture->w;
		set_pixel(wolf->surface, x, i, get_pixel(wolf->p->sky_texture,
			to_draw_x + (int)wolf->sdl->skybox_offset, to_draw + (int)wolf->sdl->skybox_offset_y));
	}
}
