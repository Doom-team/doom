/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:36 by grinko            #+#    #+#             */
/*   Updated: 2021/02/13 18:49:36 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

int		check_scene2(t_info *str, t_info *info, t_map *map, int i)
{
	if (str->x == info->x)
		i++;
	else if (str->w == info->x)
		i++;
	if (str->x == info->w)
		i++;
	else if (str->w == info->w)
		i++;
	if (str->y == info->y)
		i++;
	else if (str->h == info->y)
		i++;
	if (str->y == info->h)
		i++;
	else if (str->h == info->h)
		i++;
	return (i);
}

int		check_scene3(t_map *map, int i)
{
	if (!ft_strchr(map->objects, 'p'))
	{
		map->inter_tex[21]->active = 0;
		map->errorflag = 2;
		return (0);
	}
	if (map->exitflag == 0)
	{
		map->inter_tex[21]->active = 0;
		map->errorflag = 3;
		return (0);
	}
	if (i == 8 || i == 12 || i == 11 || i == 10)
		return (1);
	else
	{
		map->inter_tex[21]->active = 0;
		map->errorflag = 1;
		return (0);
	}
	return (0);
}

int		check_scene(t_info *info, t_map *map)
{
	t_nod	*n;
	t_nod	*tmp;
	int		i;

	n = map->nod;
	tmp = map->nod;
	i = 0;
	while (n)
	{
		if (n->x1 == info->x || n->x2 == info->x || n->x1 == info->w ||
			n->x2 == info->w || n->y1 == info->y || n->y2 == info->y ||
			n->y1 == info->h || n->y2 == info->h)
		{
			tmp = n;
			while (tmp)
			{
				i = check_scene2(&(t_info){tmp->x1, tmp->y1, tmp->x2,
					tmp->y2}, info, map, i);
				tmp = tmp->nxt;
			}
			return (check_scene3(map, i));
		}
		n = n->nxt;
	}
	return (0);
}

int	if_if(t_map *map, t_nod *n)
{
	if (!n)
	{
		map->errorflag = 1;
		return (0);
	}
	return (1);
}

int		valid_map(t_map *map, t_info *inf)
{
	t_nod	*n;

	n = map->nod;
	if (!if_if(map, n))
		return (0);
	while (n)
	{
		if (n->x1 >= inf->x)
			inf->x = n->x1;
		else if (n->x2 >= inf->x)
			inf->x = n->x2;
		if (n->x1 <= inf->w)
			inf->w = n->x1;
		else if (n->x2 <= inf->w)
			inf->w = n->x2;
		if (n->y1 >= inf->y)
			inf->y = n->y1;
		else if (n->y2 >= inf->y)
			inf->y = n->y2;
		if (n->y1 <= inf->h)
			inf->h = n->y1;
		else if (n->y2 <= inf->h)
			inf->h = n->y2;
		n = n->nxt;
	}
	return (check_scene(&(t_info){inf->x, inf->y, inf->w, inf->y}, map));
}
