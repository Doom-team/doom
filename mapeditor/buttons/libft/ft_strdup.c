/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 18:59:05 by grinko            #+#    #+#             */
/*   Updated: 2019/09/10 14:55:49 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *arr)
{
	char	*str;
	size_t	i;

	if (!(str = (char *)malloc(sizeof(char) * ft_strlen(arr) + 1)))
		return (NULL);
	if (str)
	{
		i = 0;
		while (arr[i])
		{
			str[i] = arr[i];
			i++;
		}
		str[i] = '\0';
	}
	return (str);
}
