/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 13:39:11 by grinko            #+#    #+#             */
/*   Updated: 2021/02/11 18:09:51 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	section_click(t_map *map, int x, int y)
{
	if ((x > 20 && x < 90) && y > 20 && y < 50)
		edit_tool(map, 3);
	else if ((x > 110 && x < 180) && y > 20 && y < 50)
		edit_tool(map, 4);
	else if ((x > 200 && x < 270) && y > 20 && y < 50)
		edit_tool(map, 5);
	else if ((x > 120 && x < 180) && y > 758 && y < 788)
		map->inter_tex[21]->active = 1;
}

void	blockterxture_click2(t_map *map, int x, int y)
{
	if ((x > 70 && x < 95) && y > 410 && y < 435)
		if (map->stclick > 1)
			map->stclick--;
	if ((x > 195 && x < 220) && y > 410 && y < 435)
		if (map->stclick < 15)
			map->stclick++;
	if ((x > 20 && x < 70) && y > 670 && y < 720)
		map->musicflag = 1;
	if ((x > 90 && x < 140) && y > 670 && y < 720)
		map->musicflag = 2;
	if ((x > 160 && x < 210) && y > 670 && y < 720)
		map->musicflag = 3;
	if ((x > 230 && x < 280) && y > 670 && y < 720)
		map->musicflag = 4;
}

void	blockterxture_click(t_map *map, int x, int y)
{
	if ((x > 65 && x < 115) && y > 250 && y < 300)
		edit_blocktexture(map, 0);
	else if ((x > 165 && x < 215) && y > 250 && y < 300)
		edit_blocktexture(map, 1);
	else if ((x > 65 && x < 115) && y > 320 && y < 370)
		edit_blocktexture(map, 2);
	else if ((x > 165 && x < 215) && y > 250 && y < 370)
		edit_blocktexture(map, 3);
	else if ((x > 120 && x < 180) && y > 470 && y < 530)
	{
		map->click = 0;
		edit_blocktexture(map, 5);
	}
	blockterxture_click2(map, x, y);
}

void	showup_lick(t_map *map, int x, int y)
{
	if ((x > 260 && x < 290) && y > 205 && y < 255)
	{
		map->showactive = 1;
		if (map->inter_tex[13]->active == 1)
			map->inter_tex[13]->active = 0;
		else
			map->inter_tex[13]->active = 1;
	}
}

void	zerroother(t_map *map)
{
	int i;

	i = 0;
	map->click = 0;
	while (++i < 19)
		map->wall_tex[i]->active = 0;
	i = 0;
	while (++i < 13)
		map->floorsky_tex[i]->active = 0;
	i = 0;
	while (++i < 4)
		map->liquid_tex[i]->active = 0;

	
}

void	edit_walltexture(t_map *map, int index)
{
	int i;

	i = 0;
	zerroother(map);
	while (++i < 19)
	{
		if (i == index)
			map->wall_tex[i]->active = 1;
		else
			map->wall_tex[i]->active = 0;
	}
}
