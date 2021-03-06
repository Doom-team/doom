/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_izero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gordey <gordey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 12:30:42 by gordey            #+#    #+#             */
/*   Updated: 2020/11/04 12:30:51 by gordey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_izero(int *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		s[i] = 0;
		i++;
	}
}
