/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:18 by grinko            #+#    #+#             */
/*   Updated: 2021/02/08 16:10:50 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	i_error(void)
{
	printf("error");
	exit(1);
}

void	music(Mix_Music *music)
{
	Mix_Volume(0, 32);
	Mix_PlayMusic(music, -1);
	Mix_VolumeMusic(5);
}

void	wichonemusic(t_map *map)
{
	if (map->musicflag == 1)
		music(map->music[0]);
	else if (map->musicflag == 2)
		music(map->music[1]);
	else if (map->musicflag == 3)
		music(map->music[2]);
	else if (map->musicflag == 4)
		music(map->music[3]);
}

int		main(int ac, char **av)
{
	t_map			*map;
	unsigned int	t;
	unsigned int	t1;

	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (0);
	if (!init_all(map))
		i_error();
	draw(map);
	SDL_UpdateWindowSurface(map->win);
	events(map);
	// if (events(map) == 1 && valid_map(map))
	// {
	// 	writedown_map(map);
	// 	// continue ;
	// }
	free_panel(map);
	SDL_DestroyWindow(map->win);
	SDL_Quit();
	return (0);
}
