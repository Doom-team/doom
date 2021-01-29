/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudo_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:31:45 by clala             #+#    #+#             */
/*   Updated: 2021/01/27 15:25:46 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int				fly_correct_fuf(t_wolf *wolf)
{
	return (wolf->player->fly / 2 * 3) + (0.00294 * wolf->player->fly + 0.3106055);
}

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
	signed long long int	temp_y;//чтоб при отдалений не тормозило но там все равно говно выше макс числа
	int						size;
	t_floot_up				stage;

	ft_memset(&stage, 0, sizeof(t_floot_up));
	j = -1;
	// printf("%d\n", dist->count);
	int flagg = 0;
	while (++j < dist->count)
	{
		temp_y = ceilf((CUBE * wolf->player->dist_to_canvas) / wolf->player->distance[count_distance]->dist[j]);
		temp_y = (H - temp_y) / 2;
		size = H - temp_y;
		temp_y = size - ceilf((CUBE * wolf->walls[dist->number_wall[j]].h / 5.0f * wolf->player->dist_to_canvas) / wolf->player->distance[count_distance]->dist[j]); // отвечает за высоту ступеньки
		if (wolf->walls[dist->number_wall[j]].type_flag == 1)
		{
			if (point.x == W / 2) // для отладки по центру экрана
			{
				point.x = point.x;
				// printf("%d\n", wolf->walls[dist->number_wall[j]].squad_stage - 1);
				// printf("%d -- %d --- %d\n", j, dist->number_wall[j], wolf->walls[dist->number_wall[j]].squad_stage);
			}
			if (stage.dist[wolf->walls[dist->number_wall[j]].squad_stage - 1] == 0)
			{
				flagg = 0;
				stage.dist[wolf->walls[dist->number_wall[j]].squad_stage - 1] = wolf->player->distance[count_distance]->dist[j];
			}
			// if (wolf->player->distance[count_distance]->dist[j] < stage.dist[wolf->walls[dist->number_wall[j]].squad_stage - 1])
			// 	stage.dist[wolf->walls[dist->number_wall[j]].squad_stage - 1] = wolf->player->distance[count_distance]->dist[j];
			if (stage.y2[wolf->walls[dist->number_wall[j]].squad_stage - 1] < temp_y - (/*wolf->player->dir_y + */fly_correction_from_dist(wolf, j, count_distance) + fly_correct_fuf(wolf))
				&& flagg != 1)
			{
				flagg = 1;
				// if (point.x == W / 2)
				// 	printf("1 - %d 2 - %lld\n", stage.y2[wolf->walls[dist->number_wall[j]].squad_stage - 1], temp_y);
				stage.y2[wolf->walls[dist->number_wall[j]].squad_stage - 1] = temp_y - (/*wolf->player->dir_y +*/ fly_correction_from_dist(wolf, j, count_distance) + fly_correct_fuf(wolf));
				// if (point.x == W / 2)
				// 	printf("%d\n", stage.y2[wolf->walls[dist->number_wall[j]].squad_stage - 1]);
				stage.y1[wolf->walls[dist->number_wall[j]].squad_stage - 1] = -1; // и тут по вертикальным полосам
			}
			else if (stage.y1[wolf->walls[dist->number_wall[j]].squad_stage - 1] < temp_y - (/*wolf->player->dir_y +*/ fly_correction_from_dist(wolf, j, count_distance)/* + wolf->t_cof*/))
			{
				// printf("d\n");
				if (stage.y1[wolf->walls[dist->number_wall[j]].squad_stage - 1] == -1)
					stage.y1[wolf->walls[dist->number_wall[j]].squad_stage - 1] = stage.y2[wolf->walls[dist->number_wall[j]].squad_stage - 1];
				stage.y2[wolf->walls[dist->number_wall[j]].squad_stage - 1] = temp_y - (wolf->player->dir_y + fly_correction_from_dist(wolf, j, count_distance)/* + wolf->t_cof*/);
			}
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
			if (temp_y - (wolf->player->dir_y + fly_correction_from_dist(wolf, j, count_distance)) < -H - 2)
			{
				temp_y = -H - 1 + (wolf->player->dir_y + fly_correction_from_dist(wolf, j, count_distance));
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
			if (temp_y - (wolf->player->dir_y + fly_correction_from_dist(wolf, j, count_distance)) > 0 && temp_y - (wolf->player->dir_y + fly_correction_from_dist(wolf, j, count_distance)) < H)
			{
				offsety = (float)(temp_y - begin_y) / (size - begin_y);
				pos_y = len * offsety;
				fractpart_2 = modf(pos_y / tex_2, &intpart_2);
				color = get_pixel(wolf->walls[dist->number_wall[j]].texture1, wolf->walls[dist->number_wall[j]].texture1->w * fractpart, fractpart_2 * wolf->walls[dist->number_wall[j]].texture1->h); //где раунд коофицен колличества стен
				set_pixel(wolf->surface, point.x, temp_y - (wolf->player->dir_y + fly_correction_from_dist(wolf, j, count_distance)), color);
				// wolf->z_buff[point.x + (temp_y - wolf->player->dir_y) * W] = true;
			}
		}
	}
	stage.count += 10; //затычка
	j = -1;
	// printf("%d\n", stage.count);
	while (++j < stage.count)
		floorcast_up_fly(wolf, wolf->player->distance[count_distance], point.x, count_distance, stage, j);

	// if (point.x == W / 2) // для отладки по центру экрана
	// 	point.x = point.x;
	if (stage.count % 2 == 0)
	{
		j = dist->count - 1;
		if (j == -1)
			return ;
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
		double	fractpart_2;
		double	intpart_2;
		int		flag = 1;

		temp_y--;
		while (++temp_y < size)
		{
			if (temp_y - (wolf->player->dir_y + fly_correction_from_dist(wolf, j, count_distance)) < -H - 2)
			{
				temp_y = -H - 1 + (wolf->player->dir_y + fly_correction_from_dist(wolf, j, count_distance));
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
			if (temp_y - (wolf->player->dir_y + fly_correction_from_dist(wolf, j, count_distance)) > 0 && temp_y - (wolf->player->dir_y + fly_correction_from_dist(wolf, j, count_distance)) < H)
			{
				offsety = (float)(temp_y - begin_y) / (size - begin_y);
				pos_y = len * offsety;
				fractpart_2 = modf(pos_y / tex_2, &intpart_2);
				color = get_pixel(wolf->walls[dist->number_wall[j]].texture1, wolf->walls[dist->number_wall[j]].texture1->w * fractpart, fractpart_2 * wolf->walls[dist->number_wall[j]].texture1->h); //где раунд коофицен колличества стен
				set_pixel(wolf->surface, point.x, temp_y - (wolf->player->dir_y + fly_correction_from_dist(wolf, j, count_distance)), color);
				// wolf->z_buff[point.x + (temp_y - wolf->player->dir_y) * W] = true;
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
			if (stage.y2[wolf->walls[dist->number_wall[j]].squad_stage - 1] != 0 && stage.y2[wolf->walls[dist->number_wall[j]].squad_stage - 1] != 0)
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
	stage.count += 10; // затычка
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
	// printf ("%lld---%d\n", temp_y, size);
	while (++temp_y < size)
	{
		if (temp_y - wolf->player->dir_y < -H - 2)
		{
			temp_y = -H - 1 + wolf->player->dir_y;
			continue;
		}
		if (temp_y - wolf->player->dir_y < 0 || temp_y - wolf->player->dir_y > H)
			continue;
		// if (wolf->z_buff_2[point.x + (temp_y - wolf->player->dir_y) * W] == false)
		// 	continue;
		if (flag == 1)
		{
			count = (int)(round(wolf->walls[dist->number_wall[j]].length / CUBE));
			koof = (wolf->walls[dist->number_wall[j]].length / CUBE) / count;
			tex_1 = (wolf->walls[dist->number_wall[j]].length / count) * koof;
			pos = dist->offsetx[j] * wolf->walls[dist->number_wall[j]].length;
			fractpart = modf((pos / tex_1), &intpart);
			flag = 0;
		}
		if ((temp_y - wolf->player->dir_y > 0 && temp_y - wolf->player->dir_y < H)/* && stage.count % 2 != 0*/)
		{
			// printf("%d\n", stage.count);
			offsety = (float)(temp_y - begin_y) / (size - begin_y);
			pos_y = len * offsety;
			fractpart_2 = modf(pos_y / tex_2, &intpart_2);
			color = get_pixel(wolf->walls[dist->number_wall[j]].texture1, wolf->walls[dist->number_wall[j]].texture1->w * fractpart, fractpart_2 * wolf->walls[dist->number_wall[j]].texture1->h); //где раунд коофицен колличества стен
			set_pixel(wolf->surface, point.x, temp_y - wolf->player->dir_y, color);
			// if (temp_y < 0)
			// 	printf ("%lld---%d\n", temp_y, size);
		}
	}
}

int			fly_correction_from_dist(t_wolf	*wolf, int	j, int count_distance)
{
	return ((int)roundf(wolf->player->fly / wolf->player->distance[count_distance]->dist[j] * (28.9357956 * (W * 1.0 / H) - 1.1785647)));
}

double				correct_cof_h(t_wolf *wolf)
{
	// return (0.0953394 * logf(0.011631 * abs(wolf->player->fly)));
	return (0.0837451 * logf(abs(wolf->player->fly)) - 0.3360108);
}

void			floorcast_up_fly(t_wolf *wolf, t_distance *dist, int x, int count_distance, t_floot_up stage, int j)
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
	float	cof = 0.8654409 * pow((W * 1.0f / H), 1.0118661)/* + wolf->t_cof*/;
	float	cof_h = -0.4 * stage.h[j] + 1.0  + correct_cof_h(wolf) * stage.h[j];
	// float	cof_h = -0.4 * stage.h[j] + 1.0  + wolf->t_cof * stage.h[j];
	// float	cof_h = 1 + wolf->t_cof;

	// if (x == W / 2) // для отладки по центру экрана
	// 	x = x;
	// printf("%d\n", wolf->walls[dist->number_wall[j]].h);
	if ((stage.y1[j] == 0 && stage.y2[j] == 0)/* || (dist->dist[0] < stage.dist[j])*/)
		return ;
	// printf("%d ----%d\n", stage.y1[j], stage.y2[j]);
	// int ttm = stage.y1[j];
	// stage.y1[j] = stage.y2[j];
	// stage.y2[j] = ttm;
	// printf("%d\n", stage.h[j]);
	if (stage.y1[j] == 0 && stage.y2[j] != 0) // перевернул
	{
		// stage.y1[j] = stage.y2[j]; // если будут лаги с вертикальынми полосами то тут
		tmp = stage.y2[j];
		stage.y2[j] = H;
		stage.y1[j] = tmp;
		temp_y = stage.y1[j];
		// printf("dsd\n");
	}
	else if (stage.y1[j] == -1 && stage.y2[j] != 0)
	{
		stage.y1[j] = stage.y2[j];
		if (stage.count % 2 == 0)
		{
			// printf("%d ----%d\n", stage.y1[j], stage.y2[j]);
			tmp = stage.y2[j];
			stage.y2[j] = 0;
			// stage.y2[j] = H;
			stage.y1[j] = tmp;
			temp_y = stage.y1[j];
		}
		else
		{
			tmp = stage.y2[j];
			// stage.y2[j] = 0;
			stage.y2[j] = H;
			stage.y1[j] = tmp;
			temp_y = stage.y1[j];
		}
		
		// else
		// 	return ;
	}
	// else // сссс
		// stage.y2[j] -= wolf->player->dir_y; //cccc
	// if (stage.y1[j] == stage.y2[j])
	// 	return ;
	temp_y = stage.y1[j] - (wolf->player->dir_y + diry_correction_from_fly(wolf->player->fly));
	y = stage.y1[j];
	// printf("%d ----%d\n", stage.y1[j], stage.y2[j]);

	// stage.y1[j] -= wolf->t_cof;
	// printf("stagey1 = %d\n", stage.y1[j]);
	// temp_y = stage.y1[j] - (wolf->player->dir_y + wolf->t_cof);
	// temp_y_2 = y + wolf->player->dir_y;
	while (temp_y < stage.y2[j])
	{
		// curr_dist = H / (2.0 * y - H); // 1.05 для искажения угла и придания большей реалистичности
		curr_dist = (H - wolf->player->fly) / (2.0 * (y + wolf->player->fly) - (H - wolf->player->fly));

		// printf("%f\n", curr_dist);
		weight = curr_dist / (dist->dist[wolf->player->distance[count_distance]->count - 1] / (CUBE * cof * cof_h));
		
		currFloorX = weight * (dist->coords[wolf->player->distance[count_distance]->count - 1].x / (CUBE * cof * cof_h)) + (1.0 - weight) * (wolf->player->x / (CUBE * cof * cof_h));
		currFloorY = weight * (dist->coords[wolf->player->distance[count_distance]->count - 1].y / (CUBE * cof * cof_h)) + (1.0 - weight) * (wolf->player->y / (CUBE * cof * cof_h));
		
		textx = (int)(currFloorX * wolf->sdl->textures->w * cof * cof_h) % wolf->sdl->textures->w;
		texty = (int)(currFloorY * wolf->sdl->textures->h * cof * cof_h) % wolf->sdl->textures->h;

		if (textx > 0 && texty > 0)
		{
			if (temp_y >= 0 && temp_y <= H)
			{
				color = get_pixel(wolf->sdl->textures, textx, texty);
				// wolf->z_buff_2[x + (temp_y) * W] = true;
				set_pixel(wolf->surface, x, temp_y, color);
			}
		}
		temp_y++;
		y++;
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
	// if (x == W / 2) // для отладки по центру экрана
	// 	x = x;
	if ((stage.y1[j] == 0 && stage.y2[j] == 0)/* || (dist->dist[0] < stage.dist[j])*/)
		return ;
	// printf("%d ----%d ----- %d\n", stage.y1[j], stage.y2[j], j);
	// if (stage.y1[j] > stage.y2[j])
	// 	return ;
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
		if (stage.count % 2 == 0 && j - 1 >= 0 && stage.h[j] < stage.h[j - 1]) // dd
		{
			tmp = stage.y2[j];
			stage.y2[j] = H;
			stage.y1[j] = tmp;
			temp_y = stage.y1[j];
		}
		else
			return ;
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

		if (textx > 0 && texty > 0)
		{
			if (temp_y >= 0 && temp_y <= H)
			{
				color = get_pixel(wolf->sdl->textures, textx, texty);
				wolf->z_buff_2[x + (temp_y) * W] = true;
				set_pixel(wolf->surface, x, temp_y, color);
			}
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

	temp_y = y - (wolf->player->dir_y + diry_correction_from_fly(wolf->player->fly));
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
			if (temp_y >= H / 2 - (wolf->player->dir_y - 1) && temp_y < H)
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
	while (++i < H /*/ 2 - wolf->player->dir_y*/)//y // отрисовка неба до ,,,,
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
	return (-1.5029996 * fly - 1.064349);
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
			if (data->wolf->player->fly < 0)
				draw_column_fly(data->wolf, data->point, data->wolf->player->distance[data->count_distance], data->count_distance);
			else
				draw_column(data->wolf, data->point, data->wolf->player->distance[data->count_distance], data->count_distance);
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
