/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_param1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 21:50:35 by ahusk             #+#    #+#             */
/*   Updated: 2021/02/09 16:17:50 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

SDL_Surface		*parsing_param1(t_parser *parser,
						char **arr, bool *b)
{
	SDL_Surface		*tmp;
	SDL_Surface		*tmp1;

	if (arr[1] != 0)
	{
		if (!(tmp = IMG_Load(arr[1])))
			error((t_wolf *)parser, SDL_GetError());
		tmp1 = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_BGRA32, 0);
		SDL_FreeSurface(tmp);
		*b = true;
	}
	else
		tmp1 = NULL;
	return (tmp1);
}
