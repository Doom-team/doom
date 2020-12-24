/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 19:41:37 by grinko            #+#    #+#             */
/*   Updated: 2020/12/24 14:11:49 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void draw_player(t_map *map)
{
	fonts_classic(map, "player & items", &(t_info){100, 110, 0, 0}, REDFONT);
	if (map->player_tex[0]->active == 1)
		draw_img(map, &(t_info){25, 125, 50, 50}, map->inter_tex[15]);
	if (map->player_tex[1]->active == 1)
		draw_img(map, &(t_info){125, 142, 50, 35}, map->inter_tex[15]);
	if (map->player_tex[2]->active == 1)
		draw_img(map, &(t_info){225, 142, 50, 35}, map->inter_tex[15]);
	draw_img(map, &(t_info){30, 130, 40, 40}, map->player_tex[0]);
	draw_img(map, &(t_info){130, 150, 40, 20}, map->player_tex[1]);
	draw_img(map, &(t_info){230, 150, 40, 20}, map->player_tex[2]);
}

void draw_guns(t_map *map)
{
	fonts_classic(map, "guns & bullets", &(t_info){100, 210, 0, 0}, REDFONT);
	if (map->gun_tex[0]->active == 1)
		draw_img(map, &(t_info){25, 245, 60, 35}, map->inter_tex[15]);
	if (map->gun_tex[2]->active == 1)
		draw_img(map, &(t_info){125, 245, 60, 35}, map->inter_tex[15]);
	if (map->gun_tex[4]->active == 1)
		draw_img(map, &(t_info){225, 245, 60, 35}, map->inter_tex[15]);
	if (map->gun_tex[1]->active == 1)
		draw_img(map, &(t_info){25, 275, 25, 25}, map->inter_tex[15]);
	if (map->gun_tex[3]->active == 1)
		draw_img(map, &(t_info){125, 275, 25, 25}, map->inter_tex[15]);
	if (map->gun_tex[5]->active == 1)
		draw_img(map, &(t_info){225, 275, 25, 25}, map->inter_tex[15]);
	draw_img(map, &(t_info){30, 250, 50, 20}, map->gun_tex[0]);
	draw_img(map, &(t_info){130, 250, 50, 20}, map->gun_tex[2]);
	draw_img(map, &(t_info){230, 250, 50, 20}, map->gun_tex[4]);
	draw_img(map, &(t_info){30, 280, 20, 20}, map->gun_tex[1]);
	draw_img(map, &(t_info){130, 280, 30, 20}, map->gun_tex[3]);
	draw_img(map, &(t_info){230, 280, 30, 20}, map->gun_tex[5]);
}

void draw_enemy(t_map *map)
{
	fonts_classic(map, "enemys", &(t_info){120, 310, 0, 0}, REDFONT);
	if (map->enemy_tex[0]->active == 1)
		draw_img(map, &(t_info){25, 345, 50, 50}, map->inter_tex[15]);
	if (map->enemy_tex[1]->active == 1)
		draw_img(map, &(t_info){125, 345, 50, 50}, map->inter_tex[15]);
	if (map->enemy_tex[2]->active == 1)
		draw_img(map, &(t_info){210, 345, 70, 50}, map->inter_tex[15]);
	if (map->enemy_tex[3]->active == 1)
		draw_img(map, &(t_info){55, 425, 50, 50}, map->inter_tex[15]);
	if (map->enemy_tex[4]->active == 1)
		draw_img(map, &(t_info){155, 425, 50, 50}, map->inter_tex[15]);
	draw_img(map, &(t_info){30, 350, 40, 40}, map->enemy_tex[0]);
	draw_img(map, &(t_info){130, 350, 40, 40}, map->enemy_tex[1]);
	draw_img(map, &(t_info){220, 350, 50, 40}, map->enemy_tex[2]);
	draw_img(map, &(t_info){60, 430, 40, 40}, map->enemy_tex[3]);
	draw_img(map, &(t_info){160, 430, 40, 40}, map->enemy_tex[4]);
}

void draw_door_light_exit(t_map *map)
{
	fonts_classic(map, "door", &(t_info){120, 480, 0, 0}, REDFONT);
	if (map->door_tex[10]->active == 1)
		draw_img(map, &(t_info){100, 490, 70, 60}, map->inter_tex[15]);
	draw_img(map, &(t_info){115, 500, 40, 40}, map->door_tex[0]);
	fonts_classic(map, "light", &(t_info){120, 580, 0, 0}, REDFONT);
	if (map->door_tex[8]->active == 1)
		draw_img(map, &(t_info){100, 590, 70, 60}, map->inter_tex[15]);
	draw_img(map, &(t_info){115, 600, 40, 40}, map->door_tex[8]);
	fonts_classic(map, "finish | exit", &(t_info){100, 680, 0, 0}, REDFONT);
	if (map->door_tex[9]->active == 1)
		draw_img(map, &(t_info){120, 690, 40, 60}, map->inter_tex[15]);
	draw_img(map, &(t_info){130, 700, 20, 40}, map->door_tex[9]);
}