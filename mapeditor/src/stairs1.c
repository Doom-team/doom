/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stairs1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 10:51:15 by grinko            #+#    #+#             */
/*   Updated: 2021/02/13 20:18:40 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	kakoetogovno1(t_map *map, int i, int tmp)
{
	if (i == 0)
		map->stairstr = add_text("w ", ft_itoa(map->remove->x[i]), 3);
	else
	{
		map->stairstr = add_text(map->stairstr, "w ", 1);
		map->stairstr = add_text(map->stairstr, ft_itoa(map->remove->x[i]), 2);
	}
	kakoetogovno2(map, i, tmp);
	map->stairstr = add_text(map->stairstr, " ", 1);
	map->stairstr = add_text(map->stairstr, "1", 1);
	map->stairstr = add_text(map->stairstr, " ", 1);
	map->stairstr = add_text(map->stairstr, ft_itoa(map->stirsgroup), 2);
	map->stairstr = add_text(map->stairstr, "\n", 1);
}

void	savestairs(t_map *map)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = 1;
	savestairs2(map);
	while (i < map->stclick * 8)
	{
		kakoetogovno1(map, i, tmp);
		i += 2;
		if (i % 8 == 0)
			tmp++;
		if (i % 8 == 0)
			map->stirsgroup++;
	}
}

void	stairs_editor(t_map *map, int x, int y)
{
	if (map->click == 0 && interface_click(map, x, y))
	{
		map->click = 1;
		map->x_c = x;
		map->y_c = y;
	}
	else if (map->click == 1 && interface_click(map, x, y))
	{
		map->click = 0;
		savestairs(map);
		if (!map->stairsoutput)
		{
			map->stairsoutput = ft_strdup(map->stairstr);
			free(map->stairstr);
			map->stairstr = NULL;
		}
		else
			map->stairsoutput = add_text(map->stairsoutput, map->stairstr, 2);
		map->stairstr = 0;
	}
}

void	draw_prikol(t_map *map, t_info *cord)
{
	draw_floor_line(map, &(t_info){(cord->x - map->ha->nx),
		(cord->y - map->ha->ny), (cord->x + map->ha->nx),
		(cord->y + map->ha->ny)});
	draw_floor_line(map, &(t_info){cord->x - map->ha->nx,
		(cord->y - map->ha->ny), (cord->w - map->ha->nx),
		(cord->h - map->ha->ny)});
	draw_floor_line(map, &(t_info){(cord->x + map->ha->nx),
		(cord->y + map->ha->ny), (cord->w + map->ha->nx),
		(cord->h + map->ha->ny)});
	draw_floor_line(map, &(t_info){(cord->w - map->ha->nx),
		(cord->h - map->ha->ny), (cord->w + map->ha->nx),
		(cord->h + map->ha->ny)});
}

void	draw_mapstairs(t_map *map, int x, int y, int i)
{
	int		x1;
	int		y1;
	float	len;

	x1 = map->x_c;
	y1 = map->y_c;
	map->ha->nx = (y1 - y);
	map->ha->ny = (x - x1);
	map->ha->nx /= sqrt(map->ha->nx * map->ha->nx + map->ha->ny * map->ha->ny);
	map->ha->ny /= sqrt(map->ha->nx * map->ha->nx + map->ha->ny * map->ha->ny);
	map->ha->nx *= 15 * 0.7;
	map->ha->ny *= 15 * 0.7;
	len = sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
	x = x1 + (x - x1) * 20 * i / len;
	y = y1 + (y - y1) * 20 * i / len;
	draw_prikol(map, &(t_info){x1, y1, x, y});
	if (i == 1)
		stairarr1(map, &(t_info){x1, y1, x, y}, i);
	else
	{
		i = (i - 1) * 8;
		stairarr1(map, &(t_info){map->remove->x[i - 1],
			map->remove->y[i - 1], x, y}, i);
	}
}
