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

				color = get_pixel1(wolf->walls[dist->number_wall[j]].texture1, wolf->walls[dist->number_wall[j]].texture1->w * fractpart, fractpart_2 * wolf->walls[dist->number_wall[j]].texture1->h); //где раунд коофицен колличества стен
				set_pixel1(wolf->surface, wolf->walls[dist->number_wall[j]].texture1, point.x, temp_y - wolf->player->dir_y, color);
				wolf->z_buff[point.x + (temp_y - wolf->player->dir_y) * W] = true;
			}
			// temp_y++;
			i++;
		}
	}
}

void	draw_floor(SDL_Surface *surface, int x, int y, int count_distance, t_wolf *wolf, int number)
{
	if (y < 0)
		y = 0;
	float	sub_len_y;
	float	sub_len_x;
	float	len_y;
	float	len_x;
	float	offsety;
	float	offsetx;
	float	cof_1;
	float	cof_2;
	int		begin_y;
	int		begin_x;
	float	tex_1;
	float	tex_2;
	float	pos_y;
	float	pos_x;
	double	fractpart, intpart;
	double	fractpart_2, intpart_2;
	int		color;
	int		delta_y;
	int		delta_x;
	float	delta_cof_y;
	float	delta_cof_x;


	begin_y = y;
	sub_len_y = (wolf->player->distance[count_distance]->coords[wolf->player->distance[count_distance]->count - 1].y - wolf->player->y);
	sub_len_x = (wolf->player->distance[count_distance]->coords[wolf->player->distance[count_distance]->count - 1].x - wolf->player->x);
	cof_1 = sub_len_y / (H - begin_y); // шаг приращение основных координат относительно y
	cof_2 = sub_len_x / (H - begin_y); // шаг приращение основных координат относительно x
	while (y < H)
	{
		pos_y = (wolf->player->distance[count_distance]->coords[wolf->player->distance[count_distance]->count - 1].y - (cof_1 * (y - begin_y)));
		pos_x = (wolf->player->distance[count_distance]->coords[wolf->player->distance[count_distance]->count - 1].x + (cof_2 * (y - begin_y)));
		fractpart = modf((pos_y / CUBE), &intpart);
		fractpart_2 = modf((pos_x / CUBE), &intpart_2);
		color = get_pixel(wolf->sdl->textures, fractpart_2 * wolf->sdl->textures->w , fractpart * wolf->sdl->textures->h);
		set_pixel(surface, x, y, color);
		y++;
	}
}

static void	floorcast(t_wolf *wolf, t_distance *dist, int x, int y, int count_distance)
{
	float curr_dist;
	float weight;
	float currFloorX;
	float currFloorY;
	int textx;
	int texty;
	int color;

	int temp_y;

	temp_y = y - wolf->player->dir_y;

	while (temp_y < H)
	{
		curr_dist = (float)H / (float)(2 * y - H);
		
		weight = curr_dist / (float)(dist->dist[wolf->player->distance[count_distance]->count - 1]);
		
		currFloorX = weight * dist->coords[wolf->player->distance[count_distance]->count - 1].x + (1.0 - weight) * wolf->player->x;
		currFloorY = weight * dist->coords[wolf->player->distance[count_distance]->count - 1].y + (1.0 - weight) * wolf->player->y;
		
		// if (count_distance == H / 2 - 1)
		// 	printf("%f ------ %f\n", currFloorX, currFloorY);
		textx = (int)(currFloorX * wolf->sdl->textures->w) % wolf->sdl->textures->w;
		texty = (int)(currFloorY * wolf->sdl->textures->h) % wolf->sdl->textures->h;
		// if (count_distance == H / 2 - 1)
		// 	printf("%d ------ %d\n", textx, texty);


		if (textx < 0)
			textx = 0;
		if (texty < 0)
			texty = 0;
		color = get_pixel(wolf->sdl->textures, textx, texty);
		set_pixel(wolf->surface, x, temp_y, color);
		// color = get_pixel(wolf->sdl->textures, textx + CUBE * 5, texty);
		// set_pixel(wolf->surface, x, H - y, color);
		temp_y++;
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
			// draw_floor(data->wolf->surface, data->point.x, H - (data->point.y + data->wolf->player->dir_y), data->count_distance, data->wolf, data->number);
			floorcast(data->wolf, data->wolf->player->distance[data->count_distance], data->point.x, H - (data->point.y/* + data->wolf->player->dir_y*/), data->count_distance);
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