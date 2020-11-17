/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_free_arr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 12:31:56 by gordey            #+#    #+#             */
/*   Updated: 2020/11/11 15:48:56 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_safe_free(void *item)
{
	if (item)
		free(item);
}

void	ft_safe_free_arr(char **arr)
{
	char		**cpy;
	size_t		i;

	cpy = arr;
	i = 0;
	if (arr)
	{
		while (*cpy != NULL)
		{
			i++;
			cpy++;
		}
		if (*arr)
			ft_free_arr(arr, i - 1);
	}
}
