/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 20:15:20 by ahusk             #+#    #+#             */
/*   Updated: 2020/08/13 20:15:24 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include "../../doom/frameworks/SDL2.framework/Headers/SDL.h"
# include <stdio.h>
# include <fcntl.h>

typedef struct s_buff
{
	int w;
	int f;
} t_buff;

typedef struct s_wall
{
	int x1;
	int x2;
	int y1;
	int y2;
	char *texture1;
	char *texture2;
} t_wall;

typedef struct s_parser
{
	t_wall *walls;
	t_buff buff;
	int count_walls;
	int count_floor;
} t_parser;

void	parser(t_parser *parser);

#endif
