#ifndef DOOM_H
# define DOOM_H

#include "./SDL2/include/SDL2/SDL.h"
#include "./SDL2/include/SDL2/SDL_image.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
// #include "SDL/include/SDL_image.h"

// #include "SDL/frameworks/SDL2_image.framework/Headers/SDL_image.h"
#include <stdio.h>
// #include <SDL2/SDL.h>
// #include "SDL.h"

# define WIDTH 1024
# define HEIGHT 720
# define HUD 7
# define MAP 10
# define RANGL 0.017453292519943

typedef struct	s_dda
{
	int		step_x;
	int		step_y;
	double	side_x;
	double	side_y;
	int		hit;
	int		blck;
	double	dx;
	double	dy;

}				t_dda;

typedef struct	s_doom
{
	// void				*init;
	// void				*win;
	// void				*img;

	SDL_Window			*win;

	SDL_Surface			*img;
	unsigned char		*s;
	unsigned char		pixb;
	int					strb;

	int					**map;
	int					maph;
	int					mapw;

	double				p_angl;
	double				ppos_x;
	double				ppos_y;
	double				dir_x;
	double				dir_y;
	double				cam_x;
	double				cam_y;
	double				ray_x;
	double				ray_y;
	int					map_x;
	int					map_y;
	int					side;
	double				wall_x;
	int					tex_x;

	SDL_Surface			*wl_tex[4];
	unsigned char		*wl_s[4];
	unsigned char		wl_pixb[4];
	int					wl_strb[4];

	int					ntex;

	SDL_Surface			*sk_tex;
	unsigned char		*sk_s;
	unsigned char		sk_pixb;
	int					sk_strb;

	SDL_Surface			*h_tex[3];
	unsigned char		*h_s[3];
	unsigned char		h_pixb[3];
	int					h_strb[3];

	int					tic;
	int					bool_tic;
	int					f;
	int					sh;
	int					mp;
}				t_doom;

int		readmap(t_doom *dm, char *av);
void	draw(t_doom *dm);
double	calc_d(int i, t_doom *dm);
int		pkey(int key, t_doom *dm);
void	draw_hud(t_doom *dm);
void	rotate(t_doom *dm, int angl);
void	tics(t_doom *dm);
int		ext(t_doom *dm);
void	draw_floor(t_doom *dm, int pixel, char c);

#endif
