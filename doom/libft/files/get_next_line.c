/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 15:10:51 by clala             #+#    #+#             */
/*   Updated: 2020/02/15 21:53:21 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

static void		copy_to_heapfd(char **heapfd, char *stack)
{
	char		*tmp;
	size_t		len;

	if (!*heapfd)
	{
		*heapfd = ft_strdup(stack);
		return ;
	}
	len = ft_strlen(*heapfd);
	tmp = *heapfd;
	*heapfd = ft_strnew(len + BUFF_SIZE);
	if (*heapfd)
	{
		ft_memcpy(*heapfd, (const void *)tmp, len);
		ft_memcpy(*heapfd + len, (const void *)stack, BUFF_SIZE + 1);
	}
	free(tmp);
}

static void		get_line_from_heapfd(char **heapfd, char **line,
		char *n, int len_before_n)
{
	char		*tmp;
	size_t		len_n;

	if (!(*line = ft_strnew(len_before_n + 1)))
		return ;
	ft_memcpy(*line, *heapfd, len_before_n);
	tmp = *heapfd;
	len_n = ft_strlen(n);
	*heapfd = ft_strnew(len_n);
	ft_memcpy(*heapfd, n + 1, len_n - 1);
	free(tmp);
}

int				get_next_line(int const fd, char **line)
{
	static char	*heap[11000];
	char		stack[BUFF_SIZE + 1];
	int			r;
	char		*n;

	if ((read(fd, stack, 0) < 0) || fd < 0 || fd > 11000)
		return (-1);
	if (!(*line = NULL) && !heap[fd])
		heap[fd] = ft_strnew(0);
	while (!(ft_strchr(heap[fd], '\n')) && (r = read(fd, stack, BUFF_SIZE)))
	{
		stack[r] = '\0';
		copy_to_heapfd(&heap[fd], stack);
		ft_strclr(stack);
	}
	if ((n = ft_strchr(heap[fd], '\n')))
		get_line_from_heapfd(&heap[fd], line, n, n - heap[fd]);
	else
	{
		*line = heap[fd];
		heap[fd] = NULL;
	}
	if (!r && !heap[fd] && *line[0] == '\0')
		ft_strdel(line);
	return (*line ? 1 : 0);
}
