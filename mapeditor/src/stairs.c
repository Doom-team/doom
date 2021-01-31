/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stairs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 10:51:15 by grinko            #+#    #+#             */
/*   Updated: 2021/01/31 19:03:19 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

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
			map->stairstr = ft_strjoin("w ", ft_itoa(map->remove->x[i]));
		else
		{
			map->stairstr = ft_strjoin(map->stairstr, "w ");
			map->stairstr = ft_strjoin(map->stairstr, ft_itoa(map->remove->x[i]));
		}
		map->stairstr = ft_strjoin(map->stairstr, " ");
		map->stairstr = ft_strjoin(map->stairstr, ft_itoa(map->remove->y[i]));
		map->stairstr = ft_strjoin(map->stairstr, " ");
		map->stairstr = ft_strjoin(map->stairstr, ft_itoa(map->remove->x[i + 1]));
		map->stairstr = ft_strjoin(map->stairstr, " ");
		map->stairstr = ft_strjoin(map->stairstr, ft_itoa(map->remove->y[i + 1]));
		map->stairstr = ft_strjoin(map->stairstr, " ");
		map->stairstr = ft_strjoin(map->stairstr, "\"textures/wall/wall0.png\" ");
		map->stairstr = ft_strjoin(map->stairstr, ft_itoa(tmp));
		map->stairstr = ft_strjoin(map->stairstr, " ");
		map->stairstr = ft_strjoin(map->stairstr, "1");
		map->stairstr = ft_strjoin(map->stairstr, " ");
		map->stairstr = ft_strjoin(map->stairstr, ft_itoa(map->stirsgroup));
		map->stairstr = ft_strjoin(map->stairstr, "\n");
		i += 2;
		if (i % 8 == 0)
			tmp++;
		if (i % 8 == 0)
			map->stirsgroup++;
	}
	//printf("%s\n", map->stairstr);
	//printf("----------------------------------------------------------------\n");
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
			map->stairsoutput = ft_strdup(map->stairstr);
		else
			map->stairsoutput = ft_strjoin(map->stairsoutput, map->stairstr);
		free(map->stairstr);
	}
	printf("%s\n", map->stairsoutput);
		printf("----------------------------------------------------------------\n");

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
