/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gordey <gordey@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:05 by grinko            #+#    #+#             */
/*   Updated: 2020/12/30 20:16:25 by gordey           ###   ########.fr       */
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

void	fonts_classic(t_map *map, char *str, t_info *info, SDL_Color color)
{
	TTF_Font	*font;
	int			strlen;

	map->font = (t_image *)malloc(sizeof(t_image));
	strlen = ft_strlen(str);
	map->font->img = TTF_RenderText_Solid(map->fontclasic, str, color);
	map->font->img = SDL_ConvertSurfaceFormat(map->font->img,
		SDL_PIXELFORMAT_BGRA32, 0);
	init_texture(map->font->img, &(map->font->s),
		&(map->font->pixb), &(map->font->strb));
	if (struppercase(str))
		draw_img(map, &(t_info){info->x, info->y, strlen * 10, 20}, map->font);
	else
		draw_img(map, &(t_info){info->x, info->y, strlen * 7, 15}, map->font);
}

void	fonts_doom(t_map *map, char *str, t_info *info, SDL_Color color)
{
	TTF_Font	*font;
	int			strlen;

	map->font = (t_image *)malloc(sizeof(t_image));
	strlen = ft_strlen(str);
	map->font->img = TTF_RenderText_Solid(map->fontdoom, str, color);
	map->font->img = SDL_ConvertSurfaceFormat(map->font->img,
		SDL_PIXELFORMAT_BGRA32, 0);
	init_texture(map->font->img, &(map->font->s), &(map->font->pixb),
		&(map->font->strb));
	if (struppercase(str))
		draw_img(map, &(t_info){info->x, info->y, strlen * 12, 20}, map->font);
	else
		draw_img(map, &(t_info){info->x, info->y, strlen * 10, 5}, map->font);
}
