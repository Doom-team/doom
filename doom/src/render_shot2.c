/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_shot2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 21:16:53 by ahusk             #+#    #+#             */
/*   Updated: 2021/02/11 21:16:54 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		guns_shot2(SDL_Surface *screen, int flag, t_bonus *bon)
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

void			render_shot2(t_wolf *wolf, SDL_Surface *surface)
{
	if (wolf->bon->guns_fire || wolf->bon->flag_guns != 0)
	{
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
