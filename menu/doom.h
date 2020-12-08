/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 20:15:20 by ahusk             #+#    #+#             */
/*   Updated: 2020/08/13 20:15:24 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include "../doom/frameworks/SDL2.framework/Headers/SDL.h"
//# include "../doom/frameworks/SDL2_image.framework/Headers/SDL_image.h"
//# include "../doom/frameworks/SDL2_mixer.framework/Headers/SDL_mixer.h"
# include <stdbool.h>
# include <stdio.h>
# define W_W 1280
# define W_H 720
# define RGB(r, g, b) r + (g << 8) + (b << 16)

typedef struct		s_sdl
{
	SDL_Surface		*scrs;
	SDL_Renderer	*render;
	SDL_Window		*window;
	SDL_Texture		*window_texture;
	SDL_Event		e;
	unsigned char	*bytes;
	int				pitch;
	bool			run;
}					t_sdl;

typedef struct		s_position
{
	int x1;
	int x2;
	int y1;
	int y2;
}					t_position;

typedef struct		s_background
{
	SDL_Surface		*srcs;
	SDL_Surface		*texture;
	t_position		pos;
	unsigned char	*bytes_texture;
}					t_background;

typedef struct		s_button
{
	SDL_Surface		*srcs;
	SDL_Surface		*texture;
	t_position		pos;
	unsigned char	*bytes_texture;
	double			coefficient_x;
	double			coefficient_y;
}					t_button;

typedef struct		s_menu
{
	t_background background;
	t_button logo;
	t_button start;
	t_button map;
	t_button settings;
	t_button exit;
}					t_menu;

void				init_sdl(t_sdl *sdl);
void				init_menu(t_menu *menu);
void				print_menu(t_sdl *sdl, t_menu *menu);
void				create_pos_button(t_button *button, int k);
void				draw_texture(t_sdl *sdl, t_button *button, t_position *pos);

#endif
