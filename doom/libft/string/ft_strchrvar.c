/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrvar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:43:37 by clala             #+#    #+#             */
/*   Updated: 2020/02/15 21:53:21 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchrvar(const char *str, char *format, ...)
{
	va_list	ap;
	int		n;
	int		c;
	char	*s;

	s = NULL;
	va_start(ap, format);
	n = ft_atoi((const char *)format);
	while (n-- > 0)
	{
		c = va_arg(ap, int);
		if ((s = ft_strchr(str, c)))
			return (s);
	}
	va_end(ap);
	return (s);
}
