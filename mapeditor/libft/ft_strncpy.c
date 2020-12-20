/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:56:41 by grinko            #+#    #+#             */
/*   Updated: 2019/09/12 12:24:28 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = ft_strlen(src);
	if (i < n)
	{
		ft_memset(dst + i, '\0', n - i);
		return (ft_memcpy(dst, src, i));
	}
	else
		return (ft_memcpy(dst, src, n));
}
