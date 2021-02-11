/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cof.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:31:45 by skaren            #+#    #+#             */
/*   Updated: 2021/02/09 16:20:04 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int			fly_correct_fuf(t_wolf *wolf)
{
	return (wolf->player->fly / 2 * 3)\
	+ (0.00294f * wolf->player->fly + 0.3106055f);
}

int			fly_correction_from_dist(t_wolf *wolf, int j, int count_distance)
{
	return ((int)(wolf->player->fly /\
			wolf->player->distance[count_distance]->dist[j]
			* (28.9357956f * (W * 1.0 / H) - 1.1785647f))) / 64.0;
}

float		correct_cof_h(t_wolf *wolf)
{
	return (0.0837451f * logf(abs(wolf->player->fly)) - 0.3360108f);
}

int			diry_correction_from_fly(int fly)
{
	return (-1.5029996f * fly - 1.064349f);
}

float		cof_size_displ(void)
{
	return (0.8654409f * pow((W * 1.0f / H), 1.0118661f));
}
