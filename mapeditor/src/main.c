/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:18 by grinko            #+#    #+#             */
/*   Updated: 2020/12/22 13:39:20 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void i_error()
{
	printf("error");
	exit(1);
}

int main(int ac, char **av)
{
	t_map *map;
	unsigned int t;
	unsigned int t1;

	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (0);
	if(!init_all(map))
		i_error();
	draw(map);
	SDL_UpdateWindowSurface(map->win);

	if (events(map) == 1)
	{
		if (valid_map(map))
			writedown_map(map);
	}
	SDL_DestroyWindow(map->win);
	SDL_Quit();
	return (0);
}
