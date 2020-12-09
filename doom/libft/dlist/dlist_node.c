/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dlist_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 22:01:36 by clala             #+#    #+#             */
/*   Updated: 2020/02/15 22:06:46 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dlist.h"

t_dlist_node		*t_dlist_node_new(void *data)
{
	t_dlist_node	*new;

	new = (t_dlist_node *)malloc(sizeof(t_dlist_node));
	new->data = data;
	new->prev = NULL;
	new->next = NULL;
	new->data_size = 0;
	return (new);
}

/*
** Add new node and set it to go the given pointer
*/

t_dlist_node		*t_dlist_insert_after(t_dlist *list,
t_dlist_node *node, t_dlist_node *new)
{
	new->prev = node;
	if (!node->next)
		list->tail = new;
	else
	{
		new->next = node->next;
		node->next->prev = new;
	}
	node->next = new;
	list->size++;
	return (new);
}

t_dlist_node		*t_dlist_insert_before(t_dlist *list,
t_dlist_node *node, t_dlist_node *new)
{
	new->next = node;
	if (!node->prev)
		list->head = new;
	else
	{
		new->prev = node->prev;
		node->prev->next = new;
	}
	node->prev = new;
	list->size++;
	return (new);
}

/*
** add to the front of list
*/

t_dlist_node		*t_dlist_push(t_dlist *list, t_dlist_node *new)
{
	if (!list->head)
	{
		list->head = new;
		list->tail = new;
	}
	else
	{
		t_dlist_insert_before(list, list->head, new);
	}
	return (new);
}

t_dlist_node		*t_dlist_append(t_dlist *list, t_dlist_node *new)
{
	if (!list->tail)
		t_dlist_push(list, new);
	else
		t_dlist_insert_after(list, list->tail, new);
	return (new);
}
