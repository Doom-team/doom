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

static	void	monster_load_helper(t_wolf *wolf)
{
	wolf->bon->monster[0] = IMG_Load("../textures/enemy/beam/0.png");
	wolf->bon->monster[1] = IMG_Load("../textures/enemy/beam/1.png");
	wolf->bon->monster[2] = IMG_Load("../textures/enemy/beam/2.png");
	wolf->bon->monster[3] = IMG_Load("../textures/enemy/beam/3.png");
	wolf->bon->monster[4] = IMG_Load("../textures/enemy/beam/4.png");
	wolf->bon->monster[5] = IMG_Load("../textures/enemy/beam/5.png");
	wolf->bon->monster[6] = IMG_Load("../textures/enemy/abbadon/0.png");
	wolf->bon->monster[7] = IMG_Load("../textures/enemy/abbadon/1.png");
	wolf->bon->monster[8] = IMG_Load("../textures/enemy/abbadon/2.png");
	wolf->bon->monster[9] = IMG_Load("../textures/enemy/abbadon/3.png");
	wolf->bon->monster[10] = IMG_Load("../textures/enemy/abbadon/4.png");
	wolf->bon->monster[11] = IMG_Load("../textures/enemy/abbadon/5.png");
}

static	void	monster_load(t_wolf *wolf)
{
	monster_load_helper(wolf);
	wolf->bon->monster[12] = IMG_Load("../textures/enemy/arachnophyte/0.png");
	wolf->bon->monster[13] = IMG_Load("../textures/enemy/arachnophyte/1.png");
	wolf->bon->monster[14] = IMG_Load("../textures/enemy/arachnophyte/2.png");
	wolf->bon->monster[15] = IMG_Load("../textures/enemy/arachnophyte/3.png");
	wolf->bon->monster[16] = IMG_Load("../textures/enemy/arachnophyte/4.png");
	wolf->bon->monster[17] = IMG_Load("../textures/enemy/arachnophyte/5.png");
	wolf->bon->monster[18] = IMG_Load("../textures/enemy/annihilator/0.png");
	wolf->bon->monster[19] = IMG_Load("../textures/enemy/annihilator/1.png");
	wolf->bon->monster[20] = IMG_Load("../textures/enemy/annihilator/2.png");
	wolf->bon->monster[21] = IMG_Load("../textures/enemy/annihilator/3.png");
	wolf->bon->monster[22] = IMG_Load("../textures/enemy/annihilator/4.png");
	wolf->bon->monster[23] = IMG_Load("../textures/enemy/annihilator/5.png");
	wolf->bon->monster[24] = IMG_Load("../textures/enemy/hierophant/0.png");
	wolf->bon->monster[25] = IMG_Load("../textures/enemy/hierophant/1.png");
	wolf->bon->monster[26] = IMG_Load("../textures/enemy/hierophant/2.png");
	wolf->bon->monster[27] = IMG_Load("../textures/enemy/hierophant/3.png");
	wolf->bon->monster[28] = IMG_Load("../textures/enemy/hierophant/4.png");
	wolf->bon->monster[29] = IMG_Load("../textures/enemy/hierophant/5.png");
}

void			init_bonus_load(t_wolf *wolf)
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
	wolf->bon->music_ak = Mix_LoadWAV("../textures/guns/ak/shot.wav");
	wolf->bon->music_pistol = Mix_LoadWAV("../textures/guns/pistol/shot.wav");
	wolf->bon->music_shotgan = Mix_LoadWAV("../textures/guns/shotgan/shot.wav");
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
