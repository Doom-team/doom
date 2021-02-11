/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guns_shot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skaren <skaren@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:25:42 by skaren            #+#    #+#             */
/*   Updated: 2020/10/18 18:25:44 by skaren           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	render_shot(t_wolf *wolf, SDL_Surface *surface)
{
	if (wolf->bon->set_gun == 1)
		render_shot1(wolf, surface);
	if (wolf->bon->set_gun == 2)
		render_shot2(wolf, surface);
	if (wolf->bon->set_gun == 3)
		render_shot3(wolf, surface);
}
