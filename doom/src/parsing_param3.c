/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_param3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 22:39:20 by ahusk             #+#    #+#             */
/*   Updated: 2021/01/28 22:39:21 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	parsing_param3(t_param3 *obj, char **arr, int *buff)
{
	if (*buff == 0)
		return ;
	obj[--*buff].type = ft_atoi(arr[1]);
	obj[*buff].x = ft_atoi(arr[2]);
	obj[*buff].y = ft_atoi(arr[3]);
}
