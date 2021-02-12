/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:08 by grinko            #+#    #+#             */
/*   Updated: 2021/02/12 07:14:06 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	get_door_textures(t_map *map)
{
	map->door_tex[0]->img = load_image("/textures/doors/defdoor.png");
	map->door_tex[1]->img = load_image("/textures/doors/bluedoor.png");
	map->door_tex[2]->img = load_image("/textures/doors/yellowdoor.png");
	map->door_tex[3]->img = load_image("/textures/doors/reddoor.png");
	map->door_tex[4]->img = load_image("/textures/doors/switch.png");
	map->door_tex[5]->img = load_image("/textures/doors/bluekey.png");
	map->door_tex[6]->img = load_image("/textures/doors/yellowkey.png");
	map->door_tex[7]->img = load_image("/textures/doors/redkey.png");
	map->door_tex[8]->img = load_image("/textures/doors/light.png");
	map->door_tex[9]->img = load_image("/textures/doors/exit.png");
	map->door_tex[10]->img = load_image("/textures/doors/defdoor.png");
}

void	wtf(t_map *map)
{
	free(map->stairstr);
	map->stairstr = 0;
	map->plus_objects++;
}

void	save_obj_tmp3(t_map *map, int x, int y)
{
	if (map->gun_tex[3]->active == 1)
		save_objects(map, &(t_info){x, y, 7, 1},
			"../textures/guns/pistol/pistol_b.png");
	if (map->gun_tex[4]->active == 1)
		save_objects(map, &(t_info){x, y, 7, 2},
			"../textures/guns/shotgun/shotgun_b.png");
	if (map->gun_tex[5]->active == 1)
		save_objects(map, &(t_info){x, y, 7, 3},
			"../textures/guns/ak/ak_b.png");
	if (map->enemy_tex[0]->active == 1)
		save_objects(map, &(t_info){x, y, 3, 1},
			"../textures/enemy/e1.png");
	if (map->enemy_tex[1]->active == 1)
		save_objects(map, &(t_info){x, y, 3, 2},
			"../textures/enemy/e2.png");
	if (map->enemy_tex[2]->active == 1)
		save_objects(map, &(t_info){x, y, 3, 3},
			"../textures/enemy/e3.png");
}

int		sq(int x1, int y1, int x2, int y2)
{
	return ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void	two_n(t_map *map, t_color color)
{
	map->tem->i = map->tem->y1;
	map->tem->j = map->tem->x1;
	map->tem->di = (map->tem->y2 - map->tem->y1) / map->tem->dy;
	map->tem->diry = map->tem->x2 - map->tem->x1;
	map->tem->de = map->tem->dx + 1;
	if (map->tem->diry > 0)
		map->tem->diry = 1;
	if (map->tem->diry < 0)
		map->tem->diry = -1;
	while (map->tem->i != map->tem->y2)
	{
		draw_gr(map, map->tem->j, map->tem->i, color);
		map->tem->er += map->tem->de;
		if (map->tem->er >= map->tem->dy + 1)
		{
			map->tem->j += map->tem->diry;
			map->tem->er = map->tem->er - (map->tem->dy + 1);
		}
		map->tem->i += map->tem->di;
	}
}
