/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:19:22 by clala             #+#    #+#             */
/*   Updated: 2020/12/08 18:42:15 by wendell          ###   ########.fr       */
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
	dist->tex = TEX_INF;
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
		// if (temp_i > 0.)
			temp_i = RAD_360 - temp_i;
		wolf->player->distance[count_distance] = dist_to_wall(wolf, temp_i,
			count_distance);
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
	k = -(1/k);
	b = player.y1 - k * player.x1;
	if (angle < RAD_180)
	{
		if (wall.x1 * k + b > wall.y1 && wall.x2 * k + b > wall.y2)
			return (0);
	}
	else
	{
		if (wall.x1 * k + b < wall.y1 && wall.x2 * k + b < wall.y2)
			return (0);
	}
	// printf("%d %d\n", player.x1, player.y1);
	return (1);
}

float		calc_x(t_wall player, float angle, t_wall wall, float *py)
{
	float k1 = tanf(angle);
	float k2 = (float)(wall.y2 - wall.y1) / (wall.x2 - wall.x1);
	float b1 = player.y1 - k1 * player.x1;
	float b2 = wall.y1 - k2 * wall.x1;

	float x = (b2 - b1) / (k1 - k2);
	*py = k1 * x + b1;
	return (x);
}

float			calc_dist(t_wall player, float angle, t_wall wall, t_distance *v)
{
	if (!crossing(player, angle, wall))
		return (-1.);
	float px;
	float py = 0;
	px = calc_x(player, angle, wall, &py);
	v->coords.x = px;
	v->coords.y = py;
	return (vector_len(player.x1, player.y1, px, py));
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
	player.x1 = wolf->player->x;
	player.y1 = wolf->player->y;
	// printf("%d\n", player.y1);
	// float k = tanf(angle);
	// float b = player.y1 - k + player.x1;
	float dist = 20000;
	float tmp = 30000;

	int i = 0;
	while (i < 4)
	{
		// float tmp_angle = 0.0;
		// tmp_angle = ;
		// if (angle > RAD_90 && angle < RAD_180)
		// 	tmp_angle = RAD_270 - (angle - RAD_90);
		// else if (angle > RAD_0 && angle < RAD_90)
		// 	tmp_angle = RAD_360 - angle;
		// else if (angle > RAD_180 && angle < RAD_270)
		// 	tmp_angle = RAD_90 + (RAD_270 - angle);
		// else if (angle < RAD_360 && angle > RAD_270)
		// 	tmp_angle = RAD_0 + (RAD_360 - angle);
		tmp = calc_dist(player, angle, wolf->walls[i], v);
		v->tex = 1;
		// printf("%f\n", tmp);
		if (tmp != -1. && tmp < dist)
		{
			v->offsetx = sqrt(pow(v->coords.x - wolf->walls[i].x1, 2) + pow(v->coords.y - wolf->walls[i].y1, 2)) / wolf->walls[i].length;
			dist = tmp;
		}
		i++;
	}
	// printf("%f\n", dist);
	// dist *= CUBE;
	// printf("%d %d\n", player.x1, player.y1);
	v->side = 0;
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
