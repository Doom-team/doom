/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:32:04 by clala             #+#    #+#             */
/*   Updated: 2020/12/16 21:58:06 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		handle_other_keys(t_wolf *wolf)
{
	if (wolf->sdl->state[SDL_SCANCODE_I])
		wolf->bon->fps = wolf->bon->fps == 0 ? 1 : 0;
	if (wolf->sdl->state[SDL_SCANCODE_SPACE])
		wolf->player->fly -= 40;
		// wolf->bon->guns_fire = 1;
	if (wolf->sdl->state[SDL_SCANCODE_TAB])
	{
		if (wolf->player->fly + 40 <= 0)
			wolf->player->fly += 40;
	}
	if (wolf->sdl->state[SDL_SCANCODE_V]) // отладка
		wolf->t_cof += 0.01;
	if (wolf->sdl->state[SDL_SCANCODE_B]) // отладка
		wolf->t_cof -= 0.01;
	if (wolf->sdl->state[SDL_SCANCODE_H])
		wolf->sdl->menu = wolf->sdl->menu ? 0 : 1;
	if (wolf->sdl->state[SDL_SCANCODE_O])
	{
		if (wolf->bon->music_flag == 0)
		{
			Mix_PlayMusic(wolf->bon->music, -1);
			wolf->bon->music_flag = 1;
		}
		else
		{
			wolf->bon->music_flag = 0;
			Mix_HaltMusic();
		}
	}
}

static void		handle_keys(t_wolf *wolf, SDL_Event *event, t_map *map,
	t_player *p)
{
	const		Uint8 *s;

	s = wolf->sdl->state;
	if (event->key.keysym.sym == SDLK_ESCAPE)
		wolf->sdl->run = false;
	if (s[SDL_SCANCODE_D])
	{
		calc_move(wolf, p->speed * sinf(p->dir + RAD_90),
		-(p->speed * cosf(p->dir + RAD_90)));
		// printf("%f\n", wolf->player->rght_d);
	}
	if (s[SDL_SCANCODE_A])
		calc_move(wolf, p->speed * sinf(p->dir - RAD_90),
		-(p->speed * cosf(p->dir - RAD_90)));
	if (s[SDL_SCANCODE_DOWN] || s[SDL_SCANCODE_S])
		calc_move(wolf, p->speed * sinf(p->dir), -(p->speed * cosf(p->dir)));
	if (s[SDL_SCANCODE_W] || s[SDL_SCANCODE_UP])
		calc_move(wolf, -(p->speed * sinf(p->dir)), p->speed * cosf(p->dir));
	if ((s[SDL_SCANCODE_RIGHT] || s[SDL_SCANCODE_E])
	&& add_arc(&p->dir, -0.05))
		add_skybox_offset(wolf->sdl, W / (float)wolf->sdl->sky->w * 60.0);
	if ((s[SDL_SCANCODE_LEFT] || s[SDL_SCANCODE_Q]) && add_arc(&p->dir, 0.05))
		add_skybox_offset(wolf->sdl, W / (float)wolf->sdl->sky->w * -60.0);
	if (s[SDL_SCANCODE_P])
		wolf->sdl->sides_mode = wolf->sdl->sides_mode == 1 ? 0 : 1;
	if (s[SDL_SCANCODE_M])
		map->mm_show = map->mm_show == 1 ? 0 : 1;
	handle_other_keys(wolf);
}

static void		handle_event(t_wolf *wolf, SDL_Event *event)
{
	while (SDL_PollEvent(event))
	{
		if (event->type == SDL_QUIT)
			wolf->sdl->run = false;
		if (event->type == SDL_MOUSEMOTION)
			rotate(wolf, event);
		if (event->type == SDL_MOUSEBUTTONDOWN)
		{
			if (event->button.button == SDL_BUTTON_LEFT)
				wolf->bon->guns_fire = 1;
		}
		if (event->type == SDL_MOUSEBUTTONUP)
		{
			if (event->button.button == SDL_BUTTON_LEFT)
				wolf->bon->guns_fire = 0;
		}
		if (event->type == SDL_KEYDOWN)
			handle_keys(wolf, event, wolf->map, wolf->player);
	}
}

void			wolf_loop(t_wolf *wolf)
{
	SDL_Event	event;

	while (wolf->sdl->run)
	{
		// recalc(wolf);
		handle_event(wolf, &event);
		// draw_background(wolf->surface); // для отладки
		all_get_distance(wolf);
		pseudo_3d(wolf, wolf->player, wolf->surface);
		// render_coin(wolf, wolf->surface);
		// render_monster(wolf, wolf->surface);
		render_score_coin(wolf);
		render_fps(wolf, wolf->bon);
		render_aim(wolf);
		render_shot(wolf, wolf->surface);
		// wolf->map->mm_show ? draw_minimap(wolf, wolf->map, wolf->player) : 0;
		// wolf->sdl->menu ? draw_menu(wolf) : 0;
		SDL_UpdateWindowSurface(wolf->sdl->win);
		// printf("fly = %d, cof = %f\n", wolf->player->fly, wolf->t_cof); // для отладки кофов
	}
	// SDL_DestroyWindow(wolf->sdl->win);
	// TTF_Quit();
	// SDL_Quit();
	// exit(EXIT_SUCCESS);
}