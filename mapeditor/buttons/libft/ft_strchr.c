/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 17:18:35 by grinko            #+#    #+#             */
/*   Updated: 2019/09/10 14:51:27 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	size_t len;

	len = ft_strlen(str) + 1;
	while (len--)
	{
		if (*str++ == c)
			return ((char *)(str - 1));
	}
	return (NULL);
}
