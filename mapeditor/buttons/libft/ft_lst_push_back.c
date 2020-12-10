/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_push_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 17:48:32 by grinko            #+#    #+#             */
/*   Updated: 2019/09/13 17:48:33 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_push_back(t_list **alst, void const *cont, size_t cont_size)
{
	t_list *blst;

	blst = *alst;
	while (blst->next)
		blst = (blst)->next;
	(blst)->next = ft_lstnew(cont, cont_size);
}
