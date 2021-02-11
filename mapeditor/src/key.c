/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:16 by grinko            #+#    #+#             */
/*   Updated: 2021/02/12 01:06:02 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

int		mkey(int key, int x, int y, t_map *map)
{
	if (key == 1)
	{
		if (map->block_tex[5]->active == 1)
			stairs_editor(map, x, y);
		if (map->inter_tex[6]->active)
			wall_editor(map, x, y);
		if (map->inter_tex[8]->active)
			remove_tool(map, x, y);
		if (map->inter_tex[4]->active)
			change_texture(map, x, y);
		if (some_texture_active(map) == 4)
			change_texture(map, x, y);
	}
	SDL_UpdateWindowSurface(map->win);
	return (0);
}

int		pkey(int key, t_map *map)
{
	if (key == 27)
		SDL_Quit();
	return (0);
}

void	i_error(void)
{
	printf("error");
	exit(1);
}

void	music(Mix_Music *music)
{
	printf("zashel\n");
	Mix_Volume(0, 32);
	Mix_PlayMusic(music, -1);
	Mix_VolumeMusic(5);
}

void	wichonemusic(t_map *map)
{
	printf("music: %d\n", map->musicflag);
	if (map->musicflag == 1)
		music(map->music[0]);
	else if (map->musicflag == 2)
		music(map->music[1]);
	else if (map->musicflag == 3)
		music(map->music[2]);
	else if (map->musicflag == 4)
		music(map->music[3]);
}
