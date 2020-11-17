/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:27:05 by grinko            #+#    #+#             */
/*   Updated: 2019/09/11 17:33:22 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;

	if (!del || !alst)
		return ;
	while (*alst)
	{
		tmp = (*alst)->next;
		del(((*alst)->content), (*alst)->content_size);
		free(*alst);
		*alst = tmp;
	}
	*alst = NULL;
}
