/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:37:42 by grinko            #+#    #+#             */
/*   Updated: 2021/02/13 14:54:29 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	draw_img(t_map *map, t_info *info, t_image *st)
{
	int	i;
	int	j;
	int	pixel1;
	int	pixel2;

	i = info->y;
	while (i < HEIGHT && i < info->y + info->h)
	{
		j = info->x;
		while (j < WIDTH && j < info->x + info->w)
		{
			pixel1 = i * map->inter_tex[0]->strb + j * map->inter_tex[0]->pixb;
			pixel2 = (int)((double)(i - info->y) / info->h * st->img->h) *
				st->strb + (int)((double)(j - info->x) / info->w *
					st->img->w) * st->pixb;
			if (st->s[pixel2 + 3])
			{
				map->inter_tex[0]->s[pixel1] = st->s[pixel2];
				map->inter_tex[0]->s[++pixel1] = st->s[++pixel2];
				map->inter_tex[0]->s[++pixel1] = st->s[++pixel2];
			}
			j++;
		}
		i++;
	}
}

void	draw_color(t_map *map, int pixel, t_color color)
{
	map->inter_tex[0]->s[pixel] = color.b;
	map->inter_tex[0]->s[++pixel] = color.g;
	map->inter_tex[0]->s[++pixel] = color.r;
}

void	draw_pixel(t_map *map, int x, int y, t_color color)
{
	int pixel;

	if (x < WIDTH && y < HEIGHT)
	{
		pixel = (x * map->inter_tex[0]->pixb) + (y * map->inter_tex[0]->strb);
		draw_color(map, pixel, color);
	}
}

void	draw_point(t_map *map, int x, int y, t_color color)
{
	int	i;
	int	j;
	int	pixel;

	i = -1;
	while (i < 1)
	{
		j = -1;
		while (j < 1)
		{
			if (x + i >= 0 && y + j >= 0 && x + i < WIDTH && y + j < HEIGHT)
			{
				pixel = ((x + i) * map->inter_tex[0]->pixb) + ((y + j) *
					map->inter_tex[0]->strb);
				draw_color(map, pixel, color);
			}
			j++;
		}
		i++;
	}
}

void	draw(t_map *map)
{
	draw_basic_interface(map);
	whichone_tool(map);
	if (map->click)
		bigdot(map, map->x_c, map->y_c, RED);
	if ((map->click || map->tmpclick) && (map->block_tex[0]->active ||
		map->block_tex[1]->active || map->block_tex[2]->active ||
			map->block_tex[3]->active))
	{
		map->click = 0;
		map->tmpclick = 0;
		made_blocks(map, map->x_c, map->y_c);
	}
	draw_nodes(map);
	if (SDL_UpdateWindowSurface(map->win) == -1)
		error("SDL Error!");
}
