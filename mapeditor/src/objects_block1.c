/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_block1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:48:27 by grinko            #+#    #+#             */
/*   Updated: 2021/02/12 01:48:20 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	draw_door_winp1(t_map *map)
{
	draw_img(map, &(t_info){WIDTH / 2 - 165, 5, 330, 140},
		map->inter_tex[16]);
	draw_img(map, &(t_info){WIDTH / 2 - 130, 60, 20, 20},
		map->door_tex[4]);
	draw_img(map, &(t_info){WIDTH / 2 + 80, 100, 65, 30},
		map->floorsky_tex[0]);
	fonts_classic(map, "SAVE", &(t_info){WIDTH / 2 + 90, 105, 0, 0},
		WHITEFONT);
	draw_img(map, &(t_info){WIDTH / 2 - 145, 100, 65, 30},
		map->floorsky_tex[0]);
	fonts_classic(map, "CANCEL", &(t_info){WIDTH / 2 - 142, 105, 0, 0},
		WHITEFONT);
}

void	draw_door_winp2(t_map *map)
{
	draw_img(map, &(t_info){WIDTH / 2 - 165, 5, 330, 140},
		map->inter_tex[16]);
	draw_img(map, &(t_info){WIDTH / 2 + 80, 100, 65, 30},
		map->floorsky_tex[0]);
	fonts_classic(map, "SAVE", &(t_info){WIDTH / 2 + 90, 105, 0, 0},
		WHITEFONT);
	draw_img(map, &(t_info){WIDTH / 2 - 145, 100, 65, 30},
		map->floorsky_tex[0]);
	fonts_classic(map, "CANCEL", &(t_info){WIDTH / 2 - 142, 105, 0, 0},
		WHITEFONT);
}

void	draw_door_winp3(t_map *map)
{
	draw_img(map, &(t_info){WIDTH / 2 - 165, 5, 330, 140},
		map->inter_tex[16]);
	draw_img(map, &(t_info){WIDTH / 2 - 140, 10, 40, 40}, map->door_tex[0]);
	draw_img(map, &(t_info){WIDTH / 2 - 130, 60, 20, 20}, map->door_tex[4]);
	draw_img(map, &(t_info){WIDTH / 2 - 60, 10, 40, 40}, map->door_tex[1]);
	draw_img(map, &(t_info){WIDTH / 2 - 50, 60, 20, 20}, map->door_tex[5]);
	draw_img(map, &(t_info){WIDTH / 2 + 20, 10, 40, 40}, map->door_tex[2]);
	draw_img(map, &(t_info){WIDTH / 2 + 30, 60, 20, 20}, map->door_tex[6]);
	draw_img(map, &(t_info){WIDTH / 2 + 90, 10, 40, 40}, map->door_tex[3]);
	draw_img(map, &(t_info){WIDTH / 2 + 100, 60, 20, 20}, map->door_tex[7]);
	draw_img(map, &(t_info){WIDTH / 2 + 80, 100, 65, 30},
		map->floorsky_tex[0]);
	fonts_classic(map, "SAVE", &(t_info){WIDTH / 2 + 90, 105, 0, 0},
		WHITEFONT);
	draw_img(map, &(t_info){WIDTH / 2 - 145, 100, 65, 30},
		map->floorsky_tex[0]);
	fonts_classic(map, "CANCEL", &(t_info){WIDTH / 2 - 142, 105, 0, 0},
		WHITEFONT);
}

void	draw_door_win(t_map *map)
{
	if (map->validflag == 7)
	{
		draw_door_winp1(map);
	}
	else if (map->validflag == 8)
	{
		draw_door_winp2(map);
	}
	else
	{
		draw_door_winp3(map);
	}
}

void	draw_obj_block(t_map *map)
{
	draw_player(map);
	draw_guns(map);
	draw_enemy(map);
	draw_door_light_exit(map);
}
