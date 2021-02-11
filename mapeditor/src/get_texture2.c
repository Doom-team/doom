/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:08 by grinko            #+#    #+#             */
/*   Updated: 2021/02/12 00:43:49 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	get_wall_textures(t_map *map)
{
	map->wall_tex[0]->img = load_image("/textures/interface/blackblock.png");
	map->wall_tex[1]->img = load_image("/textures/walls/wall1.png");
	map->wall_tex[2]->img = load_image("/textures/walls/wall2.png");
	map->wall_tex[3]->img = load_image("/textures/walls/wall3.png");
	map->wall_tex[4]->img = load_image("/textures/walls/wall4.png");
	map->wall_tex[5]->img = load_image("/textures/walls/wall5.png");
	map->wall_tex[6]->img = load_image("/textures/walls/wall6.png");
	map->wall_tex[7]->img = load_image("/textures/walls/wall7.png");
	map->wall_tex[8]->img = load_image("/textures/walls/wall8.png");
	map->wall_tex[9]->img = load_image("/textures/walls/wall9.png");
	map->wall_tex[10]->img = load_image("/textures/walls/wall10.png");
	map->wall_tex[11]->img = load_image("/textures/walls/wall11.png");
	map->wall_tex[12]->img = load_image("/textures/walls/wall12.png");
	map->wall_tex[13]->img = load_image("/textures/walls/wall13.png");
	map->wall_tex[14]->img = load_image("/textures/walls/wall14.png");
	map->wall_tex[15]->img = load_image("/textures/walls/wall15.png");
	map->wall_tex[16]->img = load_image("/textures/walls/wall16.png");
	map->wall_tex[17]->img = load_image("/textures/walls/wall17.png");
	map->wall_tex[18]->img = load_image("/textures/walls/wall18.png");
	map->wall_tex[19]->img = load_image("/textures/walls/wall19.png");
}

void	get_liquid_textures(t_map *map)
{
	map->liquid_tex[0]->img = load_image("/textures/interface/blackblock.png");
	map->liquid_tex[1]->img = load_image("/textures/liquids/lava.png");
	map->liquid_tex[2]->img = load_image("/textures/liquids/water.png");
	map->liquid_tex[3]->img = load_image("/textures/liquids/nukage.png");
}

void	get_enemy_textures(t_map *map)
{
	map->enemy_tex[0]->img = load_image("/textures/enemy/beam.png");
	map->enemy_tex[1]->img = load_image("/textures/enemy/abbadon.png");
	map->enemy_tex[2]->img = load_image("/textures/enemy/arachnophyte.png");
	map->enemy_tex[3]->img = load_image("/textures/enemy/annihilator.png");
	map->enemy_tex[4]->img = load_image("/textures/enemy/hierophant.png");
}

void	get_player_textures(t_map *map)
{
	map->player_tex[0]->img = load_image("/textures/player/player.png");
	map->player_tex[1]->img = load_image("/textures/player/health.png");
	map->player_tex[2]->img = load_image("/textures/player/armor.png");
}

void	get_gun_textures(t_map *map)
{
	map->gun_tex[0]->img = load_image("/textures/guns/pistol.png");
	map->gun_tex[1]->img = load_image("/textures/guns/pistol_b.png");
	map->gun_tex[2]->img = load_image("/textures/guns/shotgun.png");
	map->gun_tex[3]->img = load_image("/textures/guns/shotgun_b.png");
	map->gun_tex[4]->img = load_image("/textures/guns/ak.png");
	map->gun_tex[5]->img = load_image("/textures/guns/ak_b.png");
}
