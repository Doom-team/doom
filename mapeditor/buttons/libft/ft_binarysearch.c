/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binarysearch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 13:41:06 by grinko            #+#    #+#             */
/*   Updated: 2019/09/12 14:10:41 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_binarysearch(int a, int *arr, int n)
{
	int low;
	int high;
	int middle;

	low = 0;
	high = n - 1;
	while (low <= high)
	{
		middle = (low + high) / 2;
		if (a < arr[middle])
			high = middle - 1;
		else if (a > arr[middle])
			low = middle + 1;
		else
			return (middle);
	}
	return (-1);
}
