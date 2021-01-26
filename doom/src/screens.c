/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screens.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:43:38 by ahusk             #+#    #+#             */
/*   Updated: 2021/01/26 15:43:39 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void	hooks_screen(t_sdl *sdl, t_menu *menu)
{
	while (SDL_PollEvent(&sdl->e) != 0)
	{
		if (sdl->e.type == SDL_QUIT)
			sdl->button_flag = 1;
		if (sdl->e.type == SDL_KEYDOWN)
		{
			if (sdl->e.key.keysym.sym == SDLK_ESCAPE)
				sdl->button_flag = 1;
			if (sdl->e.key.keysym.sym == SDLK_RETURN)
				sdl->run_screen = false;
		}
	}
}

void		screen_start(t_wolf *wolf)
{
	hooks_screen(wolf->sdl, wolf->menu);
	SDL_LockTexture(wolf->sdl->window_texture, NULL,
		(void**)&wolf->sdl->bytes, &wolf->sdl->pitch);
	draw_button(wolf->sdl, (t_button *)&wolf->menu->screen_start);
	SDL_UnlockTexture(wolf->sdl->window_texture);
	SDL_RenderCopy(wolf->sdl->render,
		wolf->sdl->window_texture, NULL, NULL);
	SDL_RenderPresent(wolf->sdl->render);
	if (wolf->sdl->button_flag == 1)
		quit(wolf->sdl);
}

void		screen_death(t_wolf *wolf)
{
	hooks_screen(wolf->sdl, wolf->menu);
	SDL_LockTexture(wolf->sdl->window_texture, NULL,
		(void**)&wolf->sdl->bytes, &wolf->sdl->pitch);
	draw_button(wolf->sdl, (t_button *)&wolf->menu->screen_death);
	SDL_UnlockTexture(wolf->sdl->window_texture);
	SDL_RenderCopy(wolf->sdl->render,
		wolf->sdl->window_texture, NULL, NULL);
	SDL_RenderPresent(wolf->sdl->render);
	if (wolf->sdl->button_flag == 1)
		quit(wolf->sdl);
}

void		screen_win(t_wolf *wolf)
{
	hooks_screen(wolf->sdl, wolf->menu);
	SDL_LockTexture(wolf->sdl->window_texture, NULL,
		(void**)&wolf->sdl->bytes, &wolf->sdl->pitch);
	draw_button(wolf->sdl, (t_button *)&wolf->menu->screen_win);
	SDL_UnlockTexture(wolf->sdl->window_texture);
	SDL_RenderCopy(wolf->sdl->render,
		wolf->sdl->window_texture, NULL, NULL);
	SDL_RenderPresent(wolf->sdl->render);
	if (wolf->sdl->button_flag == 1)
		quit(wolf->sdl);
}
