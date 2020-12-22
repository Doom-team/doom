/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceiling_text.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:37:30 by grinko            #+#    #+#             */
/*   Updated: 2020/12/22 13:37:32 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void findceilingnod(t_map *map)
{
	int w;
	int h;
	t_nod *n;

	n = map->nod;
	w = map->tmpfloor_x - map->floor_x;
	h = map->tmpfloor_y - map->floor_y;
	while (n)
	{
		if ((n->x1 >= map->floor_x && n->x1 <= map->tmpfloor_x) && (n->y1 >= map->floor_y && n->y1 <= map->tmpfloor_y) &&
		(n->x2 >= map->floor_x && n->x2 <= map->tmpfloor_x) && (n->y2 >= map->floor_y && n->y2 <= map->tmpfloor_y))
		{
			n->texture->ceiling_name = "ceiling";
			n->texture->ceiling_name = ft_strjoin(n->texture->ceiling_name, ft_itoa(map->index_tex));
			n->texture->ceiling_name = ft_strjoin(n->texture->ceiling_name, ".png");
		}
		n = n->nxt;
	}
}
