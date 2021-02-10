/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:26:06 by clala             #+#    #+#             */
/*   Updated: 2020/10/18 18:26:22 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	init_bonus_load(t_wolf *wolf)
{
	wolf->bon->ak_image[0] = IMG_Load("../textures/guns/ak/0.png");
	wolf->bon->ak_image[1] = IMG_Load("../textures/guns/ak/1.png");
	wolf->bon->ak_image[2] = IMG_Load("../textures/guns/ak/2.png");
	wolf->bon->ak_image[3] = IMG_Load("../textures/guns/ak/3.png");
	wolf->bon->pistol_image[0] = IMG_Load("../textures/guns/pistol/0.png");
	wolf->bon->pistol_image[1] = IMG_Load("../textures/guns/pistol/1.png");
	wolf->bon->pistol_image[2] = IMG_Load("../textures/guns/pistol/2.png");
	wolf->bon->pistol_image[3] = IMG_Load("../textures/guns/pistol/3.png");
	wolf->bon->pistol_image[4] = IMG_Load("../textures/guns/pistol/4.png");
	wolf->bon->shotgun_image[0] = IMG_Load("../textures/guns/shotgun/0.png");
	wolf->bon->shotgun_image[1] = IMG_Load("../textures/guns/shotgun/1.png");
	wolf->bon->shotgun_image[2] = IMG_Load("../textures/guns/shotgun/2.png");
	wolf->bon->shotgun_image[3] = IMG_Load("../textures/guns/shotgun/3.png");
	wolf->bon->shotgun_image[4] = IMG_Load("../textures/guns/shotgun/4.png");
	wolf->bon->shotgun_image[5] = IMG_Load("../textures/guns/shotgun/5.png");
	wolf->bon->shotgun_image[6] = IMG_Load("../textures/guns/shotgun/6.png");
	wolf->bon->image_aim = IMG_Load("textures/aim.png");
	wolf->bon->my_font = TTF_OpenFont("ttf/19888.ttf", (int)(H / 28));
	// wolf->bon->music_guns = Mix_LoadWAV("music/01664_q6IhiXXL.wav");
	wolf->bon->music_ak = Mix_LoadWAV("../textures/guns/ak/shot.wav");
	wolf->bon->music_pistol = Mix_LoadWAV("../textures/guns/pistol/shot.wav");
	wolf->bon->music_shotgan = Mix_LoadWAV("../textures/guns/shotgan/shot.wav");
	// wolf->bon->music_coin = Mix_LoadWAV("music/coin_m.wav");
	// wolf->bon->music = Mix_LoadMUS("music/Oto Kapanadze - Mystic Mountain.mp3");
	// if (!wolf->bon->image_1 || !wolf->bon->image_2 || !wolf->bon->image_3 ||
	// 	!wolf->bon->image_4 || !wolf->bon->image_5 ||
	// 	!wolf->bon->my_font ||
	// 	!wolf->bon->music_guns ||
	// 	!wolf->bon->music || !wolf->bon->music_coin ||
	// 	!wolf->bon->image_aim)
	// 	error(wolf, SDL_GetError());
	//  ПРОВЕРКИ НЕТУ !!!!!
}

void	init_bonus(t_wolf *wolf)
{
	init_bonus_load(wolf);
	wolf->bon->set_gun = 1;
	wolf->monster->penetration_flag = 0;
	wolf->bon->fps = 1;
	wolf->bon->start_time = 0;
	wolf->bon->fps_count = 0;
	wolf->bon->guns_fire = 0;
	wolf->bon->img_location.w = W / 3;
	wolf->bon->img_location.h = H / 3;
	wolf->bon->img_location.x = (W / 2) - (W / 6);
	wolf->bon->img_location.y = H - H / 3;
	wolf->bon->flag_guns = 0;
	wolf->bon->start_guns = 0;
	wolf->monster->score_coin = 0;
}
