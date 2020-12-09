/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guns_shot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:25:42 by clala             #+#    #+#             */
/*   Updated: 2020/10/18 18:25:44 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	guns_shot(SDL_Surface *screen, int flag, t_bonus *bon)
{
	if (flag == 2)
	{
		Mix_Volume(0, 32);
		Mix_PlayChannel(1, bon->music_guns, 0);
		Mix_VolumeMusic(5);
	}
	flag == 1 ? SDL_BlitScaled(bon->image_1, NULL, screen,
		&bon->img_location) : 0;
	flag == 2 ? SDL_BlitScaled(bon->image_2, NULL, screen,
		&bon->img_location) : 0;
	flag == 3 ? SDL_BlitScaled(bon->image_3, NULL, screen,
		&bon->img_location) : 0;
	flag == 4 ? SDL_BlitScaled(bon->image_4, NULL, screen,
		&bon->img_location) : 0;
	flag == 5 ? SDL_BlitScaled(bon->image_5, NULL, screen,
		&bon->img_location) : 0;
}

void	render_shot(t_wolf *wolf, SDL_Surface *surface)
{
	if (wolf->bon->guns_fire || wolf->bon->flag_guns != 0)
	{
		wolf->bon->guns_fire = 0;
		if (!wolf->bon->start_guns)
		{
			wolf->bon->flag_guns++;
			wolf->bon->start_guns = SDL_GetTicks();
		}
		if (wolf->bon->start_guns + 200 < SDL_GetTicks())
		{
			wolf->bon->flag_guns++;
			wolf->bon->start_guns = SDL_GetTicks();
		}
		guns_shot(surface, wolf->bon->flag_guns, wolf->bon);
		wolf->bon->flag_guns == 5 ? wolf->bon->flag_guns = 0 : 0;
	}
	else
		guns_shot(surface, 1, wolf->bon);
}
