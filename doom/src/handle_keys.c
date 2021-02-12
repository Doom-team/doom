/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 14:03:08 by ahusk             #+#    #+#             */
/*   Updated: 2021/02/12 14:03:10 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		handle_other_keys(t_wolf *wolf)
{
	if (wolf->sdl->state[SDL_SCANCODE_I])
		wolf->bon->fps = wolf->bon->fps == 0 ? 1 : 0;
	if (wolf->sdl->state[SDL_SCANCODE_SPACE])
	{
		if (wolf->player->flying)
			wolf->player->fly -= UP_LENGTH;
		else if (!wolf->player->in_jump && abs(wolf->player->fly) ==
			wolf->player->inside_step)
			jump(wolf);
	}
	if (wolf->sdl->state[SDL_SCANCODE_TAB])
	{
		if (wolf->player->fly + UP_LENGTH < 0)
			wolf->player->fly += UP_LENGTH;
		if (wolf->player->fly > 0)
			wolf->player->fly = 0;
	}
	if (wolf->sdl->state[SDL_SCANCODE_H])
		wolf->sdl->menu = wolf->sdl->menu ? 0 : 1;
}

static void		handle_keys_helper1(t_wolf *wolf)
{
	if (wolf->p->walls[wolf->player->indx_obj].type_flag != 2)
	{
		wolf->p->walls[wolf->player->indx_obj].active = 0;
		wolf->player->dist_obj = MAXFLOAT;
	}
	if (wolf->p->walls[wolf->player->indx_obj].type_flag == 2)
	{
		if (wolf->p->walls[wolf->player->indx_obj].type_stage == 1)
			wolf->p->walls[wolf->player->indx_obj].opening = 1;
		if (wolf->p->walls[wolf->player->indx_obj].type_stage == 2 &&
			wolf->bon->key_blue)
			wolf->p->walls[wolf->player->indx_obj].opening = 1;
		if (wolf->p->walls[wolf->player->indx_obj].type_stage == 3 &&
			wolf->bon->key_yellow)
			wolf->p->walls[wolf->player->indx_obj].opening = 1;
		if (wolf->p->walls[wolf->player->indx_obj].type_stage == 4 &&
			wolf->bon->key_red)
			wolf->p->walls[wolf->player->indx_obj].opening = 1;
	}
	if (wolf->p->walls[wolf->player->indx_obj].type_flag == 4)
		wolf->player->hp = 100;
}

static void		handle_keys_helper2(t_wolf *wolf)
{
	if (wolf->p->walls[wolf->player->indx_obj].type_flag == 6 &&
		wolf->p->walls[wolf->player->indx_obj].type_stage == 1)
		wolf->bon->set_gun = 1;
	if (wolf->p->walls[wolf->player->indx_obj].type_flag == 6 &&
		wolf->p->walls[wolf->player->indx_obj].type_stage == 2)
		wolf->bon->set_gun = 2;
	if (wolf->p->walls[wolf->player->indx_obj].type_flag == 6 &&
		wolf->p->walls[wolf->player->indx_obj].type_stage == 3)
		wolf->bon->set_gun = 3;
	if (wolf->p->walls[wolf->player->indx_obj].type_flag == 6)
		wolf->player->num_ammo = 10;
	if (wolf->p->walls[wolf->player->indx_obj].type_flag == 7 &&
		wolf->p->walls[wolf->player->indx_obj].type_stage == 1 &&
			wolf->bon->set_gun == 1)
		wolf->player->num_ammo = 10;
	else if (wolf->p->walls[wolf->player->indx_obj].type_flag == 7 &&
		wolf->p->walls[wolf->player->indx_obj].type_stage == 2 &&
			wolf->bon->set_gun == 2)
		wolf->player->num_ammo = 10;
	else if (wolf->p->walls[wolf->player->indx_obj].type_flag == 7 &&
		wolf->p->walls[wolf->player->indx_obj].type_stage == 3 &&
			wolf->bon->set_gun == 3)
		wolf->player->num_ammo = 10;
	else if (wolf->p->walls[wolf->player->indx_obj].type_flag == 7)
		wolf->p->walls[wolf->player->indx_obj].active = 1;
}

static void		handle_keys_helper3(t_wolf *wolf, const Uint8 *s)
{
	if (s[SDL_SCANCODE_D])
	{
		wolf->player->run_r = 1;
		wolf->player->run_l = 0;
	}
	if (s[SDL_SCANCODE_A])
	{
		wolf->player->run_l = 1;
		wolf->player->run_r = 0;
	}
	if (s[SDL_SCANCODE_S])
	{
		wolf->player->run_b = 1;
		wolf->player->run_f = 0;
	}
	if (s[SDL_SCANCODE_W])
	{
		wolf->player->run_f = 1;
		wolf->player->run_b = 0;
	}
	if (s[SDL_SCANCODE_P])
		wolf->sdl->sides_mode = !wolf->sdl->sides_mode;
	if (s[SDL_SCANCODE_U])
		wolf->player->flying = !wolf->player->flying;
}

void			handle_keys(t_wolf *wolf, SDL_Event *event)
{
	const		Uint8 *s;

	s = wolf->sdl->state;
	if (event->key.keysym.sym == SDLK_ESCAPE)
		wolf->sdl->run = false;
	if (s[SDL_SCANCODE_F])
	{
		if (wolf->player->dist_obj <= 1.)
		{
			handle_keys_helper1(wolf);
			handle_keys_helper2(wolf);
			if (wolf->p->walls[wolf->player->indx_obj].type_flag == 8 &&
				wolf->p->walls[wolf->player->indx_obj].type_stage == 2)
				wolf->bon->key_blue = 1;
			if (wolf->p->walls[wolf->player->indx_obj].type_flag == 8 &&
				wolf->p->walls[wolf->player->indx_obj].type_stage == 3)
				wolf->bon->key_yellow = 1;
			if (wolf->p->walls[wolf->player->indx_obj].type_flag == 8 &&
				wolf->p->walls[wolf->player->indx_obj].type_stage == 4)
				wolf->bon->key_red = 1;
			wolf->player->dist_obj = MAXFLOAT;
		}
	}
	handle_keys_helper3(wolf, s);
	handle_other_keys(wolf);
}
