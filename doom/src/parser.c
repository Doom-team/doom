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

void init_size(t_parser *parser, char *l)
{
	char **arr;
	int i;

	i = 0;
	arr = ft_strsplit(l, ' ');
	while (arr[i] != 0)
	{
		if (arr[i][0] == 'w')
		{
			parser->count_walls = ft_atoi(arr[i + 1]);
			parser->walls = (t_wall *)malloc(parser->count_walls * sizeof(t_wall));
			parser->buff.w = parser->count_walls;
		}
		if (arr[i][0] == 'f')
		{
			parser->count_floor = ft_atoi(arr[i + 1]);
			//parser->walls = (t_wall *)malloc(parser->count_walls * sizeof(t_wall));
		}
		i += 2;
	}
}

void parsing(t_parser *parser, char *l)
{
	char **arr;

	arr = ft_strsplit(l, ' ');
	if (arr[0][0] == 'w')
	{
		parser->walls[--parser->buff.w].x1 = ft_atoi(arr[1]) * CUBE;
		parser->walls[parser->buff.w].y1 = ft_atoi(arr[2]) * CUBE;
		parser->walls[parser->buff.w].x2 = ft_atoi(arr[3]) * CUBE;
		parser->walls[parser->buff.w].y2 = ft_atoi(arr[4]) * CUBE;
		if (arr[5] != 0)
		{
			parser->walls[parser->buff.w].texture1 = arr[5];
			if (arr[6] != 0)
				parser->walls[parser->buff.w].texture2 = arr[6];
			else
				parser->walls[parser->buff.w].texture2 = NULL;
		}
		else
		{
			parser->walls[parser->buff.w].texture1 = NULL;
			parser->walls[parser->buff.w].texture2 = NULL;
		}
		parser->walls[parser->buff.w].vert = !(parser->walls[parser->buff.w].x2 - parser->walls[parser->buff.w].x1);
		parser->walls[parser->buff.w].length = sqrt(pow(parser->walls[parser->buff.w].x2 - parser->walls[parser->buff.w].x1, 2) + pow(parser->walls[parser->buff.w].y2 - parser->walls[parser->buff.w].y1, 2));
	}
}

void parser(t_parser *parser, t_wolf *wolf)
{
	char *line;
	int ch;
	int fd;

	ch = 0;
	fd = open("map.txt", O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (ch++ == 0)
			init_size(parser, line);
		else
			parsing(parser, line);
	}
	// //Проверка
	// for (int i = 0; i < parser->count_walls; i++)
	// 	printf("%d %d %d %d %s %s\n", parser->walls[i].x1, parser->walls[i].x2, parser->walls[i].y1, parser->walls[i].y2,
	// 			parser->walls[i].texture1, parser->walls[i].texture2);
	close(fd);
	wolf->walls = parser->walls;
	wolf->count_walls = parser->count_walls;
}
