/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 17:48:16 by grinko            #+#    #+#             */
/*   Updated: 2019/09/10 14:42:16 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long long int	sign;
	long long int	temp;

	sign = 1;
	temp = 0;
	while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\v'
	|| *str == '\r' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		temp = (temp * 10) + (*str - '0');
		str++;
	}
	return (temp * sign);
}
