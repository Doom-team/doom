/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_block.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:48:27 by grinko            #+#    #+#             */
/*   Updated: 2020/12/22 19:43:12 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	draw_obj_block(t_map * map)
{
	draw_player(map);
	draw_guns(map);
	draw_enemy(map);
	draw_door_light_exit(map);
}

void objectsblock(t_map *map)
{
	draw_obj_block(map);
	
}