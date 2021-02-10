/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 19:19:15 by ahusk             #+#    #+#             */
/*   Updated: 2021/02/08 19:41:34 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		init_param(t_parser *parser)
{
	parser->walls[parser->buff.w].vert = !(parser->walls[parser->buff.w].x2 -
		parser->walls[parser->buff.w].x1);
	parser->walls[parser->buff.w].length =
		sqrt(pow(parser->walls[parser->buff.w].x2 -
			parser->walls[parser->buff.w].x1, 2) +
			pow(parser->walls[parser->buff.w].y2 -
			parser->walls[parser->buff.w].y1, 2));
}

static void		parsing_type(t_parser *parser, char **arr)
{
	if (arr[7])
	{
		parser->walls[parser->buff.w].type_flag = ft_atoi(arr[7]);
		if (parser->walls[parser->buff.w].type_flag >= 3)
		{
			parser->walls[parser->buff.w].realx =
				parser->walls[parser->buff.w].x1;
			parser->walls[parser->buff.w].realy =
				parser->walls[parser->buff.w].y1;
		}
	}
}

void			parsing_walls(t_parser *parser, char **arr)
{
	SDL_Surface		*tmp;

	if (parser->buff.w == 0)
		return ;
	parser->walls[--parser->buff.w].x1 = ft_atoi(arr[1]) / RESIZE;
	parser->walls[parser->buff.w].y1 = ft_atoi(arr[2]) / RESIZE;
	parser->walls[parser->buff.w].x2 = ft_atoi(arr[3]) / RESIZE;
	parser->walls[parser->buff.w].y2 = ft_atoi(arr[4]) / RESIZE;
	if (arr[5] != 0)
	{
		if (!(tmp = IMG_Load(arr[5])))
			error((t_wolf *)parser, SDL_GetError());
		parser->walls[parser->buff.w].texture1 =
			SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_BGRA32, 0);
		SDL_FreeSurface(tmp);
	}
	if (arr[6])
		parser->walls[parser->buff.w].h = ft_atoi(arr[6]);
	parsing_type(parser, arr);
	if (arr[8])
		parser->walls[parser->buff.w].squad_stage = ft_atoi(arr[8]);
	init_param(parser);
}
