/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:39 by grinko            #+#    #+#             */
/*   Updated: 2020/12/22 13:39:40 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void change_text_inter2(t_map *map)
{
	draw_line(map, &(t_info){WIDTH/2 - 100, 40, 0, 40}, (t_color){0,0,0});
	draw_line(map, &(t_info){WIDTH/2 - 100, 41, 0, 40}, (t_color){0,0,0});
	draw_line(map, &(t_info){WIDTH/2 + 120, 40, 0, 40}, (t_color){0,0,0});
	draw_line(map, &(t_info){WIDTH/2 + 120, 41, 0, 40}, (t_color){0,0,0});
	draw_img(map, &(t_info){WIDTH/2 + 80, 100, 65, 30}, map->floorsky_tex[0]);
	fonts_classic(map, "SAVE", &(t_info){WIDTH/2 + 90, 105, 0, 0}, WHITEFONT);
	draw_img(map, &(t_info){WIDTH/2 - 145, 100, 65, 30}, map->floorsky_tex[0]);
	fonts_classic(map, "CANCEL", &(t_info){WIDTH/2 - 142, 105, 0, 0}, WHITEFONT);
}

void change_text_inter(t_map *map)
{
	draw_img(map, &(t_info){WIDTH/2 - 165, 5, 330, 150}, map->inter_tex[16]);
	if (map->inter_tex[17]->active == 0)
		draw_img(map, &(t_info){WIDTH/2 - 10, 3, 30, 35}, map->inter_tex[17]);
	else
		draw_img(map, &(t_info){WIDTH/2 - 10, 3, 30, 35}, map->inter_tex[18]);
	if (map->inter_tex[19]->active == 0)
		draw_img(map, &(t_info){WIDTH/2 - 10, 83, 30, 35}, map->inter_tex[19]);
	else
		draw_img(map, &(t_info){WIDTH/2 - 10, 83, 30, 35}, map->inter_tex[20]);
	draw_line(map, &(t_info){WIDTH/2 - 100, 40, 220, 0}, (t_color){0,0,0});
	draw_line(map, &(t_info){WIDTH/2 - 100, 41, 220, 0}, (t_color){0,0,0});
	draw_line(map, &(t_info){WIDTH/2 - 100, 60, 220, 0}, (t_color){0,0,0});
	draw_line(map, &(t_info){WIDTH/2 - 100, 61, 220, 0}, (t_color){0,0,0});
	draw_line(map, &(t_info){WIDTH/2 - 100, 80, 220, 0}, (t_color){0,0,0});
	draw_line(map, &(t_info){WIDTH/2 - 100, 81, 220, 0}, (t_color){0,0,0});
	change_text_inter2(map);
}

void	save_texture(t_map *map, int index, int num)
{
	t_nod *n;

	n = map->nod;
	while (n)
	{
		if (n->index == map->index_wall)
		{
			n->texture->texture_name[num] = "wall";
			n->texture->texture_name[num] = ft_strjoin(n->texture->texture_name[num], ft_itoa(index));
			n->texture->texture_name[num] = ft_strjoin(n->texture->texture_name[num], ".png");
		}
		n = n->nxt;
	}
}

void	get_wall_cord(t_map *map, int x, int y)
{
	if (map->click == 0 && interface_click(map, x, y) && range_click(&(t_info){x, y, WIDTH / 2 - 165, 5}, 330, 150))
	{
		cursor(map, "/textures/interface/firstdot.png", 0, 16);
		map->click = 1;
		map->change_x = x;
		map->change_y = y;
		find_coord(map, &(map->change_x), &(map->change_y));
		map->change_x -= map->z_x;
		map->change_y -= map->z_y;
	}
	else if (interface_click(map, x, y) && range_click(&(t_info){x, y, WIDTH / 2 - 165, 5}, 330, 150))
	{
		map->click = 0;
		cursor(map, "/textures/interface/seconddot.png", 0, 16);
		find_coord(map, &x, &y);
		changer(map, x - map->z_x, y - map->z_y);
	}
}

void open_texture_win(t_map *map)
{
	if (map->inter_tex[16]->active == 1)
	{
		change_text_inter(map);
		map->validflag = draw_changer_texture(map);
	}
	if (map->inter_tex[16]->active == 2 && map->validflag == 3)
	{
		save_texture(map, map->index_tex, 0);
		map->inter_tex[17]->active = 0;
		map->inter_tex[19]->active = 0;
		map->inter_tex[16]->active = 0;
	}
	else if (map->inter_tex[16]->active == 2 && map->validflag == 4)
	{
		save_texture(map, map->index_tex, 1);
		map->inter_tex[17]->active = 0;
		map->inter_tex[19]->active = 0;
		map->inter_tex[16]->active = 0;
	}
}
