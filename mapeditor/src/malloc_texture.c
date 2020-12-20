#include "../include/map.h"

void	malloc_interface(t_map *map)
{
	int i;

	i = -1;
	while (++i < 22)
		map->inter_tex[i] = (t_image *)malloc(sizeof(t_image));
	get_inter_textures(map);
	i = 0;
	while (++i < 22)
	{
		map->inter_tex[i]->img = SDL_ConvertSurfaceFormat(map->inter_tex[i]->img, SDL_PIXELFORMAT_BGRA32, 0);
		init_texture(map->inter_tex[i]->img, &(map->inter_tex[i]->s), &(map->inter_tex[i]->pixb), &(map->inter_tex[i]->strb));
		map->inter_tex[i]->active = 0;
	}
	map->inter_tex[3]->active = 1;
	map->inter_tex[6]->active = 1;
}

void	malloc_block_texture(t_map *map)
{
	int i;

	i = -1;
	map->remove = malloc(sizeof(t_removeinfo*)); ///
	map->remove->x = malloc(sizeof(int *) * 10); /// 
	map->remove->y = malloc(sizeof(int *) * 10); ////
	while (++i < 4)
		map->block_tex[i] = (t_image *)malloc(sizeof(t_image));
	get_block_textures(map);
	i = -1;
	while (++i < 4)
	{
		map->block_tex[i]->img = SDL_ConvertSurfaceFormat(map->block_tex[i]->img, SDL_PIXELFORMAT_BGRA32, 0);
		init_texture(map->block_tex[i]->img, &(map->block_tex[i]->s), &(map->block_tex[i]->pixb), &(map->block_tex[i]->strb));
		map->block_tex[i]->active = 0;
	}
}

void	malloc_floorsky_texture(t_map *map)
{
	int i;

	i = -1;
	while (++i < 13)
		map->floorsky_tex[i] = (t_image *)malloc(sizeof(t_image));
	get_floorsky_textures(map);
	i = -1;
	while (++i < 13)
	{
		map->floorsky_tex[i]->img = SDL_ConvertSurfaceFormat(map->floorsky_tex[i]->img, SDL_PIXELFORMAT_BGRA32, 0);
		init_texture(map->floorsky_tex[i]->img, &(map->floorsky_tex[i]->s), &(map->floorsky_tex[i]->pixb), &(map->floorsky_tex[i]->strb));
		map->floorsky_tex[i]->active = 0;
	}
}

void	malloc_wall_texture(t_map *map)
{
	int i;

	i = -1;
	while (++i < 20)
		map->wall_tex[i] = (t_image *)malloc(sizeof(t_image));
	get_wall_textures(map);
	i = -1;
	while (++i < 20)
	{
		map->wall_tex[i]->img = SDL_ConvertSurfaceFormat(map->wall_tex[i]->img, SDL_PIXELFORMAT_BGRA32, 0);
		init_texture(map->wall_tex[i]->img, &(map->wall_tex[i]->s), &(map->wall_tex[i]->pixb), &(map->wall_tex[i]->strb));
		map->wall_tex[i]->active = 0;
	}
}

void	malloc_liquid_texture(t_map *map)
{
	int i;

	i = -1;
	while (++i < 4)
		map->liquid_tex[i] = (t_image *)malloc(sizeof(t_image));
	get_liquid_textures(map);
	i = -1;
	while (++i < 4)
	{
		map->liquid_tex[i]->img = SDL_ConvertSurfaceFormat(map->liquid_tex[i]->img, SDL_PIXELFORMAT_BGRA32, 0);
		init_texture(map->liquid_tex[i]->img, &(map->liquid_tex[i]->s), &(map->liquid_tex[i]->pixb), &(map->liquid_tex[i]->strb));
		map->liquid_tex[i]->active = 0;
	}
}