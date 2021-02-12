/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hud.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 20:01:12 by ahusk             #+#    #+#             */
/*   Updated: 2021/02/05 20:01:14 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		render_ammo(t_wolf *wolf, SDL_Rect *img_location)
{
	int	i;

	i = -1;
	while (++i < wolf->player->num_ammo && i < 10)
	{
		*img_location = set_rect_sdl(W / 14 + (27 * i),
			H * 19 / 25, W / 50, H / 25);
		SDL_BlitScaled(wolf->menu->ammo.texture, NULL,
			wolf->surface, img_location);
	}
}

static void		render_keys(t_wolf *wolf, SDL_Rect *img_location)
{
	if (wolf->bon->key_red == 1)
	{
		*img_location = set_rect_sdl(W * 2 / 25,
			H * 24 / 27, W / 50, H / 25);
		SDL_BlitScaled(wolf->bon->key_red_tex, NULL,
			wolf->surface, img_location);
	}
	if (wolf->bon->key_blue == 1)
	{
		*img_location = set_rect_sdl(W * 3 / 25,
			H * 24 / 27, W / 50, H / 25);
		SDL_BlitScaled(wolf->bon->key_blue_tex, NULL,
			wolf->surface, img_location);
	}
	if (wolf->bon->key_yellow == 1)
	{
		*img_location = set_rect_sdl(W * 4 / 25,
			H * 24 / 27, W / 50, H / 25);
		SDL_BlitScaled(wolf->bon->key_yellow_tex, NULL,
			wolf->surface, img_location);
	}
}

void			render_hud(t_wolf *wolf)
{
	SDL_Rect	img_location;

	img_location = set_rect_sdl(W / 19, H * 13 / 16,
		(W * 11 / 40) * (wolf->player->hp / 100), H / 15);
	SDL_BlitScaled(wolf->menu->hp_bar.texture,
		NULL, wolf->surface, &img_location);
	img_location = set_rect_sdl(0, H * 8 / 10, W / 3, H / 11);
	SDL_BlitScaled(wolf->menu->hp.texture, NULL, wolf->surface, &img_location);
	render_ammo(wolf, &img_location);
	render_keys(wolf, &img_location);
}
