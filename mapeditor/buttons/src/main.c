#include "../include/map.h"

void i_error()
{
	printf("error");
	exit(1);
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
		i_error();
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
