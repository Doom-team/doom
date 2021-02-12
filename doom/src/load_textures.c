/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <skaren@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:27:09 by skaren            #+#    #+#             */
/*   Updated: 2020/10/18 18:29:01 by skaren           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	Uint32	*target_pixel;

	if (pixel == UINT32_MAX || x >= surface->w || y >= surface->h\
	|| x < 0 || y < 0)
		return ;
	target_pixel = (Uint32 *)((Uint8 *)surface->pixels + y \
	* surface->pitch + x * sizeof(*target_pixel));
	*target_pixel = pixel;
}

Uint32		get_pixel(SDL_Surface *surface, int x, int y)
{
	Uint8	*p;

	if (x >= surface->w || y >= surface->h)
		return (UINT32_MAX);
	p = (Uint8 *)surface->pixels + y * surface->pitch + x \
	* surface->format->BytesPerPixel;
	return (*(Uint32 *)p);
}
