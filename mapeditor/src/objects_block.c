/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_block.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:48:27 by grinko            #+#    #+#             */
/*   Updated: 2020/12/26 13:24:18 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void set_object(t_map *map, int x, int y)
{
	if (map->player_tex[0])
		return ;
}

void draw_door_win(t_map *map)
{
	draw_img(map, &(t_info){WIDTH/2 - 165, 5, 330, 160}, map->inter_tex[16]);
	// if (map->door_tex[0]->active == 1)
	// 	draw_img(map, &(t_info){WIDTH/2 - 140, 20, 40, 40}, map->inter_tex[15]);
	draw_img(map, &(t_info){WIDTH/2 - 140, 10, 40, 40}, map->door_tex[0]);
	// // if (map->door_tex[4]->active == 1)
	// 	draw_img(map, &(t_info){WIDTH/2 - 130, 70, 20, 20}, map->inter_tex[15]);
	draw_img(map, &(t_info){WIDTH/2 - 130, 60, 20, 20}, map->door_tex[4]);

	// if (map->door_tex[1]->active == 1)
	// 	draw_img(map, &(t_info){WIDTH/2 - 60, 20, 40, 40}, map->inter_tex[15]);
	draw_img(map, &(t_info){WIDTH/2 - 60, 10, 40, 40}, map->door_tex[1]);
	// // if (map->door_tex[5]->active == 1)
	// 	draw_img(map, &(t_info){WIDTH/2 - 50, 70, 20, 20}, map->inter_tex[15]);
	draw_img(map, &(t_info){WIDTH/2 - 50, 60, 20, 20}, map->door_tex[5]);

	// if (map->door_tex[2]->active == 1)
	// 	draw_img(map, &(t_info){WIDTH/2 + 20, 20, 40, 40}, map->inter_tex[15]);
	draw_img(map, &(t_info){WIDTH/2 + 20, 10, 40, 40}, map->door_tex[2]);
	// // if (map->door_tex[6]->active == 1)
	// 	draw_img(map, &(t_info){WIDTH/2 + 30, 70, 20, 20}, map->inter_tex[15]);
	draw_img(map, &(t_info){WIDTH/2 + 30, 60, 20, 20}, map->door_tex[6]);

	// if (map->door_tex[3]->active == 1)
	// 	draw_img(map, &(t_info){WIDTH/2 + 90, 20, 40, 40}, map->inter_tex[15]);
	draw_img(map, &(t_info){WIDTH/2 + 90, 10, 40, 40}, map->door_tex[3]);
	// // if (map->door_tex[7]->active == 1)
	// 	draw_img(map, &(t_info){WIDTH/2 + 100, 70, 20, 20}, map->inter_tex[15]);
	draw_img(map, &(t_info){WIDTH/2 + 100, 60, 20, 20}, map->door_tex[7]);

	draw_img(map, &(t_info){WIDTH/2 + 80, 100, 65, 30}, map->floorsky_tex[0]);
	fonts_classic(map, "SAVE", &(t_info){WIDTH/2 + 90, 105, 0, 0}, WHITEFONT);
	draw_img(map, &(t_info){WIDTH/2 - 145, 100, 65, 30}, map->floorsky_tex[0]);
	fonts_classic(map, "CANCEL", &(t_info){WIDTH/2 - 142, 105, 0, 0}, WHITEFONT);
}

void	draw_obj_block(t_map *map)
{
	draw_player(map);
	draw_guns(map);
	draw_enemy(map);
	draw_door_light_exit(map);
}
void	doorshit(t_map *map)
{
	if (map->door_tex[0]->active == 0 && map->door_tex[1]->active == 0 && map->door_tex[2]->active == 0 && map->door_tex[3]->active == 0)
	{
		map->inter_tex[16]->active = 1;
		draw_door_win(map);
	}
	if (map->door_tex[0]->active == 1)
		draw_img(map, &(t_info){310, 760, 40, 40}, map->door_tex[0]);
	if (map->door_tex[1]->active == 1)
		draw_img(map, &(t_info){310, 760, 40, 40}, map->door_tex[1]);
	if (map->door_tex[2]->active == 1)
		draw_img(map, &(t_info){310, 760, 40, 40}, map->door_tex[2]);
	if (map->door_tex[3]->active == 1)
		draw_img(map, &(t_info){310, 760, 40, 40}, map->door_tex[3]);
}

// void draw_door_line(t_map *map, int x, int y, int pix)
// {
// 	if ((map->inter_tex[0]->s[pix] == 0 && map->inter_tex[0]->s[++pix] == 255 && map->inter_tex[0]->s[++pix] == 0)
// }

// int xyround(t_map *map, int x, int y)
// {
// 	int pixp;
// 	int pixm;
// 	int i;
// 	int j;

// 	i = 0;
// 	// pix = y * map->inter_tex[0]->strb + x * map->inter_tex[0]->pixb;
// 	// if (map->inter_tex[0]->s[pix] == 0 && map->inter_tex[0]->s[++pix] == 255 && map->inter_tex[0]->s[++pix] == 0)
// 	// 	printf("greeeeeeen\n");
// 	// printf("%d	%d	%d\n", map->inter_tex[0]->s[pix], map->inter_tex[0]->s[++pix], map->inter_tex[0]->s[++pix]);
// 	while (i < 5)
// 	{
// 		j = 0;
// 		while (j < 5)
// 		{
// 			pixp = (y * map->inter_tex[0]->strb + i) + (x * map->inter_tex[0]->pixb + j);
// 			pixm = (y * map->inter_tex[0]->strb - i) + (x * map->inter_tex[0]->pixb - j);
// 			if ((map->inter_tex[0]->s[pixp] == 0 && map->inter_tex[0]->s[++pixp] == 255 && map->inter_tex[0]->s[++pixp] == 0) ||
// 				(map->inter_tex[0]->s[pixm] == 0 && map->inter_tex[0]->s[++pixm] == 255 && map->inter_tex[0]->s[++pixm] == 0)) // didn't work
// 			{
// 				// draw_color(map, pixp, RED);
// 				draw_pixel(map, x+j, y+i, RED);
// 				// /draw_door_line(map, x+j, y+i, pixp);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	// if (map->inter_tex[0]->s[pix] == 0 && map->inter_tex[0]->s[++pix] == 255 && map->inter_tex[0]->s[++pix] == 0)
		
// 	return (0);
// }

// void	drawillwall(t_map *map, int x, int y)
// {
// 	if (xyround(x, y))
// }

void objectsblock(t_map *map)
{
	draw_obj_block(map);
	if (map->door_tex[10]->active == 1)
	{
		
		doorshit(map);
		// if (map->door_tex[0]->active == 0 && map->door_tex[1]->active == 0 || map->door_tex[2]->active == 1 ||
		// map->door_tex[3]->active == 1 || map->door_tex[4]->active == 1 || map->door_tex[5]->active == 1)
			// draw_door_win(map);
	}
	if (map->validflag == 6)
	{
		save_texture(map, map->index_tex, 1);
		// map->inter_tex[17]->active = 0;
		// map->inter_tex[19]->active = 0;
		// map->inter_tex[16]->active = 0;
	}
}