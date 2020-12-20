/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 18:49:35 by grinko            #+#    #+#             */
/*   Updated: 2019/09/11 20:58:38 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *str, const void *src, size_t n)
{
	unsigned char	*cstr;
	unsigned char	*csrc;

	cstr = (unsigned char *)str;
	csrc = (unsigned char *)src;
	if (str == src)
		return (str);
	while (n--)
		*cstr++ = *csrc++;
	return (str);
}
