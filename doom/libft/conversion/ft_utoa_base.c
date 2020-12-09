/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:28:53 by clala             #+#    #+#             */
/*   Updated: 2020/02/15 21:53:21 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_utoa_base(uintmax_t n, int precision)
{
	uint8_t	len;
	char	*str;

	len = ft_uimaxtmaxlen(n);
	precision = (precision - len > 0) ? precision - len : 0;
	len += precision;
	if (!(str = ft_strnewchr(len, '0')))
		return (NULL);
	while (len-- - precision > 0)
	{
		str[len] = ft_itoc(n % 10);
		n /= 10;
	}
	return (str);
}
