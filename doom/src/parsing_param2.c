/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_param2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 22:39:03 by ahusk             #+#    #+#             */
/*   Updated: 2021/01/28 22:39:05 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	parsing_param2(t_param2 *obj, char **arr, int *buff)
{
	if (*buff == 0)
		return ;
	obj[--*buff].x = ft_atoi(arr[1]) / RESIZE;
	obj[*buff].y = ft_atoi(arr[2]) / RESIZE;
}
