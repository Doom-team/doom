/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 20:25:18 by clala             #+#    #+#             */
/*   Updated: 2019/11/27 20:26:32 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char				*ft_uitoa_base(unsigned int value, int base)
{
	char			*str;
	int				size;
	int				flag;
	unsigned int	tmp;

	flag = 0;
	size = 0;
	if (base < 2 || base > 16)
		return (0);
	tmp = value;
	while (tmp /= base)
		size++;
	size = size + flag + 1;
	str = (char *)malloc(sizeof(char) * size + 1);
	str[size] = '\0';
	if (flag == 1)
		str[0] = '-';
	while (size > flag)
	{
		str[size - 1] = HEX_CHARS[ft_abs(value % base)];
		size--;
		value /= base;
	}
	return (str);
}
