/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:16 by grinko            #+#    #+#             */
/*   Updated: 2020/12/24 20:25:15 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

int		mkey(int key, int x, int y, t_map *map)
{
	if (key == 1)
	{
		if (map->inter_tex[6]->active)
			wall_editor(map, x, y);
		if (map->inter_tex[8]->active)
			remove_tool(map, x, y);
		if (map->inter_tex[4])
			change_texture(map, x, y);
		if (map->door_tex[0]->active == 1 || map->door_tex[1]->active == 1 || map->door_tex[2]->active == 1 || map->door_tex[3]->active == 1)
			change_texture(map, x, y);
	}
	SDL_UpdateWindowSurface(map->win);
	return (0);
}

int		pkey(int key, t_map *map)
{
	if (key == 27)
		SDL_Quit();

	return (0);
}