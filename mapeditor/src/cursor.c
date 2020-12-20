#include "../include/map.h"

void cursor(t_map *map, const char *file, int hot_x, int hot_y)
{
	map->curosr_img = (t_image *)malloc(sizeof(t_image));
	map->curosr_img->img = IMG_Load(file);
	map->curosr_img->img = SDL_ConvertSurfaceFormat(map->curosr_img->img, SDL_PIXELFORMAT_BGRA32, 0);
	init_texture(map->curosr_img->img,&(map->curosr_img->s), &(map->curosr_img->pixb), &(map->curosr_img->strb));
	map->cursor = SDL_CreateColorCursor(map->curosr_img->img, hot_x, hot_y);
	SDL_SetCursor(map->cursor);
}
