/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stairs2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 10:51:15 by grinko            #+#    #+#             */
/*   Updated: 2021/02/13 18:10:25 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	stairswhile(t_map *map, int x, int y)
{
	int i;

	i = 1;
	while (i <= map->stclick)
	{
		draw_mapstairs(map, x, y, i);
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

void	kakoetogovno2(t_map *map, int i, int tmp)
{
	map->stairstr = add_text(map->stairstr, " ", 1);
	map->stairstr = add_text(map->stairstr, ft_itoa(map->remove->y[i]), 2);
	map->stairstr = add_text(map->stairstr, " ", 1);
	map->stairstr = add_text(map->stairstr, ft_itoa(map->remove->x[i + 1]), 2);
	map->stairstr = add_text(map->stairstr, " ", 1);
	map->stairstr = add_text(map->stairstr, ft_itoa(map->remove->y[i + 1]), 2);
	map->stairstr = add_text(map->stairstr, " ", 1);
	map->stairstr = add_text(map->stairstr, "../textures/wall/wall1.png ", 1);
	map->stairstr = add_text(map->stairstr, ft_itoa(tmp), 2);
}

void	savestairs2(t_map *map)
{
	add_my_node(map, &(t_info){map->remove->x[0], map->remove->y[0],
		map->remove->x[1], map->remove->y[1] }, 1);
	add_my_node(map, &(t_info){map->remove->x[0], map->remove->y[0],
		map->remove->x[map->stclick * 8 - 2],
		map->remove->y[map->stclick * 8 - 2]}, 1);
	add_my_node(map, &(t_info){map->remove->x[1], map->remove->y[1],
		map->remove->x[map->stclick * 8 - 1],
		map->remove->y[map->stclick * 8 - 1]}, 1);
	add_my_node(map, &(t_info){map->remove->x[map->stclick * 8 - 2],
		map->remove->y[map->stclick * 8 - 2],
		map->remove->x[map->stclick * 8 - 1],
		map->remove->y[map->stclick * 8 - 1]}, 1);
}

void	stairarr2(t_map *map, t_info *cor, int i)
{
	map->remove->x[i] = map->remove->x[i - 2];
	map->remove->y[i] = map->remove->y[i - 2];
	map->remove->x[i + 1] = map->remove->x[i - 1];
	map->remove->y[i + 1] = map->remove->y[i - 1];
	map->remove->x[i + 2] = map->remove->x[i - 2];
	map->remove->y[i + 2] = map->remove->y[i - 2];
	map->remove->x[i + 3] = cor->w - map->ha->nx;
	map->remove->y[i + 3] = cor->h - map->ha->ny;
	map->remove->x[i + 4] = map->remove->x[i - 1];
	map->remove->y[i + 4] = map->remove->y[i - 1];
	map->remove->x[i + 5] = cor->w + map->ha->nx;
	map->remove->y[i + 5] = cor->h + map->ha->ny;
	map->remove->x[i + 6] = cor->w - map->ha->nx;
	map->remove->y[i + 6] = cor->h - map->ha->ny;
	map->remove->x[i + 7] = cor->w + map->ha->nx;
	map->remove->y[i + 7] = cor->h + map->ha->ny;
}
