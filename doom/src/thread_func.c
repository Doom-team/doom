/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:31:45 by skaren            #+#    #+#             */
/*   Updated: 2021/02/09 16:20:04 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static	void	main_rendering(t_pthrdata *data)
{
	data->point.y = roundf((data->wolf->player->dist_to_canvas)\
	/ data->wolf->player->distance[data->count_distance]->\
	dist[data->wolf->p->count_walls - 1]);
	data->point.y = (H - data->point.y) / 2;
	draw_sky(data->wolf, data->point.x,\
	data->point.y - data->wolf->player->dir_y);
	floorcast(data->wolf, data->wolf->player->distance[data->count_distance]\
	, data->point, data->count_distance);
	if (data->wolf->player->fly < 0)
		draw_column_fly(data->wolf, data->point, data->count_distance);
	else
		draw_column(data->wolf, data->point, data->count_distance);
}

static	void	*thread_func(void *thread_data)
{
	t_pthrdata	*data;
	int			end;

	data = thread_data;
	data->count_distance = roundf(W - W * 1.0f / THREAD * data->number - 1);
	data->point.x = roundf((W * data->number * 1.0f) / THREAD);
	if (data->interlaced_rendering)
		data->point.x++;
	end = roundf(((W * data->number * 1.0f) / THREAD) + (W * 1.0f / THREAD));
	while (data->point.x < end)
	{
		if (data->wolf->player->distance[data->count_distance]->dist[0] != 0)
			main_rendering(data);
		data->count_distance -= 2;
		data->point.x += 2;
	}
	return (NULL);
}

static	void	wait_and_free_thread(pthread_t *threads,\
				t_pthrdata *thread_data)
{
	int			i;

	i = -1;
	while (++i < THREAD)
		pthread_join(threads[i], NULL);
	free(threads);
	free(thread_data);
}

void			pseudo_3d(t_wolf *wolf)
{
	t_point		point;
	pthread_t	*threads;
	t_pthrdata	*thread_data;
	int			i;

	i = -1;
	point.x = wolf->sdl->interlaced_rendering == 0 ? 0 : 1;
	ft_memset(&wolf->z_buff, 0, W * H * sizeof(bool));
	if (!(threads = (pthread_t*)malloc(THREAD * sizeof(pthread_t))))
		error(wolf, ERR_MALLOC);
	if (!(thread_data = (t_pthrdata*)malloc(THREAD * sizeof(t_pthrdata))))
		error(wolf, ERR_MALLOC);
	while (++i < THREAD)
	{
		thread_data[i].number = i;
		thread_data[i].wolf = wolf;
		thread_data[i].point = point;
		thread_data[i].interlaced_rendering = wolf->sdl->interlaced_rendering;
		thread_data[i].count_distance = 0;
		pthread_create(&(threads[i]), NULL, thread_func, &thread_data[i]);
	}
	wait_and_free_thread(threads, thread_data);
	wolf->sdl->interlaced_rendering =\
		wolf->sdl->interlaced_rendering == 0 ? 1 : 0;
}
