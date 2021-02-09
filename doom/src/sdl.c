/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:32:04 by clala             #+#    #+#             */
/*   Updated: 2021/02/08 20:40:38 by wendell          ###   ########.fr       */
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
		else if (!wolf->player->in_jump)
			jump(wolf);
	}
		// wolf->bon->guns_fire = 1;
	if (wolf->sdl->state[SDL_SCANCODE_TAB])
	{
		if (wolf->player->fly + UP_LENGTH < 0)
			wolf->player->fly += UP_LENGTH;
		if (wolf->player->fly > 0)
			wolf->player->fly = 0;
	}
	if (wolf->sdl->state[SDL_SCANCODE_V]) // отладка
		wolf->t_cof += 0.001;
	if (wolf->sdl->state[SDL_SCANCODE_B]) // отладка
		wolf->t_cof -= 0.001;
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
		wolf->player->run_r = 1;
		wolf->player->run_l = 0;
		// calc_move(wolf, p->speed * sinf(p->dir + RAD_90),
		// -(p->speed * cosf(p->dir + RAD_90)));
	}
	if (s[SDL_SCANCODE_A])
	{
		wolf->player->run_l = 1;
		wolf->player->run_r = 0;
		// calc_move(wolf, p->speed * sinf(p->dir - RAD_90),
		// -(p->speed * cosf(p->dir - RAD_90)));
	}
	if (s[SDL_SCANCODE_DOWN] || s[SDL_SCANCODE_S])
	{
		wolf->player->run_b = 1;
		wolf->player->run_f = 0;
		// calc_move(wolf, p->speed * sinf(p->dir), -(p->speed * cosf(p->dir)));
	}
	if (s[SDL_SCANCODE_W] || s[SDL_SCANCODE_UP])
	{
		wolf->player->run_f = 1;
		wolf->player->run_b = 0;
		// calc_move(wolf, -(p->speed * sinf(p->dir)), p->speed * cosf(p->dir));
	}
	if ((s[SDL_SCANCODE_RIGHT] || s[SDL_SCANCODE_E])
	&& add_arc(&p->dir, -0.05))
		add_skybox_offset(wolf, W / (float)wolf->p->sky_texture->w * 60.0);
	if ((s[SDL_SCANCODE_LEFT] || s[SDL_SCANCODE_Q]) && add_arc(&p->dir, 0.05))
		add_skybox_offset(wolf, W / (float)wolf->p->sky_texture->w * -60.0);
	if (s[SDL_SCANCODE_P])
		wolf->sdl->sides_mode = wolf->sdl->sides_mode == 1 ? 0 : 1;
	// if (s[SDL_SCANCODE_M])
	// 	map->mm_show = map->mm_show == 1 ? 0 : 1;
	if (s[SDL_SCANCODE_U])
		wolf->player->flying = !wolf->player->flying;
	handle_other_keys(wolf);
}

static void		handle_ukeys(t_wolf *wolf, int key)
{
	if (key == 119)
		wolf->player->run_f = 0;
	if (key == 115)
		wolf->player->run_b = 0;
	if (key == 100)
		wolf->player->run_r = 0;
	if (key == 97)
		wolf->player->run_l = 0;
}

void		handle_phisics(t_wolf *wolf, t_player *p)
{
	if (wolf->player->run_b && wolf->player->run_r)
		calc_move(wolf, p->speed * sinf(p->dir + RAD_45),
		-(p->speed * cosf(p->dir + RAD_45)));
	else if (wolf->player->run_b && wolf->player->run_l)
		calc_move(wolf, p->speed * sinf(p->dir - RAD_45), -(p->speed * cosf(p->dir - RAD_45)));
	else if (wolf->player->run_f && wolf->player->run_r)
		calc_move(wolf, -(p->speed * sinf(p->dir - RAD_45)), p->speed * cosf(p->dir - RAD_45));
	else if (wolf->player->run_f && wolf->player->run_l)
		calc_move(wolf, -(p->speed * sinf(p->dir + RAD_45)), p->speed * cosf(p->dir + RAD_45));
	else if (wolf->player->run_f)
		calc_move(wolf, -(p->speed * sinf(p->dir)), p->speed * cosf(p->dir));
	else if (wolf->player->run_b)
		calc_move(wolf, p->speed * sinf(p->dir), -(p->speed * cosf(p->dir)));
	else if (wolf->player->run_l)
		calc_move(wolf, p->speed * sinf(p->dir - RAD_90),
		-(p->speed * cosf(p->dir - RAD_90)));
	else if (wolf->player->run_r)
		calc_move(wolf, p->speed * sinf(p->dir + RAD_90),
		-(p->speed * cosf(p->dir + RAD_90)));
}

void		handle_event(t_wolf *wolf, SDL_Event *event)
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
		if (event->type == SDL_KEYUP)
			handle_ukeys(wolf, (unsigned char)event->key.keysym.sym);
	}
}

void			wolf_loop(t_wolf *wolf)
{
	SDL_Event	event;

	while (wolf->sdl->run)
	{
		recalc(wolf);
		handle_event(wolf, &event);
		handle_phisics(wolf, wolf->player);
		// draw_background(wolf->surface); // для отладки
		all_get_distance(wolf);
		// printf("%f\n", wolf->player->distance[W/2]->dist[0]);
		pseudo_3d(wolf, wolf->player, wolf->surface);
		// render_coin(wolf, wolf->surface);
		// render_monster(wolf, wolf->surface);
		render_score_coin(wolf);
		render_fps(wolf, wolf->bon);
		render_aim(wolf);
		render_hud(wolf);
		render_shot(wolf, wolf->surface);
		// wolf->map->mm_show ? draw_minimap(wolf, wolf->map, wolf->player) : 0;
		// wolf->sdl->menu ? draw_menu(wolf) : 0;
		screen_death(wolf, &event);
		SDL_UpdateWindowSurface(wolf->sdl->win);
		// printf("fly = %d, cof = %f\n", wolf->player->fly, wolf->t_cof); // для отладки кофов
	}
	// SDL_DestroyWindow(wolf->sdl->win);
	// TTF_Quit();
	// SDL_Quit();
	// exit(EXIT_SUCCESS);
}