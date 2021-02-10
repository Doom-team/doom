/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:05 by grinko            #+#    #+#             */
/*   Updated: 2021/02/10 13:18:51 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

int		struppercase(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 65 && str[i] <= 90)
			return (1);
		i++;
	}
	return (0);
}

SDL_Surface		*load_font(t_map *map, char *str, TTF_Font *font, SDL_Color color)
{
	SDL_Surface		*tmp;
	SDL_Surface		*tmp1;

	if (!(tmp = TTF_RenderText_Solid(font, str, color)))
	{
		SDL_FreeSurface(tmp);
		error((char *)SDL_GetError());
	}
	tmp1 = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_BGRA32, 0);
	SDL_FreeSurface(tmp);
	tmp = NULL;
	return (tmp1);
}

void	fonts_classic(t_map *map, char *str, t_info *info, SDL_Color color)
{
	int			strlen;
	SDL_Surface		*tmp;

	strlen = ft_strlen(str);
	map->font->img = load_font(map, str, map->fontclasic, color);
	tmp = map->font->img;
	init_texture(map->font->img, &(map->font->s),
		&(map->font->pixb), &(map->font->strb));
	SDL_FreeSurface(tmp);
	if (struppercase(str))
		draw_img(map, &(t_info){info->x, info->y, strlen * 10, 20}, map->font);
	else
		draw_img(map, &(t_info){info->x, info->y, strlen * 7, 15}, map->font);
}

void	fonts_doom(t_map *map, char *str, t_info *info, SDL_Color color)
{
	int				strlen;
	SDL_Surface		*tmp;

	strlen = ft_strlen(str);
	map->font->img = load_font(map, str, map->fontdoom, color);
	tmp = map->font->img;
	init_texture(map->font->img, &(map->font->s), &(map->font->pixb),
		&(map->font->strb));
	SDL_FreeSurface(tmp);
	if (struppercase(str))
		draw_img(map, &(t_info){info->x, info->y, strlen * 12, 20}, map->font);
	else
		draw_img(map, &(t_info){info->x, info->y, strlen * 10, 5}, map->font);
}
