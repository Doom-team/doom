/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:37:45 by grinko            #+#    #+#             */
/*   Updated: 2021/02/12 00:12:19 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	draw_hlider(t_map *map)
{
	char *str;

	str = ft_itoa(map->whclick);
	if (map->inter_tex[6]->active)
	{
		draw_img(map, &(t_info){70, 180, 25, 25}, map->inter_tex[11]);
		draw_img(map, &(t_info){195, 180, 25, 25}, map->inter_tex[10]);
		draw_line(map, &(t_info){95, 192, 100, 0}, (t_color){255, 255, 255});
		draw_line(map, &(t_info){95, 193, 100, 0}, (t_color){255, 255, 255});
		draw_line(map, &(t_info){95, 194, 100, 0}, (t_color){255, 255, 255});
		fonts_classic(map, "wall height", &(t_info){102, 172, 0, 0}, WHITEFONT);
		fonts_classic(map, str, &(t_info){130, 202, 0, 0},
			WHITEFONT);
	}
	free(str);
}

void	draw_line(t_map *map, t_info *info, t_color color)
{
	int i;

	i = -1;
	if (info->h != 0)
	{
		while (++i < info->h)
			draw_pixel(map, info->x, info->y + i, color);
	}
	else if (info->w != 0)
	{
		while (++i < info->w)
			draw_pixel(map, info->x + i, info->y, color);
	}
}

void	bigdot(t_map *map, int x, int y, t_color color)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			draw_point(map, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	draw_grid(t_map *map)
{
	int i;
	int j;

	i = -1;
	while (++i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			if ((i % SCALE == 0) && (j % SCALE == 0))
				draw_point(map, j, i, GREY);
			else if ((i % SCALE == 0) || (j % SCALE == 0))
				draw_pixel(map, j, i, APPLEGREY);
			else
				draw_pixel(map, j, i, (t_color){0, 0, 0});
			j++;
		}
	}
}

void	draw_floor_line(t_map *map, t_info *cor)
{
	zerotem(map);
	map->tem->x1 = cor->x;
	map->tem->x2 = cor->w;
	if (map->tem->x1 < 0 && map->tem->x2 < 0)
		return ;
	map->tem->y1 = cor->y;
	map->tem->y2 = cor->h;
	map->tem->dx = abs(map->tem->x1 - map->tem->x2);
	map->tem->dy = abs(map->tem->y1 - map->tem->y2);
	map->tem->er = 0;
	map->tem->de = map->tem->dy + 1;
	map->tem->j = map->tem->y1;
	map->tem->i = map->tem->x1;
	map->tem->di = 0;
	if (map->tem->dx > map->tem->dy)
		one_n(map, YELLOW);
	else if (map->tem->dy != 0)
		two_n(map, YELLOW);
	bigdot(map, map->tem->x1, map->tem->y1, HOTPINK);
	bigdot(map, map->tem->x2, map->tem->y2, HOTPINK);
}
