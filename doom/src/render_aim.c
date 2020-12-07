#include "../includes/wolf3d.h"

void    render_aim(t_wolf *wolf)
{
	SDL_Rect    img_location;

	img_location = set_rect_sdl(W / 2 - H / 8 , H / 2 - H / 8, H / 4, H / 4);
	SDL_BlitScaled(wolf->bon->image_aim, NULL, wolf->surface, &img_location);
}

void	penetration_check(t_wolf *wolf, SDL_Rect img_location)
{
	if (wolf->bon->guns_fire == 1)
	{
		if (img_location.x <= W / 2 && img_location.x + img_location.w >= W / 2)
		{
			if (img_location.y <= H / 2 && img_location.y + img_location.h >= H / 2)
			{
				wolf->monster->penetration_flag = 1;
			}
		}
	}
}