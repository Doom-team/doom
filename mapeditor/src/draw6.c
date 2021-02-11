/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:37:42 by grinko            #+#    #+#             */
/*   Updated: 2021/02/12 00:10:21 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	draw_basic_interface(t_map *map)
{
	SDL_FillRect(map->inter_tex[0]->img, NULL, 0);
	draw_grid(map);
	draw_img(map, &(t_info){0, 0, 300, 800}, map->inter_tex[1]);
	draw_img(map, &(t_info){10, 110, 280, 680}, map->inter_tex[2]);
	draw_img(map, &(t_info){20, 20, 70, 30}, map->inter_tex[3]);
	draw_img(map, &(t_info){110, 20, 70, 30}, map->inter_tex[4]);
	draw_img(map, &(t_info){200, 20, 70, 30}, map->inter_tex[5]);
	draw_img(map, &(t_info){80, 60, 30, 30}, map->inter_tex[6]);
	draw_img(map, &(t_info){130, 60, 30, 30}, map->inter_tex[7]);
	draw_img(map, &(t_info){180, 60, 30, 30}, map->inter_tex[8]);
	draw_img(map, &(t_info){120, 758, 60, 30}, map->inter_tex[21]);
}

void	draw_block_textures(t_map *map)
{
	draw_img(map, &(t_info){65, 250, 50, 50}, map->block_tex[0]);
	draw_img(map, &(t_info){165, 250, 50, 50}, map->block_tex[1]);
	draw_img(map, &(t_info){65, 320, 50, 50}, map->block_tex[2]);
	draw_img(map, &(t_info){165, 320, 50, 50}, map->block_tex[3]);
}

void	draw_standartpanel(t_map *map)
{
	draw_block_textures(map);
	draw_slider(map);
	draw_stairs(map);
	draw_tests(map);
	draw_music(map);
}

void	error_log(t_map *map)
{
	if (map->errorflag == 1)
		fonts_classic(map, "map is not closed!",
			&(t_info){350, HEIGHT - 20, 0, 0}, REDFONT);
	if (map->errorflag == 2)
		fonts_classic(map, "set player position!",
			&(t_info){350, HEIGHT - 20, 0, 0}, REDFONT);
}

void	whichone_tool(t_map *map)
{
	if (map->inter_tex[3]->active || map->inter_tex[6]->active ||
		map->inter_tex[7]->active || map->inter_tex[8]->active)
		draw_standartpanel(map);
	if (map->inter_tex[4]->active == 1)
		texture_block(map);
	if (map->showactive == 2)
		open_floor_win(map);
	if (map->inter_tex[5]->active == 1)
		objectsblock(map);
	if (map->inter_tex[6]->active == 1)
	{
		fonts_classic(map, "edit tool", &(t_info){305, 780, 0, 0}, WHITEFONT);
		draw_hlider(map);
	}
	if (map->inter_tex[7]->active == 1)
		fonts_classic(map, "info tool", &(t_info){305, 780, 0, 0}, WHITEFONT);
	if (map->inter_tex[8]->active == 1)
		fonts_classic(map, "remove tool", &(t_info){305, 780, 0, 0}, WHITEFONT);
	error_log(map);
}
