/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stairs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 10:51:15 by grinko            #+#    #+#             */
/*   Updated: 2021/02/11 15:26:14 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	stairswhile(t_map *map, int x, int y)
{
	int i;

	i = 1;
	while (i <= map->stclick)
	{
		draw_mapstairs(map, x , y , i);
		i++;
	}
}

char	*add_text(char *s1, char *s2, int f)
{
	char *str;

	if (!s1 || !s2)
		return (NULL);
	str = ft_strjoin(s1, s2);
	if (f == 1)
		free(s1);
	else if (f == 2)
	{
		free(s1);
		free(s2);
	}
	else if (f == 3)
		free(s2);
	return (str);
}

void savestairs(t_map *map)
{
	int i;
	int tmp;

	i = 0;
	tmp = 1;
	add_my_node(map, &(t_info){map->remove->x[0] , map->remove->y[0] , map->remove->x[1] , map->remove->y[1] }, 1);
	add_my_node(map, &(t_info){map->remove->x[0] , map->remove->y[0] , map->remove->x[map->stclick * 8 - 2] , map->remove->y[map->stclick * 8 - 2] }, 1);
	add_my_node(map, &(t_info){map->remove->x[1] , map->remove->y[1] , map->remove->x[map->stclick * 8 - 1] , map->remove->y[map->stclick * 8 - 1] }, 1);
	add_my_node(map, &(t_info){map->remove->x[map->stclick * 8 - 2] , map->remove->y[map->stclick * 8 - 2] , map->remove->x[map->stclick * 8 - 1] , map->remove->y[map->stclick * 8 - 1] }, 1);

	while (i < map->stclick * 8)
	{
		if (i == 0)
			map->stairstr = add_text("w ", ft_itoa(map->remove->x[i]), 3);
		else
		{
			map->stairstr = add_text(map->stairstr, "w ", 1);
			map->stairstr = add_text(map->stairstr, ft_itoa(map->remove->x[i]), 2);
		}
		map->stairstr = add_text(map->stairstr, " ", 1);
		map->stairstr = add_text(map->stairstr, ft_itoa(map->remove->y[i]), 2);
		map->stairstr = add_text(map->stairstr, " ", 1);
		map->stairstr = add_text(map->stairstr, ft_itoa(map->remove->x[i + 1]), 2);
		map->stairstr = add_text(map->stairstr, " ", 1);
		map->stairstr = add_text(map->stairstr, ft_itoa(map->remove->y[i + 1]), 2);
		map->stairstr = add_text(map->stairstr, " ", 1);
		map->stairstr = add_text(map->stairstr, "../textures/wall/wall1.png ", 1);
		map->stairstr = add_text(map->stairstr, ft_itoa(tmp), 2);
		map->stairstr = add_text(map->stairstr, " ", 1);
		map->stairstr = add_text(map->stairstr, "1", 1);
		map->stairstr = add_text(map->stairstr, " ", 1);
		map->stairstr = add_text(map->stairstr, ft_itoa(map->stirsgroup), 2);
		map->stairstr = add_text(map->stairstr, "\n", 1);
		i += 2;
		if (i % 8 == 0)
			tmp++;
		if (i % 8 == 0)
			map->stirsgroup++;
	}
}

void	stairs_editor(t_map *map, int x, int y)
{
	// if (map->stairsoutput)
	// 	free(map->stairsoutput);
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
			map->stairsoutput = ft_strdup(map->stairstr);
		else
			map->stairsoutput = add_text(map->stairsoutput, map->stairstr, 0);
		free(map->stairstr);
		map->stairstr = 0;
	}
}


void	stairarr(t_map *map, t_info *cor, int i, float nx, float ny)
{
	if (i == 1)
	{
		map->remove->x[i-1] = cor->x - nx;
		map->remove->y[i-1] = cor->y - ny;
		map->remove->x[i] = cor->x + nx;
		map->remove->y[i] = cor->y + ny;

		map->remove->x[i+1] = cor->x - nx;
		map->remove->y[i+1] = cor->y - ny;
		map->remove->x[i+2] = cor->w - nx;
		map->remove->y[i+2] = cor->h - ny;

		map->remove->x[i+3] = cor->x + nx;
		map->remove->y[i+3] = cor->y + ny;
		map->remove->x[i+4] = cor->w + nx;
		map->remove->y[i+4] = cor->h + ny;

		map->remove->x[i+5] = cor->w - nx;
		map->remove->y[i+5] = cor->h - ny;
		map->remove->x[i+6] = cor->w + nx;
		map->remove->y[i+6] = cor->h + ny;
	}
	else
	{
		map->remove->x[i] = map->remove->x[i-2];
		map->remove->y[i] = map->remove->y[i-2];
		map->remove->x[i + 1] = map->remove->x[i-1];
		map->remove->y[i + 1] = map->remove->y[i-1];
		map->remove->x[i+2] = map->remove->x[i-2];
		map->remove->y[i+2] = map->remove->y[i-2];
		map->remove->x[i+3] = cor->w - nx;
		map->remove->y[i+3] = cor->h - ny;
		map->remove->x[i+4] = map->remove->x[i-1];
		map->remove->y[i+4] = map->remove->y[i-1];
		map->remove->x[i+5] = cor->w + nx;
		map->remove->y[i+5] = cor->h + ny;
		map->remove->x[i+6] = cor->w - nx;
		map->remove->y[i+6] = cor->h - ny;
		map->remove->x[i+7] = cor->w + nx;
		map->remove->y[i+7] = cor->h + ny;
	}
}

void	draw_mapstairs(t_map *map, int x, int y, int i)
{
	int x1;
	int y1;
	float nx;
	float ny;
	float tmp;
	int width = 15;
	float len;

	x1 = map->x_c ;
	y1 = map->y_c ;
	
	nx = (y1 - y);
	ny = (x - x1);
	nx /= sqrt(nx*nx + ny*ny);
	ny /= sqrt(nx*nx + ny*ny);
	nx *= width * 0.7;
	ny *= width * 0.7;
	len = sqrt((x - x1)* (x - x1) + (y - y1) * (y - y1));
	x = x1 + (x - x1) * 20 * i / len;
	y = y1 + (y - y1) * 20  * i / len;
	draw_floor_line(map, &(t_info){(x1 - nx), (y1 - ny) , (x1 + nx), (y1 + ny)});
	draw_floor_line(map, &(t_info){x1 - nx, (y1 - ny) , (x - nx) , (y - ny) });
	draw_floor_line(map, &(t_info){(x1 + nx) , (y1 + ny) , (x + nx) , (y + ny) });
	draw_floor_line(map, &(t_info){(x - nx) , (y - ny) , (x + nx) , (y + ny) });
	if (i == 1)
		stairarr(map, &(t_info){x1, y1, x, y}, i, nx, ny);
	else
	{
		i = (i-1) * 8;
		stairarr(map, &(t_info){map->remove->x[i - 1], map->remove->y[i - 1], x, y}, i, nx, ny);
	}
}
