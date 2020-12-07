/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintfmt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:24:34 by clala             #+#    #+#             */
/*   Updated: 2020/02/15 21:53:27 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_bintfmt(char *number)
{
	int		i;

	i = 0;
	while (number[i] && number[i] != '.')
		++i;
	if (ft_strchr(number, '.'))
	{
		number = ft_strtrimend(number, "0");
		number = ft_strnlstrip(number, "0", i - 1);
	}
	else
		number = ft_strnlstrip(number, "0", i - 1);
	return (number);
}
