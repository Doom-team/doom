/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:37:45 by grinko            #+#    #+#             */
/*   Updated: 2021/02/12 00:12:26 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	draw_music(t_map *map)
{
	fonts_classic(map, "MISIC", &(t_info){122, 640, 0, 0}, BLACKFONT);
	draw_img(map, &(t_info){20, 670, 50, 50}, map->block_tex[4]);
	draw_img(map, &(t_info){90, 670, 50, 50}, map->block_tex[4]);
	draw_img(map, &(t_info){160, 670, 50, 50}, map->block_tex[4]);
	draw_img(map, &(t_info){230, 670, 50, 50}, map->block_tex[4]);
}

void	draw_tests(t_map *map)
{
	fonts_doom(map, "DOES NOT WORK", &(t_info){80, 540, 0, 0}, REDFONT);
	draw_img(map, &(t_info){35, 560, 60, 60}, map->block_tex[6]);
	draw_img(map, &(t_info){120, 560, 60, 60}, map->block_tex[7]);
	draw_img(map, &(t_info){200, 560, 60, 60}, map->block_tex[8]);
}

void	draw_stairs(t_map *map)
{
	char *str;

	str = ft_itoa(map->stclick);
	draw_img(map, &(t_info){40, 400, 220, 50}, map->inter_tex[9]);
	draw_img(map, &(t_info){70, 410, 25, 25}, map->inter_tex[11]);
	draw_img(map, &(t_info){195, 410, 25, 25}, map->inter_tex[10]);
	draw_line(map, &(t_info){95, 422, 100, 0}, (t_color){255, 255, 255});
	draw_line(map, &(t_info){95, 423, 100, 0}, (t_color){255, 255, 255});
	draw_line(map, &(t_info){95, 424, 100, 0}, (t_color){255, 255, 255});
	fonts_classic(map, "stairs height", &(t_info){102, 402, 0, 0}, WHITEFONT);
	fonts_classic(map, str, &(t_info){130, 432, 0, 0},
		WHITEFONT);
	draw_img(map, &(t_info){120, 470, 60, 60}, map->block_tex[5]);
	free(str);
}

void	draw_slider(t_map *map)
{
	draw_img(map, &(t_info){40, 120, 220, 100}, map->inter_tex[9]);
	if (map->block_tex[0]->active || map->block_tex[1]->active ||
		map->block_tex[2]->active || map->block_tex[3]->active)
	{
		draw_img(map, &(t_info){70, 140, 25, 25}, map->inter_tex[11]);
		draw_img(map, &(t_info){195, 140, 25, 25}, map->inter_tex[10]);
		draw_line(map, &(t_info){95, 152, 100, 0}, (t_color){255, 255, 255});
		draw_line(map, &(t_info){95, 153, 100, 0}, (t_color){255, 255, 255});
		draw_line(map, &(t_info){95, 154, 100, 0}, (t_color){255, 255, 255});
		bigdot(map, 115 + (map->wclick), 153, RED);
		fonts_classic(map, "radius", &(t_info){122, 132, 0, 0}, WHITEFONT);
	}
}
