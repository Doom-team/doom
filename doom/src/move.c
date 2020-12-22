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

void	add_skybox_offset_y(t_sdl *sdl, int to_add)
{
	sdl->skybox_offset_y += to_add;
	while (sdl->skybox_offset_y > sdl->sky->h)
		sdl->skybox_offset_y -= sdl->sky->h;
	while (sdl->skybox_offset_y < 0)
		sdl->skybox_offset_y += sdl->sky->h;
}

void	add_skybox_offset(t_sdl *sdl, float to_add)
{
	sdl->skybox_offset += to_add;
	while (sdl->skybox_offset > sdl->sky->w)
		sdl->skybox_offset -= sdl->sky->w;
	while (sdl->skybox_offset < 0)
		sdl->skybox_offset += sdl->sky->w;
}

void	rotate(t_wolf *wolf, SDL_Event *event)
{
	if (-event->motion.xrel * 0.01 / 10 > 0.05 || -event->motion.xrel * 0.01 / 10 < -0.05)
	{
		if (-event->motion.xrel > 0)
		{
			add_arc(&(wolf->player->dir), 0.05);
			add_skybox_offset(wolf->sdl, W / (float)wolf->sdl->sky->w * -60.0);
		}
		else
		{
			add_arc(&(wolf->player->dir), -0.05);
			add_skybox_offset(wolf->sdl, W / (float)wolf->sdl->sky->w * 60.0);
		}
	}
	else
	{
		add_arc(&(wolf->player->dir), -event->motion.xrel * 0.005);
		add_skybox_offset(wolf->sdl, event->motion.xrel * W / (float)wolf->sdl->sky->w * 6.0);
		// printf("%f\n", event->motion.xrel * W / (float)wolf->sdl->sky->w * 6.0);
	}
	// printf("%d\n", wolf->sdl->sky->w);
	wolf->player->dir_y += (int)(H / 200.0 * event->motion.yrel / 5.0);
	if (wolf->player->dir_y > H / 4 * 3)
		wolf->player->dir_y = H / 4 * 3;
	if (wolf->player->dir_y	< -H / 4 * 3)
		wolf->player->dir_y	= -H / 4 * 3;
	// printf("%f\n", wolf->sdl->skybox_offset_y);
	if (wolf->player->dir_y	!= -H / 4 * 3 && wolf->player->dir_y != H / 4 * 3)
		add_skybox_offset_y(wolf->sdl, (int)(H / 200.0 * event->motion.yrel / 5.0));
}

void	calc_move(t_wolf *wolf, float dy, float dx)
{
	// int		player_box;

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
