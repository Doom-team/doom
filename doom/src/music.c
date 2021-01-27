/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   music.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:31:38 by clala             #+#    #+#             */
/*   Updated: 2021/01/26 16:04:34 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	music(t_bonus *bon)
{
	Mix_Volume(0, 32);
	if (bon->music_flag == 1)
		Mix_PlayMusic(bon->music, -1);
	Mix_VolumeMusic(5);
}
