/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writemap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gordey <gordey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:41 by grinko            #+#    #+#             */
/*   Updated: 2020/12/29 15:20:47 by gordey           ###   ########.fr       */
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
		maxlen = ft_strlen("s \"textures/floor/sky1.png\"\n");
		if (write(fd, "s \"textures/floor/sky1.png\"\n", maxlen) != maxlen)
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
		maxlen = ft_strlen("f \"textures/floor/floor1.png\"\n");
		if (write(fd, "f \"textures/floor/floor1.png\"\n", maxlen) != maxlen)
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
	maxlen = ft_strlen("walls: ") + ft_strlen(ft_itoa(num_w)) +
		ft_strlen(count_floor(map, fd)) + 2; // ft_strlen(count_floor(map, fd))
	buffer = malloc(sizeof(char *) * (maxlen));
	buffer = "walls: ";
	buffer = ft_strjoin(buffer, ft_itoa(num_w));
	buffer = ft_strjoin(buffer, "\t");
	buffer = ft_strjoin(buffer, count_floor(map, fd));
	buffer = ft_strjoin(buffer, "\n");
	// printf("return: %s\n",count_floor(map, fd));
	if (write(fd, buffer, maxlen) != maxlen)
		printf("error\n");
	free(buffer);
}

char	*count_floor(t_map *map, int fd)
{
	char *buffer;

	buffer = ft_strjoin("floor: ", "1");
	buffer = ft_strjoin(buffer, "\t");
	buffer = ft_strjoin(buffer, "ceiling: ");
	if (map->ceilingstr)
		buffer = ft_strjoin(buffer, "1");
	else
		buffer = ft_strjoin(buffer, "0");
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
		maxlen = ft_strlen("textures/wall/wall0.png");
	buf = malloc(sizeof(char *) * (maxlen + 3));
	buf = " ";
	if (n->texture->texture_name[0] != NULL)
	{
		buf = ft_strjoin(buf, "\"textures/wall/");
		buf = ft_strjoin(buf, n->texture->texture_name[0]);
		buf = ft_strjoin(buf, "\"");
	}
	else
		buf = ft_strjoin(buf, "\"textures/wall/wall0.png\"");
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
	buf = ft_strjoin(buf, ft_itoa((int)n->x1));
	buf = ft_strjoin(buf, " ");
	buf = ft_strjoin(buf, ft_itoa((int)n->y1));
	buf = ft_strjoin(buf, " ");
	buf = ft_strjoin(buf, ft_itoa((int)n->x2));
	buf = ft_strjoin(buf, " ");
	buf = ft_strjoin(buf, ft_itoa((int)n->y2));
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
		maxlen = ft_strlen(n->texture->type_name) + ft_strlen(write_wall_xy(n))
			+ ft_strlen(ft_itoa(n->wallh)) + ft_strlen(write_wall_text(n)) + 6;
		buffer = malloc(sizeof(char *) * (maxlen));
		buffer = n->texture->type_name;
		buffer = ft_strjoin(buffer, write_wall_xy(n));
		buffer = ft_strjoin(buffer, write_wall_text(n));
		buffer = ft_strjoin(buffer, " ");
		buffer = ft_strjoin(buffer, ft_itoa(n->wallh));
		buffer = ft_strjoin(buffer, " ");
		buffer = ft_strjoin(buffer, ft_itoa(n->type));
		buffer = ft_strjoin(buffer, " ");
		buffer = ft_strjoin(buffer, ft_itoa(n->grnum));
		buffer = ft_strjoin(buffer, "\n");
		if (write(fd, buffer, maxlen) != maxlen)
			printf("error\n");
		free(buffer);
		n = n->nxt;
	}
}

int		writedown_map(t_map *map)
{
	int fd;

	if ((fd = open("./maps/test.txt", O_WRONLY)) == -1)
	{
		printf("Cannot open file.\n");
		exit(1);
	}
	ft_strlen(NULL);
	count_write(map, fd);
	write_walls(map, fd);
	write_floor(map, fd);
	write_ceiling(map, fd);
	write_objects(map, fd);
	close(fd);
	return (0);
}
