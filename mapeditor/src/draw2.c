/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:37:45 by grinko            #+#    #+#             */
/*   Updated: 2020/12/22 13:38:54 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void draw_slider(t_map *map)
{
	draw_img(map, &(t_info){40, 120, 220, 100}, map->inter_tex[9]);
	if (map->block_tex[0]->active || map->block_tex[1]->active ||
	 map->block_tex[2]->active || map->block_tex[3]->active)
	{
		draw_img(map, &(t_info){70, 140, 25, 25}, map->inter_tex[11]);
		draw_img(map, &(t_info){195, 140, 25, 25}, map->inter_tex[10]);
		draw_line(map, &(t_info){95, 152, 100, 0}, (t_color){255,255,255});
		draw_line(map, &(t_info){95, 153, 100, 0}, (t_color){255,255,255});
		draw_line(map, &(t_info){95, 154, 100, 0}, (t_color){255,255,255});
		bigdot(map, 115 + (map->wclick), 153, RED);
		fonts_classic(map, "radius", &(t_info){122, 132, 0, 0}, WHITEFONT);
	}
}

void draw_hlider(t_map *map)
{
	// draw_img(map, &(t_info){40, 120, 220, 100}, map->inter_tex[9]);
	if (map->inter_tex[6]->active)
	{
		draw_img(map, &(t_info){70, 180, 25, 25}, map->inter_tex[11]);
		draw_img(map, &(t_info){195, 180, 25, 25}, map->inter_tex[10]);
		draw_line(map, &(t_info){95, 192, 100, 0}, (t_color){255,255,255});
		draw_line(map, &(t_info){95, 193, 100, 0}, (t_color){255,255,255});
		draw_line(map, &(t_info){95, 194, 100, 0}, (t_color){255,255,255});
		// bigdot(map, 182 + (map->whclick), 193, RED);
		fonts_classic(map, "wall height", &(t_info){102, 172, 0, 0}, WHITEFONT);
		fonts_classic(map, ft_itoa(map->whclick), &(t_info){130, 202, 0, 0}, WHITEFONT);
	}
}

void draw_line(t_map *map, t_info *info, t_color color)
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

void bigdot(t_map *map, int x, int y, t_color color)
{
	int i;
	int j;

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

void draw_grid(t_map *map)
{
	int i;
	int j;

	i = -1;
	while (++i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			if ((i - map->z_y) % SCALE == 0 && (j - map->z_x) % SCALE == 0)
				draw_point(map, j, i, GREY);
			else if ((i - map->z_y) % SCALE == 0 || (j - map->z_x) % SCALE == 0)
				
				draw_pixel(map, j, i, APPLEGREY);
			else
				draw_pixel(map, j, i, (t_color){0, 0, 0});
			j++;
		}
	}
}



void draw_floor_line(t_map *map, t_info *cor)
{
	int x1;
	int y1;
	int x2;
	int y2;

	int dx;
	int dy;
	int er;
	int de;

	int i;
	int j;

	int diry;
	int di;

		x1 = cor->x + map->z_x;
		x2 = cor->w + map->z_x;
		if (x1 < 0 && x2 < 0)
			return;
		y1 = cor->y + map->z_y;
		y2 = cor->h + map->z_y;
		dx = abs(x1 - x2);
		dy = abs(y1 - y2);
		er = 0;
		de = dy + 1;
		j = y1;
		i = x1;
		di = 0;
		
		if (dx > dy)
		{
			i = x1;
			j = y1;
			di = (x2 - x1) / dx;
			diry = y2 - y1;
			de = dy + 1;
			if (diry > 0)
				diry = 1;
			if (diry < 0)
				diry = -1;
			
			while (i != x2)
			{
				draw_gr(map, i, j, YELLOW);
				er += de;
				if (er >= dx + 1)
				{
					j += diry;
					er = er - (dx + 1);
				}
				i += di;
			}
		}
		else if (dy != 0)
		{
			i = y1;
			j = x1;
			di = (y2 - y1) / dy;
			diry = x2 - x1;
			de = dx + 1;
			if (diry > 0)
				diry = 1;
			if (diry < 0)
				diry = -1;
			
			while (i != y2)
			{
				draw_gr(map, j, i, YELLOW);
				er += de;
				if (er >= dy + 1)
				{
					j += diry;
					er = er - (dy + 1);
				}
				i += di;
			}
		}
		bigdot(map, x1, y1, HOTPINK);
		bigdot(map, x2, y2, HOTPINK);
}