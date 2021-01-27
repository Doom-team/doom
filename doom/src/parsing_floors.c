/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_floors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 19:30:39 by ahusk             #+#    #+#             */
/*   Updated: 2021/01/27 19:30:41 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	parsing_floors(t_parser *parser, char **arr)
{
	char	sub_arr[100];

	if (parser->buff.f)
	{
		if (arr[1] != 0)
		{
			slice(sub_arr, arr[1], 1, ft_strlen(arr[1]));
			if (!(parser->floor_texture = IMG_Load(sub_arr)))
				error((t_wolf *)parser, SDL_GetError());
		}
		else
			parser->floor_texture = NULL;
		parser->buff.f = false;
	}
}
