/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_param1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 21:50:35 by ahusk             #+#    #+#             */
/*   Updated: 2021/01/31 00:02:46 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	parsing_param1(t_parser *parser, SDL_Surface *texture,
						char **arr, bool *b)
{
	char	sub_arr[100];

	if (*b)
	{
		if (arr[1] != 0)
		{
			slice(sub_arr, arr[1], 1, ft_strlen(arr[1]));
			if (!(texture = IMG_Load(sub_arr)))
				error((t_wolf *)parser, SDL_GetError());
		}
		else
			texture = NULL;
		*b = false;
	}
}
