/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writemap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:41 by grinko            #+#    #+#             */
/*   Updated: 2021/02/10 22:12:21 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

// void ceiling(t_map *map, char buf, t_nod *n)
// {
// 	int max_x;
// 	int max_y;
// 	int min_x;
// 	int min_y;

// 	n = map->nod;
// 	max_x = -WIDTH;
// 	max_y = -HEIGHT;
// 	min_x = WIDTH;
// 	min_y = HEIGHT;
// 	while (n)
// 	{
// 		if (n->x1 >= max_x)
// 			max_x = n->x1;
// 		else if (n->x2 >= max_x)
// 			max_x = n->x2;
// 		if (n->x1 <= min_x)
// 			min_x = n->x1;
// 		else if (n->x2 <= min_x)
// 			min_x = n->x2;
// 		if (n->y1 >= max_y)
// 			max_y = n->y1;
// 		else if (n->y2 >= max_y)
// 			max_y = n->y2;
// 		if (n->y1 <= min_y)
// 			min_y = n->y1;
// 		else if (n->y2 <= min_y)
// 			min_y = n->y2;
// 		n = n->nxt;
// 	}
// 	buf = ft_strjoin("c ", ft_itoa(min_x));
// 	buf = ft_strjoin(buf, " ");
// 	buf = ft_strjoin(buf, ft_itoa(min_y));
// 	buf = ft_strjoin(buf, " ");
// 	buf = ft_strjoin(buf, ft_itoa(max_x));
// 	buf = ft_strjoin(buf, " ");
// 	buf = ft_strjoin(buf, ft_itoa(min_y));
// 	buf = ft_strjoin(buf, "\n");
// 	buf = ft_strjoin("c ", ft_itoa(min_x));
// 	buf = ft_strjoin(buf, " ");
// 	buf = ft_strjoin(buf, ft_itoa(max_y));
// 	buf = ft_strjoin(buf, " ");
// 	buf = ft_strjoin(buf, ft_itoa(man_x));
// 	buf = ft_strjoin(buf, " ");
// 	buf = ft_strjoin(buf, ft_itoa(min_y));
// 	buf = ft_strjoin(buf, "\n");
// }

void	write_ceiling(t_map *map, int fd)
{
	int		maxlen;
	char	*buffer;
	t_nod	*n;

	if (map->ceilingstr)
	{
		maxlen = ft_strlen(map->ceilingstr);
		buffer = malloc(sizeof(char *) * maxlen);
		buffer = map->ceilingstr;
		if (write(fd, buffer, maxlen) != maxlen)
			printf("error\n");
		free(buffer);
	}
	else
	{
		maxlen = ft_strlen("s ../../textures/floor/sky1.png\n");
		if (write(fd, "s ../../textures/floor/sky1.png\n", maxlen) != maxlen)
			printf("error\n");
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
		maxlen = ft_strlen("f ../../textures/floor/floor1.png\n");
		if (write(fd, "f ../../textures/floor/floor1.png\n", maxlen) != maxlen)
			printf("error\n");
	}
}

void	write_objects(t_map *map, int fd)
{
	int		maxlen;
	char	*buffer;

	if (map->objects)
	{
		maxlen = ft_strlen(map->objects);
		buffer = malloc(sizeof(char *) * maxlen);
		buffer = map->objects;
		if (write(fd, buffer, maxlen) != maxlen)
			printf("error\n"); 
		free(buffer);
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
	maxlen = ft_strlen("w ") + ft_strlen(ft_itoa(num_w)) + 1; // ft_strlen(count_floor(map, fd))
	buffer = malloc(sizeof(char *) * (maxlen));
	buffer = "w ";
	buffer = add_text(buffer, ft_itoa(num_w), 3);
	// buffer = add_text(buffer, " ", 1);
	//buffer = add_text(buffer, count_floor(map, fd), 2);
	buffer = add_text(buffer, "\n", 1);
	// printf("return: %s\n",count_floor(map, fd));
	if (write(fd, buffer, maxlen) != maxlen)
		printf("error\n");
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
		return (n->texture->texture_name[1]);
	if (n->texture->texture_name[0] != NULL)
		maxlen = ft_strlen(n->texture->texture_name[0]);
	else
		maxlen = ft_strlen("../../textures/wall/wall0.png");
	buf = malloc(sizeof(char *) * (maxlen + 3));
	buf = " ";
	if (n->texture->texture_name[0] != NULL)
	{
		buf = add_text(buf, "../../textures/wall/", 0);
		buf = add_text(buf, n->texture->texture_name[0], 1);
	}
	else
		buf = add_text(buf, "../../textures/wall/wall0.png", 0);
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
		if (n->type == 0)
		{
			maxlen = ft_strlen(n->texture->type_name) + ft_strlen(write_wall_xy(n))
				+ ft_strlen(ft_itoa(n->wallh)) + ft_strlen(write_wall_text(n)) + 6;
			buffer = malloc(sizeof(char *) * (maxlen));
			buffer = n->texture->type_name;
			buffer = add_text(buffer, write_wall_xy(n), 3);
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
			free(buffer);
		}
		n = n->nxt;
	}
	if (write(fd, map->stairsoutput, ft_strlen(map->stairsoutput)) != ft_strlen(map->stairsoutput))
		printf("error\n");
}

int		writedown_map(t_map *map)
{
	int fd;

	if ((fd = open("./maps/test.txt", O_WRONLY)) == -1)
		error("Cannot open file.\n");
	ft_strlen(NULL);
	count_write(map, fd);
	write_walls(map, fd);
	write_floor(map, fd);
	write_ceiling(map, fd);
	write_objects(map, fd);
	close(fd);
	return (1);
}
