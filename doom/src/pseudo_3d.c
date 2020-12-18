/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudo_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:31:45 by clala             #+#    #+#             */
/*   Updated: 2020/12/16 21:05:32 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	draw_column(t_wolf *wolf,
t_point point, t_distance *dist, int count_distance)
{
	int		color;
	int		i;
	int		height;
	double	fractpart, intpart;
	float	koof;
	int		count;
	float	tex_1;
	float	pos;
	int		j;
	int		temp_y;
	int		size;

	// поинт y начало отрисовки стены сайз конец
	// temp_y -= wolf->player->dir_y;
	// size -= wolf->player->dir_y;
	j = -1;
	while (++j < dist->count)
	{
		// if (wolf->walls[dist->number_wall[j]].h == 1)
		// 	temp_y = ceilf((CUBE / 10 * wolf->player->dist_to_canvas) / wolf->player->distance[count_distance]->dist[j]);
		// else
		temp_y = ceilf((CUBE * wolf->player->dist_to_canvas) / wolf->player->distance[count_distance]->dist[j]);
		temp_y = (H - temp_y) / 2;
		size = H - temp_y;
		temp_y = size - ceilf((CUBE * wolf->walls[dist->number_wall[j]].h / 5 * wolf->player->dist_to_canvas) / wolf->player->distance[count_distance]->dist[j]); // отвечает за высоту ступеньки
		i = 0;
		height = H - temp_y * 2;
		if (dist->number_wall[j] >= 0 && dist->number_wall[j] <= wolf->count_walls - 1)
		{
			count = (int)(round(wolf->walls[dist->number_wall[j]].length / CUBE));
			koof = (wolf->walls[dist->number_wall[j]].length / CUBE) / count;
			tex_1 = (wolf->walls[dist->number_wall[j]].length / count) * koof;
			pos = dist->offsetx[j] * wolf->walls[dist->number_wall[j]].length;
			fractpart = modf((pos / tex_1), &intpart);
		}
		else
			return ;
		while (temp_y < size)
		{
			if (temp_y - wolf->player->dir_y > 0 && temp_y - wolf->player->dir_y < H)
			{
				color = get_pixel1(wolf->walls[dist->number_wall[j]].texture1, wolf->walls[dist->number_wall[j]].texture1->w * fractpart, i * wolf->walls[dist->number_wall[j]].texture1->w / height); //где раунд коофицен колличества стен
				set_pixel1(wolf->surface, wolf->walls[dist->number_wall[j]].texture1, point.x, temp_y - wolf->player->dir_y, color);
			}
			temp_y++;
			i++;
		}
	}
}

void	draw_floor(SDL_Surface *surface, int x, int y)
{
	if (y < 0)
		y = 0;
	while (y < H)
	{
		set_pixel(surface, x, y, COLOR_GREY_LIGHT);
		y++;
	}
}

void	draw_sky(t_wolf *wolf, int x, int y)
{
	int		i;
	int		to_draw;

	i = -1;
	if (y < 0)
		y = 0;
	if (y > H)
		y = H;
	while (++i < y)
	{
		to_draw = i < wolf->sdl->sky->h - 1 ? i : wolf->sdl->sky->h / 2;
		set_pixel(wolf->surface, x, i, get_pixel(wolf->sdl->sky,
			x + wolf->sdl->skybox_offset, to_draw));
	}
}

// static void	floorcast(t_wolf *wolf, t_distance *dist, int x, int y)
// {
// 	float curr_dist;
// 	float weight;
// 	float currFloorX;
// 	float currFloorY;
// 	int textx;
// 	int texty;
// 	int color;

// 	int temp_y;

// 	temp_y = y - wolf->player->dir_y;
// 	while (temp_y < H)
// 	{
// 		curr_dist = (float)H / (float)(2 * y - H);
		
// 		weight = curr_dist / (dist->dist);
		
// 		currFloorX = weight * dist->coords.x + (1.f - weight) * wolf->player->x;
// 		currFloorY = weight * dist->coords.y + (1.f - weight) * wolf->player->y;
		
// 		textx = (int)(currFloorX * CUBE) % CUBE;
// 		texty = (int)(currFloorY * CUBE) % CUBE;
		
// 		if (textx < 0)
// 			textx = 0;
// 		if (texty < 0)
// 			texty = 0;
		
// 		color = get_pixel(wolf->sdl->textures, textx, texty);
// 		set_pixel(wolf->surface, x, temp_y, color);
// 		// color = get_pixel(wolf->sdl->textures, textx + CUBE * 5, texty);
// 		// set_pixel(wolf->surface, x, H - y, color);
// 		temp_y++;
// 		y++;
// 	}
// }

void	pseudo_3d(t_wolf *wolf, t_player *player, SDL_Surface *surface)
{
	t_point	point;
	int		count_distance;
	float	dir;

	count_distance = W - 1;
	dir = player->dir;
	add_arc(&dir, player->fov / 2);
	point.y = 0;
	if (wolf->sdl->interlaced_rendering == 0)
		point.x = 0;
	else
		point.x = 1;
	while (point.x < W)
	{
		if (player->distance[count_distance]->dist[0] != 0)
		{
			point.y = ceilf((CUBE * player->dist_to_canvas) / player->distance[count_distance]->dist[0]);
			point.y = (H - point.y) / 2; // сколько отступ сверху и снизу
			draw_sky(wolf, point.x, point.y - wolf->player->dir_y);
			// floorcast(wolf, player->distance[count_distance], point.x, H - (point.y) + 1);
			draw_floor(surface, point.x, H - (point.y + wolf->player->dir_y));
			draw_column(wolf, point, player->distance[count_distance], count_distance);
		}
		count_distance -= 2;
		point.x += 2;
		add_arc(&dir, -player->step);
	}
	if (wolf->sdl->interlaced_rendering == 0)
		wolf->sdl->interlaced_rendering = 1;
	else
		wolf->sdl->interlaced_rendering = 0;
}