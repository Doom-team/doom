#include "../include/map.h"

void	showtexture(t_map *map)
{
	int i;
	int y;

	i = 8;
	y = 20;
	while (++i < 19)
	{
		if (map->wall_tex[i]->active == 1)
			draw_img(map, &(t_info){320 - 10, y - 10, 70, 70}, map->inter_tex[15]);
		draw_img(map, &(t_info){320, y, 50, 50}, map->wall_tex[i]);
		y += 80;
	}
}

void	showfloorsky(t_map *map)
{
	int i;
	int y;

	i = 8;
	y = 20;
	while (++i < 13)
	{
		if (map->floorsky_tex[i]->active == 1)
			draw_img(map, &(t_info){320 - 10, y - 10, 70, 70}, map->inter_tex[15]);
		draw_img(map, &(t_info){320, y, 50, 50}, map->floorsky_tex[i]);
		y += 80;
	}
}


void showupcontent(t_map *map)
{
	int i;
	int y;

	i = 8;
	y = 20;
	if (map->showactive == 1)
	{
		draw_img(map, &(t_info){260, 205, 30, 50}, map->inter_tex[14]);
		showtexture(map);
	}
}

void draw_showuppanel(t_map *map, int x, int y, int inx)
{
	if (map->inter_tex[13]->active == 1)
	{
		draw_img(map, &(t_info){305, 0, 80, 800}, map->inter_tex[12]);
		showupcontent(map);
	}
	else
		draw_img(map, &(t_info){x, y, 30, 50}, map->inter_tex[13]);
	
}

void draw_small_panel_tex(t_map *map)
{
	int i;

	i = 0;
	while (++i < 19)
		if (map->wall_tex[i]->active == 1 && map->inter_tex[13]->active == 0)
		{
			map->index_tex = i;
			draw_img(map, &(t_info){310, 770, 25, 25}, map->wall_tex[i]);
		}
	i = 0;
	while (++i < 13)
		if (map->floorsky_tex[i]->active == 1 && map->inter_tex[13]->active == 0)
		{
			map->index_tex = i;
			draw_img(map, &(t_info){310, 770, 25, 25}, map->floorsky_tex[i]);
		}
	i = 0;
	while (++i < 4)
		if (map->liquid_tex[i]->active == 1 && map->inter_tex[13]->active == 0)
			draw_img(map, &(t_info){310, 770, 25, 25}, map->liquid_tex[i]);
}
