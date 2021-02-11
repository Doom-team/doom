/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writemap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:41 by grinko            #+#    #+#             */
/*   Updated: 2021/02/11 23:19:38 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	write_music(t_map *map, int fd)
{
	int		maxlen;
	char	*buffer;
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
	char	*buffer;

	printf("STR: %s\n", map->objects);
	if (map->objects)
	{
		maxlen = ft_strlen(map->objects);
		if (write(fd, map->objects, maxlen) != maxlen)
			error("Write Error\n");
		free(map->objects);
	}
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
	maxlen = ft_strlen("w ") + ft_strlen(ft_itoa(num_w)) + 1;
	buffer = malloc(sizeof(char *) * (maxlen));
	buffer = "w ";
	buffer = add_text(buffer, ft_itoa(num_w), 3);
	buffer = add_text(buffer, "\n", 1);
	if (write(fd, buffer, maxlen) != maxlen)
		error("Write Error\n");
	free(buffer);
}

char	*count_floor(t_map *map, int fd)
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
	{
		printf("vishel\n");
		return (NULL);
	}
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
			maxlen = ft_strlen(n->texture->type_name) + ft_strlen(write_wall_xy(n))
				+ ft_strlen(ft_itoa(n->wallh)) + ft_strlen(write_wall_text(n)) + 6;
			if (n->type == 2)
				maxlen += ft_strlen(n->texture->texture_name[0]);
			buffer = malloc(sizeof(char *) * (maxlen));
			buffer = n->texture->type_name;
			buffer = add_text(buffer, write_wall_xy(n), 3);
			if (n->type == 2)
				buffer = add_text(buffer, n->texture->texture_name[0], 1);
			else
				buffer = add_text(buffer, write_wall_text(n), 2);
			buffer = add_text(buffer, " ", 1);
			buffer = add_text(buffer, ft_itoa(n->wallh), 2);
			buffer = add_text(buffer, " ", 1);
			buffer = add_text(buffer, ft_itoa(n->type), 2);
			buffer = add_text(buffer, " ", 1);
			buffer = add_text(buffer, ft_itoa(n->grnum), 2);
			buffer = add_text(buffer, "\n", 1);
			if (write(fd, buffer, maxlen) != maxlen)
				error("Write Error\n");
			//free(buffer);
		}
		n = n->nxt;
	}
	if (write(fd, map->stairsoutput, ft_strlen(map->stairsoutput)) != ft_strlen(map->stairsoutput))
		printf("error\n");
}

int		writedown_map(t_map *map)
{
	int fd;

	if ((fd = open("../textures/map.txt", O_WRONLY |  O_CREAT| O_TRUNC, S_IWRITE | S_IREAD)) == -1)
		error("Cannot open file.\n");
	ft_strlen(NULL);
	count_write(map, fd);
	write_walls(map, fd);
	write_floor(map, fd);
	write_ceiling(map, fd);
	write_music(map, fd);
	write_objects(map, fd);
	close(fd);
	return (1);
}
