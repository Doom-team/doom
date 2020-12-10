#include "../includes/wolf3d.h"

void create_pos_button(t_button *button, int k)
{
	button->pos.x1 = W / 2 - (W / button->coefficient_x) / 2;
	button->pos.x2 = W / button->coefficient_x + button->pos.x1;
	button->pos.y1 = H * k / 7 - (H / button->coefficient_y);
	button->pos.y2 = H / button->coefficient_y + button->pos.y1;
}

void create_button(t_button *button, char *file, int k)
{
	if (!(button->srcs = SDL_LoadBMP(file)))
		exit (0);
	button->texture = SDL_ConvertSurfaceFormat(button->srcs, SDL_PIXELFORMAT_ABGR8888, 0);
	button->bytes_texture = (unsigned char *)button->texture->pixels;
	if (k == 0)
	{
		button->pos.x1 = W / 2 - (W / 1.5) / 2;
		button->pos.x2 = W / 1.5 + button->pos.x1;
		button->pos.y1 = H * 7 / 15 - (H / 2.2);
		button->pos.y2 = H / 2.2 + button->pos.y1;
		return;
	}
	button->coefficient_x = 3.56;
	button->coefficient_y = 7.8;
	create_pos_button(button, k);
}

void create_background(t_background *background)
{
	if (!(background->srcs = SDL_LoadBMP("textures/background.bmp")))
		exit(0);
	background->texture = SDL_ConvertSurfaceFormat(background->srcs, SDL_PIXELFORMAT_ABGR8888, 0);
	background->bytes_texture = (unsigned char *)background->texture->pixels;
	background->pos.x1 = 0;
	background->pos.x2 = W;
	background->pos.y1 = 0;
	background->pos.y2 = H;
}

void init_menu(t_menu *menu)
{
	create_background(&(menu->background));
	create_button((&menu->logo), "textures/doom_logo.bmp", 0);
	create_button((&menu->start), "textures/start_button.bmp", 4);
	create_button((&menu->map), "textures/map_button.bmp", 5);
	create_button((&menu->settings), "textures/settings_button.bmp", 6);
	create_button((&menu->exit), "textures/exit_button.bmp", 7);
}