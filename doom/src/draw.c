/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:21:35 by clala             #+#    #+#             */
/*   Updated: 2020/10/18 18:23:36 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		draw_line(SDL_Surface *surface,
t_point start, t_point end, int color)
{
	t_point	d;
	t_point	s;
	int		err;
	int		e2;

	d.x = abs(end.x - start.x);
	d.y = abs(end.y - start.y);
	s.x = start.x < end.x ? 1 : -1;
	s.y = start.y < end.y ? 1 : -1;
	err = (d.x > d.y ? d.x : -d.y) / 2;
	while (1)
	{
		if (start.x > W || start.x < 0 || start.y > H || start.y < 0)
			break ;
		set_pixel(surface, start.x, start.y, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		e2 = err;
		err = e2 > -d.x ? err - d.y : err;
		start.x = e2 > -d.x ? start.x + s.x : start.x;
		err = e2 < d.y ? err + d.x : err;
		start.y = e2 < d.y ? start.y + s.y : start.y;
	}
}

void		draw_rectangle(SDL_Surface *surface, t_point start,
t_point width_height, int color)
{
	int		i;
	int		j;
	t_point	temp;

	i = -1;
	while (++i < width_height.y)
	{
		j = -1;
		temp.y = i + start.y;
		while (++j < width_height.x)
		{
			temp.x = j + start.x;
			set_pixel(surface, temp.x, temp.y, color);
		}
	}
}

void		draw_ray(t_wolf *wolf, float dir, int x, int y)
{
	int		dx0;
	int		dy0;
	int		dx1;
	int		dy1;

	dx0 = cos(dir - wolf->player->fov / 2) * wolf->map->mm_cube * 4;
	dy0 = sin(dir - wolf->player->fov / 2) * wolf->map->mm_cube * 4;
	dx1 = cos(dir + wolf->player->fov / 2) * wolf->map->mm_cube * 4;
	dy1 = sin(dir + wolf->player->fov / 2) * wolf->map->mm_cube * 4;
	draw_line(
		wolf->surface,
		dot(x, y),
		dot(x + dx0, y - dy0),
		COLOR_WHITE);
	draw_line(
		wolf->surface,
		dot(x, y),
		dot(x + dx1, y - dy1),
		COLOR_WHITE);
}

void		draw_background(SDL_Surface *surface)
{
	int		i;
	int		j;

	i = -1;
	while (++i < W)
	{
		j = -1;
		while (++j < H)
		{
			set_pixel(surface, i, j, COLOR_BLACK);
		}
	}
}

int			draw_minimap(t_wolf *wolf, t_map *map, t_player *p)
{
	int		i;

	draw_rectangle(wolf->surface, map->mm_start, dot(map->mm_w, map->mm_h),
		COLOR_GREY_LIGHT);
	i = -1;
	while (++i < map->h * map->w)
	{
		if (ft_strchr(WALLSET, map->map[i]))
		{
			draw_rectangle(wolf->surface, dot(
				((i % map->w) * map->mm_cube + map->mm_start.x),
				((i / map->w) * map->mm_cube + map->mm_start.y)),
			dot(map->mm_cube, map->mm_cube), 0xbbbb00);
		}
	}
	draw_rectangle(wolf->surface,
		dot(p->x * map->mm_cube_coef + (map->mm_start.x - map->mm_p_size),
			p->y * map->mm_cube_coef + (map->mm_start.y - map->mm_p_size)),
		dot(map->mm_p_size * 2, map->mm_p_size * 2), 0xFFFFFF);
	draw_ray(wolf, p->dir, p->x * map->mm_cube_coef + map->mm_start.x,
		p->y * map->mm_cube_coef + map->mm_start.y);
	return (1);
}
