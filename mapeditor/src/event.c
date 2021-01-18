/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:00 by grinko            #+#    #+#             */
/*   Updated: 2021/01/18 17:57:27 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"
// Вангую что искомая точка лежит на отрезке (х1, у1, х2, у2).
// В этом случае длина исходного отрезка LL=sqrt((x2-x1)^2+(y2-y1)^2)
// И координаты искомой точки
// x=x1+(x2-x1)*L/LL
// y=y1+(y2-y1)*L/LL

void	draw_mapstairs(t_map *map, int x, int y)
{
	int x1;
	int y1;
	float nx;
	float ny;
	float tmp;
	int width = 15;
	float len;
	// int t_x = x;
	// int t_y = y;

	x1 = map->x_c - map->z_x;
	y1 = map->y_c - map->z_y;
	
	nx = (y1 - y);
	ny = (x - x1);
	nx /= sqrt(nx*nx + ny*ny);
	ny /= sqrt(nx*nx + ny*ny);
	nx *= width;
	ny *= width;
	len = sqrt((x - x1)* (x - x1) + (y - y1) * (y - y1));
	x = x1 + (x - x1) * 20 * map->stclick / len;
	y = y1 + (y - y1) * 20 * map->stclick / len;
	draw_floor_line(map, &(t_info){x1 - nx, (y1 - ny) , (x - nx) , (y - ny) });
	draw_floor_line(map, &(t_info){(x1 + nx) , (y1 + ny) , (x + nx) , (y + ny) });
	draw_floor_line(map, &(t_info){(x1 - nx), (y1 - ny) , (x1 + nx), (y1 + ny)});
	draw_floor_line(map, &(t_info){(x - nx) , (y - ny) , (x + nx) , (y + ny) });
	
	// if (map->floor_x < 5)
	// {
	// 	// printf("h\n");
	// 	float x_tmp;
	// 	float y_tmp;

	// 	x_tmp = x - x1;
	// 	y_tmp = y - y1;
	// 	x_tmp /= sqrt(x_tmp*x_tmp + y_tmp*y_tmp);
	// 	y_tmp /= sqrt(x_tmp*x_tmp + y_tmp*y_tmp);
	// 	x1 = map->x_c - map->z_x + x_tmp * 20;
	// 	y1 = map->y_c - map->z_y + y_tmp * 20;
	// 	// map->x_c = map->x_c + x_tmp * 20;
	// 	// map->y_c = map->y_c + y_tmp * 20;
	// 	map->x_c = x;
	// 	map->y_c = y;
	// 	map->floor_x++;
	// 	draw_mapstairs(map, t_x, t_y);
	// }
	// float x_tmp;
	// float y_tmp;

	// x_tmp = x - x1;
	// y_tmp = y - y1;

	// x_tmp /= sqrt(x_tmp*x_tmp + y_tmp*y_tmp);
	// y_tmp /= sqrt(x_tmp*x_tmp + y_tmp*y_tmp);
	// x1 = map->x_c - map->z_x + x_tmp * 20;
	// y1 = map->y_c - map->z_y + y_tmp * 20;
	// printf("%f %f\n",x_tmp, y_tmp);

	// // nx = (y1 - y);
	// // ny = (x - x1);
	// // nx /= sqrt(nx*nx + ny*ny);
	// // ny /= sqrt(nx*nx + ny*ny);
	// // nx *= width;
	// // ny *= width;
	// len = sqrt((x - x1)* (x - x1) + (y - y1) * (y - y1));
	// 	printf("%f\n",len);
	// x = x1 + (x - x1) * 20 / len;
	// y = y1 + (y - y1) * 20 / len;
	// draw_floor_line(map, &(t_info){x1 - nx, (y1 - ny) , (x - nx) , (y - ny) });
	// draw_floor_line(map, &(t_info){(x1 + nx) , (y1 + ny) , (x + nx) , (y + ny) });
	// draw_floor_line(map, &(t_info){(x1 - nx), (y1 - ny) , (x1 + nx), (y1 + ny)});
	// draw_floor_line(map, &(t_info){(x - nx) , (y - ny) , (x + nx) , (y + ny) });

}


// void	draw_mapstairs(t_map *map, int x, int y)
// {
// 	//printf("line\n");
// 	int x1;
// 	int y1;
// 	int nx;
// 	int ny;
// 	int width = 20;

// 	x1 = map->x_c - map->z_x;
// 	y1 = map->y_c - map->z_y;
// 	nx = (y1 - y);
// 	ny = (x - x1);
// 	// printf("nx : %d\n", nx);
// 	// printf("ny : %d\n", ny);
// 	draw_floor_line(map, &(t_info){x1 - nx, (y1 - ny) , (x - nx) , (y - ny) });
// 	draw_floor_line(map, &(t_info){(x1 + nx) , (y1 + ny) , (x + nx) , (y + ny) });
// 	draw_floor_line(map, &(t_info){(x1 - nx), (y1 - ny) , (x1 + nx), (y1 + ny)});
// 	draw_floor_line(map, &(t_info){(x - nx) , (y - ny) , (x + nx) , (y + ny) });
	
// }

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
		draw_mapstairs(map, x - map->z_x, y - map->z_y);
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
