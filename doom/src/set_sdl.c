/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sdl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:31:59 by clala             #+#    #+#             */
/*   Updated: 2020/10/18 19:43:59 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

SDL_Color	set_color_sdl(int a, int b, int c)
{
	SDL_Color	color;

	color.r = a;
	color.g = b;
	color.b = c;
	color.a = 255;
	return (color);
}

SDL_Rect	set_rect_sdl(int x, int y, int w, int h)
{
	SDL_Rect	location;

	location.x = x;
	location.y = y;
	location.w = w;
	location.h = h;
	return (location);
}
