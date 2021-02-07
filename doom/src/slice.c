/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 21:05:49 by ahusk             #+#    #+#             */
/*   Updated: 2021/01/27 21:05:51 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	slice(char s[100], char *a, int from, int to)
{
	int i;
	int j;

	i = 0;
	j = from;
	while (j <= to - 2)
		s[i++] = a[j++];
	s[i] = '\0';
}