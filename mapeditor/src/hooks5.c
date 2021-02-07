/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gordey <gordey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 13:39:11 by grinko            #+#    #+#             */
/*   Updated: 2021/02/07 20:08:06 by gordey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	liquidtx_click(t_map *map, int x, int y)
{
	int i;
	int x_c;
	int y_c;

	i = 0;
	x_c = 20;
	y_c = 620;
	while (++i < 4)
	{
		if ((x > x_c && x < x_c + 50) && (y > y_c && y < y_c + 50))
			edit_liquidtexture(map, i);
		x_c += 90;
	}
}

void	terxtures_click(t_map *map, int x, int y)
{
	edit_blocktexture(map, -1);
	showup_lick(map, x, y);
	walltx_click(map, x, y);
	floortx_click(map, x, y);
	skytx_click(map, x, y);
	liquidtx_click(map, x, y);
}

void	change_texture_click(t_map *map, int x, int y)
{
	if ((x > WIDTH / 2 - 10 && x < WIDTH / 2 + 20) && (y > 3 && y < 38))
	{
		map->inter_tex[17]->active = 1;
		map->inter_tex[19]->active = 0;
	}
	if ((x > WIDTH / 2 - 10 && x < WIDTH / 2 + 20) && (y > 83 && y < 118))
	{
		map->inter_tex[17]->active = 0;
		map->inter_tex[19]->active = 1;
	}
	if ((x > WIDTH / 2 - 145 && x < WIDTH / 2 - 80) && (y > 100 && y < 130))
	{
		map->inter_tex[16]->active = 0;
		map->inter_tex[17]->active = 0;
		map->inter_tex[19]->active = 0;
	}
	if ((x > WIDTH / 2 + 80 && x < WIDTH / 2 + 145) && (y > 100 && y < 130))
		map->inter_tex[16]->active = 2;
}

void	change_floor_click(t_map *map, int x, int y)
{
	if ((x > WIDTH / 2 + 20 && x < WIDTH / 2 + 90) && (y > 10 && y < 30))
		map->floorsky_tex[0]->active = 1;
	if ((x > WIDTH / 2 + 20 && x < WIDTH / 2 + 90) && (y > 30 && y < 50))
		map->floorsky_tex[0]->active = 2;
	if ((x > WIDTH / 2 + 120 && x < WIDTH / 2 + 185) && (y > 60 && y < 90))
	{
		zerroother(map);
		map->inter_tex[16]->active = 4;
	}
	if ((x > WIDTH / 2 - 100 && x < WIDTH / 2 - 35) && (y > 60 && y < 90))
	{
		zerroother(map);
		map->inter_tex[16]->active = 0;
	}
}

void	floorker(t_map *map, int x, int y)
{
	int x1;
	int y1;

	//x1 = x;
	//y1 = y;
	//find_coord(map, &x1, &y1);
	draw(map);
	if (some_texture_active(map) == 2)
	{
		open_floor_win(map);
		// if (x1 != x || y1 != y)
		// 	get_floor_cordi(map, x1 , y1 );
	}
}