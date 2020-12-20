#include "../include/map.h"

int some_texture_active(t_map *map)
{
	int i;

	i = 0;
	while (++i < 19)
		if (map->wall_tex[i]->active == 1)
			return (1);
	i = 0;
	while (++i < 13)
		if (map->floorsky_tex[i]->active == 1)
			return (2);
	i = 0;
	while (++i < 4)
		if (map->liquid_tex[i]->active == 1)
			return (3);
	return (0);
}

int	find_texture_name(char *str)
{
	int i;

	i = 0;
	if (ft_strlen(str) == 9)
		i = ft_atoi(&str[4]);
	else if (ft_strlen(str) == 10)
	{
		i = ft_atoi(&str[5]);
		i += 10;
	}
	return (i);
}

void	changer(t_map *map, int x, int y)
{
	int tmp;

	if (some_texture_active(map) == 1)
	{
		tmp = find_nod(map, x, y);
		if (tmp > 0)
		{
			map->index_wall = tmp;
			map->inter_tex[16]->active = 1;
		}
	}
	// else if (some_texture_active(map) == 2)
	// {
	// 	map->tmpfloor_x = x;
	// 	map->tmpfloor_y = y;
	// 	// map->showactive = 2;
	// 	map->inter_tex[16]->active = 3;
	// }
}

void	change_texture(t_map *map, int x, int y)
{
	int wichone;

	wichone = some_texture_active(map);
	if (wichone == 1)
		get_wall_cord(map, x, y);
	// if (wichone == 2)
	// 	get_floor_cordi(map, x, y);
}



void	texture_block(t_map *map)
{
	draw_wall_textures(map);
	draw_showuppanel(map, 260, 205, 1);
	draw_floor_textures(map);
	draw_sky_textures(map);
	draw_liquid_textures(map);
	draw_small_panel_tex(map);
	open_texture_win(map);
	open_floor_win(map);
}