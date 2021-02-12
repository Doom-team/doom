/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_dist.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:01:24 by ahusk             #+#    #+#             */
/*   Updated: 2021/02/12 16:01:25 by ahusk            ###   ########.fr       */
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
