/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mapi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 15:06:21 by grinko            #+#    #+#             */
/*   Updated: 2019/09/08 15:06:22 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*fresh_s;
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return (NULL);
	if (!(fresh_s = ft_strnew((size_t)ft_strlen(s))))
		return (NULL);
	while (s[i])
	{
		fresh_s[i] = f(i, (char)s[i]);
		i++;
	}
	return (fresh_s);
}
