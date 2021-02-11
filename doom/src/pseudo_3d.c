/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudo_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:31:45 by skaren            #+#    #+#             */
/*   Updated: 2021/02/09 16:20:04 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			draw_column_fly(t_wolf *wolf, t_point point, t_distance *dist, int count_distance)
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

	ft_memset(&stage, 0, sizeof(t_floot_up));
	j = -1;
	int flagg = 0;
	while (++j < dist->count)
	{
		temp_y = ceilf((wolf->player->dist_to_canvas) / wolf->player->distance[count_distance]->dist[j]);
		temp_y = (H - temp_y) / 2;
		size = H - temp_y;
		temp_y = size - ceilf((wolf->p->walls[dist->number_wall[j]].h / 5.0f * wolf->player->dist_to_canvas) / wolf->player->distance[count_distance]->dist[j]);
		if (wolf->p->walls[dist->number_wall[j]].active != 1)
			continue;
		if (wolf->p->walls[dist->number_wall[j]].type_flag == 1)
		{
			if (stage.dist[wolf->p->walls[dist->number_wall[j]].squad_stage - 1] == 0)
			{
				flagg = 0;
				stage.dist[wolf->p->walls[dist->number_wall[j]].squad_stage - 1] = wolf->player->distance[count_distance]->dist[j];
			}
			if (stage.y2[wolf->p->walls[dist->number_wall[j]].squad_stage - 1] < temp_y - (fly_correction_from_dist(wolf, j, count_distance) + fly_correct_fuf(wolf))
				&& flagg != 1)
			{
				flagg = 1;
				stage.y2[wolf->p->walls[dist->number_wall[j]].squad_stage - 1] = temp_y - (fly_correction_from_dist(wolf, j, count_distance) + fly_correct_fuf(wolf));
				stage.y1[wolf->p->walls[dist->number_wall[j]].squad_stage - 1] = -1;
			}
			else if (stage.y1[wolf->p->walls[dist->number_wall[j]].squad_stage - 1] < temp_y - (fly_correction_from_dist(wolf, j, count_distance)))
			{
				if (stage.y1[wolf->p->walls[dist->number_wall[j]].squad_stage - 1] == -1)
					stage.y1[wolf->p->walls[dist->number_wall[j]].squad_stage - 1] = stage.y2[wolf->p->walls[dist->number_wall[j]].squad_stage - 1];
				stage.y2[wolf->p->walls[dist->number_wall[j]].squad_stage - 1] = temp_y - (wolf->player->dir_y + fly_correction_from_dist(wolf, j, count_distance));
			}
			if (stage.y2[wolf->p->walls[dist->number_wall[j]].squad_stage - 1] != 0 && stage.y1[wolf->p->walls[dist->number_wall[j]].squad_stage - 1] != 0)
			{
				stage.h[wolf->p->walls[dist->number_wall[j]].squad_stage - 1] = wolf->p->walls[dist->number_wall[j]].h;
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
			if (temp_y - (wolf->player->dir_y + fly_correction_from_dist(wolf, j, count_distance)) > H)
				break;
			if (temp_y - (wolf->player->dir_y + fly_correction_from_dist(wolf, j, count_distance)) < -H - 2)
			{
				temp_y = -H - 1 + (wolf->player->dir_y + fly_correction_from_dist(wolf, j, count_distance));
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
			if (temp_y - (wolf->player->dir_y + fly_correction_from_dist(wolf, j, count_distance)) > 0 && temp_y - (wolf->player->dir_y + fly_correction_from_dist(wolf, j, count_distance)) < H)
			{
				offsety = (float)(temp_y - begin_y) / (size - begin_y);
				pos_y = len * offsety;
				fractpart_2 = modf(pos_y / tex_2, &intpart_2);
				color = get_pixel(wolf->p->walls[dist->number_wall[j]].texture1, wolf->p->walls[dist->number_wall[j]].texture1->w * fractpart, fractpart_2 * wolf->p->walls[dist->number_wall[j]].texture1->h); //где раунд коофицен колличества стен
				if (color != 0)
					set_pixel(wolf->surface, point.x, temp_y - (wolf->player->dir_y + fly_correction_from_dist(wolf, j, count_distance)), color);
				if (point.x == W / 2 && H / 2 < size && H / 2 > begin_y)
				{
					if (wolf->bon->guns_fire == 1 && wolf->p->walls[dist->number_wall[j]].type_flag == 3)
						wolf->p->walls[dist->number_wall[j]].active = 0;
				}
			}
		}
	}
	stage.count += 100;
	j = -1;
	while (++j < stage.count)
		floorcast_up_fly(wolf, wolf->player->distance[count_distance], point.x, count_distance, stage, j);
	if (stage.count % 2 == 0)
	{
		j = dist->count - 1;
		if (j == -1)
			return ;
		temp_y = ceilf((wolf->player->dist_to_canvas) / wolf->player->distance[count_distance]->dist[j]);
		temp_y = (H - temp_y) / 2;
		size = H - temp_y;
		temp_y = size - ceilf((wolf->p->walls[dist->number_wall[j]].h / 5.0f * wolf->player->dist_to_canvas) / wolf->player->distance[count_distance]->dist[j]);
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
			if (wolf->p->walls[dist->number_wall[j]].active != 1)
				break;
			if (temp_y - (wolf->player->dir_y + fly_correction_from_dist(wolf, j, count_distance)) > H)
				break;
			if (temp_y - (wolf->player->dir_y + fly_correction_from_dist(wolf, j, count_distance)) < -H - 2)
			{
				temp_y = -H - 1 + (wolf->player->dir_y + fly_correction_from_dist(wolf, j, count_distance));
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
			if (temp_y - (wolf->player->dir_y + fly_correction_from_dist(wolf, j, count_distance)) > 0 && temp_y - (wolf->player->dir_y + fly_correction_from_dist(wolf, j, count_distance)) < H)
			{
				offsety = (float)(temp_y - begin_y) / (size - begin_y);
				pos_y = len * offsety;
				fractpart_2 = modf(pos_y / tex_2, &intpart_2);
				color = get_pixel(wolf->p->walls[dist->number_wall[j]].texture1, wolf->p->walls[dist->number_wall[j]].texture1->w * fractpart, fractpart_2 * wolf->p->walls[dist->number_wall[j]].texture1->h); //где раунд коофицен колличества стен
				if (color != 0)
					set_pixel(wolf->surface, point.x, temp_y - (wolf->player->dir_y + fly_correction_from_dist(wolf, j, count_distance)), color);
			}
		}
	}
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

	ft_memset(&stage, 0, sizeof(t_floot_up));
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
			if (stage.y2[wolf->p->walls[dist->number_wall[j]].squad_stage - 1] != 0 && stage.y1[wolf->p->walls[dist->number_wall[j]].squad_stage - 1] != 0)
			{
				stage.h[wolf->p->walls[dist->number_wall[j]].squad_stage - 1] = wolf->p->walls[dist->number_wall[j]].h;
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
					if (wolf->bon->guns_fire == 1 && wolf->p->walls[dist->number_wall[j]].type_flag == 3)
						wolf->p->walls[dist->number_wall[j]].active = 0;
				}
			}
		}
	}
	j = -1;
	stage.count += 100;
	while (++j < stage.count)
		floorcast_up(wolf, wolf->player->distance[count_distance], point.x, count_distance, stage, j);

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

	cof = cof_size_displ();
	cof_h = -0.4 * stage.h[j] + 1.0  + correct_cof_h(wolf) * stage.h[j];
	if ((stage.y1[j] == 0 && stage.y2[j] == 0))
		return ;
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
