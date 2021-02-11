/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:58:57 by grinko            #+#    #+#             */
/*   Updated: 2021/02/12 00:37:43 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	free_panel2(t_map *map)
{
	int	i;

	i = -1;
	while (++i < 4)
		free(map->liquid_tex[i]);
	i = -1;
	while (++i < 5)
		free(map->enemy_tex[i]);
	i = -1;
	while (++i < 3)
		free(map->player_tex[i]);
	i = -1;
	while (++i < 6)
		free(map->gun_tex[i]);
	i = -1;
	while (++i < 11)
		free(map->door_tex[i]);
}

void	free_panel1(t_map *map)
{
	int	i;

	i = -1;
	while (++i < 11)
		free(map->inter_tex[i]);
	i = -1;
	while (++i < 7)
		free(map->curosr_img[i]);
	i = -1;
	while (++i < 9)
		free(map->block_tex[i]);
	i = -1;
	while (++i < 13)
		free(map->floorsky_tex[i]);
	i = -1;
	while (++i < 20)
		free(map->wall_tex[i]);
	free_panel2(map);
}

void	free_nodes(t_map *map)
{
	t_nod	*n;
	t_nod	*tmp;

	n = map->nod;
	if (!n)
		return ;
	while (n)
	{
		tmp = n->nxt;
		free(n->texture->texture_name);
		if (n->texture->type_name)
			free(n->texture->type_name);
		free(n);
		n = tmp;
	}
	n = NULL;
}
