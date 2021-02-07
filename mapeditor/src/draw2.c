/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gordey <gordey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:37:45 by grinko            #+#    #+#             */
/*   Updated: 2021/02/07 15:22:20 by gordey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	draw_music(t_map *map)
{
	fonts_classic(map, "MISIC", &(t_info){122, 640, 0, 0}, BLACKFONT);
	draw_img(map, &(t_info){20, 670, 50, 50}, map->block_tex[4]);
	draw_img(map, &(t_info){90, 670, 50, 50}, map->block_tex[4]);
	draw_img(map, &(t_info){160, 670, 50, 50}, map->block_tex[4]);
	draw_img(map, &(t_info){230, 670, 50, 50}, map->block_tex[4]);
}

void	draw_tests(t_map *map)
{
	fonts_doom(map, "test of endurance", &(t_info){75, 540, 0, 0}, REDFONT);
	draw_img(map, &(t_info){35, 560, 60, 60}, map->block_tex[6]);
	draw_img(map, &(t_info){120, 560, 60, 60}, map->block_tex[7]);
	draw_img(map, &(t_info){200, 560, 60, 60}, map->block_tex[8]);
}

void	draw_stairs(t_map *map)
{
	draw_img(map, &(t_info){40, 400, 220, 50}, map->inter_tex[9]);
	draw_img(map, &(t_info){70, 410, 25, 25}, map->inter_tex[11]);
	draw_img(map, &(t_info){195, 410, 25, 25}, map->inter_tex[10]);
	draw_line(map, &(t_info){95, 422, 100, 0}, (t_color){255, 255, 255});
	draw_line(map, &(t_info){95, 423, 100, 0}, (t_color){255, 255, 255});
	draw_line(map, &(t_info){95, 424, 100, 0}, (t_color){255, 255, 255});
	fonts_classic(map, "stairs height", &(t_info){102, 402, 0, 0}, WHITEFONT);
	fonts_classic(map, ft_itoa(map->stclick), &(t_info){130, 432, 0, 0},
		WHITEFONT);
	draw_img(map, &(t_info){120, 470, 60, 60}, map->block_tex[5]);
}

void	draw_slider(t_map *map)
{
	draw_img(map, &(t_info){40, 120, 220, 100}, map->inter_tex[9]);
	if (map->block_tex[0]->active || map->block_tex[1]->active ||
		map->block_tex[2]->active || map->block_tex[3]->active)
	{
		draw_img(map, &(t_info){70, 140, 25, 25}, map->inter_tex[11]);
		draw_img(map, &(t_info){195, 140, 25, 25}, map->inter_tex[10]);
		draw_line(map, &(t_info){95, 152, 100, 0}, (t_color){255, 255, 255});
		draw_line(map, &(t_info){95, 153, 100, 0}, (t_color){255, 255, 255});
		draw_line(map, &(t_info){95, 154, 100, 0}, (t_color){255, 255, 255});
		bigdot(map, 115 + (map->wclick), 153, RED);
		fonts_classic(map, "radius", &(t_info){122, 132, 0, 0}, WHITEFONT);
	}
}

void	draw_hlider(t_map *map)
{
	if (map->inter_tex[6]->active)
	{
		draw_img(map, &(t_info){70, 180, 25, 25}, map->inter_tex[11]);
		draw_img(map, &(t_info){195, 180, 25, 25}, map->inter_tex[10]);
		draw_line(map, &(t_info){95, 192, 100, 0}, (t_color){255, 255, 255});
		draw_line(map, &(t_info){95, 193, 100, 0}, (t_color){255, 255, 255});
		draw_line(map, &(t_info){95, 194, 100, 0}, (t_color){255, 255, 255});
		fonts_classic(map, "wall height", &(t_info){102, 172, 0, 0}, WHITEFONT);
		fonts_classic(map, ft_itoa(map->whclick), &(t_info){130, 202, 0, 0},
			WHITEFONT);
	}
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
			if ((i ) % SCALE == 0 && (j ) % SCALE == 0)
				draw_point(map, j, i, GREY);
			else if ((i ) % SCALE == 0 || (j ) % SCALE == 0)
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
