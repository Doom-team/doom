/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 18:57:16 by wendell           #+#    #+#             */
/*   Updated: 2020/10/15 23:54:00 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	tics(t_doom *dm)
{
	if (dm->bool_tic)
		dm->tic--;
	else
		dm->tic++;
	if (dm->tic == 0 || dm->tic == 10)
		dm->bool_tic = !dm->bool_tic;
}

void	draw_map(t_doom *dm)
{
	int i;
	int j;
	int pixel;

	i = -1;
	while (++i < dm->maph * MAP)
	{
		j = -1;
		while (++j < dm->mapw * MAP)
		{
			pixel = (i * dm->pixb) + (j * dm->strb);
			if (i / MAP == (int)dm->ppos_x && j / MAP == (int)dm->ppos_y)
			{
				dm->s[pixel] = (char)(120);
				dm->s[++pixel] = (char)(200);
				dm->s[++pixel] = (char)(30);
			}
			else if (dm->map[i / MAP][j / MAP] == 1)
				draw_floor(dm, pixel, 80);
			else
				draw_floor(dm, pixel, 120);
		}
	}
}

void	draw_w(t_doom *dm, int i)
{
	int wdth;
	int j;
	int pixel;
	int px1;

	wdth = WIDTH / 2 + HUD * dm->h_tex[0]->w / 2 - 1;
	while (++i < wdth)
	{
		j = HEIGHT - HUD * dm->h_tex[0]->w + dm->tic - 1;
		while (++j < HEIGHT)
		{
			pixel = (i * dm->pixb) + (j * dm->strb);
			px1 = ((i - (WIDTH / 2 - HUD * dm->h_tex[0]->w / 2 - 1)) / HUD *
			dm->h_pixb[0]) + ((j - dm->tic - (HEIGHT - HUD * dm->h_tex[0]->h))
			/ HUD * dm->h_strb[0]);
			if (dm->h_s[0][px1] != 136 || dm->h_s[0][px1 + 2] != 152)
			{
				dm->s[pixel] = dm->h_s[0][px1];
				dm->s[++pixel] = dm->h_s[0][++px1];
				dm->s[++pixel] = dm->h_s[0][++px1];
			}
		}
	}
}

void	draw_wf(t_doom *dm, int i)
{
	int wdth;
	int j;
	int pixel;
	int px1;

	wdth = WIDTH / 2 + HUD * dm->h_tex[1 + dm->tic % 2]->w / 2 - 1;
	while (++i < wdth)
	{
		j = HEIGHT - HUD * dm->h_tex[1 + dm->tic % 2]->h + dm->tic - 1;
		while (++j < HEIGHT)
		{
			pixel = (i * dm->pixb) + (j * dm->strb);
			px1 = ((i - (WIDTH / 2 - HUD * dm->h_tex[1 + dm->tic % 2]->w / 2 -
			1)) / HUD * dm->h_pixb[1 + dm->tic % 2]) + ((j - dm->tic -
			(HEIGHT - HUD * dm->h_tex[1 + dm->tic % 2]->h)) / HUD * dm->h_strb[1
			+ dm->tic % 2]);
			if (dm->h_s[1 + dm->tic % 2][px1] != 136 || dm->h_s[1 + dm->tic
			% 2][px1 + 1] != 0 || dm->h_s[1 + dm->tic % 2][px1 + 2] != 152)
			{
				dm->s[pixel] = dm->h_s[1 + dm->tic % 2][px1];
				dm->s[++pixel] = dm->h_s[1 + dm->tic % 2][++px1];
				dm->s[++pixel] = dm->h_s[1 + dm->tic % 2][++px1];
			}
		}
	}
}

void	draw_hud(t_doom *dm)
{
	int i;

	i = WIDTH / 2 - HUD * dm->h_tex[0]->w / 2 - 1;
	if (!dm->f)
		draw_w(dm, i);
	else
		draw_wf(dm, i);
	if (dm->mp)
		draw_map(dm);
}
