/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stairs3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 10:51:15 by grinko            #+#    #+#             */
/*   Updated: 2021/02/12 18:28:28 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	stairarr1(t_map *map, t_info *cor, int i)
{
	if (i == 1)
	{
		map->remove->x[i - 1] = cor->x - map->ha->nx;
		map->remove->y[i - 1] = cor->y - map->ha->ny;
		map->remove->x[i] = cor->x + map->ha->nx;
		map->remove->y[i] = cor->y + map->ha->ny;
		map->remove->x[i + 1] = cor->x - map->ha->nx;
		map->remove->y[i + 1] = cor->y - map->ha->ny;
		map->remove->x[i + 2] = cor->w - map->ha->nx;
		map->remove->y[i + 2] = cor->h - map->ha->ny;
		map->remove->x[i + 3] = cor->x + map->ha->nx;
		map->remove->y[i + 3] = cor->y + map->ha->ny;
		map->remove->x[i + 4] = cor->w + map->ha->nx;
		map->remove->y[i + 4] = cor->h + map->ha->ny;
		map->remove->x[i + 5] = cor->w - map->ha->nx;
		map->remove->y[i + 5] = cor->h - map->ha->ny;
		map->remove->x[i + 6] = cor->w + map->ha->nx;
		map->remove->y[i + 6] = cor->h + map->ha->ny;
	}
	else
		stairarr2(map, cor, i);
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

void	lstdelone2(t_nod **fd_lst, t_nod *fd, t_nod *file, t_nod *last)
{
	if (last)
		last->nxt = file->nxt;
	else
		*fd_lst = file->nxt;
	free(file);
}

void	save_texture1(t_map *map, t_nod *n)
{
	n->type = 2;
	if (map->door_tex[0]->active == 1)
	{
		// printf("here\n");
		n->grnum = 1;
		n->texture->texture_name[0] =
			" ../textures/doors/defdoor.png";
	}
	if (map->door_tex[1]->active == 1)
	{
		n->grnum = 2;
		n->texture->texture_name[0] =
			" ../textures/doors/bluedoor.png";
	}
	if (map->door_tex[2]->active == 1)
	{
		n->grnum = 3;
		n->texture->texture_name[0] =
			" ../textures/doors/yellowdoor.png";
	}
	if (map->door_tex[3]->active == 1)
	{
		n->grnum = 4;
		n->texture->texture_name[0] =
			" ../textures/doors/reddoor.png";
	}
}

char	*write_walls2(t_map *map, char *buffer, t_nod *n)
{
	if (n->type == 2)
		buffer = add_text(buffer, n->texture->texture_name[0], 1);
	else
		buffer = add_text(buffer, write_wall_text(n), 2);
	buffer = add_text(buffer, " ", 1);
	buffer = add_text(buffer, ft_itoa(n->wallh), 2);
	buffer = add_text(buffer, " ", 1);
	buffer = add_text(buffer, ft_itoa(n->type), 2);
	buffer = add_text(buffer, " ", 1);
	buffer = add_text(buffer, ft_itoa(n->grnum), 2);
	buffer = add_text(buffer, "\n", 1);
	return (buffer);
}
