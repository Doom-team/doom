/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buble_sort_fly.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 16:55:11 by ahusk             #+#    #+#             */
/*   Updated: 2021/02/12 16:55:13 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		buble_sort_helper(t_distance *v, t_helper help, float f_temp)
{
	v->dist[help.j - 1] = v->dist[help.j];
	v->number_wall[help.j - 1] = v->number_wall[help.j];
	v->offsetx[help.j - 1] = v->offsetx[help.j];
	v->coords[help.j - 1] = v->coords[help.j];
	v->dist[help.j] = f_temp;
}

void			buble_sort_fly(t_distance *v)
{
	t_helper	help;
	float		f_temp;
	int			number_temp;
	float		of_temp;
	t_float2	cor_temp;

	help.x = -1;
	while (++help.x < v->count - 1)
	{
		help.j = v->count;
		while (--help.j > help.x)
		{
			if (v->dist[help.j - 1] < v->dist[help.j])
			{
				f_temp = v->dist[help.j - 1];
				number_temp = v->number_wall[help.j - 1];
				of_temp = v->offsetx[help.j - 1];
				cor_temp = v->coords[help.j - 1];
				buble_sort_helper(v, help, f_temp);
				v->number_wall[help.j] = number_temp;
				v->offsetx[help.j] = of_temp;
				v->coords[help.j] = cor_temp;
			}
		}
	}
}
