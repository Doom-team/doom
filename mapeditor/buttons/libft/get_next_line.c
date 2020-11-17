/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gordey <gordey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 20:59:16 by grinko            #+#    #+#             */
/*   Updated: 2020/11/04 12:37:57 by gordey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	goodwork(char **str, char **line, int vitalya, int fd)
{
	int		len;
	char	*tmp;

	len = 0;
	if (vitalya == 0 && str[fd] == NULL)
		return (0);
	str = &str[fd];
	while ((*str)[len] != '\n' && (*str)[len] != '\0')
		len++;
	if ((*str)[len] == '\n')
	{
		*line = ft_strsub(*str, 0, len);
		tmp = ft_strdup(&((*str)[len + 1]));
		free(*str);
		*str = tmp;
		if ((*str)[0] == '\0')
			ft_strdel(str);
	}
	else
	{
		*line = ft_strdup(*str);
		ft_strdel(str);
	}
	return (1);
}

int	get_next_line(const int fd, char **line)
{
	static char	*str[ARR_SIZE];
	char		buff[BUFF_SIZE + 1];
	char		*oleg;
	int			vitalya;

	if (!line || line == NULL)
		return (-1);
	while ((vitalya = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[vitalya] = '\0';
		if (str[fd] == NULL)
			str[fd] = ft_strdup(buff);
		else if (str[fd] != NULL)
		{
			oleg = ft_strjoin(str[fd], buff);
			free(str[fd]);
			str[fd] = oleg;
		}
		if (ft_strchr(str[fd], '\n'))
			break ;
	}
	if (vitalya < 0)
		return (-1);
	return (goodwork(str, line, vitalya, fd));
}
