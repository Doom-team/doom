/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:37:42 by grinko            #+#    #+#             */
/*   Updated: 2021/02/13 20:26:28 by grinko           ###   ########.fr       */
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
	if (i < 0)
		i = 0;
	while (i < HEIGHT && i < info->y + info->h)
	{
		j = info->x;
		if (j < 0)
			j = 0;
		while (j < WIDTH && j < info->x + info->w)
		{
			pixel1 = i * map->inter_tex[0]->strb + j * map->inter_tex[0]->pixb;
			pixel2 = (int)((float)(i - info->y) * st->img->h / info->h) * st->strb
			+ (int)((float)(j - info->x) * st->img->w / info->w) * st->pixb;
			if (pixel2 < 0 || pixel1 < 0)
			{
				printf("%d %d\n", pixel1, pixel2);
				return ;
			}
			if (st->s[pixel2 + 3])
				funcfunc(pixel1, pixel2, map, st);
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

	if (x < WIDTH && y < HEIGHT && x >= 0 && y >= 0)
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
	pixel = 0;
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
