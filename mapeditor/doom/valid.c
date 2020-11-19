/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 20:14:36 by wendell           #+#    #+#             */
/*   Updated: 2020/10/15 23:53:59 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		mal_map(t_doom *dm)
{
	int i;

	if (!(dm->map = (int **)malloc(sizeof(int *) * dm->maph)))
		return (0);
	i = -1;
	if (dm->maph <= 2 || dm->mapw <= 2)
		return (0);
	while (++i < dm->maph)
		if (!(dm->map[i] = (int*)malloc(dm->mapw * sizeof(int))))
			return (0);
	return (1);
}

int		ext(t_doom *dm)
{
	exit(0);
	return (0);
}

int		mapwtodm(t_doom *dm, int mapw)
{
	dm->mapw = mapw;
	return (0);
}

int		check_size(t_doom *dm, char *buff)
{
	int i;
	int j;
	int mapw;

	j = 0;
	i = -1;
	mapw = 0;
	while (buff[++i] != '\0')
	{
		if (buff[i] == '2')
			j++;
		if (buff[i] == '\n')
		{
			if (dm->maph != 0 && mapw != dm->mapw)
				return (0);
			else
				mapw = mapwtodm(dm, mapw);
			dm->maph++;
		}
		else
			mapw++;
	}
	if (j != 1 || (mapw != 0 && mapw != dm->mapw))
		return (0);
	return (1);
}

void	init_pl(t_doom *dm, int k, int j)
{
	dm->ppos_x = k + 0.51;
	dm->ppos_y = j + 0.51;
	dm->map[k][j] = 0;
}

int		cr_map(t_doom *dm, char *buff, int j, int k)
{
	int i;

	i = -1;
	while (buff[++i] != '\0')
		if (buff[i] != '\n')
		{
			if ((k == 0 || k == dm->maph - 1 || j == 0 ||
			j == dm->mapw - 1) && buff[i] != 49)
				return (0);
			if (buff[i] == 48 || buff[i] == 49)
				dm->map[k][j] = buff[i] - 48;
			else if (buff[i] == 50)
				init_pl(dm, k, j);
			else
				return (0);
			j++;
		}
		else
		{
			k++;
			j = 0;
		}
	return (1);
}

int		readmap(t_doom *dm, char *av)
{
	char	buff[10000];
	int		i;
	int		mapw;
	int		j;
	int		k;

	j = open(av, O_RDONLY);
	mapw = 0;
	if (j == -1)
		ext(dm);
	if ((k = read(j, buff, 10000)) < 1 || k > 10000)
		ext(dm);
	buff[k] = '\0';
	if (!check_size(dm, buff))
		return (0);
	if (!mal_map(dm))
		return (0);
	k = 0;
	j = 0;
	cr_map(dm, buff, j, k);
	return (1);
}
