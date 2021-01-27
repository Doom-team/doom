/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ceiling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 19:59:48 by ahusk             #+#    #+#             */
/*   Updated: 2021/01/27 19:59:50 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	parsing_ceiling(t_parser *parser, char **arr)
{
	char	sub_arr[100];

	if (parser->buff.c)
	{
		if (arr[1] != 0)
		{
			slice(sub_arr, arr[1], 1, ft_strlen(arr[1]));
			if (!(parser->ceiling_texture = IMG_Load(sub_arr)))
				error((t_wolf *)parser, SDL_GetError());
		}
		else
			parser->ceiling_texture = NULL;
		parser->buff.c = false;
	}
}
