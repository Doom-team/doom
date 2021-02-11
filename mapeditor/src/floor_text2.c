/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_text2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:03 by grinko            #+#    #+#             */
/*   Updated: 2021/02/12 00:34:37 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

char	*mapstrcpy(char *dst, const char *str)
{
	size_t	i;

	i = 0;
	if (!(dst = malloc(sizeof(char *) * ft_strlen(str))))
		return (NULL);
	while (str[i])
	{
		dst[i] = str[i];
		i++;
	}
	return (dst);
}

void	strfloor(t_map *map)
{
	map->floorstr = add_text("f", " ../textures/floor/floor", 0);
	map->floorstr = add_text(map->floorstr, ft_itoa(map->index_tex), 2);
	map->floorstr = add_text(map->floorstr, ".png", 1);
	map->floorstr = add_text(map->floorstr, "\n", 1);
}

void	strceiling(t_map *map)
{
	map->ceilingstr = add_text("c", " ../textures/floor/floor", 0);
	map->ceilingstr = add_text(map->ceilingstr, ft_itoa(map->index_tex), 2);
	map->ceilingstr = add_text(map->ceilingstr, ".png", 1);
	map->ceilingstr = add_text(map->ceilingstr, "\n", 1);
}

void	open_floor_win(t_map *map)
{
	int tmp;

	tmp = 0;
	if (some_texture_active(map) == 2)
		map->validflag = change_floor_inter(map);
	if (map->inter_tex[16]->active == 4)
	{
		if (map->validflag == 4)
		{
			strfloor(map);
			map->temporary = NULL;
		}
		if (map->validflag == 5)
		{
			strceiling(map);
			map->temporary = NULL;
		}
		map->inter_tex[16]->active = 0;
	}
}
