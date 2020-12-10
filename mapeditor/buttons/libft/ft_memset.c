/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 18:52:24 by grinko            #+#    #+#             */
/*   Updated: 2019/09/10 14:47:45 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *arr, int c, size_t n)
{
	unsigned char *str;
	unsigned char sym;

	str = arr;
	sym = (unsigned char)c;
	while (n--)
		*str++ = (unsigned char)c;
	return (arr);
}
