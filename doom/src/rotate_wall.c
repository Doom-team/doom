/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 14:32:33 by ahusk             #+#    #+#             */
/*   Updated: 2021/02/12 14:32:35 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

t_wall			rotate_wall(t_wall w, t_wolf *wolf, int i)
{
	float angle;

	angle = search_angle(w, wolf, i);
	if (w.type_flag != 2)
	{
		w.x1 = w.realx - sinf(-angle) * 0.5;
		w.x2 = w.realx + sinf(-angle) * 0.5;
		w.y1 = w.realy + cosf(-angle) * 0.5;
		w.y2 = w.realy - cosf(-angle) * 0.5;
	}
	if (w.type_flag == 3)
		w.texture1 = wolf->bon->monster[(w.type_stage - 1) *
			6 + (int)((RAD_360 - angle) / RAD_60)];
	return (w);
}
