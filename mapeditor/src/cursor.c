/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gordey <gordey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:37:37 by grinko            #+#    #+#             */
/*   Updated: 2021/02/07 13:40:18 by gordey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	cursor(t_map *map, int index, int hot_x, int hot_y)
{
	map->cursor = SDL_CreateColorCursor(map->curosr_img[index]->img,
	hot_x, hot_y);
	SDL_SetCursor(map->cursor);
}
