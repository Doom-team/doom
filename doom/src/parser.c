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

static void init_size(t_parser *parser, char *l)
{
	char	**arr;
	int		i;
	int		j;

	i = 0;
	arr = ft_strsplit(l, ' ');
	while (arr[i] != 0)
	{
		if (arr[i][0] == 'w')
		{
			parser->count_walls = ft_atoi(arr[i + 1]);
			if (!(parser->walls = (t_wall *)malloc(parser->count_walls * sizeof(t_wall))))
				error((t_wolf *)parser, ERR_MALLOC);
			parser->buff.w = parser->count_walls;
		}
		if (arr[i][0] == 'f')
		{
			parser->count_floor = ft_atoi(arr[i + 1]);
			//parser->walls = (t_wall *)malloc(parser->count_walls * sizeof(t_wall));
		}
		i += 2;
	}
	free(arr);
}

static void slice(char s[100], char *a,  int from, int to)
{
    int i;
	int j;

	i = 0;
	j = from;
	while (j <= to - 2)
		s[i++] = a[j++];
	s[i] = '\0';
}

static void parsing(t_parser *parser, char *l)
{
	char	**arr;
	char	sub_arr[100];
	int		i;
	int		j;
	// char	sub_arr_2[100];

	arr = ft_strsplit(l, ' ');
	if (arr[0][0] == 'w')
	{
		parser->walls[--parser->buff.w].x1 = ft_atoi(arr[1]) * CUBE;
		parser->walls[parser->buff.w].y1 = ft_atoi(arr[2]) * CUBE;
		parser->walls[parser->buff.w].x2 = ft_atoi(arr[3]) * CUBE;
		parser->walls[parser->buff.w].y2 = ft_atoi(arr[4]) * CUBE;
		if (arr[5] != 0)
		{
			slice(sub_arr, arr[5], 1, ft_strlen(arr[5]));
			if (!(parser->walls[parser->buff.w].texture1 = IMG_Load(sub_arr)))
				error((t_wolf *)parser, SDL_GetError());
		// 	if (arr[6] != 0)
		// 	{
		// 		slice(sub_arr_2, arr[5], 1, ft_strlen(arr[6]));
		// 		if (!(parser->walls[parser->buff.w].texture2 = IMG_Load(arr[6])))
		// 			error((t_wolf *)parser, SDL_GetError());
		// 	}
		// 	else
		// 		parser->walls[parser->buff.w].texture2 = NULL;
		}
		else
		{
			parser->walls[parser->buff.w].texture1 = NULL;
			// parser->walls[parser->buff.w].texture2 = NULL;
		}
		if (arr[6])
			parser->walls[parser->buff.w].h = ft_atoi(arr[6]);
		if (arr[7])
		{
			parser->walls[parser->buff.w].type_flag = ft_atoi(arr[7]);
		}
		if (arr[8])
		{
			parser->walls[parser->buff.w].squad_stage = ft_atoi(arr[8]);
		}
		parser->walls[parser->buff.w].vert = !(parser->walls[parser->buff.w].x2 - parser->walls[parser->buff.w].x1);
		parser->walls[parser->buff.w].length = sqrt(pow(parser->walls[parser->buff.w].x2 - parser->walls[parser->buff.w].x1, 2) + pow(parser->walls[parser->buff.w].y2 - parser->walls[parser->buff.w].y1, 2));
	}
	free(arr);
}

void parser(t_parser *parser, t_wolf *wolf)
{
	char	*line;
	int		ch;
	int		fd;

	ch = 0;
	fd = open("map.txt", O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (ch++ == 0)
			init_size(parser, line);
		else
			parsing(parser, line);
	}
	//Проверка
	// for (int i = 0; i < parser->count_walls; i++)
	// 	printf("%d %d %d %d %s %s\n", parser->walls[i].x1, parser->walls[i].x2, parser->walls[i].y1, parser->walls[i].y2,
	// 			parser->walls[i].texture1, parser->walls[i].texture2);
	close(fd);
	free(line);
	wolf->walls = parser->walls;
	wolf->count_walls = parser->count_walls;
}