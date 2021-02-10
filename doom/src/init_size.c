/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 21:03:34 by ahusk             #+#    #+#             */
/*   Updated: 2021/01/28 21:03:36 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		init_param1(t_parser *parser)
{
	parser->buff.f = false;
	parser->buff.s = false;
	parser->buff.c = false;
	parser->buff.p = false;
	parser->buff.x = false;
}

void			init_size(t_parser *parser, char *l)
{
	char	**arr;
	int		i;

	i = 0;
	arr = ft_strsplit(l, ' ');
	while (arr[i] != 0)
	{
		if (arr[i][0] == 'w')
		{
			parser->count_walls = ft_atoi(arr[i + 1]);
			parser->buff.w_check = false;
			if (!(parser->walls = (t_wall *)malloc(parser->count_walls
				* sizeof(t_wall))))
				error((t_wolf *)parser, ERR_MALLOC);
			parser->buff.w = parser->count_walls;
		}
		free(arr[i]);
		free(arr[i + 1]);
		i += 2;
	}
	init_param1(parser);
	free(arr);
}
