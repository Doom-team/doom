/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_text1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:03 by grinko            #+#    #+#             */
/*   Updated: 2021/02/12 11:22:58 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

int		change_floor_inter(t_map *map)
{
	draw_img(map, &(t_info){WIDTH / 2 - 115, 5, 330, 100}, map->inter_tex[16]);
	draw_img(map, &(t_info){WIDTH / 2 + 20, 10, 70, 20}, map->floorsky_tex[0]);
	if (map->floorsky_tex[0]->active == 1)
		fonts_classic(map, "floor", &(t_info){WIDTH / 2 + 40, 14, 0, 0}, SABF);
	else
		fonts_classic(map, "floor", &(t_info){WIDTH / 2 + 40, 14, 0, 0},
			WHITEFONT);
	draw_img(map, &(t_info){WIDTH / 2 + 20, 30, 70, 20}, map->floorsky_tex[0]);
	if (map->floorsky_tex[0]->active == 2)
		fonts_classic(map, "celing", &(t_info){WIDTH / 2 + 40, 34, 0, 0}, SABF);
	else
		fonts_classic(map, "celing", &(t_info){WIDTH / 2 + 40, 34, 0, 0},
			WHITEFONT);
	draw_img(map, &(t_info){WIDTH / 2 + 120, 60, 65, 30}, map->floorsky_tex[0]);
	fonts_classic(map, "SAVE", &(t_info){WIDTH / 2 + 130, 65, 0, 0}, WHITEFONT);
	draw_img(map, &(t_info){WIDTH / 2 - 100, 60, 65, 30}, map->floorsky_tex[0]);
	fonts_classic(map, "CANCEL", &(t_info){WIDTH / 2 - 95, 65, 0, 0},
		WHITEFONT);
	if (map->floorsky_tex[0]->active == 1)
		return (4);
	else if (map->floorsky_tex[0]->active == 2)
		return (5);
	else
		return (0);
}

int		checknod(t_map *map, int x, int y)
{
	t_nod *n;

	n = map->nod;
	while (n)
	{
		if ((n->x1 == x && n->y1 == y) || (n->x2 == x && n->y2 == y))
			return (1);
		n = n->nxt;
	}
	return (0);
}

char	**ft_clear(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}
