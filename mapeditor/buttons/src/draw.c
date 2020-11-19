#include "../include/map.h"

// int init_texture(SDL_Surface *tex, unsigned char **s, unsigned char *pixb, int *strb)
// {
// 	*s = (unsigned char*)(tex->pixels);
// 	*pixb = (tex->format->BytesPerPixel);
// 	*strb = (tex->pitch);
// 	return (0);
// }

// void draw_pixel(t_map *mp, int x, int y, unsigned char c)
// {
// 	int pixel;

// 	if (x < WIDTH && y < HEIGHT)
// 	{
// 		pixel = (x * mp->pixb) + (y * mp->strb);
// 		draw_floor(mp, pixel, c);
// 	}
// }

// void draw_point(t_map *mp, int x, int y, unsigned char c)
// {
// 	int i;
// 	int j;
// 	int pixel;

// 	i = -1;
// 	while (i < 1)
// 	{
// 		j = -1;
// 		while (j < 1)
// 		{
// 			if (x + i >= 0 && y + j >= 0 && x + i < WIDTH && y + j < HEIGHT)
// 			{
// 				pixel = ((x + i) * mp->pixb) + ((y + j) * mp->strb);
// 				draw_floor(mp, pixel, c);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void draw_gr(t_map *mp, int x, int y, unsigned char c)
// {
// 	int pixel;

// 	if (x < WIDTH && y < HEIGHT)
// 	{
// 		pixel = (x * mp->pixb) + (y * mp->strb);
// 		mp->s[pixel] = 0;
// 		mp->s[++pixel] = c;
// 		mp->s[++pixel] = 0;
// 	}
// }

// void draw_pr(t_map *mp, int x, int y, unsigned char c)
// {
// 	int pixel;

// 	if (x < WIDTH && y < HEIGHT)
// 	{
// 		pixel = (x * mp->pixb) + (y * mp->strb);
// 		mp->s[pixel] = c;
// 		mp->s[++pixel] = 0;
// 		mp->s[++pixel] = c;
// 	}
// }

// void draw_node(t_map *mp, t_nod *n)
// {
// 	int x1 = n->x1 + mp->z_x;
// 	int x2 = n->x2 + mp->z_x;
// 	if (x1 < 0 && x2 < 0)
// 		return;
// 	int y1 = n->y1 + mp->z_y;
// 	int y2 = n->y2 + mp->z_y;
// 	int dx = abs(x1 - x2);
// 	int dy = abs(y1 - y2);
// 	int er = 0;
// 	int de = dy + 1;
// 	int j = y1;
// 	int diry;
// 	int i = x1;
// 	int di = 0;
// 	if (dx > dy)
// 	{
// 		i = x1;
// 		j = y1;
// 		di = (x2 - x1) / dx;
// 		diry = y2 - y1;
// 		de = dy + 1;
// 		if (diry > 0)
// 			diry = 1;
// 		if (diry < 0)
// 			diry = -1;
		
// 		while (i != x2)
// 		{
// 			draw_gr(mp, i, j, 80);
// 			er += de;
// 			if (er >= dx + 1)
// 			{
// 				j += diry;
// 				er = er - (dx + 1);
// 			}
// 			i += di;
// 		}
// 	}
// 	else if (dy != 0)
// 	{
// 		i = y1;
// 		j = x1;
// 		di = (y2 - y1) / dy;
// 		diry = x2 - x1;
// 		de = dx + 1;
// 		if (diry > 0)
// 			diry = 1;
// 		if (diry < 0)
// 			diry = -1;
		
// 		while (i != y2)
// 		{
// 			draw_gr(mp, j, i, 80);
// 			er += de;
// 			if (er >= dy + 1)
// 			{
// 				j += diry;
// 				er = er - (dy + 1);
// 			}
// 			i += di;
// 		}
// 	}
// 	draw_pixel(mp, x1, y1, 250);
// 	draw_pixel(mp, x2, y2, 250);
// }

// void draw_nodes(t_map *mp)
// {
// 	t_nod *n;

// 	n = mp->nod;
// 	if (n == NULL)
// 		return;
// 	while (n)
// 	{
// 		draw_node(mp, n);
// 		n = n->nxt;
// 	}
// }

// void	draw_color(t_map *map, int pixel, t_color color) // unsigned char c
// {
// 	map->s[pixel] = color.b;
// 	map->s[++pixel] = color.g;
// 	map->s[++pixel] = color.r;
// }

// void draw_img(t_map *map, int x, int y, int wdth, int hth)
// {
// 	int i;
// 	int j;
// 	int pixel1;
// 	int pixel2;

// 	i = y;
// 	while (i < HEIGHT && i < y + hth)
// 	{
// 		j = x;
// 		while (j < WIDTH && j < x + wdth)
// 		{
// 			map->interface->inter_tex[0]->strb
// 			pixel1 = i * mp->strb + j * mp->pixb;
// 			pixel2 = (int)((double)(i-y)/hth *mp->img1->h) * mp->strb1 + (int)((double)(j - x)/wdth*mp->img1->w) * mp->pixb1;
// 			mp->s[pixel1] = mp->s1[pixel2];
// 			mp->s[++pixel1] = mp->s1[++pixel2];
// 			mp->s[++pixel1] = mp->s1[++pixel2];
// 			j++;
// 		}
// 		i++;
// 	}
// }
void draw_img(t_map *map, int inx, int x, int y, int wdth, int hth)
{
	int i;
	int j;
	int pixel1;
	int pixel2;

	i = y;
	while (i < HEIGHT && i < y + hth)
	{
		j = x;
		while (j < WIDTH && j < x + wdth)
		{
			
			pixel1 = i * map->inter_tex[0]->strb + j * map->inter_tex[0]->pixb;

			pixel2 = (int)((double)(i-y)/hth * map->inter_tex[inx]->img->h) * map->inter_tex[inx]->strb + (int)((double)(j - x)/wdth * map->inter_tex[inx]->img->w) * map->inter_tex[inx]->pixb;
			map->inter_tex[0]->s[pixel1] = map->inter_tex[inx]->s[pixel2];
			map->inter_tex[0]->s[++pixel1] = map->inter_tex[inx]->s[++pixel2];
			map->inter_tex[0]->s[++pixel1] = map->inter_tex[inx]->s[++pixel2];
			j++;
		}
		i++;
	}
}

// void draw_img(t_map *map, int inx, int x, int y, int wdth, int hth) --------- one struct
// {
// 	int i;
// 	int j;
// 	int pixel1;
// 	int pixel2;

// 	i = y;
// 	while (i < HEIGHT && i < y + hth)
// 	{
// 		j = x;
// 		while (j < WIDTH && j < x + wdth)
// 		{
			
// 			pixel1 = i * map->strb + j * map->pixb;

// 			pixel2 = (int)((double)(i-y)/hth * map->img2->h) * map->strb2 + (int)((double)(j - x)/wdth * map->img2->w) * map->pixb2;
// 			map->s[pixel1] = map->s2[pixel2];
// 			map->s[++pixel1] = map->s2[++pixel2];
// 			map->s[++pixel1] = map->s2[++pixel2];
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void draw_button(t_btn b, t_map *map)
// {
// 	int x = b.xpos;
// 	int y = b.ypos;
// 	int pixel;

// 	y = b.ypos;
// 	while (y < b.ypos + b.h)
// 	{
// 		x = b.xpos;
// 		while (x < b.xpos + b.w)
// 		{
// 			pixel = (x * map->pixb) + (y * map->strb);
// 			draw_color(map, pixel, b.color);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// void	draw_img_pix(t_map *map, int pixel1, int pixel2)
// {
// 	map->s[pixel1] = map->b_s[pixel2];
// 	map->s[++pixel1] = map->b_s[++pixel2];
// 	map->s[++pixel1] = map->b_s[++pixel2];
// }

void draw(t_map *map)
{
	SDL_FillRect(map->inter_tex[0]->img, NULL, 0);
	draw_img(map, 1, 0, 0, 300, HEIGHT);
	draw_img(map, 2, 10, 130, 280, HEIGHT - 150);
	draw_img(map, 3, 20, 20, 70, 30);
	draw_img(map, 4, 110, 20, 70, 30);
	draw_img(map, 5, 200, 20, 70, 30);


	// draw_pl(map);
	SDL_UpdateWindowSurface(map->win);
}