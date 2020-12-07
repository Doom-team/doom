/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrnew.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 13:40:34 by clala             #+#    #+#             */
/*   Updated: 2019/12/10 18:35:04 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_arr(char **arr, int i)
{
	while (i > -1)
		free(arr[i--]);
	free(arr);
}

char		**ft_strarrnew(int x, int y)
{
	char	**arr;
	int		i;

	i = 0;
	if (!(arr = (char **)malloc(sizeof(char *) * y)))
		return (NULL);
	while (i < y)
	{
		arr[i] = ft_strnew(x);
		if (!arr[i])
		{
			free_arr(arr, i - 1);
			return (NULL);
		}
		i++;
	}
	return (arr);
}
