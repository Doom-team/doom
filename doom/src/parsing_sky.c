/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_sky.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 20:02:52 by ahusk             #+#    #+#             */
/*   Updated: 2021/01/27 20:02:53 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	parsing_sky(t_parser *parser, char **arr)
{
	char	sub_arr[100];

	if (parser->buff.s)
	{
		if (arr[1] != 0)
		{
			slice(sub_arr, arr[1], 1, ft_strlen(arr[1]));
			if (!(parser->sky_texture = IMG_Load(sub_arr)))
				error((t_wolf *)parser, SDL_GetError());
		}
		else
			parser->sky_texture = NULL;
		parser->buff.s = false;
	}
}
