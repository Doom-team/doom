#ifndef MAP_H
# define MAP_H

#include "../SDL2/include/SDL2/SDL.h"
#include "../SDL2/include/SDL2/SDL_image.h"
// #include "SDL2/SDL.h"
#include <stdio.h>
#include <math.h>
# include <unistd.h>
#include <fcntl.h>

# define WIDTH 1024
# define HEIGHT 720
# define SCALE 50

typedef struct		s_nod
{
	short				x1;
	short				y1;
	short				x2;
	short				y2;
	struct s_nod	*nxt;
}					t_nod;

typedef struct	s_map
{
	SDL_Window			*win;

	SDL_Surface			*img;
	unsigned char		*s;
	unsigned char		pixb;
	int					strb;
	unsigned int		amask;

	SDL_Surface			*img1;
	unsigned char		*s1;
	unsigned char		pixb1;
	int					strb1;
	unsigned int 		amask1;

	t_nod *nod;

	int z_x;
	int z_y;
	int click;
	int x_clck;
	int y_clck;
	int sh;
	int fd;
}				t_map;

void draw_pixel(t_map *mp, int x, int y, unsigned char c);
void draw_line(t_map *mp, int x, int y);
void draw_point(t_map *mp, int x, int y, unsigned char c);
void draw_grid(t_map *mp);
void add_node(t_map *mp, int x, int y);
void draw_nodes(t_map *mp);
void	find_coord(t_map *mp, double *x, double *y);
void draw_pr(t_map *mp, int x, int y, unsigned char c);

#endif