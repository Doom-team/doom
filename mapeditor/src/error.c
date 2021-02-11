/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 00:31:17 by grinko            #+#    #+#             */
/*   Updated: 2021/02/12 00:31:44 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void	error(char *s)
{
	ft_putstr(C_RED);
	ft_putstr(s);
	ft_putstr(C_NRM);
	ft_putchar('\n');
	exit(EXIT_FAILURE);
}

void	error_free_s(t_map *map, char *s)
{
	ft_putstr(C_RED);
	ft_putstr(s);
	ft_putstr(C_NRM);
	ft_putchar('\n');
	free(s);
	exit(EXIT_FAILURE);
}
