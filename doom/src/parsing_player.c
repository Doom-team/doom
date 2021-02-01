/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 01:09:47 by ahusk             #+#    #+#             */
/*   Updated: 2021/01/29 01:09:50 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	parsing_player(t_param2 *obj, char **arr, int *buff)
{
	if (*buff == 0)
		return ;
	obj->x = ft_atoi(arr[1]) / RESIZE;
	obj->y = ft_atoi(arr[2]) / RESIZE;
}
