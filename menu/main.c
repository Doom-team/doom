/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 00:19:54 by ahusk             #+#    #+#             */
/*   Updated: 2020/08/22 00:19:56 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void quit(t_sdl *sdl)
{
	SDL_DestroyRenderer(sdl->render);
	sdl->render = NULL;
	SDL_DestroyTexture(sdl->window_texture);
	sdl->window_texture = NULL;
	SDL_DestroyWindow(sdl->window);
	sdl->window = NULL;
	SDL_Quit();
}

void check_pos_button(t_sdl *sdl, t_button *button, int k)
{
	if (sdl->e.motion.x > button->pos.x1 && sdl->e.motion.x < button->pos.x2 &&
		sdl->e.motion.y > button->pos.y1 && sdl->e.motion.y < button->pos.y2)
	{
		button->coefficient_x = 3.4;
		button->coefficient_y = 7.4;
		create_pos_button(button, k);
		if (sdl->e.button.button == SDL_BUTTON_LEFT && k == 7)
			sdl->run = false;
	}
	else
	{
		button->coefficient_x = 3.56;
		button->coefficient_y = 7.8;
		create_pos_button(button, k);
	}
}

void hooks(t_sdl *sdl, t_menu *menu)
{
	while (SDL_PollEvent(&sdl->e) != 0)
	{
		if (sdl->e.type == SDL_QUIT)
			sdl->run = false;
		if (sdl->e.type == SDL_KEYDOWN)
		{
			if (sdl->e.key.keysym.sym == SDLK_ESCAPE)
				sdl->run = false;
		}
		if (sdl->e.type == SDL_MOUSEMOTION || sdl->e.type == SDL_MOUSEBUTTONDOWN)
		{
			check_pos_button(sdl, &menu->start, 4);
			check_pos_button(sdl, &menu->map, 5);
			check_pos_button(sdl, &menu->settings, 6);
			check_pos_button(sdl, &menu->exit, 7);
		}
	}
}

int main(int arg, char **argv)
{
	t_sdl sdl;
	t_menu menu;
	init_sdl(&sdl);
	init_menu(&menu);
	while (sdl.run)
	{
		hooks(&sdl, &menu);
		SDL_LockTexture(sdl.window_texture, NULL, (void**)&sdl.bytes, &sdl.pitch);
		print_menu(&sdl, &menu);
		SDL_UnlockTexture(sdl.window_texture);
		SDL_RenderCopy(sdl.render, sdl.window_texture, NULL, NULL);
		SDL_RenderPresent(sdl.render);
	}
	quit(&sdl);
	return (0);
}
