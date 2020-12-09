/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 16:54:47 by grinko            #+#    #+#             */
/*   Updated: 2019/09/11 18:21:24 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *listik;

	if (!(listik = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		listik->content = NULL;
		listik->content_size = 0;
	}
	else
	{
		if (!(listik->content = malloc(content_size)))
		{
			free(listik);
			return (NULL);
		}
		ft_memcpy(listik->content, content, content_size);
		listik->content_size = content_size;
	}
	listik->next = NULL;
	return (listik);
}
