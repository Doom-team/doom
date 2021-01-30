/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:32:04 by clala             #+#    #+#             */
/*   Updated: 2021/01/30 23:05:42 by wendell          ###   ########.fr       */
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
	if (-event->motion.xrel * 0.001 > 0.05 || -event->motion.xrel * 0.001 < -0.05)
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
	if (wolf->player->dir_y < -H / 4 * 3)
		wolf->player->dir_y = -H / 4 * 3;
	// printf("%f\n", wolf->sdl->skybox_offset_y);
	if (wolf->player->dir_y != -H / 4 * 3 && wolf->player->dir_y != H / 4 * 3)
		add_skybox_offset_y(wolf->sdl, (int)(H / 200.0 * event->motion.yrel / 5.0));
}

void	falling(t_wolf *wolf)
{
	SDL_Event	event;
	if (wolf->player->inside_step > abs(wolf->player->fly))
	{
		while (abs(wolf->player->fly) < wolf->player->inside_step)
		{
			wolf->player->fly -= UP_LENGTH/2;
			handle_event(wolf, &event);
			all_get_distance(wolf);
			pseudo_3d(wolf, wolf->player, wolf->surface);
			render_score_coin(wolf);
			render_fps(wolf, wolf->bon);
			render_aim(wolf);
			render_shot(wolf, wolf->surface);
			SDL_UpdateWindowSurface(wolf->sdl->win);
		}
	}
	else if (wolf->player->inside_step < abs(wolf->player->fly))
	{
		while (abs(wolf->player->fly) > wolf->player->inside_step)
		{
			wolf->player->fly += UP_LENGTH/2;
			handle_event(wolf, &event);
			all_get_distance(wolf);
			pseudo_3d(wolf, wolf->player, wolf->surface);
			render_score_coin(wolf);
			render_fps(wolf, wolf->bon);
			render_aim(wolf);
			render_shot(wolf, wolf->surface);
			SDL_UpdateWindowSurface(wolf->sdl->win);
		}
	}
}

void	jump(t_wolf *wolf)
{
	int i = 0;
	SDL_Event	event;

	wolf->player->in_jump = 1;
	while (i < 24)
	{
		wolf->player->fly -= UP_LENGTH/12;
		handle_event(wolf, &event);
		all_get_distance(wolf);
		pseudo_3d(wolf, wolf->player, wolf->surface);
		render_score_coin(wolf);
		render_fps(wolf, wolf->bon);
		render_aim(wolf);
		render_shot(wolf, wolf->surface);
		SDL_UpdateWindowSurface(wolf->sdl->win);
		i++;
	}
	falling(wolf);
	wolf->player->in_jump = 0;
}

void	calc_move(t_wolf *wolf, float dy, float dx)
{
	if (wolf->player->flying)
	{
		wolf->player->x += dx * 0.979;
		wolf->player->y += dy * 0.979;
	}
	else
	{
		recalc(wolf);
		if (dx > 0) 
		{
			if (wolf->player->rght_d->dist > dx + wolf->player->speed)
				wolf->player->x += dx * 0.979;
			else if(wolf->player->rght_d->wall.type_flag == 1 && UP_LENGTH * wolf->player->rght_d->wall.h + wolf->player->fly <= UP_LENGTH)
				wolf->player->x += dx * 0.979;
		}
		else if(dx < 0)
		{
			if (wolf->player->left_d->dist > fabs(dx) + wolf->player->speed)
				wolf->player->x += dx * 0.979;
			else if(wolf->player->left_d->wall.type_flag == 1 && UP_LENGTH * wolf->player->left_d->wall.h + wolf->player->fly <= UP_LENGTH)
				wolf->player->x += dx * 0.979;
		}
		recalc(wolf);
		if (dy > 0) 
		{
			if (wolf->player->up_d->dist > dy + wolf->player->speed)
				wolf->player->y += dy * 0.979;
			else if(wolf->player->up_d->wall.type_flag && UP_LENGTH * wolf->player->up_d->wall.h + wolf->player->fly <= UP_LENGTH)
				wolf->player->y += dy * 0.979;
		}
		else if(dy < 0)
		{
			if (wolf->player->down_d->dist > fabs(dy) + wolf->player->speed)
				wolf->player->y += dy * 0.979;
			else if(wolf->player->down_d->wall.type_flag && UP_LENGTH * wolf->player->down_d->wall.h + wolf->player->fly <= UP_LENGTH)
				wolf->player->y += dy * 0.979;
		}
		recalc(wolf);
		if (!wolf->player->in_jump)
			falling(wolf);
	}
}
