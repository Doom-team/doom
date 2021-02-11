/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:18 by grinko            #+#    #+#             */
/*   Updated: 2021/02/12 01:06:16 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

int		main(int ac, char **av)
{
	t_map			*map;
	unsigned int	t;
	unsigned int	t1;

	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (0);
	if (!init_all(map))
		error_free_s(map, "initialization error!");
	draw(map);
	SDL_UpdateWindowSurface(map->win);
	events(map);
	free_panel1(map);
	SDL_DestroyWindow(map->win);
	SDL_Quit();
	return (0);
}
