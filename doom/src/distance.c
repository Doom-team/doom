/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:19:22 by clala             #+#    #+#             */
/*   Updated: 2020/12/16 22:11:59 by wendell          ###   ########.fr       */
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
	dist->dist = 99999.f;
	dist->offsetx = 0;
	// dist->tex = TEX_INF;
	dist->coords.x = -1;
	dist->coords.y = -1;
}

void			all_get_distance(t_wolf *wolf)
{
	float		i;
	int			count_distance;
	float		cos_agle;
	float		temp_i;

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
		wolf->player->distance[count_distance] = dist_to_wall(wolf, temp_i,	count_distance);
		wolf->player->distance[count_distance]->dist *= cosf(cos_agle);
		// if (count_distance == W / 2)
		// 	printf("dist - %f\n", wolf->player->distance[count_distance]->dist);
		cos_agle -= wolf->player->step;
		i += wolf->player->step;
		count_distance++;
	}
}

float vector_len(int x1, int y1, int x2, int y2)
{
	return (sqrt((float)((x2-x1)* (x2-x1) + (y2-y1) * (y2-y1))));
}

int crossing(t_wall player, float angle, t_wall wall)
{
	float k = tanf(angle);
	float b = player.y1 - k * player.x1;
	if (!((wall.y1 - k*wall.x1 - b) * (wall.y2 - k*wall.x2 - b) < 0))
		return (0);
	// k = -(1/k);
	// b = player.y1 - k * player.x1;

	if (angle < RAD_180)
	{
		if (wall.y1 < player.y1 && wall.y2 < player.y1)
			return (0);
	}
	else
	{
		if (wall.y1 > player.y1 && wall.y2 > player.y1)
			return (0);
	}
	if (angle < RAD_90 || angle > RAD_270)
	{
		// printf("1\n");
		if (wall.x1 < player.x1 && wall.x2 < player.x1)
			return (0);
	}
	else
	{
		// printf("2\n");
		if (wall.x1 > player.x1 && wall.x2 > player.x1)
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

float		calc_x(t_wall player, float angle, t_wall wall, float *py)
{
	float k1 = tanf(angle);
	float b1 = player.y1 - k1 * player.x1;
	float x;
	float k2;
	float b2;
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

float			calc_dist(t_wall player, float angle, t_wall wall, t_distance *v)
{
	if (!crossing(player, angle, wall))
		return (-1.);
	// printf("%f\n", angle / RAD_1);
	float px;
	float py = 0;
	px = calc_x(player, angle, wall, &py);
	if (angle < RAD_90 || angle > RAD_270)
	{
		if (px < player.x1)
			return (-1.);
	}
	else
	{
		if (px > player.x1)
			return (-1.);
	}
	v->coords.x = px;
	v->coords.y = py;
	return (vector_len(player.x1, player.y1, px, py));
}

float			calc_dist_without_v(t_wall player, float angle, t_wall wall)
{
	if (!crossing(player, angle, wall))
		return (-1.);
	// printf("%f\n", angle / RAD_1);
	float px;
	float py = 0;
	px = calc_x(player, angle, wall, &py);
	if (angle < RAD_90 || angle > RAD_270)
	{
		if (px < player.x1)
			return (-1.);
	}
	else
	{
		if (px > player.x1)
			return (-1.);
	}
	return (vector_len(player.x1, player.y1, px, py));
}

void calculate_distance(t_wolf *wolf, float angle, float *d)
{
	t_wall player;
	player.x1 = round(wolf->player->x);
	player.y1 = round(wolf->player->y);
	float dist = 20000;
	float tmp = -1;
	int i = 0;
	while (i < wolf->count_walls)
	{
		tmp = calc_dist_without_v(player, angle, wolf->walls[i]);
		if (tmp != -1. && tmp < dist)
			dist = tmp;
		i++;
	}
	*d = dist;
}

void recalc(t_wolf *wolf)
{
	calculate_distance(wolf, RAD_1, &(wolf->player->rght_d));
	calculate_distance(wolf, RAD_90, &(wolf->player->up_d));
	calculate_distance(wolf, RAD_180 + RAD_1, &(wolf->player->left_d));
	calculate_distance(wolf, RAD_270 + RAD_1, &(wolf->player->down_d));
	// printf("%f %f %f %f\n", wolf->player->up_d, wolf->player->down_d, wolf->player->left_d, wolf->player->rght_d);
}

t_distance		*dist_to_wall(t_wolf *wolf,
float angle, int count_distance)
{
	// t_distance	*h;
	t_distance	*v;

	v = wolf->player->distance_vert[count_distance];
	// h = wolf->player->distance_horiz[count_distance];
	t_distance_clear(v);
	// t_distance_clear(h);
	// find_vertical_intersection(wolf, angle, v);
	// find_horizontal_intersection(wolf, angle, h);
	t_wall player;
	player.x1 = round(wolf->player->x);
	player.y1 = round(wolf->player->y);
	// printf("%d\n", player.y1);
	// float k = tanf(angle);
	// float b = player.y1 - k + player.x1;
	float dist = 20000;
	float tmp = -1;

	int i = 0;
	while (i < wolf->count_walls)
	{
		tmp = calc_dist(player, angle, wolf->walls[i], v);
		// v->tex = 1;
		// printf("%f\n", tmp);
		if (tmp != -1. && tmp < dist)
		{
			v->number_wall = i;
			v->offsetx = sqrtf(powf(v->coords.x - wolf->walls[i].x1, 2) + powf(v->coords.y - wolf->walls[i].y1, 2)) / wolf->walls[i].length;
			dist = tmp;
		}
		i++;
	}
	// printf("%f\n", dist);
	// dist *= CUBE;
	// printf("%d %d\n", player.x1, player.y1);
	// v->side = 0;
	if (dist > 0 && dist < 20000)
		v->dist = dist;
	return(v);
	// if (v->dist > h->dist)
	// {
	// 	if (dist > 0 && dist < 20000)
	// 		h->dist = dist;
	// 	return (h);
	// }
	// else
	// {
	// 	v->side = 1;
	// 	return (v);
	// }
}
