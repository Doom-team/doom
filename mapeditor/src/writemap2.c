/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writemap2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:41 by grinko            #+#    #+#             */
/*   Updated: 2021/02/13 20:14:15 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	write_music(t_map *map, int fd)
{
	int		maxlen;
	char	*str;

	if (map->musicoutput != 0)
	{
		if (map->musicoutput == 1)
			str = "m ../textures/music/m1.mp3\n";
		else if (map->musicoutput == 2)
			str = "m ../textures/music/m2.mp3\n";
		else if (map->musicoutput == 3)
			str = "m ../textures/music/m3.mp3\n";
		else if (map->musicoutput == 4)
			str = "m ../textures/music/m4.mp3\n";
		maxlen = ft_strlen(str);
		if (write(fd, str, maxlen) != maxlen)
			error("Write Error\n");
	}
	else
	{
		maxlen = ft_strlen("m ../textures/music/m1.mp3\n");
		if (write(fd, "m ../textures/music/m1.mp3\n", maxlen) != maxlen)
			error("Write Error\n");
	}
}

void	write_ceiling(t_map *map, int fd)
{
	int		maxlen;
	char	*buffer;

	if (map->ceilingstr)
	{
		maxlen = ft_strlen(map->ceilingstr);
		buffer = malloc(sizeof(char *) * maxlen);
		buffer = map->ceilingstr;
		if (write(fd, buffer, maxlen) != maxlen)
			error("Write Error\n");
		free(buffer);
	}
	else
	{
		maxlen = ft_strlen("s ../textures/floor/sky1.png\n");
		if (write(fd, "s ../textures/floor/sky1.png\n", maxlen) != maxlen)
			error("Write Error\n");
	}
}

void	write_floor(t_map *map, int fd)
{
	int		maxlen;
	char	*buffer;

	if (map->floorstr)
	{
		maxlen = ft_strlen(map->floorstr);
		buffer = malloc(sizeof(char *) * maxlen);
		buffer = map->floorstr;
		if (write(fd, buffer, maxlen) != maxlen)
			printf("error\n");
		free(buffer);
	}
	else
	{
		maxlen = ft_strlen("f ../textures/floor/floor1.png\n");
		if (write(fd, "f ../textures/floor/floor1.png\n", maxlen) != maxlen)
			error("Write Error\n");
	}
}

void	write_objects(t_map *map, int fd)
{
	int		maxlen;

	maxlen = ft_strlen(map->objects);
	if (write(fd, map->objects, maxlen) != maxlen)
		error("Write Error\n");
}

void	count_write(t_map *map, int fd)
{
	t_nod	*n;
	int		maxlen;
	char	*buffer;
	int		num_w;

	num_w = 0;
	n = map->nod;
	while (n)
	{
		if (ft_strcmp(n->texture->type_name, "wall"))
			num_w++;
		n = n->nxt;
	}
	num_w += map->plus_objects;
	num_w += (map->stirsgroup - 1) * 4;
	buffer = "w ";
	buffer = add_text(buffer, ft_itoa(num_w), 3);
	buffer = add_text(buffer, "\n", 1);
	maxlen = ft_strlen(buffer);
	if (write(fd, buffer, maxlen) != maxlen)
		error("Write Error\n");
	free(buffer);
}
