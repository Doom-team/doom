/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 18:46:39 by grinko            #+#    #+#             */
/*   Updated: 2019/09/11 20:59:45 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *str, const void *src, int c, size_t n)
{
	unsigned char	*cstr;
	unsigned char	*csrc;
	unsigned char	sym;
	size_t			i;

	cstr = (unsigned char *)str;
	csrc = (unsigned char *)src;
	sym = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		cstr[i] = csrc[i];
		if (cstr[i] == sym)
			return (str + i + 1);
		i++;
	}
	return (NULL);
}
