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

void			brute_column_fly_1_1(t_wolf *wolf, t_point point, int count_distance, t_data_column *d)
{

}

void			brute_column_fly_1(t_wolf *wolf, t_point point, int count_distance, t_data_column *d)
{
	if (wolf->p->walls[d->dist->number_wall[d->j]].type_flag == 1)
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
		if (d->stage.y2[wolf->p->walls[d->dist->number_wall[d->j]].squad_stage - 1] != 0 && d->stage.y1[wolf->p->walls[d->dist->number_wall[d->j]].squad_stage - 1] != 0)
		{
			d->stage.h[wolf->p->walls[d->dist->number_wall[d->j]].squad_stage - 1] = wolf->p->walls[d->dist->number_wall[d->j]].h;
			d->sub_stage.h[d->stage.count] = d->stage.h[wolf->p->walls[d->dist->number_wall[d->j]].squad_stage - 1];
			d->sub_stage.y1[d->stage.count] = d->stage.y1[wolf->p->walls[d->dist->number_wall[d->j]].squad_stage - 1];
			d->sub_stage.y2[d->stage.count] = d->stage.y2[wolf->p->walls[d->dist->number_wall[d->j]].squad_stage - 1];
			d->sub_stage.dist[d->stage.count] = d->stage.dist[wolf->p->walls[d->dist->number_wall[d->j]].squad_stage - 1];
			d->stage.count++;
		}
	}
}

void			brute_column_fly(t_wolf *wolf, t_point point, int count_distance, t_data_column *d)
{
	while (++d->j < d->dist->count)
	{
		d->temp_y = ceilf((wolf->player->dist_to_canvas) / wolf->player->distance[count_distance]->dist[d->j]);
		d->temp_y = (H - d->temp_y) / 2;
		d->size = H - d->temp_y;
		d->temp_y = d->size - ceilf((wolf->p->walls[d->dist->number_wall[d->j]].h / 5.0f * wolf->player->dist_to_canvas) / wolf->player->distance[count_distance]->dist[d->j]);
		if (wolf->p->walls[d->dist->number_wall[d->j]].active != 1)
			continue;
		brute_column_fly_1(wolf, point, count_distance, d);
		if (d->dist->number_wall[d->j] < 0 && d->dist->number_wall[d->j] > wolf->p->count_walls - 1)
			return ;
		d->begin_y = d->temp_y;
		d->len = d->size - d->begin_y;
		d->tex_2 = d->len / (wolf->p->walls[d->dist->number_wall[d->j]].h / 5.0f);
		d->flag = 1;

		d->temp_y--;
		while (++d->temp_y < d->size)
		{
			if (d->temp_y - (wolf->player->dir_y + fly_correction_from_dist(wolf, d->j, count_distance)) > H)
				break;
			if (d->temp_y - (wolf->player->dir_y + fly_correction_from_dist(wolf, d->j, count_distance)) < -H - 2)
			{
				d->temp_y = -H - 1 + (wolf->player->dir_y + fly_correction_from_dist(wolf, d->j, count_distance));
				continue;
			}
			if ((d->temp_y - wolf->player->dir_y >= 0 && d->temp_y - wolf->player->dir_y < H) && (wolf->z_buff[point.x + (d->temp_y - wolf->player->dir_y) * W] == true))
				continue;
			if (d->flag == 1)
			{
				d->count = (int)(round(wolf->p->walls[d->dist->number_wall[d->j]].length));
				d->koof = (wolf->p->walls[d->dist->number_wall[d->j]].length) / d->count;
				d->tex_1 = (wolf->p->walls[d->dist->number_wall[d->j]].length / d->count) * d->koof;
				d->pos = d->dist->offsetx[d->j] * wolf->p->walls[d->dist->number_wall[d->j]].length;
				d->fractpart = modf((d->pos / d->tex_1), &d->intpart);
				d->flag = 0;
			}
			if (d->temp_y - (wolf->player->dir_y + fly_correction_from_dist(wolf, d->j, count_distance)) > 0 && d->temp_y - (wolf->player->dir_y + fly_correction_from_dist(wolf, d->j, count_distance)) < H)
			{
				d->offsety = (float)(d->temp_y - d->begin_y) / (d->size - d->begin_y);
				d->pos_y = d->len * d->offsety;
				d->fractpart_2 = modf(d->pos_y / d->tex_2, &d->intpart_2);
				d->color = get_pixel(wolf->p->walls[d->dist->number_wall[d->j]].texture1, wolf->p->walls[d->dist->number_wall[d->j]].texture1->w * d->fractpart, d->fractpart_2 * wolf->p->walls[d->dist->number_wall[d->j]].texture1->h); //где раунд коофицен колличества стен
				if (d->color != 0)
					set_pixel(wolf->surface, point.x, d->temp_y - (wolf->player->dir_y + fly_correction_from_dist(wolf, d->j, count_distance)), d->color);
				if (point.x == W / 2 && H / 2 < d->size && H / 2 > d->begin_y)
				{
					if (wolf->bon->flag_guns == 2 && wolf->p->walls[d->dist->number_wall[d->j]].type_flag == 3 && wolf->p->walls[d->dist->number_wall[d->j]].active == 1)
					{
						wolf->p->walls[d->dist->number_wall[d->j]].active = 0;
						wolf->bon->score++;
					}
				}
			}
		}
	}
}

void			cut_ctage(t_wolf *wolf, t_point point, int count_distance, t_data_column *d)
{
	int	i;

	d->sub_stage.count = d->stage.count;
	d->j = 0;
	while (d->j < d->stage.count)
	{
		i = 0;
		while (++i < 4)
		{
			if (d->sub_stage.dist[d->j] == d->sub_stage.dist[d->j + i])
			{
				d->sub_stage.y1[d->j] = 0.f;
				d->sub_stage.y2[d->j] = 0.f;
				d->sub_stage.dist[d->j] = 0.f;
				d->sub_stage.h[d->j] = 0;
			}
		}
		d->j++;
	}
	d->j = -1;
}

int			upper_level_draw_1(t_wolf *wolf, t_point point, int count_distance, t_data_column *d)
{
	d->j = d->dist->count - 1;
	if (d->j == -1)
		return (1);
	d->temp_y = ceilf((wolf->player->dist_to_canvas) / wolf->player->distance[count_distance]->dist[d->j]);
	d->temp_y = (H - d->temp_y) / 2;
	d->size = H - d->temp_y;
	d->temp_y = d->size - ceilf((wolf->p->walls[d->dist->number_wall[d->j]].h / 5.0f * wolf->player->dist_to_canvas) / wolf->player->distance[count_distance]->dist[d->j]);
	if (d->dist->number_wall[d->j] < 0 && d->dist->number_wall[d->j] > wolf->p->count_walls - 1)
		return (1);
	d->begin_y = d->temp_y;
	d->len = d->size - d->begin_y;
	d->tex_2 = d->len / (wolf->p->walls[d->dist->number_wall[d->j]].h / 5.0f);
	d->flag = 1;
	d->temp_y--;
	return (0);
}

void			upper_level_draw_2(t_wolf *wolf, t_point point, int count_distance, t_data_column *d)
{
	if (d->flag == 1)
	{
		d->count = (int)(round(wolf->p->walls[d->dist->number_wall[d->j]].length));
		d->koof = (wolf->p->walls[d->dist->number_wall[d->j]].length) / d->count;
		d->tex_1 = (wolf->p->walls[d->dist->number_wall[d->j]].length / d->count) * d->koof;
		d->pos = d->dist->offsetx[d->j] * wolf->p->walls[d->dist->number_wall[d->j]].length;
		d->fractpart = modf((d->pos / d->tex_1), &d->intpart);
		d->flag = 0;
	}
	if (d->temp_y - (wolf->player->dir_y + fly_correction_from_dist(wolf, d->j, count_distance)) > 0 && d->temp_y - (wolf->player->dir_y + fly_correction_from_dist(wolf, d->j, count_distance)) < H)
	{
		d->offsety = (float)(d->temp_y - d->begin_y) / (d->size - d->begin_y);
		d->pos_y = d->len * d->offsety;
		d->fractpart_2 = modf(d->pos_y / d->tex_2, &d->intpart_2);
		d->color = get_pixel(wolf->p->walls[d->dist->number_wall[d->j]].texture1, wolf->p->walls[d->dist->number_wall[d->j]].texture1->w * d->fractpart, d->fractpart_2 * wolf->p->walls[d->dist->number_wall[d->j]].texture1->h); //где раунд коофицен колличества стен
		if (d->color != 0)
			set_pixel(wolf->surface, point.x, d->temp_y - (wolf->player->dir_y + fly_correction_from_dist(wolf, d->j, count_distance)), d->color);
	}
}

void			upper_level_draw(t_wolf *wolf, t_point point, int count_distance, t_data_column *d)
{
	if (d->stage.count % 2 == 0)
	{
		if (upper_level_draw_1(wolf, point, count_distance, d))
			return ;
		while (++d->temp_y < d->size)
		{
			if (wolf->p->walls[d->dist->number_wall[d->j]].active != 1)
				break;
			if (d->temp_y - (wolf->player->dir_y + fly_correction_from_dist(wolf, d->j, count_distance)) > H)
				break;
			if (d->temp_y - (wolf->player->dir_y + fly_correction_from_dist(wolf, d->j, count_distance)) < -H - 2)
			{
				d->temp_y = -H - 1 + (wolf->player->dir_y + fly_correction_from_dist(wolf, d->j, count_distance));
				continue;
			}
			if ((d->temp_y - wolf->player->dir_y >= 0 && d->temp_y - wolf->player->dir_y < H) && (wolf->z_buff[point.x + (d->temp_y - wolf->player->dir_y) * W] == true))
				continue;
			upper_level_draw_2(wolf, point, count_distance, d);
		}
	}
}

void			draw_column_fly(t_wolf *wolf, t_point point, int count_distance)
{
	t_data_column			d;

	d.dist = wolf->player->distance[count_distance];
	d.j = -1;
	d.flagg = 0;
	brute_column_fly(wolf, point, count_distance, &d);
	cut_ctage(wolf, point, count_distance, &d);
	while (++d.j < d.stage.count)
		floorcast_up_fly(wolf, wolf->player->distance[count_distance], point.x, count_distance, d.sub_stage, d.j);
	upper_level_draw(wolf, point, count_distance, &d);
}

void			draw_column(t_wolf *wolf, t_point point, t_distance *dist, int count_distance)
{
	int						color;
	double					fractpart;
	double					intpart;
	float					koof;
	int						count;
	float					tex_1;
	float					pos;
	int						j;
	signed long long int	temp_y;
	int						size;
	t_floot_up				stage;
	t_floot_up				sub_stage;

	j = -1;
	while (++j < dist->count)
	{
		temp_y = ceilf((wolf->player->dist_to_canvas) / wolf->player->distance[count_distance]->dist[j]);
		temp_y = (H - temp_y) / 2;
		size = H - temp_y;
		temp_y = size - ceilf((wolf->p->walls[dist->number_wall[j]].h / 5.0f * wolf->player->dist_to_canvas) / wolf->player->distance[count_distance]->dist[j]); // отвечает за высоту ступеньки
		if (wolf->p->walls[dist->number_wall[j]].active != 1)
			continue;
		if (wolf->p->walls[dist->number_wall[j]].type_flag == 1)
		{
			if (stage.dist[wolf->p->walls[dist->number_wall[j]].squad_stage - 1] == 0)
				stage.dist[wolf->p->walls[dist->number_wall[j]].squad_stage - 1] = wolf->player->distance[count_distance]->dist[j];
			else if (wolf->player->distance[count_distance]->dist[j] < stage.dist[wolf->p->walls[dist->number_wall[j]].squad_stage - 1])
				stage.dist[wolf->p->walls[dist->number_wall[j]].squad_stage - 1] = wolf->player->distance[count_distance]->dist[j];
			if (stage.y2[wolf->p->walls[dist->number_wall[j]].squad_stage - 1] < temp_y)
			{
				stage.y2[wolf->p->walls[dist->number_wall[j]].squad_stage - 1] = temp_y;
				stage.y1[wolf->p->walls[dist->number_wall[j]].squad_stage - 1] = -1;
			}
			else if (stage.y1[wolf->p->walls[dist->number_wall[j]].squad_stage - 1] < temp_y)
				stage.y1[wolf->p->walls[dist->number_wall[j]].squad_stage - 1] = temp_y;
			if (stage.y2[wolf->p->walls[dist->number_wall[j]].squad_stage - 1] != 0)
			{
				stage.h[wolf->p->walls[dist->number_wall[j]].squad_stage - 1] = wolf->p->walls[dist->number_wall[j]].h;
				sub_stage.h[stage.count] = stage.h[wolf->p->walls[dist->number_wall[j]].squad_stage - 1];
				sub_stage.y1[stage.count] = stage.y1[wolf->p->walls[dist->number_wall[j]].squad_stage - 1];
				sub_stage.y2[stage.count] = stage.y2[wolf->p->walls[dist->number_wall[j]].squad_stage - 1];
				sub_stage.dist[stage.count] = stage.dist[wolf->p->walls[dist->number_wall[j]].squad_stage - 1];
				stage.count++;
			}
		}
		if (dist->number_wall[j] < 0 && dist->number_wall[j] > wolf->p->count_walls - 1)
			return ;
		float	offsety;
		int		begin_y = temp_y;
		int		len = size - begin_y;
		float	tex_2 = len / (wolf->p->walls[dist->number_wall[j]].h / 5.0f);
		float	pos_y;
		double	fractpart_2;
		double	intpart_2;
		int		flag = 1;

		temp_y--;
		while (++temp_y < size)
		{
			if (temp_y - wolf->player->dir_y > H)
				break;
			if (temp_y - wolf->player->dir_y < -H - 2)
			{
				temp_y = -H - 1 + wolf->player->dir_y;
				continue;
			}
			if ((temp_y - wolf->player->dir_y >= 0 && temp_y - wolf->player->dir_y < H) && (wolf->z_buff[point.x + (temp_y - wolf->player->dir_y) * W] == true))
				continue;
			if (flag == 1)
			{
				count = (int)(round(wolf->p->walls[dist->number_wall[j]].length));
				koof = (wolf->p->walls[dist->number_wall[j]].length) / count;
				tex_1 = (wolf->p->walls[dist->number_wall[j]].length / count) * koof;
				pos = dist->offsetx[j] * wolf->p->walls[dist->number_wall[j]].length;
				fractpart = modf((pos / tex_1), &intpart);
				flag = 0;
			}
			if (temp_y - wolf->player->dir_y > 0 && temp_y - wolf->player->dir_y < H)
			{
				offsety = (float)(temp_y - begin_y) / (size - begin_y);
				pos_y = len * offsety;
				fractpart_2 = modf(pos_y / tex_2, &intpart_2);
				color = get_pixel(wolf->p->walls[dist->number_wall[j]].texture1, wolf->p->walls[dist->number_wall[j]].texture1->w * fractpart, fractpart_2 * wolf->p->walls[dist->number_wall[j]].texture1->h); //где раунд коофицен колличества стен
				if (color != 0)
				{
					set_pixel(wolf->surface, point.x, temp_y - wolf->player->dir_y, color);
					wolf->z_buff[point.x + (temp_y - wolf->player->dir_y) * W] = true;
				}
				if (point.x == W / 2 && H / 2 < size && H / 2 > begin_y)
				{
					if (wolf->bon->flag_guns == 2 && wolf->p->walls[dist->number_wall[j]].type_flag == 3 && wolf->p->walls[dist->number_wall[j]].active == 1)
					{
						wolf->p->walls[dist->number_wall[j]].active = 0;
						wolf->bon->score++;
					}
				}
			}
		}
	}
	sub_stage.count = stage.count;
	j = 0;
	while (j < stage.count)
	{
		if (sub_stage.dist[j] == sub_stage.dist[j + 1])
		{
			sub_stage.y1[j] = 0.f;
			sub_stage.y2[j] = 0.f;
			sub_stage.dist[j] = 0.f;
			sub_stage.h[j] = 0;
		}
		if (sub_stage.dist[j] == sub_stage.dist[j + 2])
		{
			sub_stage.y1[j] = 0.f;
			sub_stage.y2[j] = 0.f;
			sub_stage.dist[j] = 0.f;
			sub_stage.h[j] = 0;
		}
		if (sub_stage.dist[j] == sub_stage.dist[j + 3])
		{
			sub_stage.y1[j] = 0.f;
			sub_stage.y2[j] = 0.f;
			sub_stage.dist[j] = 0.f;
			sub_stage.h[j] = 0;
		}
		j++;
	}
	j = -1;
	while (++j < stage.count)
		floorcast_up(wolf, wolf->player->distance[count_distance], point.x, count_distance, sub_stage, j);
	j = 0;
	temp_y = ceilf((wolf->player->dist_to_canvas) / wolf->player->distance[count_distance]->dist[j]);
	temp_y = (H - temp_y) / 2;
	size = H - temp_y;
	temp_y = size - ceilf((wolf->p->walls[dist->number_wall[j]].h / 5.0f * wolf->player->dist_to_canvas) / wolf->player->distance[count_distance]->dist[j]); // отвечает за высоту ступеньки

	if (dist->number_wall[j] < 0 && dist->number_wall[j] > wolf->p->count_walls - 1)
		return ;
	float	offsety;
	int		begin_y = temp_y;
	int		len = size - begin_y;
	float	tex_2 = len / (wolf->p->walls[dist->number_wall[j]].h / 5.0f);
	float	pos_y;
	double	fractpart_2, intpart_2;
	int		flag = 1;

	temp_y--;
	while (++temp_y < size)
	{
		if (wolf->p->walls[dist->number_wall[j]].active != 1)
			break;
		if (temp_y - wolf->player->dir_y > H)
			break;
		if (temp_y - wolf->player->dir_y < -H - 2)
		{
			temp_y = -H - 1 + wolf->player->dir_y;
			continue;
		}
		if (temp_y - wolf->player->dir_y < 0 || temp_y - wolf->player->dir_y > H)
			continue;
		if (flag == 1)
		{
			count = (int)(round(wolf->p->walls[dist->number_wall[j]].length));
			koof = (wolf->p->walls[dist->number_wall[j]].length) / count;
			tex_1 = (wolf->p->walls[dist->number_wall[j]].length / count) * koof;
			pos = dist->offsetx[j] * wolf->p->walls[dist->number_wall[j]].length;
			fractpart = modf((pos / tex_1), &intpart);
			flag = 0;
		}
		if ((temp_y - wolf->player->dir_y > 0 && temp_y - wolf->player->dir_y < H))
		{
			offsety = (float)(temp_y - begin_y) / (size - begin_y);
			pos_y = len * offsety;
			fractpart_2 = modf(pos_y / tex_2, &intpart_2);
			color = get_pixel(wolf->p->walls[dist->number_wall[j]].texture1, wolf->p->walls[dist->number_wall[j]].texture1->w * fractpart, fractpart_2 * wolf->p->walls[dist->number_wall[j]].texture1->h); //где раунд коофицен колличества стен
			if (color != 0)
				set_pixel(wolf->surface, point.x, temp_y - wolf->player->dir_y, color);
		}
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
