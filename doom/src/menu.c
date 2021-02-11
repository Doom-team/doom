/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 20:31:26 by ahusk             #+#    #+#             */
/*   Updated: 2021/02/08 19:51:35 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			quit(t_sdl *sdl)
{
	SDL_DestroyRenderer(sdl->render);
	sdl->render = NULL;
	SDL_DestroyTexture(sdl->window_texture);
	sdl->window_texture = NULL;
	SDL_DestroyWindow(sdl->win);
	sdl->win = NULL;
	TTF_Quit();
	SDL_Quit();
	exit(EXIT_SUCCESS);
}

void			check_pos_button(t_sdl *sdl,
								t_button *button, int k, t_menu *menu)
{
	if (sdl->e.motion.x > button->pos.x1 && sdl->e.motion.x < button->pos.x2 &&
		sdl->e.motion.y > button->pos.y1 && sdl->e.motion.y < button->pos.y2)
	{
		button->coefficient_x = 3.4;
		button->coefficient_y = 7.4;
		if (++button->check == 1)
			Mix_PlayChannel(1, menu->move_button, 0);
		if (sdl->e.button.button == SDL_BUTTON_LEFT)
		{
			Mix_PlayChannel(1, menu->click_button, 0);
			if (k == 4)
				sdl->button_flag = 4;
			if (k <= 6)
				sdl->run_menu = false;
		}
	}
	else
	{
		button->check = 0;
		button->coefficient_x = 3.56;
		button->coefficient_y = 7.8;
	}
	create_pos_button(button, k);
}

void			hooks(t_sdl *sdl, t_menu *menu)
{
	while (SDL_PollEvent(&sdl->e) != 0)
	{
		if (sdl->e.type == SDL_QUIT)
			sdl->run_menu = false;
		if (sdl->e.type == SDL_KEYDOWN)
		{
			if (sdl->e.key.keysym.sym == SDLK_ESCAPE)
				sdl->run_menu = false;
		}
		if (sdl->e.type == SDL_MOUSEMOTION ||
			sdl->e.type == SDL_MOUSEBUTTONDOWN)
		{
			check_pos_button(sdl, &menu->start, 4, menu);
			check_pos_button(sdl, &menu->exit, 6, menu);
		}
	}
}

static void		reinit_sdl(t_wolf *wolf)
{
	SDL_DestroyWindow(wolf->sdl->win);
	wolf->sdl->win = NULL;
	wolf->sdl->win = SDL_CreateWindow("Doom", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN);
	wolf->surface = SDL_GetWindowSurface(wolf->sdl->win);
	SDL_SetRelativeMouseMode(SDL_TRUE);
}

void			menu_loop(t_wolf *wolf)
{
	Mix_PlayMusic(wolf->menu->menu_music, -1);
	while (wolf->sdl->run_menu)
	{
		hooks(wolf->sdl, wolf->menu);
		SDL_LockTexture(wolf->sdl->window_texture, NULL,
			(void**)&wolf->sdl->bytes, &wolf->sdl->pitch);
		print_menu(wolf);
		SDL_UnlockTexture(wolf->sdl->window_texture);
		SDL_RenderCopy(wolf->sdl->render,
			wolf->sdl->window_texture, NULL, NULL);
		SDL_RenderPresent(wolf->sdl->render);
	}
	if (wolf->sdl->button_flag == 4)
	{
		screen_start(wolf);
		reinit_sdl(wolf);
		wolf_loop(wolf);
	}
	if (wolf->sdl->button_flag == 6)
		quit(wolf->sdl);
}
