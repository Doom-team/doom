/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 00:30:46 by ahusk             #+#    #+#             */
/*   Updated: 2020/08/22 00:30:47 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void init_sdl(t_sdl *sdl)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	sdl->window = SDL_CreateWindow("Doom", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W_W, W_H, SDL_WINDOW_SHOWN);
	sdl->render = SDL_CreateRenderer(sdl->window, -1, SDL_RENDERER_ACCELERATED);
	sdl->window_texture = SDL_CreateTexture(sdl->render,
											SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, W_W, W_H);
	// printf ("%p\n", &sdl->render);
	// printf ("%d\n", sdl->render);
	// sdl->scrs = SDL_GetWindowSurface(sdl->window);
	sdl->run = true;
}

void create_pos_button(t_button *button, int k)
{
	button->pos.x1 = W_W / 2 - (W_W / button->coefficient_x) / 2;
	button->pos.x2 = W_W / button->coefficient_x + button->pos.x1;
	button->pos.y1 = W_H * k / 7 - (W_H / button->coefficient_y);
	button->pos.y2 = W_H / button->coefficient_y + button->pos.y1;
}

void create_button(t_button *button, char *file, int k)
{
	button->srcs = SDL_LoadBMP(file);
	button->texture = SDL_ConvertSurfaceFormat(button->srcs, SDL_PIXELFORMAT_ABGR8888, 0);
	button->bytes_texture = (unsigned char *)button->texture->pixels;
	if (k == 0)
	{
		button->pos.x1 = W_W / 2 - (W_W / 1.5) / 2;
		button->pos.x2 = W_W / 1.5 + button->pos.x1;
		button->pos.y1 = W_H * 7 / 15 - (W_H / 2.2);
		button->pos.y2 = W_H / 2.2 + button->pos.y1;
		return;
	}
	button->coefficient_x = 3.56;
	button->coefficient_y = 7.8;
	create_pos_button(button, k);
}

void create_background(t_background *background)
{
	background->srcs = SDL_LoadBMP("background.bmp");
	background->texture = SDL_ConvertSurfaceFormat(background->srcs, SDL_PIXELFORMAT_ABGR8888, 0);
	background->bytes_texture = (unsigned char *)background->texture->pixels;
	background->pos.x1 = 0;
	background->pos.x2 = W_W;
	background->pos.y1 = 0;
	background->pos.y2 = W_H;
}

void init_menu(t_menu *menu)
{
	create_background(&menu->background);
	create_button(&menu->logo, "doom_logo.bmp", 0);
	create_button(&menu->start, "start_button.bmp", 4);
	create_button(&menu->map, "map_button.bmp", 5);
	create_button(&menu->settings, "settings_button.bmp", 6);
	create_button(&menu->exit, "exit_button.bmp", 7);
}
