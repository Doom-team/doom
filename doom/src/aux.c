/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:26:06 by clala             #+#    #+#             */
/*   Updated: 2020/10/24 21:52:04 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int	add_arc(float *arc, float to_add)
{
	*arc += to_add;
	if (*arc < 0)
		*arc += RAD_360;
	else if (*arc >= RAD_360)
		*arc -= RAD_360;
	return (1);
}

int	is_angle(float angle, float rad)
{
	return (fabsf(cosf(angle) - cosf(rad)) < KLUDGE);
}

int	float_is_equal(float a, float b)
{
	return (fabsf(a - b) < KLUDGE);
}

int	draw_menu_text(t_wolf *wolf, SDL_Color f_b_color[2])
{
	render_text(wolf, ft_strdup(" show/hide menu:c  H"),
	set_rect_sdl(0, H / 3, 0, 0), f_b_color);
	render_text(wolf, ft_strdup(" show/hide map:    M"),
	set_rect_sdl(0, H / 3 + H / 20, 0, 0), f_b_color);
	render_text(wolf, ft_strdup(" show/hide FPS:    I"),
	set_rect_sdl(0, H / 3 + (H / 20) * 2, 0, 0), f_b_color);
	render_text(wolf, ft_strdup(" music on/off:     O"),
	set_rect_sdl(0, H / 3 + (H / 20) * 3, 0, 0), f_b_color);
	render_text(wolf, ft_strdup(" tex sides on/off: P"),
	set_rect_sdl(0, H / 3 + (H / 20) * 4, 0, 0), f_b_color);
	render_text(wolf, ft_strdup(" move keys:     WASD"),
	set_rect_sdl(0, H / 3 + (H / 20) * 5, 0, 0), f_b_color);
	render_text(wolf, ft_strdup(" move keys:   ARROWS"),
	set_rect_sdl(0, H / 3 + (H / 20) * 6, 0, 0), f_b_color);
	render_text(wolf, ft_strdup(" rotation:  QE/MOUSE"),
	set_rect_sdl(0, H / 3 + (H / 20) * 7, 0, 0), f_b_color);
	render_text(wolf, ft_strdup(" strafe keys:     AD"),
	set_rect_sdl(0, H / 3 + (H / 20) * 8, 0, 0), f_b_color);
	render_text(wolf, ft_strdup(" fire:         SPACE"),
	set_rect_sdl(0, H / 3 + (H / 20) * 9, 0, 0), f_b_color);
	return (1);
}

int	draw_menu(t_wolf *wolf)
{
	SDL_Color	f_b_color[2];

	f_b_color[TEXT_FOREGROUND_COLOR] = set_color_sdl(COLOR_RED);
	f_b_color[TEXT_BACKGROUND_COLOR] = set_color_sdl(COLOR_BLUE);
	draw_rectangle(wolf->surface, dot(0, H / 3),
		dot(W / 3, H / 2), COLOR_BLUE_INT);
	draw_menu_text(wolf, f_b_color);
	return (1);
}
