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

void	render_hud(t_wolf *wolf)
{
	SDL_Rect	img_location;

	img_location = set_rect_sdl(W / 19, H * 13 / 16,
		(W * 11 / 40) * (wolf->player->hp / 100), H / 15);
	SDL_BlitScaled(wolf->menu->hp_bar.texture,
		NULL, wolf->surface, &img_location);
	img_location = set_rect_sdl(0, H * 8 / 10, W / 3, H / 11);
	SDL_BlitScaled(wolf->menu->hp.texture, NULL, wolf->surface, &img_location);
}
