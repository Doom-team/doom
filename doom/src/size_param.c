/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 21:27:30 by ahusk             #+#    #+#             */
/*   Updated: 2021/01/28 21:27:31 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void		size_param3(int count, int *buff, t_param3 *object,
				t_parser *parser)
{
	if (!(object = (t_param3 *)malloc(count * sizeof(t_param3))))
		error((t_wolf *)parser, ERR_MALLOC);
	*buff = count;
}

void		size_param2(int count, int *buff, t_param2 *object,
				t_parser *parser)
{
	if (!(object = (t_param2 *)malloc(count * sizeof(t_param2))))
		error((t_wolf *)parser, ERR_MALLOC);
	*buff = count;
}

void		size_param1(char **arr, bool *b, int i)
{
	if (ft_atoi(arr[i + 1]) > 0)
		*b = true;
	else
		*b = false;
}
