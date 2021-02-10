/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:58:57 by grinko            #+#    #+#             */
/*   Updated: 2021/02/10 13:44:07 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

// void	free_image(t_image *img)
// {
// 	// free(img->s);
// 	// ft_strdel(img->pixb);
// 	img->strb = 0;
// 	img->active = 0;
// 	free(img);
// 	img = 0;
// }

void	free_panel(t_map *map)
{
	int i;

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

void	free_map(t_map *map)
{
	free_panel(map);
	free_nodes(map);
}

// void	free_interfce(t_map *map)
// {
// 	free_panel(map);
// 	free_cursor(map);
// 	malloc_block_texture(map);
// 	malloc_wall_texture(map);
// 	malloc_floorsky_texture(map);
// 	malloc_liquid_texture(map);
// 	malloc_player_texture(map);
// 	malloc_enemy_texture(map);
// 	malloc_gun_texture(map);
// 	malloc_door_texture(map);
// }


// void	free_all(t_map *map)
// {
// 	free_interface(map);
// }