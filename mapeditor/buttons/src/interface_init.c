#include "../include/map.h"

void init_texture(SDL_Surface *tex, unsigned char **s, unsigned char *pixb, int *strb)
{
	*s = (unsigned char*)(tex->pixels);
	*pixb = (tex->format->BytesPerPixel);
	*strb = (tex->pitch);
}

int		init_all(t_map *map)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
	if (!(map->win = SDL_CreateWindow("Proj", 200, 200, WIDTH, HEIGHT, SDL_WINDOW_SHOWN)))
		return (1);
	init_interface(map);

	// map->img2 = IMG_Load("/textures/panel.png");
	// map->img3 = IMG_Load("/textures/inpanel.png");
	// map->img4 = IMG_Load("/textures/blocks.png");
	// map->img5 = IMG_Load("/textures/texture.png");
	// map->img6 = IMG_Load("/textures/objects.png");


	// map->img2 = SDL_ConvertSurfaceFormat(map->img2, SDL_PIXELFORMAT_BGRA32, 0);
	// init_texture(map->img2, &(map->s2), &(map->pixb2), &(map->strb2));

	// map->img3 = SDL_ConvertSurfaceFormat(map->img3, SDL_PIXELFORMAT_BGRA32, 0);
	// init_texture(map->img3, &(map->s3), &(map->pixb3), &(map->strb3));

	// map->img4 = SDL_ConvertSurfaceFormat(map->img4, SDL_PIXELFORMAT_BGRA32, 0);
	// init_texture(map->img4, &(map->s4), &(map->pixb4), &(map->strb4));

	// map->img5 = SDL_ConvertSurfaceFormat(map->img5, SDL_PIXELFORMAT_BGRA32, 0);
	// init_texture(map->img5, &(map->s5), &(map->pixb5), &(map->strb5));

	// 	map->img6 = SDL_ConvertSurfaceFormat(map->img6, SDL_PIXELFORMAT_BGRA32, 0);
	// init_texture(map->img6, &(map->s6), &(map->pixb6), &(map->strb6));


	return (0);
}

// void	init_buttons(t_map *map)
// {
// 	map->interface.b[BLOCKS].xpos = 20;
// 	map->interface.b[BLOCKS].ypos = 20;
// 	map->interface.b[BLOCKS].h = BHIE;
// 	map->interface.b[BLOCKS].w = BWIDTH;
// 	map->interface.b[BLOCKS].active = 1;
// 	map->interface.b[BLOCKS].color = APPLEGREY;

// 	map->interface.b[TEXTURES].xpos = 120;
// 	map->interface.b[TEXTURES].ypos = 20;
// 	map->interface.b[TEXTURES].h = BHIE;
// 	map->interface.b[TEXTURES].w = BWIDTH;
// 	map->interface.b[TEXTURES].active = 1;
// 	map->interface.b[TEXTURES].color = APPLEGREY;

// 	map->interface.b[OBJECTS].xpos = 220;
// 	map->interface.b[OBJECTS].ypos = 20;
// 	map->interface.b[OBJECTS].h = BHIE;
// 	map->interface.b[OBJECTS].w = BWIDTH;
// 	map->interface.b[OBJECTS].active = 1;
// 	map->interface.b[OBJECTS].color = APPLEGREY;

// 	// map->interface.b[HIDE].xpos = 305;
// 	// map->interface.b[HIDE].ypos = 0;
// 	// map->interface.b[HIDE].h = 20;
// 	// map->interface.b[HIDE].w = 20;
// 	// map->interface.b[HIDE].active = 1;
// 	// map->interface.b[HIDE].color = ORANGE;

// 	// map->b[4].xpos = 300;
// 	// map->b[4].ypos = 130+500;
// 	// map->b[4].h = 25;
// 	// map->b[4].w = 50;
// 	// map->b[4].active = 1;
// 	// map->b[4].color = APPLEGREY;

// 	map->interface.b[5].xpos = 0;
// 	map->interface.b[5].ypos = 0;
// 	map->interface.b[5].h = HEIGHT;
// 	map->interface.b[5].w = 300;
// 	map->interface.b[5].active = 1;
// 	map->interface.b[5].color = WHITE;

// }

void	get_inter_textures(t_map *map)
{
	map->inter_tex[0]->img = SDL_GetWindowSurface(map->win);
	init_texture(map->inter_tex[0]->img, &(map->inter_tex[0]->s), &(map->inter_tex[0]->pixb), &(map->inter_tex[0]->strb));
	map->inter_tex[1]->img = IMG_Load("/textures/interface/panel2.png");
	map->inter_tex[2]->img = IMG_Load("/textures/interface/panelf.png");
	map->inter_tex[3]->img = IMG_Load("/textures/interface/blocks.png");
	map->inter_tex[4]->img = IMG_Load("/textures/interface/texture.png");
	map->inter_tex[5]->img = IMG_Load("/textures/interface/objects.png");

	map->inter_tex[6]->img = IMG_Load("/textures/interface/walltool.png");
	map->inter_tex[7]->img = IMG_Load("/textures/interface/cursortool.png");
	map->inter_tex[8]->img = IMG_Load("/textures/interface/removetool.png");
}


// void	get_tool_textures(t_map *map)
// {
// 	map->inter_tex[0]->img = IMG_Load("/textures/interface/walltool.png");
// 	map->inter_tex[1]->img = IMG_Load("/textures/interface/walltool.png");
// 	map->inter_tex[2]->img = IMG_Load("/textures/interface/walltool.png");
// }

void	init_interface(t_map *map)
{
	int i;

	i = -1;
	while (++i < 9)
	{
		// if (i < 4)
		// 	map->tools_tex[i] = (t_image *)malloc(sizeof(t_image));
		map->inter_tex[i] = (t_image *)malloc(sizeof(t_image));
	}
	get_inter_textures(map);
	i = 0;
	while (++i < 9)
	{
		map->inter_tex[i]->img = SDL_ConvertSurfaceFormat(map->inter_tex[i]->img, SDL_PIXELFORMAT_BGRA32, 0);
		init_texture(map->inter_tex[i]->img,&(map->inter_tex[i]->s), &(map->inter_tex[i]->pixb), &(map->inter_tex[i]->strb));
	}
	// i = -1;
	// while (++i < 4)
	// {
	// 	map->tools_tex[i]->img = SDL_ConvertSurfaceFormat(map->tools_tex[i]->img, SDL_PIXELFORMAT_BGRA32, 0);
	// 	init_texture(map->tools_tex[i]->img,&(map->tools_tex[i]->s), &(map->tools_tex[i]->pixb), &(map->tools_tex[i]->strb));
	// }
	
}