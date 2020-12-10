#include "../includes/wolf3d.h"

void quit(t_sdl *sdl)
{
	SDL_DestroyRenderer(sdl->render);
	sdl->render = NULL;
	SDL_DestroyTexture(sdl->window_texture);
	sdl->window_texture = NULL;
	// SDL_DestroyWindow(sdl->win);
	// sdl->win = NULL;
	// SDL_Quit();
}

void check_pos_button(t_sdl *sdl, t_button *button, int k)
{
	if (sdl->e.motion.x > button->pos.x1 && sdl->e.motion.x < button->pos.x2 &&
		sdl->e.motion.y > button->pos.y1 && sdl->e.motion.y < button->pos.y2)
	{
		button->coefficient_x = 3.4;
		button->coefficient_y = 7.4;
		create_pos_button(button, k);
		if (sdl->e.button.button == SDL_BUTTON_LEFT && k == 7)
			sdl->run_menu = false;
	}
	else
	{
		button->coefficient_x = 3.56;
		button->coefficient_y = 7.8;
		create_pos_button(button, k);
	}
}

void hooks(t_sdl *sdl, t_menu *menu)
{
	while (SDL_PollEvent(&sdl->e) != 0)
	{
		if (sdl->e.type == SDL_QUIT)
			sdl->run_menu = false;
		if (sdl->e.type == SDL_KEYDOWN)
		{
			if (sdl->e.key.keysym.sym == SDLK_ESCAPE)
				sdl->run_menu = false;
		}
		if (sdl->e.type == SDL_MOUSEMOTION || sdl->e.type == SDL_MOUSEBUTTONDOWN)
		{
			check_pos_button(sdl, &menu->start, 4);
			check_pos_button(sdl, &menu->map, 5);
			check_pos_button(sdl, &menu->settings, 6);
			check_pos_button(sdl, &menu->exit, 7);
		}
	}
}

void    menu_loop(t_wolf *wolf)
{
    while (wolf->sdl->run_menu)
    {
        hooks(wolf->sdl, wolf->menu);
		SDL_LockTexture(wolf->sdl->window_texture, NULL, (void**) &wolf->sdl->bytes, &wolf->sdl->pitch);
		print_menu(wolf);
		SDL_UnlockTexture(wolf->sdl->window_texture);
		SDL_RenderCopy(wolf->sdl->render, wolf->sdl->window_texture, NULL, NULL);
		SDL_RenderPresent(wolf->sdl->render);
    }
    quit(wolf->sdl);
}