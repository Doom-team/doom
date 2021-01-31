/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:11 by grinko            #+#    #+#             */
/*   Updated: 2021/01/31 19:03:19 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

int		interface_click(t_map *map, int x, int y)
{
	if ((x > 0 && x < 300) && y > 0 && y < 800)
		return (0);
	return (1);
}

int		range_click(t_info *info, int w, int h)
{
	if ((info->x > info->w && info->x < info->w + w) &&
		info->y > info->h && info->y < info->h + h)
		return (0);
	return (1);
}

void	tools_click(t_map *map, int x, int y)
{
	if ((x > 80 && x < 110) && y > 60 && y < 90)
		edit_tool(map, 6);
	else if ((x > 130 && x < 160) && y > 60 && y < 90)
		edit_tool(map, 7);
	else if ((x > 180 && x < 210) && y > 60 && y < 90)
		edit_tool(map, 8);
}

void	hwidget_click(t_map *map, int x, int y)
{
	if ((x > 70 && x < 95) && (y > 180 && y < 205) && map->whclick > 1)
		map->whclick -= 1;
	else if ((x > 195 && x < 220) && y > 180 && y < 205 && map->whclick < 20)
		map->whclick += 1;
}

int		widget_click(t_map *map, int x, int y)
{
	int tmp;

	tmp = map->wclick;
	if ((x > 70 && x < 95) && (y > 140 && y < 165) && map->wclick > -20)
	{
		map->tmpclick = 1;
		map->wclick -= 3;
	}
	else if ((x > 195 && x < 220) && (y > 140 && y < 165) && map->wclick < 76)
	{
		map->tmpclick = 1;
		map->wclick += 3;
	}
	if (map->wclick != tmp)
		return (0);
	return (1);
}

void	section_click(t_map *map, int x, int y)
{
	if ((x > 20 && x < 90) && y > 20 && y < 50)
		edit_tool(map, 3);
	else if ((x > 110 && x < 180) && y > 20 && y < 50)
		edit_tool(map, 4);
	else if ((x > 200 && x < 270) && y > 20 && y < 50)
		edit_tool(map, 5);
	else if ((x > 120 && x < 180) && y > 758 && y < 788)
		map->inter_tex[21]->active = 1;
}

void	blockterxture_click(t_map *map, int x, int y)
{
	if ((x > 65 && x < 115) && y > 250 && y < 300)
		edit_blocktexture(map, 0);
	else if ((x > 165 && x < 215) && y > 250 && y < 300)
		edit_blocktexture(map, 1);
	else if ((x > 65 && x < 115) && y > 320 && y < 370)
		edit_blocktexture(map, 2);
	else if ((x > 165 && x < 215) && y > 250 && y < 370)
		edit_blocktexture(map, 3);
	else if ((x > 120 && x < 180) && y > 470 && y < 530)
	{
		map->click = 0;
		printf("st\t\t\t\the\n");
		edit_blocktexture(map, 5);
	}
	if ((x > 70 && x < 95) && y > 410 && y < 435) /// света 
		if (map->stclick > 1)
			map->stclick--;
	if ((x > 195 && x < 220) && y > 410 && y < 435)
		if (map->stclick < 15)
			map->stclick++;
	
	if ((x > 20 && x < 70) && y > 670 && y < 720)
		map->musicflag = 1;
	if ((x > 90 && x < 140) && y > 670 && y < 720)
		map->musicflag = 2;
	if ((x > 160 && x < 210) && y > 670 && y < 720)
		map->musicflag = 3;
	if ((x > 230 && x < 280) && y > 670 && y < 720)
		map->musicflag = 4;
}

void	showup_lick(t_map *map, int x, int y)
{
	if ((x > 260 && x < 290) && y > 205 && y < 255)
	{
		map->showactive = 1;
		if (map->inter_tex[13]->active == 1)
			map->inter_tex[13]->active = 0;
		else
			map->inter_tex[13]->active = 1;
	}
	// if ((x > 260 && x < 290) && y > 370 && y < 420)
	// {
	// 	map->showactive = 2;
	// 	if (map->inter_tex[13]->active == 1)
	// 		map->inter_tex[13]->active = 0;
	// 	else
	// 		map->inter_tex[13]->active = 1;
	// }
}

void	zerroother(t_map *map)
{
	int i;

	i = 0;
	while (++i < 19)
		map->wall_tex[i]->active = 0;
	i = 0;
	while (++i < 13)
		map->floorsky_tex[i]->active = 0;
	i = 0;
	while (++i < 4)
		map->liquid_tex[i]->active = 0;
}

void	edit_walltexture(t_map *map, int index)
{
	int i;

	i = 0;
	zerroother(map);
	while (++i < 19)
	{
		if (i == index)
			map->wall_tex[i]->active = 1;
		else
			map->wall_tex[i]->active = 0;
	}
}

void	edit_floortexture(t_map *map, int index)
{
	int i;

	i = 0;
	zerroother(map);
	while (++i < 13)
	{
		if (i == index)
			map->floorsky_tex[i]->active = 1;
		else
			map->floorsky_tex[i]->active = 0;
	}
}

void	edit_liquidtexture(t_map *map, int index)
{
	int i;

	i = 0;
	zerroother(map);
	while (++i < 4)
	{
		if (i == index)
			map->liquid_tex[i]->active = 1;
		else
			map->liquid_tex[i]->active = 0;
	}
}

void	walltx_click(t_map *map, int x, int y)
{
	int i;
	int x_c;
	int y_c;

	i = 0;
	x_c = 20;
	y_c = 170;
	while (++i < 9)
	{
		if ((x > x_c && x < x_c + 50) && (y > y_c && y < y_c + 50))
			edit_walltexture(map, i);
		x_c += 60;
		if (i == 4)
		{
			x_c = 20;
			y_c = 230;
		}
	}
	if (map->inter_tex[13]->active == 1)
	{
		x_c = 20;
		i = 8;
		while (++i < 19)
		{
			if ((x > 320 && x < 370) && (y > x_c && y < x_c + 50))
				edit_walltexture(map, i);
			x_c += 80;
		}
	}
}

void	floortx_click(t_map *map, int x, int y)
{
	int i;
	int x_c;
	int y_c;

	i = 0;
	x_c = 20;
	y_c = 340;
	while (++i < 9)
	{
		if ((x > x_c && x < x_c + 50) && (y > y_c && y < y_c + 50))
			edit_floortexture(map, i);
		x_c += 60;
		if (i == 4)
		{
			x_c = 20;
			y_c = 400;
		}
	}
}

void	skytx_click(t_map *map, int x, int y)
{
	int i;
	int x_c;
	int y_c;

	i = 8;
	x_c = 20;
	y_c = 520;
	while (++i < 13)
	{
		if ((x > x_c && x < x_c + 50) && (y > y_c && y < y_c + 50))
			edit_floortexture(map, i);
		x_c += 60;
		if (i == 4)
		{
			x_c = 20;
			y_c = 400;
		}
	}
}

void	liquidtx_click(t_map *map, int x, int y)
{
	int i;
	int x_c;
	int y_c;

	i = 0;
	x_c = 20;
	y_c = 620;
	while (++i < 4)
	{
		if ((x > x_c && x < x_c + 50) && (y > y_c && y < y_c + 50))
			edit_liquidtexture(map, i);
		x_c += 90;
	}
}

void	terxtures_click(t_map *map, int x, int y)
{
	edit_blocktexture(map, -1);
	showup_lick(map, x, y);
	walltx_click(map, x, y);
	floortx_click(map, x, y);
	skytx_click(map, x, y);
	liquidtx_click(map, x, y);
}

void	change_texture_click(t_map *map, int x, int y)
{
	if ((x > WIDTH / 2 - 10 && x < WIDTH / 2 + 20) && (y > 3 && y < 38))
	{
		map->inter_tex[17]->active = 1;
		map->inter_tex[19]->active = 0;
	}
	if ((x > WIDTH / 2 - 10 && x < WIDTH / 2 + 20) && (y > 83 && y < 118))
	{
		map->inter_tex[17]->active = 0;
		map->inter_tex[19]->active = 1;
	}
	if ((x > WIDTH / 2 - 145 && x < WIDTH / 2 - 80) && (y > 100 && y < 130))
	{
		map->inter_tex[16]->active = 0;
		map->inter_tex[17]->active = 0;
		map->inter_tex[19]->active = 0;
	}
	if ((x > WIDTH / 2 + 80 && x < WIDTH / 2 + 145) && (y > 100 && y < 130))
	{
		map->inter_tex[16]->active = 2;
	}
}

void	change_floor_click(t_map *map, int x, int y)
{
	if ((x > WIDTH / 2 + 20 && x < WIDTH / 2 + 90) && (y > 10 && y < 30))
		map->floorsky_tex[0]->active = 1;
	if ((x > WIDTH / 2 + 20 && x < WIDTH / 2 + 90) && (y > 30 && y < 50))
		map->floorsky_tex[0]->active = 2;
	if ((x > WIDTH / 2 + 120 && x < WIDTH / 2 + 185) && (y > 60 && y < 90))
	{
		zerroother(map);
		map->inter_tex[16]->active = 4;
	}
	if ((x > WIDTH / 2 - 100 && x < WIDTH / 2 - 35) && (y > 60 && y < 90))
	{
		zerroother(map);
		map->inter_tex[16]->active = 0;
	}
}

void	floorker(t_map *map, int x, int y)
{
	int x1;
	int y1;

	//x1 = x;
	//y1 = y;
	//find_coord(map, &x1, &y1);
	draw(map);
	if (some_texture_active(map) == 2)
	{
		open_floor_win(map);
		// if (x1 != x || y1 != y)
		// 	get_floor_cordi(map, x1 , y1 );
	}
}

void	zerroothero(t_map *map)
{
	int i;

	i = -1;
	while (++i < 3)
		map->player_tex[i]->active = 0;
	i = -1;
	while (++i < 6)
		map->gun_tex[i]->active = 0;
	i = -1;
	while (++i < 5)
		map->enemy_tex[i]->active = 0;
	i = -1;
	while (++i < 11)
		map->door_tex[i]->active = 0;
}

void	edit_object(t_map *map, t_image **name, int n, int index)
{
	int i;

	i = -1;
	if (map->inter_tex[5]->active == 1)
		zerroothero(map);
	while (++i < n)
	{
		if (i == index)
			name[i]->active = 1;
		else
			name[i]->active = 0;
	}
}

void	objects_click(t_map *map, int x, int y)
{
	if ((x > 30 && x < 70) && (y > 130 && y < 170))
		edit_object(map, map->player_tex, 3, 0);
	if ((x > 130 && x < 170) && (y > 150 && y < 170))
		edit_object(map, map->player_tex, 3, 1);
	if ((x > 230 && x < 270) && (y > 150 && y < 170))
		edit_object(map, map->player_tex, 3, 2);
	if ((x > 30 && x < 80) && (y > 250 && y < 270))
		edit_object(map, map->gun_tex, 6, 0);
	if ((x > 130 && x < 180) && (y > 250 && y < 270))
		edit_object(map, map->gun_tex, 6, 2);
	if ((x > 230 && x < 280) && (y > 250 && y < 270))
		edit_object(map, map->gun_tex, 6, 4);
	if ((x > 30 && x < 50) && (y > 280 && y < 300))
		edit_object(map, map->gun_tex, 6, 1);
	if ((x > 130 && x < 160) && (y > 280 && y < 300))
		edit_object(map, map->gun_tex, 6, 3);
	if ((x > 230 && x < 260) && (y > 280 && y < 300))
		edit_object(map, map->gun_tex, 6, 5);
	if ((x > 30 && x < 70) && (y > 350 && y < 390))
		edit_object(map, map->enemy_tex, 5, 0);
	if ((x > 130 && x < 170) && (y > 350 && y < 390))
		edit_object(map, map->enemy_tex, 5, 1);
	if ((x > 230 && x < 280) && (y > 350 && y < 390))
		edit_object(map, map->enemy_tex, 5, 2);
	if ((x > 60 && x < 100) && (y > 430 && y < 470))
		edit_object(map, map->enemy_tex, 5, 3);
	if ((x > 160 && x < 200) && (y > 430 && y < 470))
		edit_object(map, map->enemy_tex, 5, 4);
	if ((x > 115 && x < 155) && (y > 500 && y < 540))
		edit_object(map, map->door_tex, 11, 10);
	if ((x > 115 && x < 155) && (y > 600 && y < 640))
		edit_object(map, map->door_tex, 11, 8);
	if ((x > 130 && x < 150) && (y > 700 && y < 740))
		edit_object(map, map->door_tex, 11, 9);
}

void	get_door(t_map *map, int x, int y)
{
	if ((x > WIDTH / 2 - 140 && x < WIDTH / 2 - 100) && (y > 10 && y < 50))
	{
		map->door_tex[0]->active = 1;
		map->door_tex[1]->active = 0;
		map->door_tex[2]->active = 0;
		map->door_tex[3]->active = 0;
		// edit_object(map, map->door_tex, 1, 0);
	}
	if ((x > WIDTH / 2 - 60 && x < WIDTH / 2 - 20) && (y > 10 && y < 50))
	{
		map->door_tex[0]->active = 0;
		map->door_tex[1]->active = 1;
		map->door_tex[2]->active = 0;
		map->door_tex[3]->active = 0;
	}
	if ((x > WIDTH / 2 + 20 && x < WIDTH / 2 + 60) && (y > 10 && y < 50))
	{
		map->door_tex[0]->active = 0;
		map->door_tex[1]->active = 0;
		map->door_tex[2]->active = 1;
		map->door_tex[3]->active = 0;
	}
	if ((x > WIDTH / 2 + 90 && x < WIDTH / 2 + 130) && (y > 10 && y < 50))
	{
		map->door_tex[0]->active = 0;
		map->door_tex[1]->active = 0;
		map->door_tex[2]->active = 0;
		map->door_tex[3]->active = 1;
	}
	if ((x > WIDTH / 2 - 130 && x < WIDTH / 2 - 110) && (y > 60 && y < 80))
	{
		//map->validflag = -1;
		map->door_tex[0]->active = 0;
		map->door_tex[4]->active = 1;
	}
	if ((x > WIDTH / 2 + 80 && x < WIDTH / 2 + 145) && (y > 100 && y < 130))
	{
		printf("9\n");
		map->validflag = 9;
	}
	if ((x > WIDTH / 2 - 145 && x < WIDTH / 2 - 80) && (y > 100 && y < 130))
	{
		zerroothero(map);
	}
}

int		searchelem(char *str1, char *str2)
{
	char *istr;

	//Поиск строки
	istr = ft_strstr(str1, str2);
	//Вывод результата поиска на консоль
	if (istr == NULL)
		return (0);
	else
	{
		//printf ("Искомая строка начинается с символа %d\n",istr-str1+1);
		return (istr - str1 + 1);
	}
}

void	rewrite(t_map *map, int inx, int x, int y)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	tmp = malloc(sizeof(char *));
	if (map->player_tex[0]->active == 1 || map->door_tex[9]->active == 1)
	{
		if (map->objects)
		{
			tmp = ft_strncpy(tmp, map->objects, inx);
			tmp[inx] = '\0';
		}
		while (map->objects[inx] && map->objects[inx] != '\n')
			inx++;
		inx++;
		if (map->player_tex[0]->active == 1)
			str = ft_strjoin("p ", ft_itoa(x));
		else if (map->door_tex[9]->active == 1)
			str = ft_strjoin("b ", ft_itoa(x));
		str = ft_strjoin(str, " ");
		str = ft_strjoin(str, ft_itoa(y));
		str = ft_strjoin(str, "\n");
		if (tmp)
		{
			tmp = ft_strjoin(tmp, str);
			map->objects = ft_strjoin(tmp, &map->objects[inx]);
		}
		else
			map->objects = ft_strjoin(str, &map->objects[inx]);
	}
	free(tmp);
}

void	cordinator(t_map *map, char *c, int x, int y)
{
	if (ft_strlen(map->objects) != 0)
	{
		if (map->player_tex[0]->active == 1 && searchelem(map->objects, "p "))
		{
			rewrite(map, searchelem(map->objects, "p ") - 1, x, y);
			return ;
		}
		if (map->door_tex[9]->active == 1 && searchelem(map->objects, "b "))
		{
			rewrite(map, searchelem(map->objects, "b ") - 1, x, y);
			return ;
		}
		map->objects = ft_strjoin(map->objects, c);
		map->objects = ft_strjoin(map->objects, ft_itoa(x));
		map->objects = ft_strjoin(map->objects, " ");
		map->objects = ft_strjoin(map->objects, ft_itoa(y));
		map->objects = ft_strjoin(map->objects, "\n");
	}
	else
	{
		map->objects = ft_strjoin(c, ft_itoa(x));
		map->objects = ft_strjoin(map->objects, " ");
		map->objects = ft_strjoin(map->objects, ft_itoa(y));
		map->objects = ft_strjoin(map->objects, "\n");
	}
}

void	save_objcord(t_map *map, int x, int y)
{
	if (interface_click(map, x, y))
	{
		if (map->player_tex[0]->active == 1)
			cordinator(map, "p ", x, y);
		if (map->player_tex[1]->active == 1)
			cordinator(map, "h ", x, y);
		if (map->player_tex[2]->active == 1)
			cordinator(map, "a ", x, y);
		if (map->gun_tex[0]->active == 1)
			cordinator(map, "g 1 ", x, y);
		if (map->gun_tex[1]->active == 1)
			cordinator(map, "b 1 ", x, y);
		if (map->gun_tex[2]->active == 1)
			cordinator(map, "g 2 ", x, y);
		if (map->gun_tex[3]->active == 1)
			cordinator(map, "b 2 ", x, y);
		if (map->gun_tex[4]->active == 1)
			cordinator(map, "g 3 ", x, y);
		if (map->gun_tex[5]->active == 1)
			cordinator(map, "b 3 ", x, y);
		if (map->enemy_tex[0]->active == 1)
			cordinator(map, "e 1 ", x, y);
		if (map->enemy_tex[1]->active == 1)
			cordinator(map, "e 2 ", x, y);
		if (map->enemy_tex[2]->active == 1)
			cordinator(map, "e 3 ", x, y);
		if (map->enemy_tex[3]->active == 1)
			cordinator(map, "e 4 ", x, y);
		if (map->enemy_tex[4]->active == 1)
			cordinator(map, "e 5 ", x, y);
		if (map->door_tex[8]->active == 1)
			cordinator(map, "l ", x, y);
		if (map->door_tex[9]->active == 1)
			cordinator(map, "b ", x, y);
		printf("new: %s\n", map->objects);
		if (map->door_tex[4]->active == 1 && range_click(&(t_info){x, y,
			WIDTH / 2 - 165, 5}, 330, 150))
		{
			map->validflag = 8;
			cordinator(map, "k 1 ", x, y);//map->door_tex[5]->active = 1;
		}
		if (map->door_tex[5]->active == 1 && range_click(&(t_info){x, y,
			WIDTH / 2 - 165, 5}, 330, 150) && map->click == 1)
		{
			map->validflag = 8;
			cordinator(map, "k 2 ", x, y);
		}
		if (map->door_tex[6]->active == 1 && range_click(&(t_info){x, y,
			WIDTH / 2 - 165, 5}, 330, 150) && map->click == 1)
		{
			map->validflag = 8;
			cordinator(map, "k 3 ", x, y);
		}
		if (map->door_tex[7]->active == 1 && range_click(&(t_info){x, y,
			WIDTH / 2 - 165, 5}, 330, 150) && map->click == 1)
		{
			map->validflag = 8;
			cordinator(map, "k 4 ", x, y);
		}
	}
}

int		catch_click(t_map *map, int x, int y)
{
	section_click(map, x, y); // клик по секциям
	tools_click(map, x, y); // клик по инструментам
	if (map->inter_tex[3]->active == 1)
	{
		map->inter_tex[6]->active = 1;
		blockterxture_click(map, x, y); // клик готовым блокам раздела блоки
		if (!widget_click(map, x, y))// клик по виждету размера раздела блоки
			remove_blocks(map);
		hwidget_click(map, x, y);
	}
	if (map->inter_tex[4]->active == 1)
	{
		terxtures_click(map, x, y); // клики в разделе тексты
		floorker(map, x, y);
	}
	if (map->inter_tex[5]->active == 1 && !map->inter_tex[4]->active && !map->inter_tex[3]->active)
	{
		objects_click(map, x, y);
		if (map->door_tex[10]->active == 1 && map->inter_tex[16]->active == 1)
			get_door(map, x, y);
		save_objcord(map, x, y);
		//printf("obj string : |%s|\n", map->objects);
	}
	if (map->inter_tex[16]->active == 1)
		change_texture_click(map, x, y); // клики по текстурам если блок текстуры активны
	if (some_texture_active(map) == 2)
		change_floor_click(map, x, y); // клики по текстурам если блок пола потолка активны
	if (map->inter_tex[21]->active == 1)
	{
		map->inter_tex[21]->active = 0;
		return (1);
	}
	else
		return (0);
}
