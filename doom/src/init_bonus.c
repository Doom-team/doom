/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaren <skaren@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:26:06 by skaren            #+#    #+#             */
/*   Updated: 2020/10/18 18:26:22 by skaren           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		init_bonus_load_helper1(t_wolf *wolf)
{
	if (!(wolf->bon->ak_image[0] = IMG_Load("../textures/guns/ak/0.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->ak_image[1] = IMG_Load("../textures/guns/ak/1.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->ak_image[2] = IMG_Load("../textures/guns/ak/2.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->ak_image[3] = IMG_Load("../textures/guns/ak/3.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->pistol_image[0] =
		IMG_Load("../textures/guns/pistol/0.bmp")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->pistol_image[1] =
		IMG_Load("../textures/guns/pistol/1.bmp")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->pistol_image[2] =
		IMG_Load("../textures/guns/pistol/2.bmp")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->pistol_image[3] =
		IMG_Load("../textures/guns/pistol/3.bmp")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->pistol_image[4] =
		IMG_Load("../textures/guns/pistol/4.bmp")))
		error(wolf, SDL_GetError());
}

static void		init_bonus_load_helper2(t_wolf *wolf)
{
	if (!(wolf->bon->shotgun_image[0] =
		IMG_Load("../textures/guns/shotgun/0.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->shotgun_image[1] =
		IMG_Load("../textures/guns/shotgun/1.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->shotgun_image[2] =
		IMG_Load("../textures/guns/shotgun/2.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->shotgun_image[3] =
		IMG_Load("../textures/guns/shotgun/3.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->shotgun_image[4] =
		IMG_Load("../textures/guns/shotgun/4.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->shotgun_image[5] =
		IMG_Load("../textures/guns/shotgun/5.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->shotgun_image[6] =
		IMG_Load("../textures/guns/shotgun/6.png")))
		error(wolf, SDL_GetError());
}

static void		init_bonus_load(t_wolf *wolf)
{
	init_bonus_load_helper1(wolf);
	init_bonus_load_helper2(wolf);
	if (!(wolf->bon->image_aim = IMG_Load("textures/aim.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->my_font = TTF_OpenFont("ttf/19888.ttf", (int)(H / 28))))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->music_ak = Mix_LoadWAV("../textures/guns/ak/shot.wav")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->music_pistol =
		Mix_LoadWAV("../textures/guns/pistol/shot.wav")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->music_shotgan =
		Mix_LoadWAV("../textures/guns/shotgun/shot.wav")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->key_red_tex = IMG_Load("../textures/pickup/redkey.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->key_blue_tex = IMG_Load("../textures/pickup/bluekey.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->key_yellow_tex =
		IMG_Load("../textures/pickup/yellowkey.png")))
		error(wolf, SDL_GetError());
}

void			init_bonus(t_wolf *wolf)
{
	monster_load(wolf);
	init_bonus_load(wolf);
	wolf->bon->flag_play_chunk = 0;
	wolf->bon->set_gun = 1;
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
	wolf->bon->score = 0;
	wolf->bon->key_blue = 0;
	wolf->bon->key_yellow = 0;
	wolf->bon->key_red = 0;
}
