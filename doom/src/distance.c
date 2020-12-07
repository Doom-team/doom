/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:19:22 by clala             #+#    #+#             */
/*   Updated: 2020/10/24 21:54:06 by clala            ###   ########.fr       */
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
	if (v->dist > h->dist)
	{
		h->side = 0;
		return (h);
	}
	else
	{
		v->side = 1;
		return (v);
	}
}
