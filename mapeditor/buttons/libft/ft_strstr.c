/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 17:19:13 by grinko            #+#    #+#             */
/*   Updated: 2019/09/10 15:06:26 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str1, const char *str2)
{
	size_t i;

	i = 0;
	if (!*str2)
		return ((char *)(str1));
	if (str2 == str1)
		return ((char *)(str1));
	while (*str1)
	{
		while (str1[i] == str2[i] && str2[i])
			i++;
		if (!str2[i])
			return ((char *)str1);
		str1++;
		i = 0;
	}
	return (NULL);
}
