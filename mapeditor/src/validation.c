/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:36 by grinko            #+#    #+#             */
/*   Updated: 2020/12/22 13:39:37 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

int check_scene(t_info *info, t_map *map) // x = max_x, y = max_y, w = min_x, h = min_y
{
	t_nod *n;
	t_nod *tmp;
	int i;
	
	n = map->nod;
	tmp = map->nod;
	i = 0;
	while (n)
	{
		if (n->x1 == info->x || n->x2 == info->x || n->x1 == info->w || n->x2 == info->w ||
		n->y1 == info->y || n->y2 == info->y || n->y1 == info->h || n->y2 == info->h)
		{
			tmp = n;
			while (tmp)
			{
				if (tmp->x1 == info->x)
					i++;
				else if (tmp->x2 == info->x)
					i++;
				if (tmp->x1 == info->w)
					i++;
				else if (tmp->x2 == info->w)
					i++;
				if (tmp->y1 == info->y)
					i++;
				else if (tmp->y2 == info->y)
					i++;
				if (tmp->y1 == info->h)
					i++;
				else if (tmp->y2 == info->h)
					i++;
				tmp = tmp->nxt;
			}
			if (i == 8 || i == 12 || i == 11 || i == 10) // ????????????maybe
			{
				printf("that's cool map!\n");
				return(1);
			}
			else
			{
				map->inter_tex[21]->active = 0;
				map->validflag = 1;
				events(map);
			}
			break ;
		}
		n = n->nxt;
	}
	return (0);
}

int valid_map(t_map *map)
{
	t_nod *n;
	int max_x;
	int max_y;
	int min_x;
	int min_y;
	
	n = map->nod;
	max_x = -WIDTH;
	max_y = -HEIGHT;
	min_x = WIDTH;
	min_y = HEIGHT;
	while (n)
	{
		if (n->x1 >= max_x)
			max_x = n->x1;
		else if (n->x2 >= max_x)
			max_x = n->x2;
		if (n->x1 <= min_x)
			min_x = n->x1;
		else if (n->x2 <= min_x)
			min_x = n->x2;
		if (n->y1 >= max_y)
			max_y = n->y1;
		else if (n->y2 >= max_y)
			max_y = n->y2;
		if (n->y1 <= min_y)
			min_y = n->y1;
		else if (n->y2 <= min_y)
			min_y = n->y2;
		n = n->nxt;
	}
	if (check_scene(&(t_info){max_x, max_y, min_x, min_y}, map))
		return (1);
	// printf("max x: %d y: %d\n", max_x, max_y);
	// printf("min x: %d y: %d\n", min_x, min_y);
	return (0);
}