/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:46:01 by clala             #+#    #+#             */
/*   Updated: 2020/02/20 18:59:05 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int			ft_printf(const char *format, ...)
{
	va_list	ap;
	int		written;

	va_start(ap, format);
	written = ft_vdprintf(1, format, &ap);
	va_end(ap);
	return (written);
}

int			ft_dprintf(int fd, const char *format, ...)
{
	va_list	ap;
	int		written;

	va_start(ap, format);
	written = ft_vdprintf(fd, format, &ap);
	va_end(ap);
	return (written);
}

int			ft_asprintf(char **s, const char *format, ...)
{
	int		written;
	va_list	ap;

	va_start(ap, format);
	written = ft_vasprintf(s, format, &ap);
	va_end(ap);
	return (written);
}
