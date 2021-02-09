/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 20:25:38 by ahusk             #+#    #+#             */
/*   Updated: 2020/12/26 20:25:40 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	create_pos_button(t_button *button, int k)
{
	button->pos.x1 = W / 2 - (W / button->coefficient_x) / 2;
	button->pos.x2 = W / button->coefficient_x + button->pos.x1;
	button->pos.y1 = H * k / 7 - (H / button->coefficient_y);
	button->pos.y2 = H / button->coefficient_y + button->pos.y1;
}

void	create_button(t_button *button, char *file, int k)
{
	if (!(button->srcs = SDL_LoadBMP(file)))
		exit(0);
	button->texture = SDL_ConvertSurfaceFormat(button->srcs,
		SDL_PIXELFORMAT_ABGR8888, 0);
	button->bytes_texture = (unsigned char *)button->texture->pixels;
	if (k == 0)
	{
		button->pos.x1 = W / 2 - (W / 1.5) / 2;
		button->pos.x2 = W / 1.5 + button->pos.x1;
		button->pos.y1 = H * 7 / 15 - (H / 2.2);
		button->pos.y2 = H / 2.2 + button->pos.y1;
		return ;
	}
	button->coefficient_x = 3.56;
	button->coefficient_y = 7.8;
	create_pos_button(button, k);
}

void	create_background(t_background *background, char *file)
{
	if (!(background->srcs = IMG_Load(file)))
		exit(0);
	background->texture = SDL_ConvertSurfaceFormat(background->srcs,
		SDL_PIXELFORMAT_ABGR8888, 0);
	background->bytes_texture = (unsigned char *)background->texture->pixels;
	background->pos.x1 = 0;
	background->pos.x2 = W;
	background->pos.y1 = 0;
	background->pos.y2 = H;
}

void	init_menu(t_menu *menu)
{
	Mix_VolumeMusic(32);
	menu->menu_music = Mix_LoadMUS("music/Main_menu.mp3");
	menu->move_button = Mix_LoadWAV("music/move_button.wav");
	menu->click_button = Mix_LoadWAV("music/click_button.wav");
	create_background(&(menu->background), "textures/background.bmp");
	create_background(&(menu->screen_start), "textures/screen_start.bmp");
	create_background(&(menu->screen_death), "textures/screen_death.bmp");
	create_background(&(menu->screen_win), "textures/screen_win.bmp");
	create_background(&(menu->hp), "textures/hp.png");
	create_background(&(menu->hp_bar), "textures/hp_bar.png");
	create_button((&menu->logo), "textures/doom_logo.bmp", 0);
	create_button((&menu->start), "textures/start_button.bmp", 4);
	create_button((&menu->exit), "textures/exit_button.bmp", 6);
}
