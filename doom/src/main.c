/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:29:09 by skaren            #+#    #+#             */
/*   Updated: 2021/02/08 20:21:13 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

t_point			dot(int x, int y)
{
	t_point	new;

	new.x = x;
	new.y = y;
	return (new);
}

int				max(int a, int b)
{
	return (a > b ? a : b);
}

static t_wolf	*t_wolf_new(void)
{
	t_wolf		*new;

	!(new = (t_wolf *)malloc(sizeof(t_wolf))) ? error(new, ERR_MALLOC) : 0;
	// !(new->map = (t_map *)malloc(sizeof(t_map))) ? error(new, ERR_MALLOC) : 0;
	!(new->p = (t_parser *)malloc(sizeof(t_parser))) ? error(new, ERR_MALLOC) : 0;
	if (!(new->player = (t_player *)malloc(sizeof(t_player))))
		error(new, ERR_MALLOC);
	if (!(new->sdl = (t_sdl *)malloc(sizeof(t_sdl))))
		error(new, ERR_MALLOC);
	if (!(new->bon = (t_bonus *)malloc(sizeof(t_bonus))))
		error(new, ERR_MALLOC);
	if (!(new->menu = (t_menu *)malloc(sizeof(t_menu))))
		error(new, ERR_MALLOC);
	if (!(new->player->up_d = (t_way *)malloc(sizeof(t_way))))
		error(new, ERR_MALLOC);
	if (!(new->player->down_d = (t_way *)malloc(sizeof(t_way))))
		error(new, ERR_MALLOC);
	if (!(new->player->rght_d = (t_way *)malloc(sizeof(t_way))))
		error(new, ERR_MALLOC);
	if (!(new->player->left_d = (t_way *)malloc(sizeof(t_way))))
		error(new, ERR_MALLOC);
	parser(new);
	recalc(new);
	printf("%d\n", new->p->count_walls);
	new->t_cof = 0;
	return (new);
}

int				main()
{
	t_wolf		*wolf;

	wolf = NULL;
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	SDL_Init(SDL_INIT_EVERYTHING) != 0 ? error(wolf, SDL_GetError()) : 0;
	TTF_Init() != 0 ? error(wolf, SDL_GetError()) : 0;
	wolf = t_wolf_new();
	// printf("main %p\n", &(wolf->p->floor_texture));
	init_player(wolf, wolf->player, wolf->map);
	init_bonus(wolf);
	init_sdl(wolf);
	init_menu(wolf->menu);
	menu_loop(wolf);
	return (0);
}
