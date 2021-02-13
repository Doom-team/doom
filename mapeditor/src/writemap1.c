/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writemap1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:41 by grinko            #+#    #+#             */
/*   Updated: 2021/02/13 20:20:57 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

char	*count_floor(t_map *map)
{
	char *buffer;

	buffer = add_text("floor: ", "1", 0);
	buffer = add_text(buffer, " ", 1);
	buffer = add_text(buffer, "ceiling: ", 1);
	if (map->ceilingstr)
		buffer = add_text(buffer, "1", 1);
	else
		buffer = add_text(buffer, "0", 1);
	return (buffer);
}

char	*write_wall_text(t_nod *n)
{
	char	*buf;
	int		maxlen;

	maxlen = 0;
	if (n->type == 2)
		return (NULL);
	if (n->texture->texture_name[0] != NULL)
		maxlen = ft_strlen(n->texture->texture_name[0]);
	else
		maxlen = ft_strlen("../textures/wall/wall1.png");
	buf = malloc(sizeof(char *) + 3);
	buf = " ";
	if (n->texture->texture_name[0] != NULL)
	{
		buf = add_text(buf, "../textures/wall/", 0);
		buf = add_text(buf, n->texture->texture_name[0], 1);
	}
	else
		buf = add_text(buf, "../textures/wall/wall1.png", 0);
	return (buf);
}

char	*write_wall_xy(t_nod *n)
{
	char	*buf;
	int		maxlen;

	maxlen = ft_strlen(ft_itoa((int)n->x1)) + ft_strlen(ft_itoa((int)n->y1)) +
		ft_strlen(ft_itoa((int)n->x2)) + ft_strlen(ft_itoa((int)n->y2));
	buf = malloc(sizeof(char *) * (maxlen + 4));
	buf = " ";
	buf = add_text(buf, ft_itoa((int)n->x1), 3);
	buf = add_text(buf, " ", 1);
	buf = add_text(buf, ft_itoa((int)n->y1), 2);
	buf = add_text(buf, " ", 1);
	buf = add_text(buf, ft_itoa((int)n->x2), 2);
	buf = add_text(buf, " ", 1);
	buf = add_text(buf, ft_itoa((int)n->y2), 2);
	return (buf);
}

void	write_walls(t_map *map, int fd)
{
	t_nod	*n;
	int		maxlen;
	char	*buffer;

	n = map->nod;
	while (n)
	{
		if (n->type == 0 || n->type == 2)
		{
			buffer = n->texture->type_name;
			buffer = add_text(buffer, write_wall_xy(n), 3);
			buffer = write_walls2(buffer, n);
			maxlen = ft_strlen(buffer);
			if (write(fd, buffer, maxlen) != maxlen)
				error("Write Error\n");
		}
		n = n->nxt;
	}
	if (write(fd, map->stairsoutput, ft_strlen(map->stairsoutput))
		!= (int)ft_strlen(map->stairsoutput))
		error("Write Error\n");
}

int		writedown_map(t_map *map)
{
	int fd;

	if ((fd = open("../textures/map.txt", O_WRONLY | O_CREAT
		| O_TRUNC, S_IWRITE | S_IREAD)) == -1)
		error("Cannot open file.\n");
	count_write(map, fd);
	write_walls(map, fd);
	write_floor(map, fd);
	write_ceiling(map, fd);
	write_music(map, fd);
	write_objects(map, fd);
	close(fd);
	return (1);
}
