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

void		parsing(t_parser *parser, char *l)
{
	char	**arr;

	arr = ft_strsplit(l, ' ');
	if (arr[0][0] == 'x')
		parsing_param2(&parser->exit, arr, &parser->buff.x);
	if (arr[0][0] == 'p')
		parsing_param2(&parser->player, arr, &parser->buff.p);
	if (arr[0][0] == 'w')
		parsing_walls(parser, arr);
	if (arr[0][0] == 'f' && !parser->buff.f)
		parser->floor_texture = parsing_param1(parser, arr, &parser->buff.f);
	if (arr[0][0] == 'm' && !parser->buff.m)
		parser->music = parsing_music(parser, arr, &parser->buff.m);
	if (arr[0][0] == 'c' && !parser->buff.c)
		parser->ceiling_texture = parsing_param1(parser, arr, &parser->buff.c);
	if (arr[0][0] == 's' && !parser->buff.s)
		parser->sky_texture = parsing_param1(parser, arr, &parser->buff.s);
	free_2dchararr_terminated(arr);
}

void		parser(t_wolf *wolf)
{
	char		*line;
	int			ch;
	int			fd;

	ch = 0;
	if ((fd = open("../textures/map.txt", O_RDONLY)) == -1)
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
	check_valid(&wolf->p->buff);
	free(line);
}
