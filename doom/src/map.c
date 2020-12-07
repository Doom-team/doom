/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:29:42 by clala             #+#    #+#             */
/*   Updated: 2020/10/24 21:16:53 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void	validate_map(t_wolf *wolf, char *map, int map_size)
{
	int		len_first;
	int		curr_start;
	int		i;

	i = 0;
	len_first = -1;
	wolf->map->h = 0;
	while (i < map_size)
	{
		curr_start = i;
		while (map[i] && map[i] != '\n')
		{
			if (!ft_strchr(CHARSET, map[i]))
				error_inv_c(wolf, ERR_MAP_CHAR, map[i]);
			i++;
		}
		i - curr_start < MAP_MIN_COL_NUM ? \
			error_inv_n(wolf, ERR_MAP_COL_NUM, wolf->map->h + 1) : 0;
		len_first = len_first == -1 ? i - curr_start : len_first;
		len_first != i - curr_start ? error(wolf, ERR_MAP_NOT_RECT) : 0;
		i++;
		wolf->map->h++;
	}
	wolf->map->h < MAP_MIN_ROW_NUM ? error(wolf, ERR_MAP_ROW_NUM) : 0;
	wolf->map->w = len_first;
}

static char	*get_map(t_wolf *wolf, int *was_read, char *map_name)
{
	char	*s;
	int		fd;

	s = ft_strnew(MAP_MAX_SIZE + 1);
	fd = open(map_name, O_RDONLY);
	fd < 0 ? error(wolf, ERR_FILE_OPEN) : 0;
	read(fd, s, 0) < 0 ? error(wolf, ERR_FILE_READ) : 0;
	*was_read = read(fd, s, MAP_MAX_SIZE + 1);
	if (*was_read > MAP_MAX_SIZE)
		error(wolf, ERR_MAP_BIG);
	if (*was_read < MAP_MIN_SIZE)
		error(wolf, ERR_MAP_SMALL);
	return (s);
}

static void	check_logic(t_wolf *wolf)
{
	int		i;
	char	*s;
	t_map	*map;

	map = wolf->map;
	i = -1;
	s = NULL;
	while (++i < map->w)
	{
		if (!ft_strchr(WALLSET, map->map[i]) ||
		!ft_strchr(WALLSET, map->map[map->w * (map->h - 1) + i]))
			ft_asprintf(&s, ERR_MAP_BORDER_COL, i + 1);
	}
	i = -1;
	while (++i < map->h)
	{
		if (!ft_strchr(WALLSET, map->map[i * map->w]) ||
		!ft_strchr(WALLSET, map->map[i * map->w + (map->w - 1)]))
			ft_asprintf(&s, ERR_MAP_BORDER_ROW, i + 1);
	}
	s ? error_free_s(wolf, s) : 0;
}

static void	check_start(t_wolf *wolf)
{
	int		start_coin_counter[2];
	int		i;
	t_map	*map;

	map = wolf->map;
	start_coin_counter[0] = 0;
	start_coin_counter[1] = 0;
	i = -1;
	while (++i < map->w * map->h)
	{
		if (map->map[i] == TEX_COIN)
		{
			wolf->monster->monster_pos[3].y = ((i / wolf->map->w) + 0.5) * CUBE;
			wolf->monster->monster_pos[3].x = ((i % wolf->map->w) + 0.5) * CUBE;
			map->map[i] = TEX_FLOOR;
			++start_coin_counter[1] > 1 ? error(wolf, ERR_MAP_MULT_COIN) : 0;
		}
		if (map->map[i] == TEX_START)
		{
			map->player_start = i;
			map->map[i] = TEX_FLOOR;
			++start_coin_counter[0] > 1 ? error(wolf, ERR_MAP_MULT_START) : 0;
		}
	}
	!start_coin_counter[0] ? error(wolf, ERR_MAP_NO_START) : 0;
}

void		init_map(t_wolf *wolf, char *map_name)
{
	int		map_size;
	char	*str_map;
	int		i;
	int		j;

	if (ft_strcmp((char *)(map_name + ft_strlen(map_name) - 4), ".txt"))
		error(wolf, ERR_MAP_NOT_TXT);
	str_map = get_map(wolf, &map_size, map_name);
	validate_map(wolf, str_map, map_size);
	wolf->map->map = ft_strnew(wolf->map->h * wolf->map->w);
	!wolf->map->map ? error(wolf, ERR_MALLOC) : 1;
	i = -1;
	j = 0;
	while (++i < map_size)
	{
		if (str_map[i] != '\n')
			wolf->map->map[j++] = str_map[i];
	}
	wolf->map->w_pix = wolf->map->w * CUBE;
	wolf->map->h_pix = wolf->map->h * CUBE;
	free(str_map);
	check_start(wolf);
	check_logic(wolf);
	init_mm(wolf->map);
}
