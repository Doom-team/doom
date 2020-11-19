#include "doom.h"

void	rotate(t_doom *dm, int angl)
{
	double x;
	double y;
	double rangl;

	rangl = angl * RANGL;
	x = dm->dir_x;
	y = dm->dir_y;
	dm->dir_x = cos(rangl) * x - sin(rangl) * y;
	dm->dir_y = sin(rangl) * x + cos(rangl) * y;
	x = dm->cam_x;
	y = dm->cam_y;
	dm->cam_x = cos(rangl) * x - sin(rangl) * y;
	dm->cam_y = sin(rangl) * x + cos(rangl) * y;
}

int init_texture(SDL_Surface *tex, unsigned char **s, unsigned char *pixb, int *strb)
{
	*s = (unsigned char*)(tex->pixels);
	*pixb = (tex->format->BytesPerPixel);
	*strb = (tex->pitch);
	return (0);
}

int		init_tex1(t_doom *dm)
{
	// dm->sk_tex = IMG_Load("pics/w1.bmp");
	if (!(dm->sk_tex = IMG_Load("pics/sk.png")))
		return(1);
	dm->sk_tex = SDL_ConvertSurfaceFormat(dm->sk_tex, SDL_PIXELFORMAT_BGRA32, 0);
	init_texture(dm->sk_tex, &dm->sk_s, &dm->sk_pixb, &dm->sk_strb);
	if (!(dm->h_tex[0] = IMG_Load("pics/w0.bmp")))
		return(1);
	if (!(dm->h_tex[1] = IMG_Load("pics/w1.bmp")))
		return(1);
	if (!(dm->h_tex[2] = IMG_Load("pics/w2.bmp")))
		return(1);
	int i;
	i = -1;
	while (++i < 3)
		dm->h_tex[i] = SDL_ConvertSurfaceFormat(dm->h_tex[i], SDL_PIXELFORMAT_BGRA32, 0);
	i = -1;
	while (++i < 3)
		init_texture(dm->h_tex[i], &dm->h_s[i], &dm->h_pixb[i], &dm->h_strb[i]);
	return (0);
}

int		init_tex(t_doom *dm)
{
	int i;

	if (!(dm->wl_tex[0] = IMG_Load("pics/wl0.png")))
		return (1);
	if (!(dm->wl_tex[1] = IMG_Load("pics/wl1.png")))
		return (1);
	if (!(dm->wl_tex[2] = IMG_Load("pics/wl2.png")))
		return (1);
	if (!(dm->wl_tex[3] = IMG_Load("pics/wl3.png")))
		return (1);

	i = -1;
	while (++i < 4)
		dm->wl_tex[i] = SDL_ConvertSurfaceFormat(dm->wl_tex[i], SDL_PIXELFORMAT_BGRA32, 0);

	i = -1;
	while (++i < 4)
		init_texture(dm->wl_tex[i], &dm->wl_s[i], &dm->wl_pixb[i], &dm->wl_strb[i]);
	init_tex1(dm);
	return (0);
}

int		init_all(t_doom *dm)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
	if (!(dm->win = SDL_CreateWindow("Doom", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN)))
		return (1);
	if (!(dm->img = SDL_GetWindowSurface(dm->win)))
		return (1);
	init_texture(dm->img, &(dm->s), &(dm->pixb), &(dm->strb));
	dm->tic = 0;
	dm->bool_tic = 0;
	dm->sh = 0;
	dm->dir_x = -1;
	dm->dir_y = 0;
	dm->cam_x = 0;
	dm->cam_y = 0.75;
	dm->ntex = 0;
	dm->mp = 0;
	dm->mapw = 0;
	dm->maph = 0;
	init_tex(dm);
	return (0);
}

int main(int ac, char **av)
{
	t_doom *dm;

	if (!(dm = (t_doom *)malloc(sizeof(t_doom))))
		return (0);
	if(init_all(dm))
	{
		printf("err\n");
		return (0);
	}
	if (!(readmap(dm, av[1])))
		return (0);
	draw(dm);
	SDL_UpdateWindowSurface(dm->win);
	SDL_Event event;
	int done = 0;
	while ((!done) && SDL_WaitEvent(&event))
	{
		if (event.type == SDL_QUIT)
			done = 1;
		if (event.type == SDL_KEYDOWN)
			pkey((unsigned char)event.key.keysym.sym, dm);
			// printf("%d\n", (unsigned char)event.key.keysym.sym);
		
	}
	SDL_DestroyWindow(dm->win);
	SDL_Quit();
	return (0);
}
