/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 14:40:57 by grinko            #+#    #+#             */
/*   Updated: 2019/09/10 14:54:26 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	char	*fresh_s;

	i = 0;
	if (!s || !f)
		return (NULL);
	if (!(fresh_s = ft_strnew((size_t)ft_strlen(s))))
		return (NULL);
	while (s[i])
	{
		fresh_s[i] = f((char)(s[i]));
		i++;
	}
	return (fresh_s);
}
