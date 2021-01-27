/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 19:38:26 by ahusk             #+#    #+#             */
/*   Updated: 2020/12/16 22:05:22 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"
#include "../../doom/libft/includes/get_next_line.h"

static void		helper(char **arr, bool *b, int i)
{
	if (ft_atoi(arr[i + 1]) > 0)
		*b = true;
	else
		*b = false;
}

static void		init_size(t_parser *parser, char *l)
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
			if (!(parser->walls = (t_wall *)malloc(parser->count_walls
				* sizeof(t_wall))))
				error((t_wolf *)parser, ERR_MALLOC);
			parser->buff.w = parser->count_walls;
		}
		if (arr[i][0] == 'f')
			helper(arr, &parser->buff.f, i);
		if (arr[i][0] == 's')
			helper(arr, &parser->buff.s, i);
		if (arr[i][0] == 'c')
			helper(arr, &parser->buff.c, i);
		i += 2;
	}
	free(arr);
}

static void		parsing(t_parser *parser, char *l)
{
	char	**arr;

	arr = ft_strsplit(l, ' ');
	if (arr[0][0] == 'w')
		parsing_walls(parser, arr);
	if (arr[0][0] == 'f')
		parsing_floors(parser, arr);
	if (arr[0][0] == 'c')
		parsing_ceiling(parser, arr);
	if (arr[0][0] == 's')
		parsing_sky(parser, arr);
	free(arr);
}

void			parser(t_wolf *wolf)
{
	char		*line;
	int			ch;
	int			fd;
	t_parser	parser;

	ch = 0;
	fd = open("map.txt", O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (ch++ == 0)
			init_size(&parser, line);
		else
			parsing(&parser, line);
	}
	close(fd);
	free(line);
	wolf->walls = parser.walls;
	wolf->count_walls = parser.count_walls;
}
