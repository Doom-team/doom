/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:11 by grinko            #+#    #+#             */
/*   Updated: 2021/02/12 17:48:57 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	zerroothero(t_map *map)
{
	int i;

	i = -1;
	map->click = 0;
	while (++i < 3)
		map->player_tex[i]->active = 0;
	i = -1;
	while (++i < 6)
		map->gun_tex[i]->active = 0;
	i = -1;
	while (++i < 5)
		map->enemy_tex[i]->active = 0;
	i = -1;
	while (++i < 11)
		map->door_tex[i]->active = 0;
}

void	cordinator(t_map *map, char *c, int x, int y)
{
	if (!map->objects)
		map->objects = add_text(c, ft_itoa(x), 3);
	else
	{
		free(map->objects);
		map->objects = add_text(c, ft_itoa(x), 3);
	}
	map->objects = add_text(map->objects, " ", 1);
	map->objects = add_text(map->objects, ft_itoa(y), 2);
	map->objects = add_text(map->objects, "\n", 1);
}

void	save_objects(t_map *map, t_info *inf, char *textstr)
{
	dot_forobject(map, inf->x, inf->y);
	if (!map->stairstr)
		map->stairstr = add_text("w ", ft_itoa(inf->x), 3);
	else
	{
		map->stairstr = add_text(map->stairstr, "w ", 1);
		map->stairstr = add_text(map->stairstr, ft_itoa(inf->x), 2);
	}
	map->stairstr = add_text(map->stairstr, " ", 1);
	map->stairstr = add_text(map->stairstr, ft_itoa(inf->y), 2);
	map->stairstr = add_text(map->stairstr, " ", 1);
	map->stairstr = add_text(map->stairstr, "0", 1);
	map->stairstr = add_text(map->stairstr, " ", 1);
	map->stairstr = add_text(map->stairstr, "0", 1);
	map->stairstr = add_text(map->stairstr, " ", 1);
	map->stairstr = add_text(map->stairstr, textstr, 1);
	map->stairstr = add_text(map->stairstr, " 5", 1);
	map->stairstr = add_text(map->stairstr, " ", 1);
	map->stairstr = add_text(map->stairstr, ft_itoa(inf->w), 2);
	map->stairstr = add_text(map->stairstr, " ", 1);
	map->stairstr = add_text(map->stairstr, ft_itoa(inf->h), 2);
	map->stairstr = add_text(map->stairstr, "\n", 1);
	map->stairsoutput = (!map->stairsoutput) ? ft_strdup(map->stairstr) :
	add_text(map->stairsoutput, map->stairstr, 2);
	wtf(map);
}

void	save_obj_tmp1(t_map *map, int x, int y)
{
	if (map->player_tex[0]->active == 1)
	{
		dot_forobject(map, x, y);
		cordinator(map, "p ", x, y);
	}
	if (map->player_tex[1]->active == 1)
		save_objects(map, &(t_info){x, y, 4, 0},
			"../textures/pickup/health.png");
	if (map->player_tex[2]->active == 1)
		save_objects(map, &(t_info){x, y, 5, 0},
			"../textures/pickup/armor.png");
	if (map->gun_tex[0]->active == 1)
		save_objects(map, &(t_info){x, y, 6, 1},
			"../textures/guns/pistol/img.png");
	if (map->gun_tex[1]->active == 1)
		save_objects(map, &(t_info){x, y, 6, 2},
			"../textures/guns/shotgun/img.png");
	if (map->gun_tex[2]->active == 1)
		save_objects(map, &(t_info){x, y, 6, 3},
			"../textures/guns/ak/img.png");
	save_obj_tmp2(map, x, y);
}

void	save_obj_tmp2(t_map *map, int x, int y)
{
	save_obj_tmp3(map, x, y);
	if (map->enemy_tex[3]->active == 1)
		save_objects(map, &(t_info){x, y, 3, 4}, "../textures/enemy/e4.png");
	if (map->enemy_tex[4]->active == 1)
		save_objects(map, &(t_info){x, y, 3, 5}, "../textures/enemy/e5.png");
	if (map->door_tex[9]->active == 1)
	{
		map->exitflag++;
		save_objects(map, &(t_info){x, y, 9, 0}, "../textures/pickup/end.png");
	}
	if (map->door_tex[5]->active == 1 && range_click(&(t_info){x, y,
		WIDTH / 2 - 165, 5}, 330, 150) && map->click == 1)
	{
		map->validflag = 8;
		save_objects(map, &(t_info){x, y, 8, 2},
			" ../textures/pickup/bluekey.png");
	}
}
