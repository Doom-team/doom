/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 20:18:20 by ahusk             #+#    #+#             */
/*   Updated: 2021/02/10 20:18:21 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	check_valid(t_buff *buff)
{
	if (!buff->p || !buff->f || (!buff->s && !buff->c) || !buff->x || !buff->m)
		error((t_wolf*)buff, ERR_FILE_INVALID);
}
