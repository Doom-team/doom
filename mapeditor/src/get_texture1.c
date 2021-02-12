/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:39:08 by grinko            #+#    #+#             */
/*   Updated: 2021/02/12 12:14:29 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/map.h"

SDL_Surface		*load_image(char *path)
{
	SDL_Surface		*tmp;
	SDL_Surface		*tmp1;

	if (!(tmp = IMG_Load(path)))
	{
		SDL_FreeSurface(tmp);
		error((char *)SDL_GetError());
	}
	tmp1 = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_BGRA32, 0);
	SDL_FreeSurface(tmp);
	return (tmp1);
}

void			get_inter_textures(t_map *map)
{
	map->inter_tex[0]->img = SDL_GetWindowSurface(map->win);
	init_texture(map->inter_tex[0]->img, &(map->inter_tex[0]->s),
		&(map->inter_tex[0]->pixb), &(map->inter_tex[0]->strb));
	map->inter_tex[1]->img = load_image("/textures/interface/panel.png");
	map->inter_tex[2]->img = load_image("/textures/interface/panelin.png");
	map->inter_tex[3]->img = load_image("/textures/interface/blocks.png");
	map->inter_tex[4]->img = load_image("/textures/interface/texture.png");
	map->inter_tex[5]->img = load_image("/textures/interface/objects.png");
	map->inter_tex[6]->img = load_image("/textures/interface/walltool.png");
	map->inter_tex[7]->img = load_image("/textures/interface/cursortool.png");
	map->inter_tex[8]->img = load_image("/textures/interface/removetool.png");
	map->inter_tex[9]->img = load_image("/textures/interface/widgetspanel.png");
	map->inter_tex[10]->img = load_image("/textures/interface/plusbtn.png");
	map->inter_tex[11]->img = load_image("/textures/interface/minusbtn.png");
	map->inter_tex[12]->img = load_image("/textures/interface/showuppanel.png");
	map->inter_tex[13]->img = load_image("/textures/interface/showupbtn.png");
	map->inter_tex[14]->img = load_image("/textures/interface/showdownbtn.png");
	map->inter_tex[15]->img = load_image("/textures/interface/redsquare.png");
	map->inter_tex[16]->img =
		load_image("/textures/interface/textureblock.png");
	map->inter_tex[17]->img = load_image("/textures/interface/down.png");
	map->inter_tex[18]->img = load_image("/textures/interface/downactive.png");
	map->inter_tex[19]->img = load_image("/textures/interface/up.png");
	map->inter_tex[20]->img = load_image("/textures/interface/upactive.png");
	map->inter_tex[21]->img = load_image("/textures/interface/savebtn.png");
}

void			get_cursor(t_map *map)
{
	map->curosr_img[0]->img = load_image("/textures/interface/editpic.png");
	map->curosr_img[1]->img = load_image("/textures/interface/deletic.png");
	map->curosr_img[2]->img = load_image("/textures/interface/firstdot.png");
	map->curosr_img[3]->img = load_image("/textures/interface/seconddot.png");
	map->curosr_img[4]->img = load_image("../textures/pickup/bluekey.png");
	map->curosr_img[5]->img = load_image("../textures/pickup/yellowkey.png");
	map->curosr_img[6]->img = load_image("../textures/pickup/redkey.png");
}

void			get_block_textures(t_map *map)
{
	map->block_tex[0]->img = load_image("/textures/texture/square.png");
	map->block_tex[1]->img = load_image("/textures/texture/pentagon.png");
	map->block_tex[2]->img = load_image("/textures/texture/hexagon.png");
	map->block_tex[3]->img = load_image("/textures/texture/octagon.png");
	map->block_tex[4]->img = load_image("/textures/texture/music.png");
	map->block_tex[5]->img = load_image("/textures/texture/stairs.png");
	map->block_tex[6]->img = load_image("/textures/texture/watertest.png");
	map->block_tex[7]->img = load_image("/textures/texture/nuketest.png");
	map->block_tex[8]->img = load_image("/textures/texture/lavatest.png");
}

void			get_floorsky_textures(t_map *map)
{
	map->floorsky_tex[0]->img =
		load_image("/textures/interface/blackblock.png");
	map->floorsky_tex[1]->img = load_image("../textures/floor/floor1.png");
	map->floorsky_tex[2]->img = load_image("../textures/floor/floor2.png");
	map->floorsky_tex[3]->img = load_image("../textures/floor/floor3.png");
	map->floorsky_tex[4]->img = load_image("../textures/floor/floor4.png");
	map->floorsky_tex[5]->img = load_image("../textures/floor/floor5.png");
	map->floorsky_tex[6]->img = load_image("../textures/floor/floor6.png");
	map->floorsky_tex[7]->img = load_image("../textures/floor/floor7.png");
	map->floorsky_tex[8]->img = load_image("../textures/floor/floor8.png");
	map->floorsky_tex[9]->img = load_image("../textures/floor/sky1.png");
	map->floorsky_tex[10]->img = load_image("../textures/floor/sky2.png");
	map->floorsky_tex[11]->img = load_image("../textures/floor/sky3.png");
	map->floorsky_tex[12]->img = load_image("../textures/floor/sky4.png");
}
