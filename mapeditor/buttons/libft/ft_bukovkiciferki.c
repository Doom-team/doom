/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bukovkiciferki.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 17:55:45 by grinko            #+#    #+#             */
/*   Updated: 2019/09/13 18:16:18 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "stdio.h"

int	ft_bukovkiciferki(const char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (!(str[i] >= 'a' && str[i] <= 'z') &&
		!(str[i] >= 'A' && str[i] <= 'Z')
		&& !(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}
