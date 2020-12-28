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
	signed long long int	temp_y;//чтоб при отдалений не тормозило но там все равно говно выше макс числа
	int						size;
	t_floot_up				stage;

	ft_memset(&stage, 0, sizeof(t_floot_up));
	j = -1;
	while (++j < dist->count)
	{
		temp_y = ceilf((CUBE * wolf->player->dist_to_canvas) / wolf->player->distance[count_distance]->dist[j]);
		temp_y = (H - temp_y) / 2;
		size = H - temp_y;
		temp_y = size - ceilf((CUBE * wolf->walls[dist->number_wall[j]].h / 5.0f * wolf->player->dist_to_canvas) / wolf->player->distance[count_distance]->dist[j]); // отвечает за высоту ступеньки

		if (wolf->walls[dist->number_wall[j]].type_flag == 1)
		{
			if (stage.dist[wolf->walls[dist->number_wall[j]].squad_stage - 1] == 0)
				stage.dist[wolf->walls[dist->number_wall[j]].squad_stage - 1] = wolf->player->distance[count_distance]->dist[j];
			else if (wolf->player->distance[count_distance]->dist[j] < stage.dist[wolf->walls[dist->number_wall[j]].squad_stage - 1])
				stage.dist[wolf->walls[dist->number_wall[j]].squad_stage - 1] = wolf->player->distance[count_distance]->dist[j];
			if (stage.y2[wolf->walls[dist->number_wall[j]].squad_stage - 1] < temp_y)
			{
				stage.y2[wolf->walls[dist->number_wall[j]].squad_stage - 1] = temp_y;
				stage.y1[wolf->walls[dist->number_wall[j]].squad_stage - 1] = -1; // и тут по вертикальным полосам
			}
			else if (stage.y1[wolf->walls[dist->number_wall[j]].squad_stage - 1] < temp_y)
				stage.y1[wolf->walls[dist->number_wall[j]].squad_stage - 1] = temp_y;
			if (stage.y2[wolf->walls[dist->number_wall[j]].squad_stage - 1] != 0/* && stage.y2[wolf->walls[dist->number_wall[j]].squad_stage - 1] != 0*/)
			{
				stage.h[wolf->walls[dist->number_wall[j]].squad_stage - 1] = wolf->walls[dist->number_wall[j]].h;
				stage.count++;
			}
		}
		if (dist->number_wall[j] < 0 && dist->number_wall[j] > wolf->count_walls - 1)
			return ;
		float	offsety;
		int		begin_y = temp_y;
		int		len = size - begin_y;
		float	tex_2 = len / (wolf->walls[dist->number_wall[j]].h / 5.0f);
		float	pos_y;
		double	fractpart_2;
		double	intpart_2;
		int		flag = 1;

		temp_y--;
		while (++temp_y < size)
		{
			if (temp_y - wolf->player->dir_y < -H - 2)
			{
				temp_y = -H - 1 + wolf->player->dir_y;
				continue;
			}
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
				color = get_pixel(wolf->walls[dist->number_wall[j]].texture1, wolf->walls[dist->number_wall[j]].texture1->w * fractpart, fractpart_2 * wolf->walls[dist->number_wall[j]].texture1->h); //где раунд коофицен колличества стен
				set_pixel(wolf->surface, point.x, temp_y - wolf->player->dir_y, color);
				wolf->z_buff[point.x + (temp_y - wolf->player->dir_y) * W] = true;
			}
		}
	}
	j = -1;
	stage.count++;
	// printf("%d\n", stage.count);
	while (++j < stage.count)
		floorcast_up(wolf, wolf->player->distance[count_distance], point.x, count_distance, stage, j);

	j = 0;
	temp_y = ceilf((CUBE * wolf->player->dist_to_canvas) / wolf->player->distance[count_distance]->dist[j]);
	temp_y = (H - temp_y) / 2;
	size = H - temp_y;
	temp_y = size - ceilf((CUBE * wolf->walls[dist->number_wall[j]].h / 5.0f * wolf->player->dist_to_canvas) / wolf->player->distance[count_distance]->dist[j]); // отвечает за высоту ступеньки

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
	while (++temp_y < size)
	{
		if (temp_y - wolf->player->dir_y < -H - 2)
		{
			temp_y = -H - 1 + wolf->player->dir_y;
			continue;
		}
		if (temp_y - wolf->player->dir_y < 0 || temp_y - wolf->player->dir_y > H)
			continue;
		if (wolf->z_buff_2[point.x + (temp_y - wolf->player->dir_y) * W] == false)
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
		if ((temp_y - wolf->player->dir_y > 0 && temp_y - wolf->player->dir_y < H) && stage.count % 2 != 0)
		{
			// printf("%d\n", stage.count);
			offsety = (float)(temp_y - begin_y) / (size - begin_y);
			pos_y = len * offsety;
			fractpart_2 = modf(pos_y / tex_2, &intpart_2);
			color = get_pixel(wolf->walls[dist->number_wall[j]].texture1, wolf->walls[dist->number_wall[j]].texture1->w * fractpart, fractpart_2 * wolf->walls[dist->number_wall[j]].texture1->h); //где раунд коофицен колличества стен
			set_pixel(wolf->surface, point.x, temp_y - wolf->player->dir_y, color);
		}
	}
}

void			floorcast_up(t_wolf *wolf, t_distance *dist, int x, int count_distance, t_floot_up stage, int j)
{
	float	curr_dist;
	float	weight;
	float	currFloorX;
	float	currFloorY;
	int		textx;
	int		texty;
	int		color;
	int		temp_y;
	int		y;
	int		tmp;
	float	cof = 0.8654409 * pow((W * 1.0f / H), 1.0118661);
	float	cof_h = -0.4 * stage.h[j] + 1;

	// printf("%d\n", wolf->walls[dist->number_wall[j]].h);
	// printf("%d ----%d\n", stage.y1[j], stage.y2[j]);
	if ((stage.y1[j] == 0 && stage.y2[j] == 0)/* || (dist->dist[0] < stage.dist[j])*/)
		return ;
	if (stage.y1[j] == 0 && stage.y2[j] != 0)
	{
		// stage.y1[j] = stage.y2[j]; // если будут лаги с вертикальынми полосами то тут
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
			stage.y2[j] = H;
			stage.y1[j] = tmp;
			temp_y = stage.y1[j];
		}
	}
	else
		stage.y2[j] -= wolf->player->dir_y;
	temp_y = stage.y1[j] - wolf->player->dir_y;
	y = stage.y1[j];
	// temp_y_2 = y + wolf->player->dir_y;
	while (temp_y < stage.y2[j])
	{
		curr_dist = H / (2.0 * y - H); // 1.05 для искажения угла и придания большей реалистичности
		// printf("%f\n", curr_dist);
		weight = curr_dist / (dist->dist[wolf->player->distance[count_distance]->count - 1] / (CUBE * cof * cof_h));
		
		currFloorX = weight * (dist->coords[wolf->player->distance[count_distance]->count - 1].x / (CUBE * cof * cof_h)) + (1.0 - weight) * (wolf->player->x / (CUBE * cof * cof_h));
		currFloorY = weight * (dist->coords[wolf->player->distance[count_distance]->count - 1].y / (CUBE * cof * cof_h)) + (1.0 - weight) * (wolf->player->y / (CUBE * cof * cof_h));
		
		textx = (int)(currFloorX * wolf->sdl->textures->w * cof * cof_h) % wolf->sdl->textures->w;
		texty = (int)(currFloorY * wolf->sdl->textures->h * cof * cof_h) % wolf->sdl->textures->h;

		if (textx < 0)
			textx = 0;
		if (texty < 0)
			texty = 0;
		color = get_pixel(wolf->sdl->textures, textx, texty);
		if (temp_y >= 0 && temp_y <= H)
		{
			wolf->z_buff_2[x + (temp_y) * W] = true;
			set_pixel(wolf->surface, x, temp_y, color);
		}
		temp_y++;
		y++;
	}
}

static void		floorcast(t_wolf *wolf, t_distance *dist, int x, int y, int count_distance)
{
	float curr_dist;
	float weight;
	float currFloorX;
	float currFloorY;
	int textx;
	int texty;
	int color;
	int temp_y;
	// int temp_y_2;
	float	cof = 0.8654409 * pow((W * 1.0f / H), 1.0118661);

	temp_y = y - (wolf->player->dir_y /* + diry_correction_from_fly(wolf->player->fly)*/);
	// temp_y_2 = y + wolf->player->dir_y;
	// printf("temp_y = %d, y = %d\n", temp_y, y);
	while (temp_y < H)
	{
		curr_dist = (H - wolf->player->fly) / (2.0 * (y + wolf->player->fly) - (H - wolf->player->fly));
		// printf("%f\n", curr_dist);
		weight = curr_dist / (dist->dist[wolf->player->distance[count_distance]->count - 1] / (CUBE * cof));
		
		currFloorX = weight * (dist->coords[wolf->player->distance[count_distance]->count - 1].x / (CUBE * cof)) + (1.0 - weight) * (wolf->player->x / (CUBE * cof));
		currFloorY = weight * (dist->coords[wolf->player->distance[count_distance]->count - 1].y / (CUBE * cof)) + (1.0 - weight) * (wolf->player->y / (CUBE * cof));
		
		textx = (int)(currFloorX * wolf->sdl->textures->w * cof) % wolf->sdl->textures->w;
		texty = (int)(currFloorY * wolf->sdl->textures->h * cof) % wolf->sdl->textures->h;

		// if (textx < 0)
		// 	continue;
		// if (texty < 0)
		// 	continue;
		// color = get_pixel1(wolf->sdl->textures, textx, texty);
		// set_pixel1(wolf->surface, wolf->sdl->textures, x, temp_y, color);
		if (textx > 0 && texty > 0)
		{
			if (temp_y >= 0 && temp_y < H)
			{
				color = get_pixel(wolf->sdl->textures, textx, texty);
				set_pixel(wolf->surface, x, temp_y, color);
			}
		}
		// color = get_pixel(wolf->sdl->textures, textx, texty);
		// if (temp_y_2 >= 0)
		// 	set_pixel(wolf->surface, x, H - temp_y_2, color);
		temp_y++;
		// temp_y_2++;
		y++;
	}
	// printf("temp_y = %d, y = %d\n", temp_y, y);
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
	while (++i < H)//y
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

int				diry_correction_from_fly(int fly)
{
	// return (roundf(-0.5725921 * fly + 53.424221));
	// return (roundf(-0.6358073 * fly + 59.9166667));
	return 0;
	// return (roundf(-0.5622013 * fly + 43.9338034));
	// return (roundf(0.0631079 * fly + 41.5548913));
}

void*			threadFunc(void* thread_data)
{
	//получаем структуру с данными
	pthrData 	*data = thread_data;
	int			end;
 
	data->count_distance = roundf(W - W * 1.0f / THREAD * data->number - 1);
	data->point.x = roundf((W * data->number * 1.0f) / THREAD);
	if (data->interlaced_rendering)
		data->point.x++;
	end = roundf(((W * data->number * 1.0f) / THREAD) + (W * 1.0f / THREAD));
	while (data->point.x < end)
	{
		if (data->wolf->player->distance[data->count_distance]->dist[0] != 0)
		{
			data->point.y = roundf((CUBE * data->wolf->player->dist_to_canvas) / data->wolf->player->distance[data->count_distance]->dist[data->wolf->count_walls - 1]);
			data->point.y = (H - data->point.y) / 2;
			draw_sky(data->wolf, data->point.x, data->point.y - data->wolf->player->dir_y);
			floorcast(data->wolf, data->wolf->player->distance[data->count_distance], data->point.x, H - data->point.y, data->count_distance);
			// draw_column(data->wolf, data->point, data->wolf->player->distance[data->count_distance], data->count_distance);
		}
		data->count_distance -= 2;
		data->point.x += 2;
	}
	return NULL;
}

// void	pseudo_3d(t_wolf *wolf, t_player *player, SDL_Surface *surface)
// {
// 	t_point	point;
// 	int		count_distance;
// 	float	dir;

// 	count_distance = W - 1;
// 	dir = player->dir;
// 	add_arc(&dir, player->fov / 2);
// 	point.y = 0;
// 	if (wolf->sdl->interlaced_rendering == 0)
// 		point.x = 0;
// 	else
// 		point.x = 1;
// 	ft_memset(&wolf->z_buff, 0, W * H * sizeof(bool));
// 	while (point.x < W)
// 	{
// 		if (player->distance[count_distance]->dist[0] != 0)
// 		{
// 			point.y = roundf((CUBE * wolf->player->dist_to_canvas) / wolf->player->distance[count_distance]->dist[wolf->count_walls - 1]);
// 			point.y = (H - point.y) / 2;
// 			draw_sky(wolf, point.x, point.y - wolf->player->dir_y);
// 			floorcast(wolf, wolf->player->distance[count_distance], point.x, H - point.y, count_distance);
// 			draw_column(wolf, point, wolf->player->distance[count_distance], count_distance);
// 		}
// 		count_distance -= 2;
// 		point.x += 2;
// 		add_arc(&dir, -player->step);
// 	}
// 	if (wolf->sdl->interlaced_rendering == 0)
// 		wolf->sdl->interlaced_rendering = 1;
// 	else
// 		wolf->sdl->interlaced_rendering = 0;
// }

void			pseudo_3d(t_wolf *wolf, t_player *player, SDL_Surface *surface)
{
	t_point		point;
	pthread_t	*threads;
	pthrData	*threadData;
	int			i;

	i = -1;
	if (wolf->sdl->interlaced_rendering == 0)
		point.x = 0;
	else
		point.x = 1;
	ft_memset(&wolf->z_buff, 0, W * H * sizeof(bool));
	ft_memset(&wolf->z_buff_2, 0, W * H * sizeof(bool));
	threads = (pthread_t*)malloc(THREAD * sizeof(pthread_t));
	threadData = (pthrData*)malloc(THREAD * sizeof(pthrData));
	while (++i < THREAD)
	{
		threadData[i].number = i;
		threadData[i].wolf = wolf;
		threadData[i].point = point;
		threadData[i].interlaced_rendering = wolf->sdl->interlaced_rendering;
		threadData[i].count_distance = 0;
		pthread_create(&(threads[i]), NULL, threadFunc, &threadData[i]);
	}
	i = -1;
	while (++i < THREAD)
		pthread_join(threads[i], NULL);
	free(threads);
	free(threadData);
	if (wolf->sdl->interlaced_rendering == 0)
		wolf->sdl->interlaced_rendering = 1;
	else
		wolf->sdl->interlaced_rendering = 0;
}
