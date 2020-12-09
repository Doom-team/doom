/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:26:06 by clala             #+#    #+#             */
/*   Updated: 2020/10/18 18:26:22 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	init_player(t_wolf *wolf, t_player *p, t_map *map)
{
	int	i;

	i = -1;
	while (++i < W)
	{
		p->distance_horiz[i] = t_distance_new(wolf);
		p->distance_vert[i] = t_distance_new(wolf);
	}
	p->size = 10;
	p->x = CUBE * (map->player_start % map->w) + p->size;
	p->y = CUBE * (map->player_start / map->w) + p->size;
	p->speed = 10.0;
	p->fov = RAD_60;
	p->dir = RAD_0;
	p->dir_y = 0;
	p->size = 10;
	p->dist_to_canvas = (W / 2) / tan(p->fov / 2);
	p->step = p->fov / W;
	p->floor_offset = 0;
}

void	init_tex_arr(t_wolf *wolf)
{
	int	i;

	i = -1;
	wolf->sdl->tex_arr[TEX_BORDER] = CUBE * 6;
	while (++i < 1 << 8)
		wolf->sdl->tex_arr[i] = wolf->sdl->tex_arr[TEX_BORDER];
	wolf->sdl->tex_arr[TEX_WALL] = CUBE * 7;
	wolf->sdl->tex_arr[TEX_EAST] = CUBE * 2;
	wolf->sdl->tex_arr[TEX_SOUTH] = CUBE * 3;
	wolf->sdl->tex_arr[TEX_NORTH] = CUBE * 4;
	wolf->sdl->tex_arr[TEX_WEST] = CUBE * 5;
	wolf->sdl->tex_arr[TEX_BLOOD] = CUBE * 0;
	wolf->sdl->tex_arr[TEX_PANEL] = CUBE * 1;
	wolf->sdl->tex_arr[TEX_BOULD] = CUBE * 2;
	wolf->sdl->tex_arr[TEX_CORALL] = CUBE * 3;
	wolf->sdl->tex_arr[TEX_EYES] = CUBE * 4;
	wolf->sdl->tex_arr[TEX_ISLE] = CUBE * 5;
}

void	init_mm(t_map *map)
{
	int	map_max_side;

	map_max_side = max(map->w, map->h);
	map->mm_cube = (W / 3) / map_max_side;
	map->mm_start.x = 16;
	map->mm_start.y = 16;
	map->mm_w = map->mm_cube * map->w;
	map->mm_h = map->mm_cube * map->h;
	map->mm_p_size = map->mm_cube / 4;
	map->mm_cube_coef = (float)map->mm_cube / CUBE;
	map->mm_map_coef = (float)map->mm_w / W;
	map->mm_show = 1;
}

void	init_sdl(t_wolf *wolf)
{
	wolf->sdl->win = SDL_CreateWindow("Wolf3d", 100,
		100, W, H, SDL_WINDOW_SHOWN);
	!wolf->sdl->win ? error(wolf, SDL_GetError()) : 0;
	if (!(wolf->sdl->icon = SDL_LoadBMP(ICON_PATH)))
		error(wolf, SDL_GetError());
	if (!(wolf->sdl->sky = SDL_LoadBMP(SKY_PATH)))
		error(wolf, SDL_GetError());
	if (!(wolf->sdl->textures = SDL_LoadBMP(TEXTURE_PATH)))
		error(wolf, SDL_GetError());
	SDL_SetWindowIcon(wolf->sdl->win, wolf->sdl->icon);
	wolf->sdl->sides_mode = 1;
	wolf->surface = SDL_GetWindowSurface(wolf->sdl->win);
	wolf->sdl->skybox_offset = 0;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	wolf->sdl->run = 1;
	wolf->sdl->menu = 0;
	wolf->sdl->state = SDL_GetKeyboardState(NULL);
	wolf->sdl->interlaced_rendering = 0;
}
