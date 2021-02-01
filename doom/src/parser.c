/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 19:38:26 by ahusk             #+#    #+#             */
/*   Updated: 2021/01/30 23:54:55 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"
#include "../../doom/libft/includes/get_next_line.h"

static void		help_parsing(t_parser *parser, char **arr)
{
	if (arr[0][0] == 'h')
		parsing_param2(parser->healths, arr, &parser->buff.h);
	if (arr[0][0] == 'a')
		parsing_param2(parser->armors, arr, &parser->buff.a);
	if (arr[0][0] == 'l')
		parsing_param2(parser->lights, arr, &parser->buff.l);
	if (arr[0][0] == 'p')
		parsing_player(&parser->player, arr, &parser->buff.p);
}

static void		parsing(t_parser *parser, char *l)
{
	char	**arr;

	arr = ft_strsplit(l, ' ');
	help_parsing(parser, arr);
	if (arr[0][0] == 'w')
		parsing_walls(parser, arr);
	if (arr[0][0] == 'f')
		parsing_param1(parser, parser->floor_texture, arr, &parser->buff.f);
	if (arr[0][0] == 'c')
		parsing_param1(parser, parser->ceiling_texture, arr, &parser->buff.c);
	if (arr[0][0] == 's')
		parsing_param1(parser, parser->sky_texture, arr, &parser->buff.s);
	if (arr[0][0] == 'g')
		parsing_param3(parser->guns, arr, &parser->buff.g);
	if (arr[0][0] == 'b')
		parsing_param3(parser->bullets, arr, &parser->buff.b);
	if (arr[0][0] == 'e')
		parsing_param3(parser->enemys, arr, &parser->buff.e);
	free(arr);
}

void			parser(t_wolf *wolf)
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
	}
	close(fd);
	free(line);
}
