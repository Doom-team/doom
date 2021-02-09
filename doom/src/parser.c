/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 19:38:26 by ahusk             #+#    #+#             */
/*   Updated: 2021/02/08 20:20:39 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"
#include "../../doom/libft/includes/get_next_line.h"

void		help_parsing(t_parser *parser, char **arr)
{
	if (arr[0][0] == 'h')
		parsing_param2(parser->healths, arr, &parser->buff.h);
	if (arr[0][0] == 'a')
		parsing_param2(parser->armors, arr, &parser->buff.a);
	if (arr[0][0] == 'k')
		parsing_param3(parser->keys, arr, &parser->buff.k);
	if (arr[0][0] == 'x')
		parsing_player(&parser->exit, arr, &parser->buff.x);
	if (arr[0][0] == 'p')
		parsing_player(&parser->player, arr, &parser->buff.p);
}

void		parsing(t_parser *parser, char *l)
{
	char	**arr;

	arr = ft_strsplit(l, ' ');
	help_parsing(parser, arr);
	if (arr[0][0] == 'w')
		parsing_walls(parser, arr);
	if (arr[0][0] == 'f')
		parser->floor_texture = parsing_param1(parser, arr, &parser->buff.f);
	if (arr[0][0] == 'c')
		parser->ceiling_texture = parsing_param1(parser, arr, &parser->buff.c);
	if (arr[0][0] == 's')
		parser->sky_texture = parsing_param1(parser, arr, &parser->buff.s);
	if (arr[0][0] == 'g')
		parsing_param3(parser->guns, arr, &parser->buff.g);
	if (arr[0][0] == 'b')
		parsing_param3(parser->bullets, arr, &parser->buff.b);
	if (arr[0][0] == 'e')
		parsing_param3(parser->enemys, arr, &parser->buff.e);
	free_2dchararr_terminated(arr);
}

void		parser(t_wolf *wolf)
{
	char		*line;
	int			ch;
	int			fd;

	ch = 0;
	if ((fd = open("test.txt", O_RDONLY)) == -1)
		error((t_wolf *)wolf->p, ERR_FILE_OPEN);
	while (get_next_line(fd, &line) > 0)
	{
		if (ch++ == 0)
			init_size(wolf->p, line);
		else
			parsing(wolf->p, line);
		free(line);
	}
	close(fd);
	free(line);
}
