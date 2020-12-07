/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:23:45 by clala             #+#    #+#             */
/*   Updated: 2020/10/24 21:21:01 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		error(t_wolf *wolf, const char *s)
{
	ft_dprintf(STDERR_FILENO, "%s%s%s\n", C_RED, s, C_NRM);
	exit(EXIT_FAILURE);
	return ((int)wolf);
}

int		error_free_s(t_wolf *wolf, char *s)
{
	ft_dprintf(STDERR_FILENO, "%s%s%s\n", C_RED, s, C_NRM);
	free(s);
	exit(EXIT_FAILURE);
	return ((int)wolf);
}

int		error_inv_c(t_wolf *wolf, char *s, char inv_char)
{
	ft_dprintf(STDERR_FILENO, "%s%s%c%s\n", C_RED, s, inv_char, C_NRM);
	exit(EXIT_FAILURE);
	return ((int)wolf);
}

int		error_inv_n(t_wolf *wolf, char *s, int inv_num)
{
	ft_dprintf(STDERR_FILENO, "%s%s%c%s\n", C_RED, s, inv_num, C_NRM);
	exit(EXIT_FAILURE);
	return ((int)wolf);
}
