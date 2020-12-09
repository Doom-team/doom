/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:53:12 by clala             #+#    #+#             */
/*   Updated: 2020/02/15 21:53:21 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*listnew;

	if (content_size + 1 < content_size)
		return (NULL);
	listnew = (t_list*)ft_memalloc(sizeof(t_list));
	if (!listnew)
		return (NULL);
	if (content == NULL)
	{
		listnew->content = NULL;
		listnew->content_size = 0;
	}
	else
	{
		listnew->content = malloc(content_size);
		if (listnew->content == NULL)
		{
			free(listnew);
			return (NULL);
		}
		ft_memmove(listnew->content, content, content_size);
		listnew->content_size = content_size;
	}
	listnew->next = NULL;
	return (listnew);
}
