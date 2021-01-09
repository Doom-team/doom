/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gordey <gordey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:37:42 by grinko            #+#    #+#             */
/*   Updated: 2020/12/29 19:32:53 by gordey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	draw_img(t_map *map, t_info *info, t_image *st)
{
	int i;
	int j;
	int pixel1;
	int pixel2;

	i = info->y;
	while (i < HEIGHT && i < info->y + info->h)
	{
		j = info->x;
		while (j < WIDTH && j < info->x + info->w)
		{
			pixel1 = i * map->inter_tex[0]->strb + j * map->inter_tex[0]->pixb;
			pixel2 = (int)((double)(i - info->y) / info->h * st->img->h) *
				st->strb + (int)((double)(j - info->x) / info->w *
					st->img->w) * st->pixb;
			if (st->s[pixel2 + 3])
			{
				map->inter_tex[0]->s[pixel1] = st->s[pixel2];
				map->inter_tex[0]->s[++pixel1] = st->s[++pixel2];
				map->inter_tex[0]->s[++pixel1] = st->s[++pixel2];
			}
			j++;
		}
		i++;
	}
}

void	draw_color(t_map *map, int pixel, t_color color)
{
	map->inter_tex[0]->s[pixel] = color.b;
	map->inter_tex[0]->s[++pixel] = color.g;
	map->inter_tex[0]->s[++pixel] = color.r;
}

void	draw_pixel(t_map *map, int x, int y, t_color color)
{
	int pixel;

	if (x < WIDTH && y < HEIGHT)
	{
		pixel = (x * map->inter_tex[0]->pixb) + (y * map->inter_tex[0]->strb);
		draw_color(map, pixel, color);
	}
}

void	draw_point(t_map *map, int x, int y, t_color color)
{
	int i;
	int j;
	int pixel;

	i = -1;
	while (i < 1)
	{
		j = -1;
		while (j < 1)
		{
			if (x + i >= 0 && y + j >= 0 && x + i < WIDTH && y + j < HEIGHT)
			{
				pixel = ((x + i) * map->inter_tex[0]->pixb) + ((y + j) *
					map->inter_tex[0]->strb);
				draw_color(map, pixel, color);
			}
			j++;
		}
		i++;
	}
}

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
	// draw_img(map, &(t_info){65, 400, 50, 50}, map->block_tex[0]);
}

void	whichone_tool(t_map *map)
{
	if (map->inter_tex[3]->active || map->inter_tex[6]->active ||
		map->inter_tex[7]->active || map->inter_tex[8]->active)
	{
		draw_block_textures(map);
		draw_slider(map);
		draw_stairs(map);
		draw_tests(map);
		draw_music(map);
	}
	// (map->inter_tex[3]->active == 1) ? (draw_slider(map), fonts_classic(map, "radius", 122, 135)) : printf("qwe\n");
	if (map->inter_tex[4]->active == 1)
		texture_block(map);
	if (map->showactive == 2)
		open_floor_win(map);
	if (map->inter_tex[5]->active == 1)
		objectsblock(map);
		//draw_img2(map, &(t_info){map->floor_x + map->z_x, map->floor_y + map->z_y, abs(map->tmpfloor_x - map->floor_x), abs(map->tmpfloor_y - map->floor_y)}, map->floorsky_tex[map->index_tex]);
	if (map->inter_tex[6]->active == 1)
	{
		fonts_classic(map, "edit tool", &(t_info){305, 780, 0, 0}, WHITEFONT);
		draw_hlider(map);
	}
	if (map->inter_tex[7]->active == 1)
		fonts_classic(map, "info tool", &(t_info){305, 780, 0, 0}, WHITEFONT);
	if (map->inter_tex[8]->active == 1)
		fonts_classic(map, "remove tool", &(t_info){305, 780, 0, 0}, WHITEFONT);
	if (map->validflag == 1)
		fonts_classic(map, "map is not closed!",
			&(t_info){350, HEIGHT - 20, 0, 0}, REDFONT);
}

void	draw(t_map *map)
{
	draw_basic_interface(map);
	whichone_tool(map);
	// open_texture_win(map);
	if (map->click)
		bigdot(map, map->x_c, map->y_c, RED);
	if ((map->click || map->tmpclick) && (map->block_tex[0]->active ||
		map->block_tex[1]->active || map->block_tex[2]->active ||
			map->block_tex[3]->active))
	{
		map->click = 0;
		map->tmpclick = 0;
		made_blocks(map, map->x_c, map->y_c);
	}
	if (map->nod != NULL)
		draw_nodes(map);
	SDL_UpdateWindowSurface(map->win);
}
