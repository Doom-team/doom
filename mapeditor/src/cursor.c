/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:37:37 by grinko            #+#    #+#             */
/*   Updated: 2021/02/09 17:39:59 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

// SDL_Cursor		*load_cursor(t_map *map, int index, int hot_x, int hot_y)
// {
// 	SDL_Cursor		*tmp;
// 	SDL_Cursor		*tmp1;

// 	if (!(tmp = SDL_CreateColorCursor(map->curosr_img[index]->img,
// 	hot_x, hot_y)))
// 		error((char *)SDL_GetError());
// 	tmp1 = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_BGRA32, 0);
// 	SDL_FreeSurface(tmp);
// 	return (tmp1);
// }

void	cursor(t_map *map, int index, int hot_x, int hot_y)
{
	map->cursor = SDL_CreateColorCursor(map->curosr_img[index]->img,
	hot_x, hot_y);
	SDL_SetCursor(map->cursor);
}
