#ifndef MAP_H
# define MAP_H

#include "../../SDL2/include/SDL2/SDL.h"
#include "../../SDL2/include/SDL2/SDL_image.h"
# include "libft.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
// #include "SDL/include/SDL_image.h"

// #include "SDL/frameworks/SDL2_image.framework/Headers/SDL_image.h"
#include <stdio.h>
// #include <SDL2/SDL.h>
// #include "SDL.h"

# define RED (t_color){255, 0, 0}
# define ORANGE (t_color){255, 150, 0}
# define YELLOW (t_color){255, 255, 0}
# define GREEN (t_color){0, 255, 0}
# define BLUE (t_color){0, 0, 255}
# define PINK (t_color){255, 0, 255}
# define APPLEGREY (t_color){125, 125, 125}
# define WHITE (t_color){255, 255, 255}

# define WIDTH 1224
# define HEIGHT 820
# define SCALE 50

// # define BWIDTH 60
// #define BHIE 25
// # define HUD 7
// # define MAP 10

enum				e_lighttypes
{
	BLOCKS = 0,
	TEXTURES,
	OBJECTS,
	HIDE
};

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct	s_plr
{
	int	xpos;
	int	ypos;
	double rxpos;
	double rypos;

}				t_plr;

typedef struct	s_btn
{
	int			xpos;
	int			ypos;
	int			h;
	int			w;
	int			active;
	t_color		color;
}				t_btn;

typedef struct	s_win
{
	int	xpos;
	int	ypos;
	int h;
	int w;
}				t_win;


typedef struct	s_image
{
SDL_Surface			*img;
unsigned char		*s;
unsigned char		pixb;
int					strb;
}					t_image;


typedef struct	s_interface
{
	t_btn				b[6];
	t_image			*inter_tex[6];
	// // SDL_Surface			*b_img;
	// unsigned char		*s;
	// unsigned char		pixb;
	// int					strb;
}				t_interface;

typedef struct	s_map
{
	SDL_Window			*win;

	// t_interface			*interface;
	t_image				*inter_tex[9];
	// t_image				*tools_tex[4];
	// t_plr				plr;
	// int					nb;

	int					z_x;
	int					z_y;

}				t_map;




void	init_interface(t_map *map);
int		init_all(t_map *map);
void	init_texture(SDL_Surface *tex, unsigned char **s, unsigned char *pixb, int *strb);
void	get_inter_textures(t_map *map);


// void	draw_color(t_map *map, int pixel, t_color color);
void	draw_img(t_map *map, int inx, int x, int y, int wdth, int hth);
// void	draw_button(t_btn b, t_map *map);
void	draw(t_map *map);



// void turn_btn(t_btn *b);
// int		press_b(t_btn b, int key, int x, int y);
// int		mkey(int key, int x, int y, t_map *map);

#endif
