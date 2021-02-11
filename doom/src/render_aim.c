#include "../includes/wolf3d.h"

void	render_aim(t_wolf *wolf)
{
	SDL_Rect	img_location;

	img_location = set_rect_sdl(W / 2 - H / 8, H / 2 - H / 8, H / 4, H / 4);
	SDL_BlitScaled(wolf->bon->image_aim, NULL, wolf->surface, &img_location);
}
