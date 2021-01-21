/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:33 by grinko            #+#    #+#             */
/*   Updated: 2021/01/21 10:56:53 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

// int delete_node(t_nod *del, t_nod **first);
// // t_nod *deletelem(t_nod *lst, t_nod *root);

void	find_remove(t_map *map, int x, int y)
{
	t_nod *tmp;
	t_nod *tmp2;
	t_nod *first;

	tmp = map->nod;
	first = map->nod;
	while (tmp)
	{
		if (((tmp->x1 + map->z_x) == x && (tmp->y1 + map->z_y) == y) ||
		((tmp->x2 + map->z_x) == x && (tmp->y2 + map->z_y) == y))
		{
			tmp2 = tmp;
			tmp = tmp->nxt;
			if (lstdelone(&map->nod, tmp2))
				map->nod = NULL;
		}
		else
			tmp = tmp->nxt;
	}
}

void	edit_tool(t_map *map, int index)
{
	int i;

	i = -1;
	edit_blocktexture(map, -1);
	zerroother(map);
	map->inter_tex[16]->active = 0;
	while (++i < 25)
	{
		if (i == index)
			map->inter_tex[i]->active = 1;
		else
			map->inter_tex[i]->active = 0;
	}
}

void	edit_blocktexture(t_map *map, int index)
{
	int i;

	i = -1;
	while (++i < 6)
	{
		if (i == index)
			map->block_tex[i]->active = 1;
		else
			map->block_tex[i]->active = 0;
	}
}

void	wall_editor(t_map *map, int x, int y)
{
	if (map->click == 0 && interface_click(map, x, y))
	{
		map->click = 1;
		map->x_c = x;
		map->y_c = y;
		find_coord(map, &(map->x_c), &(map->y_c));
	}
	else if (interface_click(map, x, y))
	{
		map->click = 0;
		find_coord(map, &x, &y);
		add_node(map, x, y);
		map->nod->index = nod_len(map->nod);
	}
}

int		lstdelone(t_nod **fd_lst, t_nod *fd)
{
	t_nod	*file;
	t_nod	*last;
	int		flag;

	last = 0;
	flag = 0;
	if (!fd_lst || !fd)
		return (0);
	file = *fd_lst;
	if (!(*fd_lst)->nxt)
		flag = 1;
	while (file)
	{
		if (file == fd)
		{
			if (last)
				last->nxt = file->nxt;
			else
				*fd_lst = file->nxt;
			free(file);
			if (flag)
				return (1);
			return (0);
		}
		last = file;
		file = file->nxt;
	}
	return (0);
}

void	remove_tool(t_map *map, int x, int y)
{
	int x1;
	int y1;

	x1 = x;
	y1 = y;
	find_coord(map, &x1, &y1);
	if (x1 != x || y1 != y)
		find_remove(map, x1, y1);
}
