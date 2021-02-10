/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 13:39:11 by grinko            #+#    #+#             */
/*   Updated: 2021/02/10 16:08:47 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	edit_object(t_map *map, t_image **name, int n, int index)
{
	int i;

	i = -1;
	if (map->inter_tex[5]->active == 1)
		zerroothero(map);
	while (++i < n)
	{
		if (i == index)
			name[i]->active = 1;
		else
			name[i]->active = 0;
	}
}

void	objects_click2(t_map *map, int x, int y)
{
	if ((x > 130 && x < 160) && (y > 280 && y < 300))
		edit_object(map, map->gun_tex, 6, 3);
	if ((x > 230 && x < 260) && (y > 280 && y < 300))
		edit_object(map, map->gun_tex, 6, 5);
	if ((x > 30 && x < 70) && (y > 350 && y < 390))
		edit_object(map, map->enemy_tex, 5, 0);
	if ((x > 130 && x < 170) && (y > 350 && y < 390))
		edit_object(map, map->enemy_tex, 5, 1);
	if ((x > 230 && x < 280) && (y > 350 && y < 390))
		edit_object(map, map->enemy_tex, 5, 2);
	if ((x > 60 && x < 100) && (y > 430 && y < 470))
		edit_object(map, map->enemy_tex, 5, 3);
	if ((x > 160 && x < 200) && (y > 430 && y < 470))
		edit_object(map, map->enemy_tex, 5, 4);
	if ((x > 115 && x < 155) && (y > 500 && y < 540))
		edit_object(map, map->door_tex, 11, 10);
	if ((x > 115 && x < 155) && (y > 600 && y < 640))
		edit_object(map, map->door_tex, 11, 8);
	if ((x > 130 && x < 150) && (y > 700 && y < 740))
		edit_object(map, map->door_tex, 11, 9);
}

void	objects_click(t_map *map, int x, int y)
{
	if ((x > 30 && x < 70) && (y > 130 && y < 170))
		edit_object(map, map->player_tex, 3, 0);
	if ((x > 130 && x < 170) && (y > 150 && y < 170))
		edit_object(map, map->player_tex, 3, 1);
	if ((x > 230 && x < 270) && (y > 150 && y < 170))
		edit_object(map, map->player_tex, 3, 2);
	if ((x > 30 && x < 80) && (y > 250 && y < 270))
		edit_object(map, map->gun_tex, 6, 0);
	if ((x > 130 && x < 180) && (y > 250 && y < 270))
		edit_object(map, map->gun_tex, 6, 2);
	if ((x > 230 && x < 280) && (y > 250 && y < 270))
		edit_object(map, map->gun_tex, 6, 4);
	if ((x > 30 && x < 50) && (y > 280 && y < 300))
		edit_object(map, map->gun_tex, 6, 1);
	objects_click2(map, x, y);
}

void	set_door(t_map *map, int indx)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (i == indx)
		{
			map->door_tex[i]->active = 1;
			return ;
		}
		map->door_tex[i]->active = 0;
		i++;
	}
}

void	get_door(t_map *map, int x, int y)
{
	if ((x > WIDTH / 2 - 140 && x < WIDTH / 2 - 100) && (y > 10 && y < 50))
		set_door(map, 0);
	if ((x > WIDTH / 2 - 60 && x < WIDTH / 2 - 20) && (y > 10 && y < 50))
		set_door(map, 1);
	if ((x > WIDTH / 2 + 20 && x < WIDTH / 2 + 60) && (y > 10 && y < 50))
		set_door(map, 2);
	if ((x > WIDTH / 2 + 90 && x < WIDTH / 2 + 130) && (y > 10 && y < 50))
		set_door(map, 3);
	if ((x > WIDTH / 2 - 130 && x < WIDTH / 2 - 110) && (y > 60 && y < 80))
	{
		map->door_tex[0]->active = 0;
		map->door_tex[4]->active = 1;
	}
	if ((x > WIDTH / 2 + 80 && x < WIDTH / 2 + 145) && (y > 100 && y < 130))
		map->validflag = 9;
	if ((x > WIDTH / 2 - 145 && x < WIDTH / 2 - 80) && (y > 100 && y < 130))
		zerroothero(map);
}

int		searchelem(char *str1, char *str2)
{
	char *istr;

	istr = ft_strstr(str1, str2);
	if (istr == NULL)
		return (0);
	else
		return (istr - str1 + 1);
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
		else if (map->door_tex[9]->active == 1)
			str = ft_strjoin("x ", ft_itoa(x));
		str = ft_strjoin(ft_strjoin(str, " "), ft_itoa(y));
		rewrite2(map, str, tmp, inx);
	}
	// if (tmp)
	// 	free(tmp);
}
