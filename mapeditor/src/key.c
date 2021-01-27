/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:16 by grinko            #+#    #+#             */
/*   Updated: 2021/01/27 13:00:18 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

int		mkey(int key, int x, int y, t_map *map)
{
	printf("click1: %d\n", map->click);
	if (key == 1)
	{
		if (map->block_tex[5]->active == 1)
		{
			printf("z5\n");
			stairs_editor(map, x, y);
		}
		if (map->inter_tex[6]->active)
		{
			printf("z1\n");
			wall_editor(map, x, y);
		}
		printf("click2: %d\n", map->click);
		if (map->inter_tex[8]->active)
		{
			printf("z2\n");
			remove_tool(map, x, y);
		}
		printf("click3: %d\n", map->click);
		if (map->inter_tex[4]->active)
		{
			printf("z3\n");
			change_texture(map, x, y);
		}
		printf("click4: %d\n", map->click);
		if (some_texture_active(map) == 4)
		{
			printf("z4\n");
			change_texture(map, x, y);
		}
		printf("click5: %d\n", map->click);

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
