/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_param1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 21:50:35 by ahusk             #+#    #+#             */
/*   Updated: 2021/02/08 20:18:01 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

SDL_Surface		*parsing_param1(t_parser *parser,
						char **arr, bool *b)
{
	char			sub_arr[100];
	SDL_Surface		*tmp;
	SDL_Surface		*tmp1;

	if (*b)
	{
		if (arr[1] != 0)
		{
			slice(sub_arr, arr[1], 1, ft_strlen(arr[1]));
			// printf("1 %s\n", sub_arr);
			if (!(tmp = IMG_Load(sub_arr)))
				error((t_wolf *)parser, SDL_GetError());
			// printf("%s\n", sub_arr);
			tmp1 = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_BGRA32, 0);
			// printf("%p\n", &(texture));
			SDL_FreeSurface(tmp);
		}
		else
			tmp1 = NULL;
		*b = false;
	}
	return (tmp1);
}
