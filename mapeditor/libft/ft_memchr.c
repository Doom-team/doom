/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 18:46:56 by grinko            #+#    #+#             */
/*   Updated: 2019/09/10 15:03:10 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char *ss;
	unsigned char sym;

	ss = (unsigned char *)str;
	sym = (unsigned char)c;
	if (str || n)
	{
		while (n--)
		{
			if (*ss == sym)
				return (ss);
			ss++;
		}
	}
	return (NULL);
}
