/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 12:40:19 by clala             #+#    #+#             */
/*   Updated: 2020/02/15 21:53:21 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char			*dupl;
	unsigned int	len;

	len = 0;
	while (src[len])
		len++;
	dupl = (char *)malloc(sizeof(char) * (len + 1));
	if (!dupl)
		return (NULL);
	len = 0;
	while (src[len])
	{
		dupl[len] = src[len];
		len++;
	}
	dupl[len] = '\0';
	return (dupl);
}
