/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_selectionsort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 13:17:06 by grinko            #+#    #+#             */
/*   Updated: 2019/09/12 14:10:43 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_selectionsort(int *arr, int size)
{
	int min;
	int tmp;
	int i;
	int j;

	i = 0;
	while (i < size - 1)
	{
		min = i;
		i++;
		j = i + 1;
		while (j < size)
		{
			if (arr[j] < arr[min])
				min = j;
		}
		tmp = arr[i];
		arr[i] = arr[min];
		arr[min] = tmp;
	}
}
