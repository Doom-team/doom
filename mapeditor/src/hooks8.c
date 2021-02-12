/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 13:39:11 by grinko            #+#    #+#             */
/*   Updated: 2021/02/12 10:15:05 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

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

void	skytx_click(t_map *map, int x, int y)
{
	int i;
	int x_c;
	int y_c;

	i = 8;
	x_c = 20;
	y_c = 520;
	while (++i < 13)
	{
		if ((x > x_c && x < x_c + 50) && (y > y_c && y < y_c + 50))
			edit_floortexture(map, i);
		x_c += 60;
		if (i == 4)
		{
			x_c = 20;
			y_c = 400;
		}
	}
}

int		searchelem(char *str1, char *str2)
{
	char *istr;

	istr = ft_strstr(str1, str2);
	if (istr == NULL)
		return (0);
	else
		return (istr - str1);
}

void	rewrite2(t_map *map, char *str, char *tmp, int inx)
{
	str = add_text(str, "\n", 1);
	if (tmp)
	{
		tmp = add_text(tmp, str, 1);
		map->objects = add_text(tmp, &map->objects[inx], 1);
	}
	else
		map->objects = add_text(str, &map->objects[inx], 1);
}

void	rewrite(t_map *map, int inx, int x, int y)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	tmp = malloc(sizeof(char *));
	if (map->player_tex[0]->active == 1 || map->door_tex[9]->active == 1)
	{
		if (map->objects)
		{
			tmp = ft_strncpy(tmp, map->objects, inx);
			tmp[inx] = '\0';
		}
		while (map->objects[inx] && map->objects[inx] != '\n')
			inx++;
		inx++;
		if (map->player_tex[0]->active == 1)
			str = ft_strjoin("p ", ft_itoa(x));
		str = ft_strjoin(ft_strjoin(str, " "), ft_itoa(y));
		rewrite2(map, str, tmp, inx);
	}
}
