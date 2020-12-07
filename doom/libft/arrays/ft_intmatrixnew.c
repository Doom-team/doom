/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intmatrixnew.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 13:40:24 by clala             #+#    #+#             */
/*   Updated: 2019/12/08 13:40:26 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_arr(int **arr, int i)
{
	while (i > -1)
		free(arr[i--]);
	free(arr);
}

int			**ft_intmatrixnew(int rows, int columns)
{
	int		**matrix;
	int		i;

	if (!(matrix = (int **)malloc(sizeof(int *) * rows)))
		return (NULL);
	i = 0;
	while (i < rows)
	{
		if (!(matrix[i] = ft_intarrnew(columns)))
		{
			free_arr(matrix, i - 1);
			return (NULL);
		}
		i++;
	}
	return (matrix);
}
