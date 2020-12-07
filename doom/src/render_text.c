/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:31:59 by clala             #+#    #+#             */
/*   Updated: 2020/10/18 19:43:59 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int			get_fps_time(t_bonus *bon)
{
	if (!bon->fps)
		return (1);
	if (!bon->start_time)
		bon->start_time = SDL_GetTicks();
	if (bon->start_time + 1000 < SDL_GetTicks())
	{
		bon->start_time = SDL_GetTicks();
		bon->fps = bon->fps_count;
		bon->fps_count = 0;
	}
	return (0);
}

void		render_text(t_wolf *wolf, char *text, SDL_Rect location,
			SDL_Color f_b_color[2])
{
	SDL_Surface		*txt_sur;

	txt_sur = TTF_RenderText_Shaded(wolf->bon->my_font, text,
	f_b_color[TEXT_FOREGROUND_COLOR], f_b_color[TEXT_BACKGROUND_COLOR]);
	free(text);
	if (txt_sur == NULL)
		error(wolf, SDL_GetError());
	SDL_BlitSurface(txt_sur, NULL, wolf->surface, &location);
	SDL_FreeSurface(txt_sur);
}

void		render_fps(t_wolf *wolf, t_bonus *bon)
{
	SDL_Color		f_b_color[2];
	SDL_Surface		*txt_sur;
	char			*str1;
	char			*str2;

	if (get_fps_time(bon))
		return ;
	f_b_color[TEXT_FOREGROUND_COLOR] = set_color_sdl(COLOR_RED);
	f_b_color[TEXT_BACKGROUND_COLOR] = set_color_sdl(COLOR_BLUE);
	txt_sur = NULL;
	bon->fps_count++;
	str1 = ft_itoa(bon->fps);
	str2 = ft_strjoin("FPS: ", str1);
	free(str1);
	render_text(
		wolf, str2,
		set_rect_sdl(W - (int)(H / 10) * 2, 2, 0, 0),
		f_b_color);
}

void		render_score_coin(t_wolf *wolf)
{
	SDL_Color		f_b_color[2];
	SDL_Surface		*text_surface;
	char			*str;
	char			*str_tmp;

	f_b_color[TEXT_FOREGROUND_COLOR] = set_color_sdl(COLOR_RED);
	f_b_color[TEXT_BACKGROUND_COLOR] = set_color_sdl(COLOR_BLUE);
	text_surface = NULL;
	str_tmp = ft_itoa(wolf->monster->score_coin);
	str = ft_strjoin("score coin: ", str_tmp);
	render_text(
		wolf, str,
		set_rect_sdl(W - (int)(H / 28) * 9, H - (int)(H / 28), 0, 0),
		f_b_color);
	free(str_tmp);
}
