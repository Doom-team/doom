/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:23:45 by clala             #+#    #+#             */
/*   Updated: 2021/02/09 16:23:04 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

void		error(char *s)
{
	ft_putstr(C_RED);
	ft_putstr(s);
	ft_putstr(C_NRM);
	free(s);
	exit(EXIT_FAILURE);
}

void		error_free_s(t_map *map, char *s)
{
	ft_putstr(C_RED);
	ft_putstr(s);
	ft_putstr(C_NRM);
	free(s);
	exit(EXIT_FAILURE);
}

// int		error_inv_c(t_wolf *wolf, char *s, char inv_char)
// {
// 	ft_dprintf(STDERR_FILENO, "%s%s%c%s\n", C_RED, s, inv_char, C_NRM);
// 	exit(EXIT_FAILURE);
// 	return ((int)wolf);
// }

// int		error_inv_n(t_wolf *wolf, char *s, int inv_num)
// {
// 	ft_dprintf(STDERR_FILENO, "%s%s%c%s\n", C_RED, s, inv_num, C_NRM);
// 	exit(EXIT_FAILURE);
// 	return ((int)wolf);
// }
