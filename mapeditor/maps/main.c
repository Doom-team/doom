#include "maps.h"


void	draw_floor(t_map *dm, int pixel, char c)
{
	dm->s[pixel] = c;
	dm->s[++pixel] = c;
	dm->s[++pixel] = c;
}

int init_texture(SDL_Surface *tex, unsigned char **s, unsigned char *pixb, int *strb)
{
	*s = (unsigned char*)(tex->pixels);
	*pixb = (tex->format->BytesPerPixel);
	*strb = (tex->pitch);
	return (0);
}

void draw_pixel(t_map *mp, int x, int y, unsigned char c)
{
	int pixel;

	if (x < WIDTH && y < HEIGHT)
	{
		pixel = (x * mp->pixb) + (y * mp->strb);
		draw_floor(mp, pixel, c);
	}
}

void draw_point(t_map *mp, int x, int y, unsigned char c)
{
	int i;
	int j;
	int pixel;

	i = -1;
	while (i < 1)
	{
		j = -1;
		while (j < 1)
		{
			if (x + i >= 0 && y + j >= 0 && x + i < WIDTH && y + j < HEIGHT)
			{
				pixel = ((x + i) * mp->pixb) + ((y + j) * mp->strb);
				draw_floor(mp, pixel, c);
			}
			j++;
		}
		i++;
	}
}

void draw_panel(t_map *mp)
{
	int i = 9;
	int j;

	while (++i < mp->scale + 10)
	{
		j = 12;
		while (j < WIDTH - 12)
		{
			draw_pixel(mp, j, i, 190);
			j++;
		}
	}
}

void draw_grid(t_map *mp)
{
	int pixel;
	int i;
	int j;
	// printf("draw\n");
	i = -1;
	while (++i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			if ((i - mp->z_y) % mp->dr_sc == 0 && (j - mp->z_x) % mp->dr_sc == 0)
				draw_point(mp, j, i, 100);
			else if ((i - mp->z_y) % mp->dr_sc == 0 || (j - mp->z_x) % mp->dr_sc == 0)
				draw_pixel(mp, j, i, 30);
			else
				draw_pixel(mp, j, i, 0);
			j++;
		}
	}
	draw_point(mp, mp->z_x, mp->z_y, 255);
		draw_nodes(mp);
	if (mp->click)
		draw_pr(mp, (mp->x_c * mp->scale) + mp->z_x, (mp->y_c * mp->scale) + mp->z_y, 150);
	// draw_point(mp, mp->z_x + mp->scale, mp->z_y + mp->scale, 255);
	draw_panel(mp);
	SDL_UpdateWindowSurface(mp->win);
}

int		pkey(int key, t_map *mp)
{
	if (key == 225)
		mp->sh = 1;
	if (key == 82)
	{
		mp->z_y -= 3;
	}
	if (key == 81)
	{
		mp->z_y += 3;
	}
	if (key == 79)
	{
		mp->z_x += 3;
	}
	if (key == 80)
	{
		mp->z_x -= 3;
	}
	if (key == 115 && mp->fd)
	{
		printf("save\n");
	}
	printf("%d\n", key);
	draw_grid(mp);
	return (0);
}

int		ukey(int key, t_map *mp)
{
	if (key == 225)
		mp->sh = 0;
	return (0);
}

int		mmove(int x, int y, t_map *mp)
{
	if (mp->sh == 0)
	{
		double x1 = ((double)x - mp->z_x) / mp->scale;
		double y1 = ((double)y - mp->z_y) / mp->scale;
		find_coord(mp, &x1, &y1);
		draw_grid(mp);
		draw_pr(mp, x1 * mp->scale + mp->z_x, y1 * mp->scale + mp->z_y, 150);
	}
	SDL_UpdateWindowSurface(mp->win);
	return (0);
}

int		mkey(int key, int x, int y, t_map *mp)
{
	double x1;
	double y1;
	// draw_grid(mp);
	if (key == 1)
	{
		if (mp->click == 0)
		{

			draw_point(mp, x, y, 250);
			mp->x_clck = x;
			mp->y_clck = y;
			mp->click = 1;
			mp->x_c = ((double)x - mp->z_x) / mp->scale;
			mp->y_c = ((double)y - mp->z_y) / mp->scale;
			if (mp->sh == 0)
				find_coord(mp, &(mp->x_c), &(mp->y_c));
		}
		else
		{
			// draw_line(mp, x, y);
			mp->click = 0;
			x1 = ((double)x - mp->z_x) / mp->scale;
			y1 = ((double)y - mp->z_y) / mp->scale;
			if (mp->sh == 0)
				find_coord(mp, &x1, &y1);
			add_node(mp, x1, y1);
		}
		
	}
	draw_grid(mp);
	// SDL_UpdateWindowSurface(mp->win);
	return (0);
}

int init(t_map *mp, char **av)
{
	if (!(mp->win = SDL_CreateWindow("MAPS", 100, 100, WIDTH, HEIGHT, SDL_WINDOW_SHOWN /*| SDL_WINDOW_RESIZABLE*/)))
		return (1);
	if (!(mp->img = SDL_GetWindowSurface(mp->win)))
		return (1);
	init_texture(mp->img, &(mp->s), &(mp->pixb), &(mp->strb));
	mp->z_x = WIDTH / 2;
	mp->z_y = HEIGHT / 2 + 50;
	mp->scale = 50;
	mp->dr_sc = mp->scale;
	mp->click = 0;
	mp->nod = NULL;
	mp->fd = open(av[1], O_WRONLY,O_TRUNC, O_CREAT, 0644);
	mp->sh = 0;
	return (0);
}

int main(int ac, char **av)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	// IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG);
	t_map *mp;
	int fd;
	int x = 0;
	int y = 0;

	if (!(mp = (t_map *)malloc(sizeof(t_map))))
		return (0);
	init(mp, av);
	draw_grid(mp);
	SDL_UpdateWindowSurface(mp->win);
	SDL_Event event;
	int done = 0;
	while ((!done) && SDL_WaitEvent(&event))
	{
		if (event.type == SDL_QUIT)
			done = 1;
		if (event.type == SDL_KEYDOWN)
		{
			pkey((unsigned char)event.key.keysym.sym, mp);
			// printf("%d\n", (unsigned char)event.key.keysym.sym);
			// pkey((unsigned char)event.key.keysym.sym, dm);
			// printf("%d\n", (unsigned char)event.key.keysym.sym);
		}
		if (event.type == SDL_KEYUP)
		{
			ukey((unsigned char)event.key.keysym.sym, mp);
		}
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			SDL_GetMouseState(&x, &y);
			mkey(event.button.button, x, y, mp);
		}
		if (event.type == SDL_MOUSEMOTION)
		{
			mmove(event.motion.x, event.motion.y, mp);
		}
		
	}
	SDL_DestroyWindow(mp->win);
	SDL_Quit();
	return (0);
}