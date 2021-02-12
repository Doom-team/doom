/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:32:04 by skaren            #+#    #+#             */
/*   Updated: 2021/02/12 03:29:11 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		handle_ukeys(t_wolf *wolf, int key)
{
	if (key == 119 || key == 70)
		wolf->player->run_f = 0;
	if (key == 115 || key == 75)
		wolf->player->run_b = 0;
	if (key == 100 || key == 50)
		wolf->player->run_r = 0;
	if (key == 97 || key == 68)
		wolf->player->run_l = 0;
}

void			handle_phisics(t_wolf *wolf, t_player *p)
{
	if (wolf->player->run_b && wolf->player->run_r)
		calc_move(wolf, p->speed * sinf(p->dir + RAD_45),
		-(p->speed * cosf(p->dir + RAD_45)));
	else if (wolf->player->run_b && wolf->player->run_l)
		calc_move(wolf, p->speed * sinf(p->dir - RAD_45),
			-(p->speed * cosf(p->dir - RAD_45)));
	else if (wolf->player->run_f && wolf->player->run_r)
		calc_move(wolf, -(p->speed * sinf(p->dir - RAD_45)),
			p->speed * cosf(p->dir - RAD_45));
	else if (wolf->player->run_f && wolf->player->run_l)
		calc_move(wolf, -(p->speed * sinf(p->dir + RAD_45)),
			p->speed * cosf(p->dir + RAD_45));
	else if (wolf->player->run_f)
		calc_move(wolf, -(p->speed * sinf(p->dir)),
			p->speed * cosf(p->dir));
	else if (wolf->player->run_b)
		calc_move(wolf, p->speed * sinf(p->dir),
			-(p->speed * cosf(p->dir)));
	else if (wolf->player->run_l)
		calc_move(wolf, p->speed * sinf(p->dir - RAD_90),
		-(p->speed * cosf(p->dir - RAD_90)));
	else if (wolf->player->run_r)
		calc_move(wolf, p->speed * sinf(p->dir + RAD_90),
		-(p->speed * cosf(p->dir + RAD_90)));
}

void			handle_event(t_wolf *wolf, SDL_Event *event)
{
	while (SDL_PollEvent(event))
	{
		if (event->type == SDL_QUIT)
			wolf->sdl->run = false;
		if (event->type == SDL_MOUSEMOTION)
			rotate(wolf, event);
		if (event->type == SDL_MOUSEBUTTONDOWN)
		{
			if (wolf->player->num_ammo > 0 && wolf->bon->guns_fire != 1)
			{
				wolf->bon->guns_fire = 1;
				wolf->player->num_ammo--;
			}
		}
		if (event->type == SDL_KEYDOWN)
			handle_keys(wolf, event);
		if (event->type == SDL_KEYUP)
			handle_ukeys(wolf, (unsigned char)event->key.keysym.sym);
	}
}

void			recalc_rotation(t_wolf *wolf)
{
	int i;

	i = 0;
	while (i < wolf->p->count_walls)
	{
		if (wolf->p->walls[i].active && wolf->p->walls[i].type_flag >= 2 &&
			wolf->p->walls[i].type_flag <= 9)
			wolf->p->walls[i] = rotate_wall(wolf->p->walls[i], wolf, i);
		if (wolf->p->walls[i].active == 1 && wolf->p->walls[i].type_flag ==
			2 && wolf->p->walls[i].opening)
			wolf->p->walls[i].h -= 0.05;
		if (wolf->p->walls[i].h <= 0.2)
		{
			wolf->p->walls[i].h = 0;
			wolf->p->walls[i].active = 0;
		}
		i++;
	}
}

void			wolf_loop(t_wolf *wolf)
{
	SDL_Event	event;

	Mix_PlayMusic(wolf->p->music, -1);
	while (wolf->sdl->run)
	{
		if (wolf->player->dist_obj != MAXFLOAT &&
			wolf->p->walls[wolf->player->indx_obj].type_flag == 9)
			screen_win(wolf, &event);
		recalc(wolf);
		handle_event(wolf, &event);
		recalc_rotation(wolf);
		handle_phisics(wolf, wolf->player);
		all_get_distance(wolf);
		pseudo_3d(wolf);
		render_score_coin(wolf);
		render_fps(wolf, wolf->bon);
		render_aim(wolf);
		render_hud(wolf);
		render_shot(wolf, wolf->surface);
		screen_death(wolf, &event);
		printf("%d %d\n", (int)(wolf->player->x * RESIZE), (int)(wolf->player->y * RESIZE));
		SDL_UpdateWindowSurface(wolf->sdl->win);
	}
}
