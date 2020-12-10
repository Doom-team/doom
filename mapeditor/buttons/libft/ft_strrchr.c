/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 17:19:01 by grinko            #+#    #+#             */
/*   Updated: 2019/09/07 17:19:03 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	size_t	len;
	char	*last;

	last = NULL;
	len = ft_strlen(str) + 1;
	while (len--)
	{
		if (*str++ == c)
			last = (char *)(str - 1);
	}
	return (last);
}
