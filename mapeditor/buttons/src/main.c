#include "../include/map.h"

void draw_gr(t_strc *strc, int x, int y, unsigned char c)
{
	int pixel;

	if (x < WIDTH && y < HEIGHT)
	{
		pixel = (x * strc->pixb) + (y * strc->strb);
		strc->s[pixel] = 0;
		strc->s[++pixel] = c;
		strc->s[++pixel] = 0;
	}
}

int init_texture(SDL_Surface *tex, unsigned char **s, unsigned char *pixb, int *strb)
{
	*s = (unsigned char*)(tex->pixels);
	*pixb = (tex->format->BytesPerPixel);
	*strb = (tex->pitch);
	return (0);
}

void	draw_color(t_strc *strc, int pixel, t_color color) // unsigned char c
{
	strc->s[pixel] = color.b;
	strc->s[++pixel] = color.g;
	strc->s[++pixel] = color.r;
}

void draw_elips(t_btn b, t_strc *strc)
{
	int x = b.xpos;
	int y = b.ypos;
	int pixel;

	y = b.ypos;
	while (y < b.ypos + b.h)
	{
		x = b.xpos;
		while (x < b.xpos + b.w)
		{
			if ((pow((abs((x) / BWIDTH)), 8) + pow(abs(((y) / BHIE)), 4)) < 1)
			{
				pixel = (x * strc->pixb) + (y * strc->strb);
				draw_color(strc, pixel, b.color); //100 + b.active * 100
			}
			x++;
		}
		y++;
	}
	printf("x = %d\n" , x);
	printf("y = %d\n" , y);
}

void draw_button(t_btn b, t_strc *strc)
{
	int x = b.xpos;
	int y = b.ypos;
	int pixel;

	y = b.ypos;
	while (y < b.ypos + b.h)
	{
		x = b.xpos;
		while (x < b.xpos + b.w)
		{
			pixel = (x * strc->pixb) + (y * strc->strb);
			draw_color(strc, pixel, b.color); //100 + b.active * 100
			x++;
		}
		y++;
	}
	printf("x = %d\n" , x);
	printf("y = %d\n" , y);
	// printf("x = %d")
}

void draw_pl(t_strc *strc)
{
	draw_gr(strc, (int)strc->plr.rxpos, (int)strc->plr.rypos, 200);
}

void draw(t_strc *strc)
{
	SDL_FillRect(strc->img, NULL, 0);
	draw_button(strc->interface.b[5], strc);
	draw_elips(strc->interface.b[0], strc);
	draw_elips(strc->interface.b[1], strc);
	draw_elips(strc->interface.b[2], strc);
	draw_button(strc->interface.b[3], strc);
	draw_button(strc->interface.b[4], strc);
	draw_pl(strc);
	SDL_UpdateWindowSurface(strc->win);
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
	init_interface(strc);

	strc->plr.xpos = 600;
	strc->plr.ypos = 600;
	strc->plr.rxpos = 600.;
	strc->plr.rypos = 600.;
	return (0);
}

void turn_btn(t_btn *b)
{
	(*b).active = !((*b).active);
}

int		press_b(t_btn b, int key, int x, int y)
{
	if (b.active && x < b.xpos + b.w && x > b.xpos && y < b.ypos + b.h && y > b.ypos)
		return (key);
	return (0);
}

int		mkey(int key, int x, int y, t_strc *strc)
{
	printf("key %d x %d y %d\n", key, x, y);
	if (press_b(strc->interface.b[0], key, x, y))
	{
		strc->plr.rypos -= 3;
	}
	if (press_b(strc->interface.b[1], key, x, y))
		strc->plr.rypos += 3;
	if (press_b(strc->interface.b[2], key, x, y))
		strc->plr.rxpos -= 3;
	if (press_b(strc->interface.b[3], key, x, y))
		strc->plr.rxpos += 3;
	if (press_b(strc->interface.b[4], key, x, y))
	{
		turn_btn(&strc->interface.b[0]);
		turn_btn(&strc->interface.b[1]);
		turn_btn(&strc->interface.b[2]);
		turn_btn(&strc->interface.b[3]);
	}
	draw(strc);
	return (0);
}

int main(int ac, char **av)
{
	t_strc *strc;
	int x = 0;
	int y = 0;
	unsigned int t;
	unsigned int t1;

	if (!(strc = (t_strc *)malloc(sizeof(t_strc))))
		return (0);
	if(init_all(strc))
	{
		printf("err\n");
		return (0);
	}
	draw(strc);
	SDL_Event event;
	int done = 0;

	t = 0;
	t1 = 0;
	// draw_button(strc->b[0], strc);
	while (!done && SDL_WaitEvent(&event))
	{
		t = SDL_GetTicks();
		// strc->plr.rypos -= ((double)t - t1)/10;
		// draw(strc);
		// printf("%u\n", t - t1);
		t1 = t;
		if (event.type == SDL_QUIT)
			done = 1;
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			SDL_GetMouseState(&x, &y);
			mkey(event.button.button, x, y, strc);
		}

		// if (event.type == SDL_KEYDOWN)
		// 	done = 1;
			// pkey((unsigned char)event.key.keysym.sym, strc);
			// printf("%d\n", (unsigned char)event.key.keysym.sym);
		
	}
	SDL_DestroyWindow(strc->win);
	SDL_Quit();
	return (0);
}
