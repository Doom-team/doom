/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 12:12:00 by clala             #+#    #+#             */
/*   Updated: 2020/02/15 21:53:21 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_atoi_base(char *str, int base)
{
	int				i;
	int				j;
	int				num;

	num = 0;
	j = 0;
	i = 0;
	while (*str && ((*str >= 9 && *str <= 13) || *str == ' '))
		str++;
	while (str[i] && ft_strchr(HEX_CHARS, ft_toupper(str[i])))
	{
		while (HEX_CHARS[j])
		{
			if (ft_toupper(str[i]) == HEX_CHARS[j])
			{
				num = num * base + j;
				j = 0;
				break ;
			}
			j++;
		}
		i++;
	}
	return (num);
}
