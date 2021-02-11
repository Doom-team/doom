/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 13:39:11 by grinko            #+#    #+#             */
/*   Updated: 2021/02/12 00:49:53 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	edit_floortexture(t_map *map, int index)
{
	int i;

	i = 0;
	zerroother(map);
	while (++i < 13)
	{
		if (i == index)
			map->floorsky_tex[i]->active = 1;
		else
			map->floorsky_tex[i]->active = 0;
	}
}

void	edit_liquidtexture(t_map *map, int index)
{
	int i;

	i = 0;
	zerroother(map);
	while (++i < 4)
	{
		if (i == index)
			map->liquid_tex[i]->active = 1;
		else
			map->liquid_tex[i]->active = 0;
	}
}

void	walltx_click2(t_map *map, int x, int y)
{
	int i;
	int x_c;

	x_c = 20;
	i = 8;
	while (++i < 19)
	{
		if ((x > 320 && x < 370) && (y > x_c && y < x_c + 50))
			edit_walltexture(map, i);
		x_c += 80;
	}
}

void	walltx_click(t_map *map, int x, int y)
{
	int i;
	int x_c;
	int y_c;

	i = 0;
	x_c = 20;
	y_c = 170;
	while (++i < 9)
	{
		if ((x > x_c && x < x_c + 50) && (y > y_c && y < y_c + 50))
			edit_walltexture(map, i);
		x_c += 60;
		if (i == 4)
		{
			x_c = 20;
			y_c = 230;
		}
	}
	if (map->inter_tex[13]->active == 1)
		walltx_click2(map, x, y);
}

void	floortx_click(t_map *map, int x, int y)
{
	int i;
	int x_c;
	int y_c;

	i = 0;
	x_c = 20;
	y_c = 340;
	while (++i < 9)
	{
		if ((x > x_c && x < x_c + 50) && (y > y_c && y < y_c + 50))
			edit_floortexture(map, i);
		x_c += 60;
		if (i == 4)
		{
			x_c = 20;
			y_c = 400;
		}
	}
}
