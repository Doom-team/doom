/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:06:37 by grinko            #+#    #+#             */
/*   Updated: 2019/09/06 19:06:47 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	void	*fresh_mem;

	if (size == ((size_t)-1))
		return (NULL);
	if (!(fresh_mem = (char *)malloc(sizeof(char) * size + 1)))
		return (NULL);
	ft_memset(fresh_mem, '\0', size + 1);
	return (fresh_mem);
}
