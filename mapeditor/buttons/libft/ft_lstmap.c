/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:45:45 by grinko            #+#    #+#             */
/*   Updated: 2019/09/11 19:48:33 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	listclear(t_list *lst)
{
	t_list	*listik;

	while (lst)
	{
		listik = lst->next;
		free(lst->content);
		free(lst);
		lst = listik;
	}
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*fresh_list;
	t_list	*new;
	t_list	*listik;

	if (!lst || !f)
		return (NULL);
	listik = f(lst);
	if (!(new = ft_lstnew(listik->content, listik->content_size)))
		return (NULL);
	fresh_list = new;
	lst = lst->next;
	while (lst)
	{
		listik = f(lst);
		if (!(new->next = ft_lstnew(listik->content, listik->content_size)))
		{
			listclear(fresh_list);
			return (NULL);
		}
		new = new->next;
		lst = lst->next;
	}
	return (fresh_list);
}
