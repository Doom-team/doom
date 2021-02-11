/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <skaren@student.42.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:27:09 by skaren            #+#    #+#             */
/*   Updated: 2020/10/18 18:29:01 by skaren           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	Uint32	*target_pixel;

	if (pixel == UINT32_MAX || x >= surface->w || y >= surface->h)
		return;
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

// void		set_pixel1(t_wolf *wolf, SDL_Surface *surface1, unsigned char *s1,
// 			int x, int y, int pixel)
// {
// 	int				pix;

// 	if (y >= H || y < 0 || y >= wolf->surface->h || x >= wolf->surface->w || pixel/4 >= (surface1->h - 1) * (surface1->w - 1))
// 		return ;
// 	pix = (x * wolf->surface->format->BytesPerPixel) + (y * wolf->surface->pitch);
// 	wolf->s[pix] = s1[pixel];
// 	wolf->s[++pix] = s1[++pixel];
// 	wolf->s[++pix] = s1[++pixel];
// }

// int			get_pixel1(SDL_Surface *surface, int x, int y)
// {
// 	int	pixel;

// 	pixel = ((x % surface->h) * surface->format->BytesPerPixel) +
// 			((y % surface->h) * surface->pitch);
// 	return (pixel);
// }

int			is_texture(t_map *map, int x, int y, char texture)
{
	return (map->map[y * map->w + x] == texture);
}
