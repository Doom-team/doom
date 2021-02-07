/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gordey <gordey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:38:58 by grinko            #+#    #+#             */
/*   Updated: 2021/02/07 15:24:40 by gordey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	tmp_draw2(t_map *map, int w, int i, t_nod *nod)
{
	int	tmp;

	if ((nod->texture->texture_name[0] != NULL &&
		map->inter_tex[17]->active == 0) ||
			(nod->texture->texture_name[1] != NULL &&
				map->inter_tex[19]->active == 0))
	{
		if (nod->texture->texture_name[1] != NULL &&
		map->inter_tex[19]->active == 0)
			tmp = find_texture_name(nod->texture->texture_name[1]);
		else
			tmp = find_texture_name(nod->texture->texture_name[0]);
		w = WIDTH / 2 - 100;
		i = -1;
		while (++i < 4)
		{
			if ((nod->texture->texture_name[1] != NULL &&
				map->inter_tex[19]->active == 0))
				draw_img(map, &(t_info){w, 60, 55, 20}, map->wall_tex[tmp]);
			else
				draw_img(map, &(t_info){w, 40, 55, 20}, map->wall_tex[tmp]);
			w += 55;
		}
	}
}

void	tmp_draw(t_map *map, int index, t_nod *nod)
{
	int	c;
	int	w;
	int	i;
	int	tmp;

	i = -1;
	tmp = 0;
	w = WIDTH / 2 - 100;
	if (map->inter_tex[17]->active == 1)
		c = 40;
	else if (map->inter_tex[19]->active == 1)
		c = 60;
	if ((map->inter_tex[17]->active == 1 ||
		map->inter_tex[19]->active == 1) && index != -1)
	{
		while (++i < 4)
		{
			draw_img(map, &(t_info){w, c, 55, 20}, map->wall_tex[index]);
			w += 55;
		}
	}
	tmp_draw2(map, w, i, nod);
}

int		draw_changer_texture(t_map *map)
{
	t_nod *tmp;

	tmp = map->nod;
	while (tmp)
	{
		if (tmp->index == map->index_wall)
		{
			if (tmp->texture->texture_name[0] != NULL ||
				tmp->texture->texture_name[1] != NULL)
				tmp_draw(map, -1, tmp);
			if (map->inter_tex[17]->active == 1)
			{
				tmp_draw(map, map->index_tex, tmp);
				return (3);
			}
			else if (map->inter_tex[19]->active == 1)
			{
				tmp_draw(map, map->index_tex, tmp);
				return (4);
			}
		}
		tmp = tmp->nxt;
	}
	return (0);
}

int		find_nod(t_map *map, int x, int y)
{
	t_nod	*n;
	int		i;

	i = 1;
	n = map->nod;
	if (n == NULL)
		return (0);
	while (n)
	{
		if ((n->x1 == map->change_x && n->y1 == map->change_y &&
			n->x2 == x && n->y2 == y) ||
		(n->x1 == x && n->y1 == y && n->x2 == map->change_x &&
			n->y2 == map->change_y))
			return (i);
		i++;
		n = n->nxt;
	}
	return (0);
}
