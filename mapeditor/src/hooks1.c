/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:11 by grinko            #+#    #+#             */
/*   Updated: 2021/02/10 16:02:28 by grinko           ###   ########.fr       */
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
	if (ft_strlen(map->objects) != 0)
	{
		if (map->player_tex[0]->active == 1 && searchelem(map->objects, "p "))
		{
			rewrite(map, searchelem(map->objects, "p ") - 1, x, y);
			return ;
		}
		if (map->door_tex[9]->active == 1 && searchelem(map->objects, "b "))
		{
			rewrite(map, searchelem(map->objects, "b ") - 1, x, y);
			return ;
		}
		map->objects = add_text(map->objects, c, 0);
		map->objects = add_text(map->objects, ft_itoa(x), 2);
		map->objects = add_text(map->objects, " ", 1);
		map->objects = add_text(map->objects, ft_itoa(y), 2);
		map->objects = add_text(map->objects, "\n", 1);
	}
	else
	{
		map->objects = add_text(c, ft_itoa(x), 3);
		map->objects = add_text(map->objects, " ", 1);
		map->objects = add_text(map->objects, ft_itoa(y), 2);
		map->objects = add_text(map->objects, "\n", 1);
	}
}

void	save_obj_tmp1(t_map *map, int x, int y)
{
	if (map->player_tex[0]->active == 1)
		cordinator(map, "p ", x, y);
	if (map->player_tex[1]->active == 1)
		cordinator(map, "h ", x, y);
	if (map->player_tex[2]->active == 1)
		cordinator(map, "a ", x, y);
	if (map->gun_tex[0]->active == 1)
		cordinator(map, "g 1 ", x, y);
	if (map->gun_tex[1]->active == 1)
		cordinator(map, "b 1 ", x, y);
	if (map->gun_tex[2]->active == 1)
		cordinator(map, "g 2 ", x, y);
	if (map->gun_tex[3]->active == 1)
		cordinator(map, "b 2 ", x, y);
	if (map->gun_tex[4]->active == 1)
		cordinator(map, "g 3 ", x, y);
	if (map->gun_tex[5]->active == 1)
		cordinator(map, "b 3 ", x, y);
	if (map->enemy_tex[0]->active == 1)
		cordinator(map, "e 1 ", x, y);
	if (map->enemy_tex[1]->active == 1)
		cordinator(map, "e 2 ", x, y);
	if (map->enemy_tex[2]->active == 1)
		cordinator(map, "e 3 ", x, y);
}
void	save_obj_tmp2(t_map *map, int x, int y)
{
	if (map->enemy_tex[3]->active == 1)
		cordinator(map, "e 4 ", x, y);
	if (map->enemy_tex[4]->active == 1)
		cordinator(map, "e 5 ", x, y);
	if (map->door_tex[8]->active == 1)
		cordinator(map, "l ", x, y);
	if (map->door_tex[9]->active == 1)
		cordinator(map, "b ", x, y);
	if (map->door_tex[4]->active == 1 && range_click(&(t_info){x, y,
		WIDTH / 2 - 165, 5}, 330, 150))
	{
		map->validflag = 8;
		cordinator(map, "k 1 ", x, y);
	}
	if (map->door_tex[5]->active == 1 && range_click(&(t_info){x, y,
		WIDTH / 2 - 165, 5}, 330, 150) && map->click == 1)
	{
		map->validflag = 8;
		cordinator(map, "k 2 ", x, y);
	}
}


void	save_objcord(t_map *map, int x, int y)
{
	if (interface_click(map, x, y))
	{
		save_obj_tmp1(map, x, y);
		save_obj_tmp2(map, x, y);
		if (map->door_tex[6]->active == 1 && range_click(&(t_info){x, y,
			WIDTH / 2 - 165, 5}, 330, 150) && map->click == 1)
		{
			map->validflag = 8;
			cordinator(map, "k 3 ", x, y);
		}
		if (map->door_tex[7]->active == 1 && range_click(&(t_info){x, y,
			WIDTH / 2 - 165, 5}, 330, 150) && map->click == 1)
		{
			map->validflag = 8;
			cordinator(map, "k 4 ", x, y);
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
	blockterxture_click(map, x, y); // клик готовым блокам раздела блоки
	if (!widget_click(map, x, y))// клик по виждету размера раздела блоки
		remove_blocks(map);
	hwidget_click(map, x, y);
}

int		catch_click(t_map *map, int x, int y)
{
	section_click(map, x, y); // клик по секциям
	tools_click(map, x, y); // клик по инструментам
	if (map->inter_tex[3]->active == 1)
		catch_click2(map, x, y);
	if (map->inter_tex[4]->active == 1)
	{
		terxtures_click(map, x, y); // клики в разделе тексты
		floorker(map, x, y);
	}
	if (map->inter_tex[5]->active == 1 && !map->inter_tex[4]->active
		&& !map->inter_tex[3]->active)
		catch_click3(map, x, y);
	if (map->inter_tex[16]->active == 1)
		change_texture_click(map, x, y); // клики по текстурам если блок текстуры активны
	if (some_texture_active(map) == 2)
		change_floor_click(map, x, y); // клики по текстурам если блок пола потолка активны
	if (map->inter_tex[21]->active == 1)
	{
		map->inter_tex[21]->active = 0;
		return (1);
	}
	else
		return (0);
}
