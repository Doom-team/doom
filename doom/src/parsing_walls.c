/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 19:19:15 by ahusk             #+#    #+#             */
/*   Updated: 2021/02/11 21:59:27 by wendell          ###   ########.fr       */
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

static void		parsing_4param(t_parser *parser, char **arr)
{
	if (arr[1])
	{
		parser->walls[--parser->buff.w].x1 = ft_atoi(arr[1]) / RESIZE;
		if (arr[2])
		{
			parser->walls[parser->buff.w].y1 = ft_atoi(arr[2]) / RESIZE;
			if (arr[3])
			{
				parser->walls[parser->buff.w].x2 = ft_atoi(arr[3]) / RESIZE;
				if (arr[4])
					parser->walls[parser->buff.w].y2 = ft_atoi(arr[4]) / RESIZE;
				else
					error((t_wolf*)parser, ERR_FILE_INVALID);
			}
			else
				error((t_wolf*)parser, ERR_FILE_INVALID);
		}
		else
			error((t_wolf*)parser, ERR_FILE_INVALID);
	}
	else
		error((t_wolf*)parser, ERR_FILE_INVALID);
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
	else
		error((t_wolf*)parser, ERR_FILE_INVALID);
}

static void		parsing_eight(t_parser *parser, char **arr)
{
	if (arr[8])
	{
		if (parser->walls[parser->buff.w].type_flag >= 2)
			parser->walls[parser->buff.w].type_stage = ft_atoi(arr[8]);
		else
			parser->walls[parser->buff.w].squad_stage = ft_atoi(arr[8]);
	}
	else
		error((t_wolf*)parser, ERR_FILE_INVALID);
}

void			parsing_walls(t_parser *parser, char **arr)
{
	SDL_Surface		*tmp;

	if (parser->buff.w == 0)
		return ;
	parsing_4param(parser, arr);
	if (arr[5] != 0)
	{
		if (!(tmp = IMG_Load(arr[5])))
			error((t_wolf *)parser, SDL_GetError());
		parser->walls[parser->buff.w].texture1 =
			SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_BGRA32, 0);
		SDL_FreeSurface(tmp);
	}
	else
		error((t_wolf*)parser, ERR_FILE_INVALID);
	if (arr[6])
		parser->walls[parser->buff.w].h = ft_atoi(arr[6]);
	else
		error((t_wolf*)parser, ERR_FILE_INVALID);
	parsing_type(parser, arr);
	parsing_eight(parser, arr);
	parser->walls[parser->buff.w].active = 1;
	parser->walls[parser->buff.w].opening = 0;
	init_param(parser);
}
