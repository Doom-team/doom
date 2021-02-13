/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 13:18:43 by grinko            #+#    #+#             */
/*   Updated: 2021/02/13 22:15:50 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		add_skybox_offset_y(t_wolf *wolf, int to_add)
{
	wolf->sdl->skybox_offset_y += to_add;
	while (wolf->sdl->skybox_offset_y > wolf->p->sky_texture->h)
		wolf->sdl->skybox_offset_y -= wolf->p->sky_texture->h;
	while (wolf->sdl->skybox_offset_y < 0)
		wolf->sdl->skybox_offset_y += wolf->p->sky_texture->h;
}

void		add_skybox_offset(t_wolf *wolf, float to_add)
{
	wolf->sdl->skybox_offset += to_add;
	while (wolf->sdl->skybox_offset > wolf->p->sky_texture->w)
		wolf->sdl->skybox_offset -= wolf->p->sky_texture->w;
	while (wolf->sdl->skybox_offset < 0)
		wolf->sdl->skybox_offset += wolf->p->sky_texture->w;
}

void		rotate(t_wolf *wolf, SDL_Event *event)
{
	if (-event->motion.xrel * 0.001 > 0.05 ||
		-event->motion.xrel * 0.001 < -0.05)
		if (-event->motion.xrel > 0)
		{
			add_arc(&(wolf->player->dir), 0.05);
			add_skybox_offset(wolf, W / (float)wolf->p->sky_texture->w * -60.0);
		}
		else
		{
			add_arc(&(wolf->player->dir), -0.05);
			add_skybox_offset(wolf, W / (float)wolf->p->sky_texture->w * 60.0);
		}
	else
	{
		add_arc(&(wolf->player->dir), -event->motion.xrel * 0.005);
		add_skybox_offset(wolf, event->motion.xrel * W /
			(float)wolf->p->sky_texture->w * 6.0);
	}
	wolf->player->dir_y += (int)(H / 200.0 * event->motion.yrel / 5.0);
	if (wolf->player->dir_y > H / 4 * 3)
		wolf->player->dir_y = H / 4 * 3;
	if (wolf->player->dir_y < -H / 4 * 3)
		wolf->player->dir_y = -H / 4 * 3;
	if (wolf->player->dir_y != -H / 4 * 3 && wolf->player->dir_y != H / 4 * 3)
		add_skybox_offset_y(wolf, (int)(H / 200.0 * event->motion.yrel / 5.0));
}

void		take_damage(t_wolf *wolf, int dmg)
{
	wolf->player->hp -= dmg;
	Mix_PlayChannel(1, wolf->p->take_damage, 0);
}

void		falling2(t_wolf *wolf, SDL_Event *event)
{
	handle_event(wolf, event);
	recalc(wolf);
	all_get_distance(wolf);
	pseudo_3d(wolf);
	render_score_coin(wolf);
	render_fps(wolf, wolf->bon);
	render_aim(wolf);
	render_hud(wolf);
	render_shot(wolf, wolf->surface);
	SDL_UpdateWindowSurface(wolf->sdl->win);
}
