#include "../includes/wolf3d.h"

void draw_texture(t_sdl *sdl, t_button *button, t_position *pos)
{
	if (button->bytes_texture[pos->x2 * 4 + 3 + pos->y2 * button->texture->pitch] != 0)
	{
		sdl->bytes[pos->x1 * 4 + 0 + pos->y1 * sdl->pitch] = button->bytes_texture[pos->x2 * 4 + 0 + pos->y2 * button->texture->pitch];
		sdl->bytes[pos->x1 * 4 + 1 + pos->y1 * sdl->pitch] = button->bytes_texture[pos->x2 * 4 + 1 + pos->y2 * button->texture->pitch];
		sdl->bytes[pos->x1 * 4 + 2 + pos->y1 * sdl->pitch] = button->bytes_texture[pos->x2 * 4 + 2 + pos->y2 * button->texture->pitch];
		sdl->bytes[pos->x1 * 4 + 3 + pos->y1 * sdl->pitch] = button->bytes_texture[pos->x2 * 4 + 3 + pos->y2 * button->texture->pitch];
	}
}

void draw_button(t_sdl *sdl, t_button *button)
{
	t_position pos;

	pos.x1 = button->pos.x1;
	while (++pos.x1 < button->pos.x2)
	{
		pos.y1 = button->pos.y1;
		pos.x2 = ((pos.x1 - button->pos.x1) * button->texture->w) / (button->pos.x2 - button->pos.x1);
		while (++pos.y1 < button->pos.y2)
		{
			pos.y2 = ((pos.y1 - button->pos.y1) * button->texture->h) / (button->pos.y2 - button->pos.y1);
			draw_texture(sdl, button, &pos);
		}
	}
}

void print_menu(t_wolf *wolf)
{
	draw_button(wolf->sdl, (t_button *)&wolf->menu->background);
	draw_button(wolf->sdl, &wolf->menu->logo);
	draw_button(wolf->sdl, &wolf->menu->start);
	draw_button(wolf->sdl, &wolf->menu->map);
	draw_button(wolf->sdl, &wolf->menu->exit);
}