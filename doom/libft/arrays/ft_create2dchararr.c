/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create2dchararr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:43:37 by clala             #+#    #+#             */
/*   Updated: 2020/02/15 22:02:50 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_create2dchararr(int rows, int columns)
{
	char	**new;
	int		i;

	if (!(new = (char **)malloc(sizeof(char *) * (rows + 1))))
		return (NULL);
	i = 0;
	while (i < rows)
	{
		if (!(new[i] = ft_strnew(columns)))
		{
			ft_free2dchararr(new, i);
			return (NULL);
		}
		i++;
	}
	return (new);
}
