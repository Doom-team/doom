/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:23:45 by clala             #+#    #+#             */
/*   Updated: 2021/02/08 19:47:28 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"


int		error(t_map *map, const char *s)
{
	ft_dprintf(STDERR_FILENO, "%s%s%s\n", C_RED, s, C_NRM);
	exit(EXIT_FAILURE);
	return (0);
}

int		error_free_s(t_map *map, char *s)
{
	ft_dprintf(STDERR_FILENO, "%s%s%s\n", C_RED, s, C_NRM);
	free(s);
	exit(EXIT_FAILURE);
	return (0);
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
