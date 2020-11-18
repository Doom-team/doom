#include "../include/map.h"

void	draw_color(t_strc *strc, int pixel, t_color color) // unsigned char c
{
	strc->s[pixel] = color.b;
	strc->s[++pixel] = color.g;
	strc->s[++pixel] = color.r;
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
			draw_color(strc, pixel, b.color);
			x++;
		}
		y++;
	}
}

void	draw_img_pix(t_strc *strc, int pixel1, int pixel2)
{
	strc->s[pixel1] = strc->b_s[pixel2];
	strc->s[++pixel1] = strc->b_s[++pixel2];
	strc->s[++pixel1] = strc->b_s[++pixel2];
}

void draw_img(t_strc *strc)
{
	int x = 0;
	int y = 0;
	int pixel1;
	int pixel2;

	y = 0;
	while (y < 320)
	{
		x = 0;
		while (x < 320)
		{
			pixel1 = (x * strc->pixb) + (y * strc->strb);
			pixel2 = (((((double)x - 0) / 320) * 320) + ((((((double)y  - 0) / 320) * 320))));
			draw_img_pix(strc, pixel1,pixel2);
			x++;
		}
		y++;
	}
}

void draw(t_strc *strc)
{
	SDL_FillRect(strc->img, NULL, 0); //залили фон цветом
	draw_button(strc->interface.b[5], strc);
	draw_button(strc->interface.b[0], strc);
	draw_button(strc->interface.b[1], strc);
	draw_button(strc->interface.b[2], strc);
	draw_button(strc->interface.b[3], strc);
	draw_button(strc->interface.b[4], strc);
	draw_img(strc);
	// draw_pl(strc);
	SDL_UpdateWindowSurface(strc->win);
}