/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:38:55 by grinko            #+#    #+#             */
/*   Updated: 2020/12/22 13:38:57 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void draw_floor_textures(t_map *map)
{
	int i;
	int x;
	int y;

	i = 0;
	x = 20;
	y = 340;
	draw_img(map, &(t_info){50, 300, 200, 30}, map->floorsky_tex[0]);
	fonts_doom(map, "FLOOR & CEILING", &(t_info){63, 307, 0, 0}, REDFONT);
	while (++i < 9)
	{
		if (map->floorsky_tex[i]->active == 1)
			draw_img(map, &(t_info){x - 10, y - 10, 70, 70}, map->inter_tex[15]);
		draw_img(map, &(t_info){x, y, 50, 50}, map->floorsky_tex[i]);
		x += 60;
		if (i == 4)
		{
			x = 20;
			y = 400;
		}
	}
}

void draw_wall_textures(t_map *map)
{
	int i;
	int x;
	int y;

	i = 0;
	x = 20;
	y = 170;
	draw_img(map, &(t_info){50, 125, 200, 30}, map->wall_tex[0]);
	fonts_doom(map, "WALLS", &(t_info){120, 132, 0, 0}, REDFONT);
	while (++i < 9)
	{
		if (map->wall_tex[i]->active == 1)
			draw_img(map, &(t_info){x - 10, y - 10, 70, 70}, map->inter_tex[15]);
		draw_img(map, &(t_info){x, y, 50, 50}, map->wall_tex[i]);
		x += 60;
		if (i == 4)
		{
			x = 20;
			y = 230;
		}
	}
}

void draw_sky_textures(t_map *map)
{
	int i;
	int x;
	int y;

	i = 8;
	x = 20;
	y = 520;
	draw_img(map, &(t_info){50, 475, 200, 30}, map->liquid_tex[0]);
	fonts_doom(map, "SKY", &(t_info){130, 482, 0, 0}, REDFONT);
	while (++i < 13)
	{
		if (map->floorsky_tex[i]->active == 1)
			draw_img(map, &(t_info){x - 10, y - 10, 70, 70}, map->inter_tex[15]);
		draw_img(map, &(t_info){x, y, 50, 50}, map->floorsky_tex[i]);
		x += 60;
	}
}

void draw_liquid_textures(t_map *map)
{
	int i;
	int x;
	int y;

	i = 0;
	x = 20;
	y = 620;
	draw_img(map, &(t_info){50, 580, 200, 30}, map->liquid_tex[0]);
	fonts_doom(map, "LIQUIDS", &(t_info){110, 587, 0, 0}, REDFONT);
	while (++i < 4)
	{
		if (map->liquid_tex[i]->active == 1)
			draw_img(map, &(t_info){x - 10, y - 10, 70, 70}, map->inter_tex[15]);
		draw_img(map, &(t_info){x, y, 50, 50}, map->liquid_tex[i]);
		x += 90;
	}
}