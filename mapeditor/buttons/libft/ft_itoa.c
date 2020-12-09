/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 17:32:45 by grinko            #+#    #+#             */
/*   Updated: 2019/09/11 19:56:53 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len(int n)
{
	size_t	len;

	len = 0;
	if (n < 0)
		len++;
	while (n > 9 || n < -9)
	{
		n = n / 10;
		len++;
	}
	len++;
	return (len);
}

static int		ft_num(int n)
{
	int	num;

	num = 0;
	if (n < 0)
		num = n % 10 * -1 + 48;
	else
		num = n % 10 + 48;
	return (num);
}

char			*ft_itoa(int n)
{
	size_t	ass;
	char	*str;

	ass = ft_len(n) - 1;
	if (!(str = ft_strnew(ass + 1)))
		return (NULL);
	while (n > 9 || n < -9)
	{
		str[ass--] = ft_num(n);
		n = n / 10;
	}
	str[ass] = ft_num(n);
	if (n < 0)
		str[ass - 1] = '-';
	return (str);
}
