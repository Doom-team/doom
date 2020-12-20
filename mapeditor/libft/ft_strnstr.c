/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 17:21:20 by grinko            #+#    #+#             */
/*   Updated: 2019/09/10 14:58:23 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t len)
{
	size_t i;
	size_t lenstr2;

	i = 0;
	lenstr2 = ft_strlen(str2);
	if (!*str2)
		return ((char *)(str1));
	if (str2 == str1)
		return ((char *)(str1));
	while (*str1 && len-- >= lenstr2)
	{
		while (str1[i] == str2[i] && str2[i])
			i++;
		if (str2[i] == '\0')
			return ((char *)str1);
		i = 0;
		str1++;
	}
	return (NULL);
}
