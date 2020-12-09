/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 18:30:50 by wendell           #+#    #+#             */
/*   Updated: 2020/10/15 23:53:57 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	draw_floor(t_doom *dm, int pixel, char c)
{
	dm->s[pixel] = c;
	dm->s[++pixel] = c;
	dm->s[++pixel] = c;
}

void	draw_skybox(t_doom *dm)
{
	int i;
	int j;
	int pixel;
	int px1;

	i = -1;
	while (++i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT / 2)
		{
			pixel = (i * dm->pixb) + (j * dm->strb);
			px1 = ((i % dm->sk_tex->h) * dm->sk_pixb) +
			((j % dm->sk_tex->h) * dm->sk_strb);
			dm->s[pixel] = dm->sk_s[px1];
			dm->s[++pixel] = dm->sk_s[++px1];
			dm->s[++pixel] = dm->sk_s[++px1];
			j++;
		}
	}
}

void	draw_wall(t_doom *dm, int pixel, int y)
{
	int px1;

	px1 = (dm->tex_x * dm->wl_pixb[dm->ntex])
	+ (y * dm->wl_strb[dm->ntex]);
	dm->s[pixel] = dm->wl_s[dm->ntex][px1];
	dm->s[++pixel] = dm->wl_s[dm->ntex][++px1];
	dm->s[++pixel] = dm->wl_s[dm->ntex][++px1];
}

void	draw(t_doom *dm)
{
	int		i;
	int		j;
	int		pixel;
	double	l;
	double	step;

	draw_skybox(dm);
	i = -1;
	while (++i < WIDTH)
	{
		j = -1;
		l = (int)(HEIGHT / calc_d(i, dm));
		step = 1.0 * dm->wl_tex[dm->ntex]->h / l;
		while (++j < HEIGHT)
		{
			pixel = (i * dm->pixb) + (j * dm->strb);
			if (j >= (l + HEIGHT) / 2)
				draw_floor(dm, pixel, 80);
			else if (j > (HEIGHT - l) / 2)
				draw_wall(dm, pixel, (int)((j - HEIGHT / 2.0 + l / 2) * step));
		}
	}
	draw_hud(dm);
	SDL_UpdateWindowSurface(dm->win);
}
