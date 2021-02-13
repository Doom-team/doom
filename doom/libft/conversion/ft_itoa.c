/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <ahusk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:47:03 by ahusk             #+#    #+#             */
/*   Updated: 2020/02/15 21:53:21 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n)
{
	int		sign;
	char	*s;
	int		len;
	int		i;

	len = ft_ilen(n);
	sign = n;
	if (!(s = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = 0;
	while (n)
	{
		s[i++] = ft_abs(n % 10) + '0';
		n /= 10;
	}
	if (sign < 0)
		s[i++] = '-';
	else if (sign == 0)
		s[i++] = '0';
	s[i] = '\0';
	ft_strrev(s);
	return (s);
}
