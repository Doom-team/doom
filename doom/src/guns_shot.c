/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guns_shot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaren <skaren@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:25:42 by skaren            #+#    #+#             */
/*   Updated: 2020/10/18 18:25:44 by skaren           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	guns_shot1(SDL_Surface *screen, int flag, t_bonus *bon)
{
	if (flag == 2)
	{
		Mix_Volume(0, 32);
		Mix_PlayChannel(1, bon->music_pistol, 0);
	}
	flag == 1 ? SDL_BlitScaled(bon->pistol_image[0], NULL, screen,
		&bon->img_location) : 0;
	flag == 2 ? SDL_BlitScaled(bon->pistol_image[1], NULL, screen,
		&bon->img_location) : 0;
	flag == 3 ? SDL_BlitScaled(bon->pistol_image[2], NULL, screen,
		&bon->img_location) : 0;
	flag == 4 ? SDL_BlitScaled(bon->pistol_image[3], NULL, screen,
		&bon->img_location) : 0;
	flag == 5 ? SDL_BlitScaled(bon->pistol_image[4], NULL, screen,
		&bon->img_location) : 0;
}

void	guns_shot2(SDL_Surface *screen, int flag, t_bonus *bon)
{
	if (flag == 2)
	{
		Mix_Volume(0, 32);
		Mix_PlayChannel(1, bon->music_ak, 0);
	}
	flag == 1 ? SDL_BlitScaled(bon->ak_image[0], NULL, screen,
		&bon->img_location) : 0;
	flag == 2 ? SDL_BlitScaled(bon->ak_image[1], NULL, screen,
		&bon->img_location) : 0;
	flag == 3 ? SDL_BlitScaled(bon->ak_image[2], NULL, screen,
		&bon->img_location) : 0;
	flag == 4 ? SDL_BlitScaled(bon->ak_image[3], NULL, screen,
		&bon->img_location) : 0;
}

void	guns_shot3(SDL_Surface *screen, int flag, t_bonus *bon)
{
	if (flag == 2)
	{
		Mix_Volume(0, 32);
		Mix_PlayChannel(1, bon->music_pistol, 0);
	}
	flag == 1 ? SDL_BlitScaled(bon->shotgun_image[0], NULL, screen,
		&bon->img_location) : 0;
	flag == 2 ? SDL_BlitScaled(bon->shotgun_image[1], NULL, screen,
		&bon->img_location) : 0;
	flag == 3 ? SDL_BlitScaled(bon->shotgun_image[2], NULL, screen,
		&bon->img_location) : 0;
	flag == 4 ? SDL_BlitScaled(bon->shotgun_image[3], NULL, screen,
		&bon->img_location) : 0;
	flag == 5 ? SDL_BlitScaled(bon->shotgun_image[4], NULL, screen,
		&bon->img_location) : 0;
	flag == 6 ? SDL_BlitScaled(bon->shotgun_image[5], NULL, screen,
		&bon->img_location) : 0;
	flag == 7 ? SDL_BlitScaled(bon->shotgun_image[6], NULL, screen,
		&bon->img_location) : 0;
}

void	render_shot1(t_wolf *wolf, SDL_Surface *surface)
{
	if (wolf->bon->guns_fire || wolf->bon->flag_guns != 0)
	{
		// wolf->bon->guns_fire = 0;
		if (!wolf->bon->start_guns)
		{
			wolf->bon->flag_guns++;
			wolf->bon->start_guns = SDL_GetTicks();
		}
		if (wolf->bon->start_guns + 100 < SDL_GetTicks())
		{
			wolf->bon->flag_guns++;
			wolf->bon->start_guns = SDL_GetTicks();
		}
		guns_shot1(surface, wolf->bon->flag_guns, wolf->bon);
		wolf->bon->flag_guns == 5 ? wolf->bon->flag_guns = 0 : 0;
	}
	else
		guns_shot1(surface, 1, wolf->bon);
}

void	render_shot2(t_wolf *wolf, SDL_Surface *surface)
{
	if (wolf->bon->guns_fire || wolf->bon->flag_guns != 0)
	{
		// wolf->bon->guns_fire = 0;
		if (!wolf->bon->start_guns)
		{
			wolf->bon->flag_guns++;
			wolf->bon->start_guns = SDL_GetTicks();
		}
		if (wolf->bon->start_guns + 100 < SDL_GetTicks())
		{
			wolf->bon->flag_guns++;
			wolf->bon->start_guns = SDL_GetTicks();
		}
		guns_shot2(surface, wolf->bon->flag_guns, wolf->bon);
		wolf->bon->flag_guns == 4 ? wolf->bon->flag_guns = 0 : 0;
	}
	else
		guns_shot2(surface, 1, wolf->bon);
}

void	render_shot3(t_wolf *wolf, SDL_Surface *surface)
{
	if (wolf->bon->guns_fire || wolf->bon->flag_guns != 0)
	{
		// wolf->bon->guns_fire = 0;
		if (!wolf->bon->start_guns)
		{
			wolf->bon->flag_guns++;
			wolf->bon->start_guns = SDL_GetTicks();
		}
		if (wolf->bon->start_guns + 100 < SDL_GetTicks())
		{
			wolf->bon->flag_guns++;
			wolf->bon->start_guns = SDL_GetTicks();
		}
		guns_shot3(surface, wolf->bon->flag_guns, wolf->bon);
		wolf->bon->flag_guns == 7 ? wolf->bon->flag_guns = 0 : 0;
	}
	else
		guns_shot3(surface, 1, wolf->bon);
}

void	render_shot(t_wolf *wolf, SDL_Surface *surface)
{
	if (wolf->bon->set_gun == 1)
		render_shot1(wolf, surface);
	if (wolf->bon->set_gun == 2)
		render_shot2(wolf, surface);
	if (wolf->bon->set_gun == 3)
		render_shot3(wolf, surface);
}
