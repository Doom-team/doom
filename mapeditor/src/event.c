/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:00 by grinko            #+#    #+#             */
/*   Updated: 2021/02/12 00:32:23 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

int		mmove(int x, int y, t_map *map, SDL_Event event)
{
	map->z_x = x;
	map->z_y = y;
	find_coord(map, &map->z_x, &map->z_y);
	draw(map);
	if (some_texture_active(map) == 2)
		if (map->z_x != x || map->z_y != y)
			bigdot(map, map->z_x, map->z_y, HOTPINK);
	map->floor_x = 0;
	if (map->block_tex[5]->active == 1)
		stairswhile(map, x, y);
	if (map->inter_tex[6]->active && interface_click(map, x, y))
	{
		if (map->z_x != x || map->z_y != y)
			bigdot(map, map->z_x, map->z_y, HOTPINK);
		cursor(map, 0, 0, 16);
	}
	else if (map->inter_tex[8]->active)
		(map->z_x != x || map->z_y != y) ? cursor(map, 1,
			8, 8) : SDL_FreeCursor(map->cursor);
	else
		SDL_FreeCursor(map->cursor);
	SDL_UpdateWindowSurface(map->win);
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
	while ((!done) && SDL_WaitEvent(&event))
	{
		if (event.type == SDL_QUIT)
			return (0);
		if (event.type == SDL_KEYDOWN)
			pkey((unsigned char)event.key.keysym.sym, map);
		if (event.type == SDL_MOUSEBUTTONDOWN)
			done = clickevent(map, x, y, event);
		if (event.type == SDL_MOUSEMOTION)
			mmove(event.motion.x, event.motion.y, map, event);
		if (done == 1)
			if (valid_map(map))
				return (writedown_map(map));
	}
	return (0);
}
