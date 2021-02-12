/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:19:22 by skaren            #+#    #+#             */
/*   Updated: 2021/02/12 15:55:16 by grinko           ###   ########.fr       */
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
	int	i;

	i = -1;
	while (++i < W)
		free(wolf->player->distance[i]);
}

void			t_distance_clear(t_distance *dist)
{
	int			i;

	i = 0;
	while (i < 1000)
	{
		dist->dist[i] = MAXFLOAT;
		dist->offsetx[i] = 0;
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

	i = wolf->player->dir - (wolf->player->fov / 2);
	count_distance = -1;
	cos_agle = wolf->player->fov / 2;
	while (++count_distance < W)
	{
		temp_i = i;
		if (temp_i > RAD_360)
			temp_i -= RAD_360;
		if (temp_i < RAD_0)
			temp_i += RAD_360;
		temp_i = RAD_360 - temp_i;
		wolf->player->distance[count_distance] =
			dist_to_wall(wolf, &(t_helper){0, 0, temp_i, count_distance});
		j = 0;
		while (j < wolf->player->distance[count_distance]->count)
			wolf->player->distance[count_distance]->dist[j++] *= cosf(cos_agle);
		cos_agle -= wolf->player->step;
		i += wolf->player->step;
	}
}

float			vector_len(float x1, float y1, float x2, float y2)
{
	return (sqrt((float)((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1))));
}

int				ifcrossing(t_float2 player, float angle, t_wall wall)
{
	float k;
	float b;

	k = tanf(angle);
	b = player.y - k * player.x;
	if (angle > RAD_180)
	{
		if ((wall.y1 > player.y && wall.y2 > player.y) ||
			(wall.x1 * k + b < wall.y1 && wall.x2 * k + b < wall.y2))
			return (0);
	}
	if (angle < RAD_90 || angle > RAD_270)
	{
		if ((wall.x1 < player.x && wall.x2 < player.x) || ((wall.y1 - b) /
			k > wall.x1 && (wall.y2 - b) / k > wall.x2))
			return (0);
	}
	else
	{
		if ((wall.x1 > player.x && wall.x2 > player.x) || ((wall.y1 - b) /
			k < wall.x1 && (wall.y2 - b) / k < wall.x2))
			return (0);
	}
	return (1);
}

int				crossing(t_float2 player, float angle, t_wall wall)
{
	float k;
	float b;

	k = tanf(angle);
	b = player.y - k * player.x;
	if (angle == RAD_90 || angle == RAD_270)
	{
		if ((player.x > wall.x1 && player.x < wall.x2) ||
			(player.x > wall.x2 && player.x < wall.x1))
			return (1);
		return (0);
	}
	if (!((wall.y1 - k * wall.x1 - b) * (wall.y2 - k * wall.x2 - b) < 0))
		return (0);
	if (angle < RAD_180)
	{
		if ((wall.y1 < player.y && wall.y2 < player.y) ||
			(wall.x1 * k + b > wall.y1 && wall.x2 * k + b > wall.y2))
			return (0);
	}
	return (ifcrossing(player, angle, wall));
}

float			calc_x(t_float2 player, float angle, t_wall wall, float *py)
{
	float b1;
	float x;
	float k2;
	float b2;

	b1 = player.y - tanf(angle) * player.x;
	if (angle == RAD_90 || angle == RAD_270)
	{
		x = player.x;
		k2 = 1.f * (wall.y2 - wall.y1) / (wall.x2 - wall.x1);
		b2 = wall.y1 - k2 * wall.x1;
		*py = k2 * x + b2;
		return (x);
	}
	if (wall.vert)
		x = wall.x1;
	else
	{
		k2 = 1.f * (wall.y2 - wall.y1) / (wall.x2 - wall.x1);
		b2 = wall.y1 - k2 * wall.x1;
		x = (b2 - b1) / (tanf(angle) - k2);
	}
	*py = tanf(angle) * x + b1;
	return (x);
}

float			calc_dist(t_float2 player, t_wall wall,
	t_distance *v, t_helper *h)
{
	float px;
	float py;

	if (!crossing(player, h->angle, wall))
		return (-1.);
	py = 0;
	px = calc_x(player, h->angle, wall, &py);
	if (h->angle < RAD_90 || h->angle > RAD_270)
	{
		if (px < player.x)
			return (-1.);
	}
	else if (h->angle == RAD_90 || h->angle == RAD_270)
	{
		if (px != player.x)
			return (-1.);
	}
	else if (px > player.x)
		return (-1.);
	v->coords[h->j].x = px;
	v->coords[h->j].y = py;
	px = vector_len(player.x, player.y, px, py);
	if (px < 0.001)
		return (-1.);
	return (px);
}

float			calc_dist_without_v(t_float2 player, float angle, t_wall wall)
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
	else if (angle == RAD_90 || angle == RAD_270)
	{
		if (px != player.x)
			return (-1.);
		if (angle == RAD_90 && py < player.y)
			return (-1.);
		if (angle == RAD_270 && py > player.y)
			return (-1.);
	}
	else if (px > player.x)
		return (-1.);
	px = vector_len(player.x, player.y, px, py);
	return (px);
}

void			calculate_distance(t_wolf *wolf, t_way *d, t_helper *h)
{
	t_float2	player;
	float		dist;
	float		tmp;

	player.x = wolf->player->x;
	player.y = wolf->player->y;
	dist = MAXFLOAT;
	tmp = -1;
	while (++h->x < wolf->p->count_walls)
	{
		if (wolf->p->walls[h->x].type_flag >= 3 || !wolf->p->walls[h->x].active)
			continue;
		tmp = calc_dist_without_v(player, h->angle, wolf->p->walls[h->x]);
		if (tmp != -1. && tmp < dist)
		{
			dist = tmp;
			h->j = h->x;
		}
	}
	d->dist = dist;
	if (h->j != -1)
		d->wall = wolf->p->walls[h->j];
}

void			recalc3(t_wolf *wolf)
{
	if (wolf->player->rght_d->wall.squad_stage ==
		wolf->player->left_d->wall.squad_stage &&
		wolf->player->rght_d->wall.squad_stage == 0)
		wolf->player->inside_step = 0;
	else if (wolf->player->left_d->wall.squad_stage ==
		wolf->player->down_d->wall.squad_stage &&
		wolf->player->left_d->wall.squad_stage == 0)
		wolf->player->inside_step = 0;
}

void			recalc2(t_wolf *wolf)
{
	if (wolf->player->up_d->wall.squad_stage ==
		wolf->player->rght_d->wall.squad_stage &&
		wolf->player->up_d->wall.squad_stage == 0)
		wolf->player->inside_step = 0;
	else if (wolf->player->up_d->wall.squad_stage ==
		wolf->player->left_d->wall.squad_stage &&
		wolf->player->up_d->wall.squad_stage == 0)
		wolf->player->inside_step = 0;
	else if (wolf->player->rght_d->wall.squad_stage ==
		wolf->player->down_d->wall.squad_stage &&
		wolf->player->rght_d->wall.squad_stage == 0)
		wolf->player->inside_step = 0;
	else
		recalc3(wolf);
}

void			calcl(t_wolf *wolf)
{
	calculate_distance(wolf, wolf->player->rght_d, &(t_helper){-1, -1, RAD_0});
	calculate_distance(wolf, wolf->player->up_d, &(t_helper){-1, -1, RAD_90});
	calculate_distance(wolf, wolf->player->left_d,
		&(t_helper){-1, -1, RAD_180});
	calculate_distance(wolf, wolf->player->down_d,
		&(t_helper){-1, -1, RAD_270});
}

void			recalc(t_wolf *wolf)
{
	int r;
	int l;
	int u;
	int d;

	calcl(wolf);
	r = wolf->player->rght_d->wall.squad_stage;
	l = wolf->player->left_d->wall.squad_stage;
	u = wolf->player->up_d->wall.squad_stage;
	d = wolf->player->down_d->wall.squad_stage;
	if (r == l && u == r && r != 0)
		wolf->player->inside_step = wolf->player->rght_d->wall.h * UP_LENGTH;
	else if (r == l && d == r && r != 0)
		wolf->player->inside_step = wolf->player->rght_d->wall.h * UP_LENGTH;
	else if (u == d && r == u && u != 0)
		wolf->player->inside_step = wolf->player->up_d->wall.h * UP_LENGTH;
	else if (u == d && l == u && u != 0)
		wolf->player->inside_step = wolf->player->up_d->wall.h * UP_LENGTH;
	else if (u == d && u == 0)
		wolf->player->inside_step = 0;
	else
		recalc2(wolf);
}

static void		buble_sort_fly(t_distance *v, t_helper *h)
{
	float		of_temp;
	t_float2	cor_temp;

	while (++h->x < v->count - 1)
	{
		h->j = v->count;
		while (--h->j > h->x)
		{
			if (v->dist[h->x - 1] < v->dist[h->x])
			{
				h->angle = v->dist[h->j - 1];
				h->prikol = v->number_wall[h->j - 1];
				of_temp = v->offsetx[h->j - 1];
				cor_temp = v->coords[h->j - 1];
				v->dist[h->j - 1] = v->dist[h->j];
				v->number_wall[h->j - 1] = v->number_wall[h->j];
				v->offsetx[h->j - 1] = v->offsetx[h->j];
				v->coords[h->j - 1] = v->coords[h->j];
				v->dist[h->j] = h->angle;
				v->number_wall[h->j] = h->prikol;
				v->offsetx[h->j] = of_temp;
				v->coords[h->j] = cor_temp;
			}
		}
	}
}

static void		buble_sort(t_distance *v, t_helper *h)
{
	float		of_temp;
	t_float2	cor_temp;

	while (++h->x < v->count - 1)
	{
		h->j = v->count;
		while (--h->j > h->x)
		{
			if (v->dist[h->j - 1] > v->dist[h->j])
			{
				h->angle = v->dist[h->j - 1];
				h->prikol = v->number_wall[h->j - 1];
				of_temp = v->offsetx[h->j - 1];
				cor_temp = v->coords[h->j - 1];
				v->dist[h->j - 1] = v->dist[h->j];
				v->number_wall[h->j - 1] = v->number_wall[h->j];
				v->offsetx[h->j - 1] = v->offsetx[h->j];
				v->coords[h->j - 1] = v->coords[h->j];
				v->dist[h->j] = h->angle;
				v->number_wall[h->j] = h->prikol;
				v->offsetx[h->j] = of_temp;
				v->coords[h->j] = cor_temp;
			}
		}
	}
}

void			dist_to_ass(t_wolf *wolf, t_distance *v, int t)
{
	v->count = t;
	if (wolf->player->fly < 0)
		buble_sort_fly(v, &(t_helper){0, -1, 0, 0});
	else
		buble_sort(v, &(t_helper){0, -1, 0, 0});
}

t_distance		*dist_to_wall(t_wolf *wolf, t_helper *h)
{
	t_distance	*v;
	t_float2	player;
	float		tmp;

	tmp = -1.0f;
	v = wolf->player->distance_vert[h->prikol];
	t_distance_clear(v);
	player.x = wolf->player->x;
	player.y = wolf->player->y;
	while (h->x < wolf->p->count_walls)
	{
		tmp = calc_dist(player, wolf->p->walls[h->x], v,
			&(t_helper){h->j, 0, h->angle});
		if (tmp != -1.0f)
		{
			v->number_wall[h->j] = h->x;
			v->offsetx[h->j] = sqrtf(powf(v->coords[h->j].x
				- wolf->p->walls[h->x].x1, 2)
				+ powf(v->coords[h->j].y - wolf->p->walls[h->x].y1, 2))
				/ wolf->p->walls[h->x].length;
			v->dist[h->j] = tmp;
			h->j++;
		}
		h->x++;
	}
	dist_to_ass(wolf, v, h->j);
	return (v);
}
