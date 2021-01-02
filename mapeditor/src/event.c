/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gordey <gordey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:00 by grinko            #+#    #+#             */
/*   Updated: 2021/01/02 15:44:46 by gordey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	draw_mapstairs(t_map *map, int x, int y)
{
	//printf("line\n");
	draw_floor_line(map, &(t_info){map->x_c - map->z_x, map->y_c - map->z_y - 20, x - map->z_x, y - map->z_y -20,});
	draw_floor_line(map, &(t_info){map->x_c - map->z_x, map->y_c - map->z_y + 20, x - map->z_x, y - map->z_y + 20,});
}

int		mmove(int x, int y, t_map *map, SDL_Event event)
{
	int x1 = x;
	int y1 = y;
	find_coord(map, &x1, &y1);
	draw(map);
	if (some_texture_active(map) == 2)
	{
		if (x1 != x || y1 != y)
			bigdot(map, x1, y1, HOTPINK);
		//draw_floor_line(map, &(t_info){map->floor_x, map->floor_y, x - map->z_x, y - map->z_y});
		
	}
	if (map->block_tex[5]->active == 1)
	{
		draw_mapstairs(map, x, y);
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
		(x1 != x || y1 != y) ? cursor(map, "/textures/interface/deletic.png", 8, 8) : SDL_FreeCursor(map->cursor);
	else
		SDL_FreeCursor(map->cursor);
	return (0);
}


int	events(t_map *map)
{
	int x = 0;
	int y = 0;
	SDL_Event event;
	int done = 0;

	while ((!done) && SDL_WaitEvent(&event))
	{
		if (event.type == SDL_QUIT)
			done = 1;
		if (event.type == SDL_KEYDOWN)
			pkey((unsigned char)event.key.keysym.sym, map);
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			wichonemusic(map);
			SDL_GetMouseState(&x, &y);
			mkey(event.button.button, x, y, map);
			if (catch_click(map, x, y))
				return (1);
			draw(map);
		}
		if (event.type == SDL_MOUSEMOTION)
		{
			mmove(event.motion.x, event.motion.y, map, event);
			SDL_UpdateWindowSurface(map->win);
		}
	}
	return (0);
}