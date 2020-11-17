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

# define WIDTH 2024
# define HEIGHT 1020

# define BWIDTH 60
#define BHIE 25
# define HUD 7
# define MAP 10

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

typedef struct	s_interface
{
	t_btn b[6];
}				t_interface;

typedef struct	s_strc
{
	SDL_Window			*win;

	SDL_Surface			*img;
	unsigned char		*s;
	unsigned char		pixb;
	int					strb;
	t_btn b[6];
	t_interface			interface;
	t_plr plr;
	int nb;

}				t_strc;




void	init_interface(t_strc *strc);
void		oneline(t_strc *strc, char *line);


#endif
