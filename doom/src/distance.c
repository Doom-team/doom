/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:19:22 by clala             #+#    #+#             */
/*   Updated: 2021/01/30 18:28:59 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

t_distance		*t_distance_new(t_wolf *wolf)
{
	t_distance	*new;

	if (!(new = (t_distance *)malloc(sizeof(t_distance))))
		error(wolf, ERR_MALLOC);
	return (new);
}

void			free_dist_arr(t_wolf *wolf)
{
	int			i;

	i = -1;
	while (++i < W)
	{
		free(wolf->player->distance[i]);
	}
}

void			t_distance_clear(t_distance *dist)
{
	int			i;

	i = 0;
	while (i < 1000)
	{
		dist->dist[i] = MAXFLOAT;
		dist->offsetx[i] = 0;
		// dist->tex = TEX_INF;
		dist->coords[i].x = -1;
		dist->coords[i].y = -1;
		i++;
	}
	dist->count = 0;
}

void			all_get_distance(t_wolf *wolf)
{
	float		i;
	int			count_distance;
	float		cos_agle;
	float		temp_i;
	int			j;

	i = wolf->player->dir;
	i = wolf->player->dir - (wolf->player->fov / 2);
	count_distance = 0;
	cos_agle = wolf->player->fov / 2;
	while (count_distance < W)
	{
		temp_i = i;
		if (temp_i > RAD_360)
			temp_i -= RAD_360;
		if (temp_i < RAD_0)
			temp_i += RAD_360;
		temp_i = RAD_360 - temp_i;
		// if (count_distance > W / 2)
		// 	printf("%f --- %f\n", wolf->player->distance[W / 2]->coords->x, wolf->player->distance[W / 2]->coords->y);
		wolf->player->distance[count_distance] = dist_to_wall(wolf, temp_i, count_distance);
		j = 0;
		while (j < wolf->player->distance[count_distance]->count)
			wolf->player->distance[count_distance]->dist[j++] *= cosf(cos_agle); //потом в цикле домножу
		// if (count_distance == W / 2)
		// 	printf("dist - %f\n", wolf->player->distance[count_distance]->dist);
		cos_agle -= wolf->player->step;
		i += wolf->player->step;
		count_distance++;
	}
}

float			vector_len(float x1, float y1, int x2, int y2)
{
	return (sqrt((float)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1))));
}

int				crossing(t_float2 player, float angle, t_wall wall)
{
	float k;
	float b;

	k = tanf(angle);
	b = player.y - k * player.x;
	if (!((wall.y1 - k * wall.x1 - b) * (wall.y2 - k * wall.x2 - b) < 0))
		return (0);
	// k = -(1/k);
	// b = player.y1 - k * player.x1;
	if (angle < RAD_180)
	{
		if (wall.y1 < player.y && wall.y2 < player.y)
			return (0);
	}
	else
	{
		if (wall.y1 > player.y && wall.y2 > player.y)
			return (0);
	}
	if (angle < RAD_90 || angle > RAD_270)
	{
		// printf("1\n");
		if (wall.x1 < player.x && wall.x2 < player.x)
			return (0);
	}
	else
	{
		// printf("2\n");
		if (wall.x1 > player.x && wall.x2 > player.x)
			return (0);
	}
	if (angle < RAD_180)
	{
		if (round(wall.x1 * k + b) > wall.y1 && round(wall.x2 * k + b) > wall.y2)
			return (0);
	}
	else
	{
		if (round(wall.x1 * k + b) < wall.y1 && round(wall.x2 * k + b) < wall.y2)
			return (0);
	}
	if (angle < RAD_90 || angle > RAD_270)
	{
		if ((wall.y1 - b) / k > wall.x1 && (wall.y2 - b) / k > wall.x2)
			return (0);
	}
	else
	{
		if ((wall.y1 - b) / k < wall.x1 && (wall.y2 - b) / k < wall.x2)
			return (0);
	}
	return (1);
}

float			calc_x(t_float2 player, float angle, t_wall wall, float *py)
{
	float k1;
	float b1;
	float x;
	float k2;
	float b2;

	k1 = tanf(angle);
	b1 = player.y - k1 * player.x;
	if (wall.vert)
	{
		x = wall.x1;
	}
	else
	{
		k2 = (float)(wall.y2 - wall.y1) / (wall.x2 - wall.x1);
		b2 = wall.y1 - k2 * wall.x1;
		x = (b2 - b1) / (k1 - k2);
	}
	*py = k1 * x + b1;
	return (x);
}

float			calc_dist(t_float2 player, float angle, t_wall wall, t_distance *v, int j)
{
	float px;
	float py;

	if (!crossing(player, angle, wall))
		return (-1.);
	py = 0;
	px = calc_x(player, angle, wall, &py);
	if (angle < RAD_90 || angle > RAD_270)
	{
		if (px < player.x)
			return (-1.);
	}
	else
	{
		if (px > player.x)
			return (-1.);
	}
	v->coords[j].x = px;
	v->coords[j].y = py;
	px = vector_len(player.x, player.y, px, py);
	if (px < 1.5)
	{
		return (-1.);
	}
	return (px);
}

float			calc_dist_without_v(t_float2 player, float angle, t_wall wall)
{
	float px;
	float py;

	if (!crossing(player, angle, wall))
		return (-1.);
	// printf("%f\n", angle / RAD_1);
	py = 0;
	px = calc_x(player, angle, wall, &py);
	if (angle < RAD_90 || angle > RAD_270)
	{
		if (px < player.x)
			return (-1.);
	}
	else
	{
		if (px > player.x)
			return (-1.);
	}
	px = vector_len(player.x, player.y, px, py);
	if (px < 1.5)
	{
		return (-1.);
	}
	return (px);
}

void			calculate_distance(t_wolf *wolf, float angle, t_way *d)
{
	t_float2	player;
	float	dist;
	float	tmp;
	int		i;
	int		j = -1;

	player.x = wolf->player->x;
	player.y = wolf->player->y;
	dist = MAXFLOAT;
	tmp = -1;
	i = 0;
	while (i < wolf->count_walls)
	{
		tmp = calc_dist_without_v(player, angle, wolf->walls[i]);
		if (tmp != -1. && tmp < dist)
		{
			dist = tmp;
			j = i;
		}
		i++;
	}
	d->dist = dist;
	if (j != -1)
		d->wall = wolf->walls[j];
	// if (j == -1)
	// {
	// 	d->wall = wolf->walls[0];
	// }
	
}

void			recalc(t_wolf *wolf)
{
	calculate_distance(wolf, RAD_0, wolf->player->rght_d);
	calculate_distance(wolf, RAD_90, wolf->player->up_d);
	calculate_distance(wolf, RAD_180, wolf->player->left_d);
	calculate_distance(wolf, RAD_270-RAD_1, wolf->player->down_d);
	if (wolf->player->rght_d->wall.squad_stage == wolf->player->left_d->wall.squad_stage && wolf->player->rght_d->wall.squad_stage != 0)
		wolf->player->inside_step = wolf->player->rght_d->wall.h * UP_LENGTH;
	else if (wolf->player->up_d->wall.squad_stage == wolf->player->down_d->wall.squad_stage && wolf->player->up_d->wall.squad_stage != 0)
		wolf->player->inside_step = wolf->player->up_d->wall.h * UP_LENGTH;
	else if (wolf->player->up_d->wall.squad_stage == wolf->player->left_d->wall.squad_stage && wolf->player->up_d->wall.squad_stage != 0)
		wolf->player->inside_step = wolf->player->up_d->wall.h * UP_LENGTH;
	else if (wolf->player->up_d->wall.squad_stage == wolf->player->rght_d->wall.squad_stage && wolf->player->up_d->wall.squad_stage != 0)
		wolf->player->inside_step = wolf->player->rght_d->wall.h * UP_LENGTH;
	else if (wolf->player->left_d->wall.squad_stage == wolf->player->down_d->wall.squad_stage && wolf->player->left_d->wall.squad_stage != 0)
		wolf->player->inside_step = wolf->player->left_d->wall.h * UP_LENGTH;
	else if (wolf->player->rght_d->wall.squad_stage == wolf->player->down_d->wall.squad_stage && wolf->player->rght_d->wall.squad_stage != 0)
		wolf->player->inside_step = wolf->player->rght_d->wall.h * UP_LENGTH;
	else
		wolf->player->inside_step = 0;
	// if (wolf->player->inside_step == wolf->player->up_d->wall.squad_stage)
	// 	wolf->player->fly = wolf->player->up_d->wall.h * UP_LENGTH;
	// else if (wolf->player->inside_step == wolf->player->rght_d->wall.squad_stage)
	// 	wolf->player->fly = wolf->player->rght_d->wall.h * UP_LENGTH;
	// else
	// printf("u %d d %d r %d l %d p %d\n", wolf->player->up_d->wall.squad_stage, wolf->player->down_d->wall.squad_stage, wolf->player->rght_d->wall.squad_stage, wolf->player->left_d->wall.squad_stage, wolf->player->inside_step);
	// printf("%f %f %f %f\n", wolf->player->up_d, wolf->player->down_d, wolf->player->left_d, wolf->player->rght_d);
}

static void		buble_sort_fly(t_distance *v)
{
	int			i;
	int			j;
	float		f_temp;
	int			number_temp;
	float		of_temp;
	t_float2	cor_temp;

	i = -1;
	while (++i < v->count - 1)
	{
		j = v->count;
		while (--j > i)
		{
			if (v->dist[j - 1] < v->dist[j])
			{
				f_temp = v->dist[j - 1];
				number_temp = v->number_wall[j - 1];
				of_temp = v->offsetx[j - 1];
				cor_temp = v->coords[j - 1];
				v->dist[j - 1] = v->dist[j];
				v->number_wall[j - 1] = v->number_wall[j];
				v->offsetx[j - 1] = v->offsetx[j];
				v->coords[j - 1] = v->coords[j];
				v->dist[j] = f_temp;
				v->number_wall[j] = number_temp;
				v->offsetx[j] = of_temp;
				v->coords[j] = cor_temp;
			}
		}
	}
}

static void		buble_sort(t_distance *v)
{
	int			i;
	int			j;
	float		f_temp;
	int			number_temp;
	float		of_temp;
	t_float2	cor_temp;

	i = -1;
	while (++i < v->count - 1)
	{
		j = v->count;
		while (--j > i)
		{
			if (v->dist[j - 1] > v->dist[j])
			{
				f_temp = v->dist[j - 1];
				number_temp = v->number_wall[j - 1];
				of_temp = v->offsetx[j - 1];
				cor_temp = v->coords[j - 1];
				v->dist[j - 1] = v->dist[j];
				v->number_wall[j - 1] = v->number_wall[j];
				v->offsetx[j - 1] = v->offsetx[j];
				v->coords[j - 1] = v->coords[j];
				v->dist[j] = f_temp;
				v->number_wall[j] = number_temp;
				v->offsetx[j] = of_temp;
				v->coords[j] = cor_temp;
			}
		}
	}
}

t_distance		*dist_to_wall(t_wolf *wolf,
float angle, int count_distance)
{
	t_distance	*v;
	t_float2		player;
	float		tmp;
	int			i;
	int			j;

	tmp = -1.0f;
	i = 0;
	j = 0;
	v = wolf->player->distance_vert[count_distance];
	t_distance_clear(v);
	player.x = wolf->player->x;
	player.y = wolf->player->y;
	while (i < wolf->count_walls)
	{
		tmp = calc_dist(player, angle, wolf->walls[i], v, j);
		if (tmp != -1.0f)
		{
			v->number_wall[j] = i;
			v->offsetx[j] = sqrtf(powf(v->coords[j].x - wolf->walls[i].x1, 2) + powf(v->coords[j].y - wolf->walls[i].y1, 2)) / wolf->walls[i].length;
			v->dist[j] = tmp;
			j++;
			tmp = -1.0f;
		}
		i++;
	}
	v->count = j;
	if (wolf->player->fly < 0)
		buble_sort_fly(v);
	else
		buble_sort(v);
	return (v);
}
