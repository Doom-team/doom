/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 18:50:33 by grinko            #+#    #+#             */
/*   Updated: 2019/09/11 21:40:42 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *str, const void *src, size_t n)
{
	unsigned char *eat;
	unsigned char *ass;

	eat = (unsigned char *)str;
	ass = (unsigned char *)src;
	if (ass < eat)
		while (n--)
			*(eat + n) = *(ass + n);
	else if (ass > eat)
		ft_memcpy(str, src, n);
	return (str);
}
