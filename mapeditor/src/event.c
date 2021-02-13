/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:00 by grinko            #+#    #+#             */
/*   Updated: 2021/02/13 20:28:17 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

int		mmove(int x, int y, t_map *map)
{
	map->z_x = x;
	map->z_y = y;
	find_coord(map, &map->z_x, &map->z_y);
	draw(map);
	if (some_texture_active(map) == 2)
		if (map->z_x != x || map->z_y != y)
			bigdot(map, map->z_x, map->z_y, HOTPINK);
	if (map->block_tex[5]->active == 1 && interface_click(map, x, y))
		stairswhile(map, x, y);
	if (map->inter_tex[6]->active && interface_click(map, x, y))
	{
		if (map->z_x != x || map->z_y != y)
			bigdot(map, map->z_x, map->z_y, HOTPINK);
	}
	return (0);
}

int		clickevent(t_map *map, int x, int y, SDL_Event event)
{
	if (map->musicflag > 0)
	{
		wichonemusic(map);
		map->musicoutput = map->musicflag;
		map->musicflag = 0;
	}
	SDL_GetMouseState(&x, &y);
	mkey(event.button.button, x, y, map);
	if (catch_click(map, x, y))
		return (1);
	draw(map);
	return (0);
}

int		events(t_map *map)
{
	int			x;
	int			y;
	SDL_Event	event;
	int			done;

	x = 0;
	y = 0;
	done = 0;
	while (!done)
	{
		if (SDL_PollEvent(&event) && !done)
		{
			if (event.type == SDL_QUIT)
				exit (0);
			if (event.type == SDL_KEYDOWN)
				pkey((unsigned char)event.key.keysym.sym, map);
			if (event.type == SDL_MOUSEMOTION)
				mmove(event.motion.x, event.motion.y, map);
			if (event.type == SDL_MOUSEBUTTONDOWN && clickevent(map, x, y, event))
				done = valid_map(map, &(t_info){-WIDTH, -HEIGHT, WIDTH, HEIGHT});
			if (done == 1)
			{
				writedown_map(map);
				free_panel1(map);
				return (0);
			}
		}
	}
	return (0);
}
