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

static void		init_param1(char **arr, t_parser *parser, int i)
{
	if (arr[i][0] == 'f')
		size_param1(arr, &parser->buff.f, i);
	if (arr[i][0] == 's')
		size_param1(arr, &parser->buff.s, i);
	if (arr[i][0] == 'c')
		size_param1(arr, &parser->buff.c, i);
	if (arr[i][0] == 'p')
		parser->buff.p = ft_atoi(arr[i + 1]);
}

static void		init_param2(char **arr, t_parser *p, int i)
{
	if (arr[i][0] == 'h')
	{
		p->count_healths = ft_atoi(arr[i + 1]);
		if (!(p->healths = (t_param2 *)malloc(p->count_healths
			* sizeof(t_param2))))
			error((t_wolf *)p, ERR_MALLOC);
		p->buff.h = p->count_healths;
	}
	if (arr[i][0] == 'a')
	{
		p->count_armors = ft_atoi(arr[i + 1]);
		if (!(p->armors = (t_param2 *)malloc(p->count_armors
			* sizeof(t_param2))))
			error((t_wolf *)p, ERR_MALLOC);
		p->buff.a = p->count_armors;
	}
	if (arr[i][0] == 'l')
	{
		p->count_lights = ft_atoi(arr[i + 1]);
		if (!(p->lights = (t_param2 *)malloc(p->count_lights
			* sizeof(t_param2))))
			error((t_wolf *)p, ERR_MALLOC);
		p->buff.l = p->count_lights;
	}
}

static void		init_param3(char **arr, t_parser *p, int i)
{
	if (arr[i][0] == 'g')
	{
		p->count_guns = ft_atoi(arr[i + 1]);
		if (!(p->guns = (t_param3 *)malloc(p->count_guns
			* sizeof(t_param3))))
			error((t_wolf *)p, ERR_MALLOC);
		p->buff.g = p->count_guns;
	}
	if (arr[i][0] == 'b')
	{
		p->count_bullets = ft_atoi(arr[i + 1]);
		if (!(p->bullets = (t_param3 *)malloc(p->count_bullets
			* sizeof(t_param3))))
			error((t_wolf *)p, ERR_MALLOC);
		p->buff.b = p->count_bullets;
	}
	if (arr[i][0] == 'e')
	{
		p->count_enemys = ft_atoi(arr[i + 1]);
		if (!(p->enemys = (t_param3 *)malloc(p->count_enemys
			* sizeof(t_param3))))
			error((t_wolf *)parser, ERR_MALLOC);
		p->buff.e = p->count_enemys;
	}
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
			if (!(parser->walls = (t_wall *)malloc(parser->count_walls
				* sizeof(t_wall))))
				error((t_wolf *)parser, ERR_MALLOC);
			parser->buff.w = parser->count_walls;
		}
		if (arr[i][0] == 'c' || arr[i][0] == 's' || arr[i][0] == 'f' ||
			arr[i][0] == 'p')
			init_param1(arr, parser, i);
		if (arr[i][0] == 'h' || arr[i][0] == 'a' || arr[i][0] == 'l')
			init_param2(arr, parser, i);
		if (arr[i][0] == 'g' || arr[i][0] == 'b' || arr[i][0] == 'e')
			init_param3(arr, parser, i);
		free(arr[i]);
		free(arr[i + 1]);
		i += 2;
	}
	free(arr);
}
