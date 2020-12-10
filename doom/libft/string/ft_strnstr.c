/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:04:19 by clala             #+#    #+#             */
/*   Updated: 2020/02/15 21:53:21 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *str, const char *substr, size_t n)
{
	size_t	i;
	size_t	j;
	char	*s;

	i = 0;
	if (!*substr)
		return ((char *)str);
	while (str[i] && i < n)
	{
		if (str[i] == *substr)
		{
			j = 0;
			s = (char *)str + i;
			while (substr[j] && i < n && str[i] == substr[j])
			{
				i++;
				j++;
			}
			if (j == (size_t)ft_strlen((char *)substr))
				return (s);
			i -= j;
		}
		i++;
	}
	return (NULL);
}
