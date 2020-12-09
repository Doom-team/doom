/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 13:56:50 by clala             #+#    #+#             */
/*   Updated: 2020/02/15 21:53:21 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_list(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->content);
		lst->content = NULL;
		lst->content_size = 0;
		free(lst->next);
		lst->next = NULL;
		free(lst);
		lst = tmp;
	}
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*temp;
	t_list	*newlist;

	if (!f || !lst)
		return (NULL);
	newlist = (t_list *)malloc(sizeof(t_list) * 1);
	if (!newlist)
		return (NULL);
	newlist = f(lst);
	temp = newlist;
	while (lst->next)
	{
		newlist->next = (t_list *)malloc(sizeof(t_list) * 1);
		if (!newlist->next)
		{
			free_list(temp);
			return (NULL);
		}
		newlist->next = f(lst->next);
		newlist = newlist->next;
		lst = lst->next;
	}
	newlist->next = NULL;
	return (temp);
}
