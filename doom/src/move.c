/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:32:04 by skaren            #+#    #+#             */
/*   Updated: 2021/02/12 03:24:52 by wendell          ###   ########.fr       */
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
	{
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
	printf("dmg %d\n", dmg);
	wolf->player->hp -= dmg;
	Mix_PlayChannel(1, wolf->p->take_damage, 0);
}

void		falling(t_wolf *wolf)
{
	SDL_Event	event;
	int			dmg;

	if (wolf->player->inside_step > abs(wolf->player->fly))
	{
		while (abs(wolf->player->fly) < wolf->player->inside_step)
		{
			wolf->player->fly -= UP_LENGTH / 2;
			handle_event(wolf, &event);
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
	}
	else if (wolf->player->inside_step < abs(wolf->player->fly))
	{
		dmg = (wolf->player->inside_step + wolf->player->fly) / 60;
		while (abs(wolf->player->fly) > wolf->player->inside_step)
		{
			wolf->player->fly += UP_LENGTH / 4;
			handle_event(wolf, &event);
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
		if (dmg < -15)
			take_damage(wolf, abs(dmg) / 2);
	}
}

void		jump(t_wolf *wolf)
{
	int			i;
	int			dmg;
	SDL_Event	event;

	i = 0;
	wolf->player->in_jump = 1;
	while (i < 12)
	{
		wolf->player->fly -= UP_LENGTH / 6;
		handle_event(wolf, &event);
		handle_phisics(wolf, wolf->player);
		all_get_distance(wolf);
		pseudo_3d(wolf);
		render_score_coin(wolf);
		render_fps(wolf, wolf->bon);
		render_aim(wolf);
		render_hud(wolf);
		render_shot(wolf, wolf->surface);
		SDL_UpdateWindowSurface(wolf->sdl->win);
		i++;
	}
	dmg = (wolf->player->inside_step + wolf->player->fly) / 60;
	while (abs(wolf->player->fly) > wolf->player->inside_step &&
			wolf->player->fly < 0)
	{
		wolf->player->fly += UP_LENGTH / 3;
		handle_event(wolf, &event);
		recalc(wolf);
		handle_phisics(wolf, wolf->player);
		all_get_distance(wolf);
		pseudo_3d(wolf);
		render_score_coin(wolf);
		render_fps(wolf, wolf->bon);
		render_aim(wolf);
		render_hud(wolf);
		render_shot(wolf, wolf->surface);
		SDL_UpdateWindowSurface(wolf->sdl->win);
	}
	wolf->player->fly = -wolf->player->inside_step;
	if (dmg < -15)
		take_damage(wolf, abs(dmg) / 2);
	wolf->player->in_jump = 0;
}

void		calc_move(t_wolf *wolf, float dy, float dx)
{
	int i;

	i = 0;
	if (wolf->player->flying)
	{
		wolf->player->x += dx * 0.8f;
		wolf->player->y += dy * 0.8f;
	}
	else
	{
		recalc(wolf);
		if (dx > 0)
		{
			if (wolf->player->rght_d->dist > fabs(dx))
			{
				i++;
				wolf->player->x += dx * 0.8f;
			}
			else if (wolf->player->rght_d->wall.type_flag == 1
				&& UP_LENGTH * wolf->player->rght_d->wall.h +
					wolf->player->fly <= UP_LENGTH)
				wolf->player->x += dx;
			else if ((!wolf->player->rght_d->wall.type_flag || wolf->player->rght_d->wall.type_flag == 2) && UP_LENGTH * wolf->player->rght_d->wall.h + wolf->player->fly < UP_LENGTH)
				wolf->player->x += dx;
		}
		else if (dx < 0)
		{
			if (wolf->player->left_d->dist > fabs(dx))
			{
				i++;
				wolf->player->x += dx * 0.8f;
			}
			else if (wolf->player->left_d->wall.type_flag == 1 &&
				UP_LENGTH * wolf->player->left_d->wall.h +
					wolf->player->fly <= UP_LENGTH)
				wolf->player->x += dx;
			else if ((!wolf->player->left_d->wall.type_flag || wolf->player->left_d->wall.type_flag == 2) &&
				UP_LENGTH * wolf->player->left_d->wall.h +
					wolf->player->fly < UP_LENGTH)
				wolf->player->x += dx;
		}
		recalc(wolf);
		if (dy > 0)
		{
			if (wolf->player->up_d->dist > fabs(dy))
			{
				i++;
				wolf->player->y += dy * 0.8f;
			}
			else if (wolf->player->up_d->wall.type_flag == 1 &&
				UP_LENGTH * wolf->player->up_d->wall.h +
					wolf->player->fly <= UP_LENGTH)
				wolf->player->y += dy;
			else if ((!wolf->player->up_d->wall.type_flag || wolf->player->up_d->wall.type_flag == 2) &&
				UP_LENGTH * wolf->player->up_d->wall.h +
					wolf->player->fly < UP_LENGTH)
				wolf->player->y += dy;
		}
		else if (dy < 0)
		{
			if (wolf->player->down_d->dist > fabs(dy))
			{
				i++;
				wolf->player->y += dy * 0.8f;
			}
			else if (wolf->player->down_d->wall.type_flag == 1 &&
				UP_LENGTH * wolf->player->down_d->wall.h +
					wolf->player->fly <= UP_LENGTH)
				wolf->player->y += dy;
			else if ((!wolf->player->down_d->wall.type_flag || wolf->player->down_d->wall.type_flag == 2) &&
				UP_LENGTH * wolf->player->down_d->wall.h +
					wolf->player->fly < UP_LENGTH)
				wolf->player->y += dy;
		}
		recalc(wolf);
		if (!wolf->player->in_jump)
			falling(wolf);
	}
}
