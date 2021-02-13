/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:37:37 by grinko            #+#    #+#             */
/*   Updated: 2021/02/13 15:20:05 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	cursor(t_map *map, int index, int hot_x, int hot_y)
{
	map->cursor = SDL_CreateColorCursor(map->curosr_img[index]->img,
	hot_x, hot_y);
	if (!map->cursor)
		error("SDL Error");
	SDL_SetCursor(map->cursor);
}
