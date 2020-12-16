/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:32:04 by clala             #+#    #+#             */
/*   Updated: 2020/12/16 22:04:42 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	add_skybox_offset(t_sdl *sdl, int to_add)
{
	sdl->skybox_offset += to_add;
	if (sdl->skybox_offset > sdl->sky->w - 1)
		sdl->skybox_offset -= sdl->sky->w;
	if (sdl->skybox_offset < 0)
		sdl->skybox_offset += sdl->sky->w;
}

void	rotate(t_wolf *wolf, SDL_Event *event)
{
	if (-event->motion.xrel * 0.01 / 10 > 0.05 || -event->motion.xrel * 0.01 / 10 < -0.05)
	{
		if (-event->motion.xrel > 0)
		{
			add_arc(&(wolf->player->dir), 0.05);
			add_skybox_offset(wolf->sdl, -5);
		}
		else
		{
			add_arc(&(wolf->player->dir), -0.05);
			add_skybox_offset(wolf->sdl, 5);
		}
	}
	else
	{
		add_arc(&(wolf->player->dir), -event->motion.xrel * 0.01 / 5);
		add_skybox_offset(wolf->sdl, event->motion.xrel / 5);
	}
	
	wolf->player->dir_y += H / 200 * event->motion.yrel / 5;
	if (wolf->player->dir_y > H / 4 * 3)
		wolf->player->dir_y = H / 4 * 3;
	if (wolf->player->dir_y	< -H / 4 * 3)
		wolf->player->dir_y	= -H / 4 * 3;
}

void	calc_move(t_wolf *wolf, float dy, float dx)
{
	int		player_box;

	// player_box = dx > 0 ? p->size : -p->size;
	// if (is_texture(map, p->x + dx + player_box, p->y, TEX_FLOOR)
	// || is_texture(map, p->x + dx + player_box, p->y, TEX_COIN))
	// {
	if ((dx > 0 && wolf->player->rght_d > 20.) || (dx < 0 && wolf->player->left_d > 20.))
		wolf->player->x += dx;
	// }
	// player_box = dy > 0 ? p->size : -p->size;
	// if (is_texture(map, p->x, p->y + dy + player_box, TEX_FLOOR) ||
	// is_texture(map, p->x, p->y + dy + player_box, TEX_COIN))
	// {
	if ((dy > 0 && wolf->player->up_d > 20.) || (dy < 0 && wolf->player->down_d > 20.))
		wolf->player->y += dy;
	// }
}
