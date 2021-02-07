/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gordey <gordey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 13:39:11 by grinko            #+#    #+#             */
/*   Updated: 2021/02/07 17:32:27 by gordey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

int		interface_click(t_map *map, int x, int y)
{
	if ((x > 0 && x < 300) && y > 0 && y < 800)
		return (0);
	return (1);
}

int		range_click(t_info *info, int w, int h)
{
	if ((info->x > info->w && info->x < info->w + w) &&
		info->y > info->h && info->y < info->h + h)
		return (0);
	return (1);
}

void	tools_click(t_map *map, int x, int y)
{
	if ((x > 80 && x < 110) && y > 60 && y < 90)
		edit_tool(map, 6);
	else if ((x > 130 && x < 160) && y > 60 && y < 90)
		edit_tool(map, 7);
	else if ((x > 180 && x < 210) && y > 60 && y < 90)
		edit_tool(map, 8);
}

void	hwidget_click(t_map *map, int x, int y)
{
	if ((x > 70 && x < 95) && (y > 180 && y < 205) && map->whclick > 1)
		map->whclick -= 1;
	else if ((x > 195 && x < 220) && y > 180 && y < 205 && map->whclick < 20)
		map->whclick += 1;
}

int		widget_click(t_map *map, int x, int y)
{
	int tmp;

	tmp = map->wclick;
	if ((x > 70 && x < 95) && (y > 140 && y < 165) && map->wclick > -20)
	{
		map->tmpclick = 1;
		map->wclick -= 3;
	}
	else if ((x > 195 && x < 220) && (y > 140 && y < 165) && map->wclick < 76)
	{
		map->tmpclick = 1;
		map->wclick += 3;
	}
	if (map->wclick != tmp)
		return (0);
	return (1);
}
