/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:11 by grinko            #+#    #+#             */
/*   Updated: 2021/02/13 20:21:21 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	dot_forobject(t_map *map, int x, int y)
{
	map->objnum++;
	map->dots.x[map->objnum] = x;
	map->dots.y[map->objnum] = y;
	cursor(map, 0, 0, 16);
}

void	save_objcord(t_map *map, int x, int y)
{
	if (interface_click(map, x, y))
	{
		save_obj_tmp1(map, x, y);
		if (map->door_tex[6]->active == 1 && range_click(&(t_info){x, y,
			WIDTH / 2 - 165, 5}, 330, 150) && map->click == 1)
		{
			map->validflag = 8;
			save_objects(map, &(t_info){x, y, 8, 3},
				" ../textures/pickup/yellowkey.png");
		}
		if (map->door_tex[7]->active == 1 && range_click(&(t_info){x, y,
			WIDTH / 2 - 165, 5}, 330, 150) && map->click == 1)
		{
			map->validflag = 8;
			save_objects(map, &(t_info){x, y, 8, 4},
				" ../textures/pickup/redkey.png");
		}
	}
}

void	catch_click3(t_map *map, int x, int y)
{
	objects_click(map, x, y);
	if (map->door_tex[10]->active == 1 && map->inter_tex[16]->active == 1)
		get_door(map, x, y);
	save_objcord(map, x, y);
}

void	catch_click2(t_map *map, int x, int y)
{
	map->inter_tex[6]->active = 1;
	blockterxture_click(map, x, y);
	if (!widget_click(map, x, y))
		remove_blocks(map);
	hwidget_click(map, x, y);
}

int		catch_click(t_map *map, int x, int y)
{
	section_click(map, x, y);
	tools_click(map, x, y);
	if (map->inter_tex[3]->active == 1)
		catch_click2(map, x, y);
	if (map->inter_tex[4]->active == 1)
	{
		terxtures_click(map, x, y);
		floorker(map);
	}
	if (map->inter_tex[5]->active == 1 && !map->inter_tex[4]->active
		&& !map->inter_tex[3]->active)
		catch_click3(map, x, y);
	if (map->inter_tex[16]->active == 1)
		change_texture_click(map, x, y);
	if (some_texture_active(map) == 2)
		change_floor_click(map, x, y);
	if (map->inter_tex[21]->active == 1)
	{
		map->inter_tex[21]->active = 0;
		return (1);
	}
	else
		return (0);
}
