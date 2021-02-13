/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:18 by grinko            #+#    #+#             */
/*   Updated: 2021/02/13 20:20:07 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

int		main(void)
{
	t_map			*map;

	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (0);
	if (!init_all(map))
		error("Initialization error!");
	draw(map);
	if (SDL_UpdateWindowSurface(map->win) == -1)
		error("SDL Error");
	events(map);
	printf("end\n");
	exit(0);
	//free_panel1(map);
	SDL_DestroyWindow(map->win);
	SDL_Quit();
	return (0);
}
