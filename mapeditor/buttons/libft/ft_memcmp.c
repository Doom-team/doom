/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 18:48:13 by grinko            #+#    #+#             */
/*   Updated: 2019/09/10 14:44:06 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *a1, const void *a2, size_t n)
{
	unsigned char *b1;
	unsigned char *b2;

	b1 = (unsigned char *)a1;
	b2 = (unsigned char *)a2;
	while (n--)
	{
		if (*b1 != *b2)
			return ((int)(*b1 - *b2));
		b1++;
		b2++;
	}
	return (0);
}
