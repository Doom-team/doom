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
	// int		height;
	double	fractpart, intpart;
	float	koof;
	int		count;
	float	tex_1;
	float	pos;
	int		j;
	signed long long int		temp_y; // чтоб при отдалений не тормозило но там все равно говно выше макс числа
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
		temp_y = size - ceilf((CUBE * wolf->walls[dist->number_wall[j]].h / 5.0f * wolf->player->dist_to_canvas) / wolf->player->distance[count_distance]->dist[j]); // отвечает за высоту ступеньки
		i = 0;
		// if (wolf->z_buff[point.x + (temp_y - wolf->player->dir_y) * W] == true)
		// 	continue;
		// height = H - temp_y * 2; // что это ??
		if (dist->number_wall[j] < 0 && dist->number_wall[j] > wolf->count_walls - 1)
			return ;
		float	offsety;
		int		begin_y = temp_y;
		int		len = size - begin_y;
		float	tex_2 = len / (wolf->walls[dist->number_wall[j]].h / 5.0f);
		float	pos_y;
		double	fractpart_2, intpart_2;
		int		flag = 1;
		temp_y--;
		// printf("temp_y = %lld\n", temp_y);
		while (++temp_y < size)
		{
			if (temp_y - wolf->player->dir_y < -H - 2)
			{
				temp_y = -H - 1 + wolf->player->dir_y;
				continue;
			}
			// if (temp_y - wolf->player->dir_y > H)
			// {
			// 	temp_y = H - 1;
			// 	continue;
			// }
			if ((temp_y - wolf->player->dir_y >= 0 && temp_y - wolf->player->dir_y < H) && (wolf->z_buff[point.x + (temp_y - wolf->player->dir_y) * W] == true))
				continue;
			if (flag == 1)
			{
				count = (int)(round(wolf->walls[dist->number_wall[j]].length / CUBE));
				koof = (wolf->walls[dist->number_wall[j]].length / CUBE) / count;
				tex_1 = (wolf->walls[dist->number_wall[j]].length / count) * koof;
				pos = dist->offsetx[j] * wolf->walls[dist->number_wall[j]].length;
				fractpart = modf((pos / tex_1), &intpart);
				flag = 0;
			}
			if (temp_y - wolf->player->dir_y > 0 && temp_y - wolf->player->dir_y < H)
			{
				offsety = (float)(temp_y - begin_y) / (size - begin_y);
				pos_y = len * offsety;
				fractpart_2 = modf(pos_y / tex_2, &intpart_2);

				color = get_pixel1(wolf->walls[dist->number_wall[j]].texture1, wolf->walls[dist->number_wall[j]].texture1->w * fractpart, fractpart_2 * wolf->walls[dist->number_wall[j]].texture1->w); //где раунд коофицен колличества стен
				set_pixel1(wolf->surface, wolf->walls[dist->number_wall[j]].texture1, point.x, temp_y - wolf->player->dir_y, color);
				wolf->z_buff[point.x + (temp_y - wolf->player->dir_y) * W] = true;
			}
			// temp_y++;
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
	int		to_draw_x;

	i = -1;
	if (y < 0)
		y = 0;
	if (y > H)
		y = H;
	while (++i < y)
	{
		to_draw = i;
		to_draw_x = x;
		while (to_draw + (int)wolf->sdl->skybox_offset_y > wolf->sdl->sky->h - 1)
			to_draw -= wolf->sdl->sky->h;
		while (to_draw_x + (int)wolf->sdl->skybox_offset > wolf->sdl->sky->w)
			to_draw_x -= wolf->sdl->sky->w;
		set_pixel(wolf->surface, x, i, get_pixel(wolf->sdl->sky,
			to_draw_x + (int)wolf->sdl->skybox_offset, to_draw + (int)wolf->sdl->skybox_offset_y));
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

void* threadFunc(void* thread_data){
	//получаем структуру с данными
	pthrData 	*data = thread_data;
	int			end;
 
	data->count_distance = W - W / THREAD * data->number - 1;
	data->point.x = (W * data->number) / THREAD;
	if (data->interlaced_rendering)
		data->point.x++;
	end = ((W * data->number) / THREAD) + (W / THREAD);
	while (data->point.x < end)
	{
		if (data->wolf->player->distance[data->count_distance]->dist[0] != 0)
		{
			data->point.y = ceilf((CUBE * data->wolf->player->dist_to_canvas) / data->wolf->player->distance[data->count_distance]->dist[data->wolf->count_walls - 1]);
			data->point.y = (H - data->point.y) / 2;
			draw_sky(data->wolf, data->point.x, data->point.y - data->wolf->player->dir_y);
			draw_floor(data->wolf->surface, data->point.x, H - (data->point.y + data->wolf->player->dir_y));
			draw_column(data->wolf, data->point, data->wolf->player->distance[data->count_distance], data->count_distance);
		}
		data->count_distance -= 2;
		data->point.x += 2;
	}
	return NULL;
}


void	pseudo_3d(t_wolf *wolf, t_player *player, SDL_Surface *surface)
{
	t_point	point;

	point.y = 0;
	if (wolf->sdl->interlaced_rendering == 0)
		point.x = 0;
	else
		point.x = 1;
	ft_memset(&wolf->z_buff, 0, W * H * sizeof(bool));

	pthread_t* threads = (pthread_t*) malloc(THREAD * sizeof(pthread_t));
	pthrData* threadData = (pthrData*) malloc(THREAD * sizeof(pthrData));
	for(int i = 0; i < THREAD; i++){
		threadData[i].number = i;
		threadData[i].wolf = wolf;
		threadData[i].point = point;
		threadData[i].interlaced_rendering = wolf->sdl->interlaced_rendering;
		threadData[i].count_distance = 0;
		pthread_create(&(threads[i]), NULL, threadFunc, &threadData[i]);
	}
	for(int i = 0; i < THREAD; i++)
		pthread_join(threads[i], NULL);
	free(threads);
	free(threadData);

	if (wolf->sdl->interlaced_rendering == 0)
		wolf->sdl->interlaced_rendering = 1;
	else
		wolf->sdl->interlaced_rendering = 0;
}