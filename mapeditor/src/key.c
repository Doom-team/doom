/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gordey <gordey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:16 by grinko            #+#    #+#             */
/*   Updated: 2021/01/02 15:04:35 by gordey           ###   ########.fr       */
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
		if (map->inter_tex[4]->active)
			change_texture(map, x, y);
		if (some_texture_active(map) == 4)
			change_texture(map, x, y);
		if (map->block_tex[5]->active == 1)
			stairs_editor(map, x, y);
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
