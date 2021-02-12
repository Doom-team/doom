/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:26:06 by skaren            #+#    #+#             */
/*   Updated: 2021/02/12 02:47:13 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		init_player_help(t_player *p)
{
	p->hp = 100.0f;
	p->num_ammo = 10;
	p->speed = 0.11f;
	p->fov = RAD_60;
	p->dir = RAD_270;
	p->dir_y = 0;
	p->fly = 0;
}

void			init_player(t_wolf *wolf, t_player *p)
{
	int	i;

	i = -1;
	while (++i < W)
	{
		p->distance_horiz[i] = t_distance_new(wolf);
		p->distance_vert[i] = t_distance_new(wolf);
	}
	init_player_help(p);
	p->dist_to_canvas = (W / 2) / tan(p->fov / 2);
	p->step = p->fov / W;
	p->floor_offset = 0;
	p->flying = 0;
	p->inside_step = 0;
	p->in_jump = 0;
	p->run_b = 0;
	p->run_f = 0;
	p->run_r = 0;
	p->run_l = 0;
	p->y = wolf->p->player.y;
	p->x = wolf->p->player.x;
	p->dist_obj = MAXFLOAT;
	p->dist_mon = MAXFLOAT;
}

void			init_sdl(t_wolf *wolf)
{
	wolf->sdl->win = SDL_CreateWindow("Doom", SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN);
	wolf->sdl->render = SDL_CreateRenderer(wolf->sdl->win, -1,
		SDL_RENDERER_ACCELERATED);
	wolf->sdl->window_texture = SDL_CreateTexture(wolf->sdl->render,
		SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, W, H);
	!wolf->sdl->win ? error(wolf, SDL_GetError()) : 0;
	if (!(wolf->sdl->icon = SDL_LoadBMP(ICON_PATH)))
		error(wolf, SDL_GetError());
	SDL_SetWindowIcon(wolf->sdl->win, wolf->sdl->icon);
	wolf->sdl->sides_mode = 1;
	wolf->sdl->skybox_offset = 0;
	wolf->sdl->skybox_offset_y = 0;
	wolf->sdl->run = 1;
	wolf->sdl->menu = 0;
	wolf->sdl->state = SDL_GetKeyboardState(NULL);
	wolf->sdl->interlaced_rendering = 0;
	wolf->sdl->run_menu = true;
	wolf->sdl->run_screen = true;
}
