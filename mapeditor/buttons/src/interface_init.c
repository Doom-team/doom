#include "../include/map.h"

int init_texture(SDL_Surface *tex, unsigned char **s, unsigned char *pixb, int *strb)
{
	*s = (unsigned char*)(tex->pixels);
	*pixb = (tex->format->BytesPerPixel);
	*strb = (tex->pitch);
	return (0);
}

int		init_all(t_strc *strc)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
	if (!(strc->win = SDL_CreateWindow("Proj", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN)))
		return (1);
	if (!(strc->img = SDL_GetWindowSurface(strc->win)))
		return (1);
	init_texture(strc->img, &(strc->s), &(strc->pixb), &(strc->strb));
	printf("1\n");
	strc->b_img = IMG_Load("qwe.jpg");
	printf("2\n");
	init_texture(strc->b_img, &(strc->b_s), &(strc->b_pixb), &(strc->b_strb));
	printf("3\n");
	init_interface(strc);
	return (0);
}

void	init_buttons(t_strc *strc)
{
	strc->interface.b[BLOCKS].xpos = 20;
	strc->interface.b[BLOCKS].ypos = 20;
	strc->interface.b[BLOCKS].h = BHIE;
	strc->interface.b[BLOCKS].w = BWIDTH;
	strc->interface.b[BLOCKS].active = 1;
	strc->interface.b[BLOCKS].color = APPLEGREY;

	strc->interface.b[TEXTURES].xpos = 120;
	strc->interface.b[TEXTURES].ypos = 20;
	strc->interface.b[TEXTURES].h = BHIE;
	strc->interface.b[TEXTURES].w = BWIDTH;
	strc->interface.b[TEXTURES].active = 1;
	strc->interface.b[TEXTURES].color = APPLEGREY;

	strc->interface.b[OBJECTS].xpos = 220;
	strc->interface.b[OBJECTS].ypos = 20;
	strc->interface.b[OBJECTS].h = BHIE;
	strc->interface.b[OBJECTS].w = BWIDTH;
	strc->interface.b[OBJECTS].active = 1;
	strc->interface.b[OBJECTS].color = APPLEGREY;

	// strc->interface.b[HIDE].xpos = 305;
	// strc->interface.b[HIDE].ypos = 0;
	// strc->interface.b[HIDE].h = 20;
	// strc->interface.b[HIDE].w = 20;
	// strc->interface.b[HIDE].active = 1;
	// strc->interface.b[HIDE].color = ORANGE;

	// strc->b[4].xpos = 300;
	// strc->b[4].ypos = 130+500;
	// strc->b[4].h = 25;
	// strc->b[4].w = 50;
	// strc->b[4].active = 1;
	// strc->b[4].color = APPLEGREY;

	strc->interface.b[5].xpos = 0;
	strc->interface.b[5].ypos = 0;
	strc->interface.b[5].h = HEIGHT;
	strc->interface.b[5].w = 300;
	strc->interface.b[5].active = 1;
	strc->interface.b[5].color = WHITE;

}

void	init_interface(t_strc *strc)
{
	init_buttons(strc);
}