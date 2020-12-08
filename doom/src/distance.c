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
		wolf->player->distance[count_distance] = dist_to_wall(wolf, temp_i,
			count_distance);
		wolf->player->distance[count_distance]->dist *= cosf(cos_agle);
		cos_agle -= wolf->player->step;
		i += wolf->player->step;
		count_distance++;
	}
}

float vector_len(int x1, int y1, int x2, int y2)
{
	return (sqrt(pow(x2-x1, 2) + pow(y2-y1, 2)));
}

float calc_sin_angle(t_wall player, int x2, int y2)
{
	int vx1 = player.x2 - player.x1;
	int vy1 = player.y2 - player.y1;
	int vx2 = x2 - player.x1;
	int vy2 = y2 - player.y1;
	float angle = acos((float)(vx1*vx2 + vy1*vy2) / sqrt((vx1*vx1 + vy1*vy1) * (vx2*vx2 + vy2*vy2)));
	return (sin(angle));
}

int crossing(t_wall player, t_wall wall)
{
	float k = (float)(player.y2 - player.y1)/(player.x2 - player.x1);
	float b = player.y1 - k * player.x1;
	if (!((wall.y1 - k*wall.x1 - b) * (wall.y2 - k*wall.x2 - b) < 0))
		return (0);
	k = (float)(wall.y2 - wall.y1)/(wall.x2 - wall.x1);
	b = wall.y1 - k * wall.x1;
	if (!((player.y1 - k*player.x1 - b) * (player.y2 - k*player.x2 - b) < 0))
		return (0);
	return (1);
}

float			calc_dist(t_wall player, t_wall wall)
{
	if (!crossing(player, wall))
		return (-1.);
	float px;
	float py;
	float z;

	px = vector_len(player.x1, player.y1, player.x2, player.y2);
	py = px * vector_len(player.x1, player.y1, wall.x1, wall.y1) * calc_sin_angle(player, wall.x1, wall.y1); //z1
	z = px * vector_len(player.x1, player.y1, wall.x2, wall.y2) * calc_sin_angle(player, wall.x2, wall.y2); //z2
	z = py / fabs(z - py);

	px = wall.x1 + (wall.x2 - wall.x1) * z;
	py = wall.y1 + (wall.y2 - wall.y1) * z;
	return (vector_len(player.x1, player.y1, px, py));
}

t_distance		*dist_to_wall(t_wolf *wolf,
float angle, int count_distance)
{
	t_distance	*h;
	t_distance	*v;

	v = wolf->player->distance_vert[count_distance];
	h = wolf->player->distance_horiz[count_distance];
	t_distance_clear(v);
	t_distance_clear(h);
	find_vertical_intersection(wolf, angle, v);
	find_horizontal_intersection(wolf, angle, h);
	t_wall player;
	player.x1 = wolf->player->x;
	player.y1 = wolf->player->y;
	float k = tanf(angle);
	float b = player.y1 - k + player.x1;
	float dist = 100000;
	float tmp = 100000;
	if (angle < RAD_90 || angle > RAD_270)
	{
		player.x2 = player.x1 + 10000;
		player.y2 = player.x2 * k + b;
	}
	else if (angle == RAD_90 || angle == RAD_270)
	{
		player.x2 = player.x1;
		player.y2 = player.y1 + 10000;
	}
	else
	{
		player.x2 = player.x1 - 10000;
		player.y2 = player.x2 * k + b;
	}
	int i = 0;
	while (i < 4)
	{
		tmp = calc_dist(player, wolf->walls[i]);
		if (tmp != -1. && tmp < dist)
			dist = tmp;
		i++;
	}
	// printf("%f\n", dist);
	// dist *= CUBE;
	printf("%d %d\n", player.x1, player.y1);
	if (v->dist > h->dist)
	{
		h->side = 0;
		if (dist > 0 && dist < 100000)
			h->dist = dist;
		return (h);
	}
	else
	{
		v->side = 1;
		if (dist > 0 && dist < 100000)
			v->dist = dist;
		return (v);
	}
}
