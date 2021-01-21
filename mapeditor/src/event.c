/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:00 by grinko            #+#    #+#             */
/*   Updated: 2021/01/21 13:54:13 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

int		mmove(int x, int y, t_map *map, SDL_Event event)
{
	int x1;
	int y1;

	x1 = x;
	y1 = y;
	find_coord(map, &x1, &y1);
	draw(map);
	if (some_texture_active(map) == 2)
	{
		if (x1 != x || y1 != y)
			bigdot(map, x1, y1, HOTPINK);
		//draw_floor_line(map, &(t_info){map->floor_x, map->floor_y, x - map->z_x, y - map->z_y});
	}
	map->floor_x = 0;
	if (map->block_tex[5]->active == 1)
	{
		ft_izero(map->remove->x, map->stclick * 8);
		ft_izero(map->remove->y, map->stclick * 8);
		int i = 1;
		while (i <= map->stclick)
		{
			// t_removeinfo *xyarray;
			
			draw_mapstairs(map, x - map->z_x, y - map->z_y, i);
			// printf("X%d: |%d|\n", i, map->remove->x[i]);
			// printf("Y%d: |%d|\n", i, map->remove->y[i]);
			i++;
		}

	}
	// if (some_texture_active(map) == 4) ////////////////////////////////////
	// {
		// drawillwall(map, x, y);
	// }
	if (map->inter_tex[6]->active && interface_click(map, x, y))
	{
		if (x1 != x || y1 != y)
			bigdot(map, x1, y1, HOTPINK);
		cursor(map, "/textures/interface/editpic.png", 0, 16);
	}
	else if (map->inter_tex[8]->active)
		(x1 != x || y1 != y) ? cursor(map, "/textures/interface/deletic.png",
			8, 8) : SDL_FreeCursor(map->cursor);
	else
		SDL_FreeCursor(map->cursor);
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
			return 0;
		if (event.type == SDL_KEYDOWN)
			pkey((unsigned char)event.key.keysym.sym, map);
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			wichonemusic(map);
			SDL_GetMouseState(&x, &y);
			mkey(event.button.button, x, y, map);
			if (catch_click(map, x, y))
				done = 1;
			draw(map);
		}
		if (event.type == SDL_MOUSEMOTION)
		{
			mmove(event.motion.x, event.motion.y, map, event);
			SDL_UpdateWindowSurface(map->win);
		}
		if (done == 1)
			if (valid_map(map))
			{
				writedown_map(map);
				return (1);
			}
	}
	return (0);
}
