/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_block2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:48:27 by grinko            #+#    #+#             */
/*   Updated: 2021/02/12 01:48:25 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	doorshit2(t_map *map)
{
	if (map->door_tex[4]->active == 1)
		draw_img(map, &(t_info){310, 715, 20, 20}, map->door_tex[4]);
	if (map->door_tex[5]->active == 1)
	{
		draw_img(map, &(t_info){310, 715, 20, 20}, map->door_tex[5]);
		cursor(map, 4, 0, 16);
	}
	if (map->door_tex[6]->active == 1)
	{
		draw_img(map, &(t_info){310, 715, 20, 20}, map->door_tex[6]);
		cursor(map, 5, 0, 16);
	}
	if (map->door_tex[7]->active == 1)
	{
		draw_img(map, &(t_info){310, 715, 20, 20}, map->door_tex[7]);
		cursor(map, 6, 0, 16);
	}
}

void	doorshit(t_map *map)
{
	if ((map->door_tex[0]->active == 0 && map->door_tex[1]->active == 0 &&
		map->door_tex[2]->active == 0 && map->door_tex[3]->active == 0) ||
		map->validflag == 6 || map->validflag == 7 || map->validflag == 8)
	{
		map->inter_tex[16]->active = 1;
		draw_door_win(map);
	}
	if (map->door_tex[0]->active == 1)
		draw_img(map, &(t_info){310, 760, 40, 40}, map->door_tex[0]);
	if (map->door_tex[1]->active == 1)
		draw_img(map, &(t_info){310, 760, 40, 40}, map->door_tex[1]);
	if (map->door_tex[2]->active == 1)
		draw_img(map, &(t_info){310, 760, 40, 40}, map->door_tex[2]);
	if (map->door_tex[3]->active == 1)
		draw_img(map, &(t_info){310, 760, 40, 40}, map->door_tex[3]);
	doorshit2(map);
}

void	objectsblock(t_map *map)
{
	draw_obj_block(map);
	if (map->door_tex[10]->active == 1)
		doorshit(map);
	if (map->validflag == 6)
	{
		if (map->door_tex[0]->active == 1)
			map->validflag = 7;
		doorshit(map);
	}
	if (map->validflag == 9)
		save_texture(map, map->index_tex, 1);
}
