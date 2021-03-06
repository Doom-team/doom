/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_music.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 22:52:37 by ahusk             #+#    #+#             */
/*   Updated: 2021/02/10 22:52:38 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

Mix_Music	*parsing_music(t_parser *parser,
						char **arr, bool *b)
{
	Mix_Music *tmp;

	tmp = NULL;
	if (arr[1] != 0)
	{
		tmp = Mix_LoadMUS(arr[1]);
		if (!tmp)
			error((t_wolf *)parser, SDL_GetError());
		if (!(parser->take_damage = Mix_LoadWAV("music/take_damage.wav")))
			error((t_wolf *)parser, SDL_GetError());
		*b = true;
	}
	return (tmp);
}
