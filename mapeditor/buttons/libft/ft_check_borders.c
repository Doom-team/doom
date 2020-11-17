/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_borders.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gordey <gordey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 12:18:47 by gordey            #+#    #+#             */
/*   Updated: 2020/11/04 12:18:52 by gordey           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		ft_check_borders(double num, double min, double max)
{
	num = num < min ? min : num;
	num = num > max ? max : num;
	return (num);
}
