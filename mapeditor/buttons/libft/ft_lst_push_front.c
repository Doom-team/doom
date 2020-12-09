/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_push_front.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 17:48:43 by grinko            #+#    #+#             */
/*   Updated: 2019/09/13 17:48:44 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_push_front(t_list **alst, void const *cont, size_t cont_size)
{
	t_list *lst;

	if (!(lst = ft_lstnew(cont, cont_size)))
		return ;
	lst->next = *alst;
	*alst = lst;
}
