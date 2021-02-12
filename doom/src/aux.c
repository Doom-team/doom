/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:26:06 by skaren            #+#    #+#             */
/*   Updated: 2021/02/12 13:16:18 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int		add_arc(float *arc, float to_add)
{
	*arc += to_add;
	if (*arc < 0)
		*arc += RAD_360;
	else if (*arc >= RAD_360)
		*arc -= RAD_360;
	return (1);
}

void	jump2(t_wolf *wolf, SDL_Event *event, int f)
{
	if (f)
		handle_event(wolf, event);
	if (!f)
	{
		handle_event(wolf, event);
		recalc(wolf);
	}
	handle_phisics(wolf, wolf->player);
	all_get_distance(wolf);
	pseudo_3d(wolf);
	render_score_coin(wolf);
	render_fps(wolf, wolf->bon);
	render_aim(wolf);
	render_hud(wolf);
	render_shot(wolf, wolf->surface);
	SDL_UpdateWindowSurface(wolf->sdl->win);
}
