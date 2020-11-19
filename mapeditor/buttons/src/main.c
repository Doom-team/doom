#include "../include/map.h"

void i_error()
{
	printf("error");
	exit(1);
}


int main(int ac, char **av)
{
	t_map *map;
	int x = 0;
	int y = 0;
	unsigned int t;
	unsigned int t1;

	if (!(map = (t_map *)malloc(sizeof(t_map))))
		return (0);
	if(init_all(map))
		i_error();
	draw(map);
	SDL_UpdateWindowSurface(map->win);


	SDL_Event event;
	int done = 0;
	
	while (!done && SDL_WaitEvent(&event))
	{
		t = SDL_GetTicks();
		// map->plr.rypos -= ((double)t - t1)/10;
		// draw(map);
		// printf("%u\n", t - t1);
		t1 = t;
		if (event.type == SDL_QUIT)
			done = 1;
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			SDL_GetMouseState(&x, &y);
			// mkey(event.button.button, x, y, map);
		}
	}
	SDL_DestroyWindow(map->win);
	SDL_Quit();
	return (0);
}
