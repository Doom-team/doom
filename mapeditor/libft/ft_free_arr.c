/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gordey <gordey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 12:36:12 by gordey            #+#    #+#             */
/*   Updated: 2020/11/04 12:36:20 by gordey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_free_arr(char **str, size_t n)
{
	while (n)
	{
		ft_safe_free(str[n]);
		n--;
	}
	ft_safe_free(str[n]);
	ft_safe_free(str);
	return (NULL);
}
