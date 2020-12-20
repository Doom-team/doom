#include "../include/map.h"
char *count_floor(t_map *map, int fd);

void write_ceiling(t_map *map, int fd)
{
	int maxlen;
	char *buffer;
	int i;

	i = 0;
	while (i < 9)
	{
		if (map->ceilingstr[i])
		{
			maxlen = ft_strlen(map->ceilingstr[i]);
			buffer = malloc(sizeof(char *) * maxlen);
			buffer = map->ceilingstr[i];
			
			if (write(fd, buffer, maxlen) != maxlen)
				printf("error\n");
			free(buffer);
		}
		i++;
	}
}

void write_floor(t_map *map, int fd)
{
	int maxlen;
	char *buffer;
	int i;

	i = 0;
	while (i < 9)
	{
		if (map->floorstr[i])
		{
			maxlen = ft_strlen(map->floorstr[i]);
			buffer = malloc(sizeof(char *) * maxlen);
			buffer = map->floorstr[i];
			printf("buf: %s i: %d\n", buffer, i);
			if (write(fd, buffer, maxlen) != maxlen)
				printf("error\n");
			free(buffer);
		}
		i++;
	}
}

void count_write(t_map *map, int fd)
{
	t_nod *n;
	int maxlen;
	char *buffer;
	int num_w;

	num_w = 0;
	n = map->nod;
	while (n)
	{
		if (ft_strcmp(n->texture->type_name, "wall"))
			num_w++;
		n = n->nxt;
	}
	maxlen = ft_strlen("walls: ") + ft_strlen(ft_itoa(num_w)) + ft_strlen(count_floor(map, fd)) + 2; // ft_strlen(count_floor(map, fd))
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

char *count_floor(t_map *map, int fd)
{
	int i;
	int tmp;
	int omp;
	char *buffer;

	i = -1;
	tmp = 0;
	omp = 0;
	while (++i < 8)
	{
		if (map->floorstr[i])
			tmp++;
		if (map->ceilingstr[i])
			omp++;
	}
	if (tmp == 0)
		buffer = ft_strjoin("floor: ", "1");
	else
		buffer = ft_strjoin("floor: ", ft_itoa(tmp));
	buffer = ft_strjoin(buffer, "\t");
	buffer = ft_strjoin(buffer, "ceiling: ");
	if (omp == 0)
		buffer = ft_strjoin(buffer, "1");
	else
		buffer = ft_strjoin(buffer, ft_itoa(omp));
	return (buffer);
}

char *write_wall_text(t_nod *n)
{
	char *buf;
	int maxlen;

	maxlen = 0;
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
	return(buf);
}

char *write_wall_xy(t_nod *n)
{
	char *buf;
	int maxlen;

	maxlen = ft_strlen(ft_itoa((int)n->x1)) + ft_strlen(ft_itoa((int)n->y1)) + ft_strlen(ft_itoa((int)n->x2)) + ft_strlen(ft_itoa((int)n->y2));
	buf = malloc(sizeof(char *) * (maxlen + 4));
	buf = " ";
	buf = ft_strjoin(buf, ft_itoa((int)n->x1));
	buf = ft_strjoin(buf, " ");
	buf = ft_strjoin(buf, ft_itoa((int)n->y1));
	buf = ft_strjoin(buf, " ");
	buf = ft_strjoin(buf, ft_itoa((int)n->x2));
	buf = ft_strjoin(buf, " ");
	buf = ft_strjoin(buf, ft_itoa((int)n->y2));
	return(buf);
}

void write_walls(t_map *map, int fd)
{
	t_nod *n;
	int maxlen;
	char *buffer;

	n = map->nod;
	while (n)
	{
		maxlen = ft_strlen(n->texture->type_name) + ft_strlen(write_wall_xy(n)) + ft_strlen(ft_itoa(n->wallh)) + ft_strlen(write_wall_text(n)) + 2;
		buffer = malloc(sizeof(char *) * (maxlen));
		buffer = n->texture->type_name;
		buffer = ft_strjoin(buffer, write_wall_xy(n));
		buffer = ft_strjoin(buffer, write_wall_text(n));
		buffer = ft_strjoin(buffer, " ");
		buffer = ft_strjoin(buffer, ft_itoa(n->wallh));
		buffer = ft_strjoin(buffer, "\n");
		if(write(fd, buffer, maxlen) != maxlen)
			printf("error\n");
		free(buffer);
		n = n->nxt;
	}
}

int writedown_map(t_map *map)
{
	int fd;

	if ((fd=open("./maps/test.txt", O_WRONLY))==-1)
	{
		printf ("Cannot open file.\n");
		exit(1);
	}
	count_write(map, fd);
	write_walls(map, fd);
	write_floor(map, fd);
	write_ceiling(map, fd);
	close(fd);
	return (0);
}