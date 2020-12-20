#include "../include/map.h"

void	get_inter_textures(t_map *map)
{
	map->inter_tex[0]->img = SDL_GetWindowSurface(map->win);
	init_texture(map->inter_tex[0]->img, &(map->inter_tex[0]->s),
	 &(map->inter_tex[0]->pixb), &(map->inter_tex[0]->strb));
	map->inter_tex[1]->img = IMG_Load("/textures/interface/panel.png");
	map->inter_tex[2]->img = IMG_Load("/textures/interface/panelin.png");
	map->inter_tex[3]->img = IMG_Load("/textures/interface/blocks.png");
	map->inter_tex[4]->img = IMG_Load("/textures/interface/texture.png");
	map->inter_tex[5]->img = IMG_Load("/textures/interface/objects.png");
	map->inter_tex[6]->img = IMG_Load("/textures/interface/walltool.png");
	map->inter_tex[7]->img = IMG_Load("/textures/interface/cursortool.png");
	map->inter_tex[8]->img = IMG_Load("/textures/interface/removetool.png");
	map->inter_tex[9]->img = IMG_Load("/textures/interface/widgetspanel.png");
	map->inter_tex[10]->img = IMG_Load("/textures/interface/plusbtn.png");
	map->inter_tex[11]->img = IMG_Load("/textures/interface/minusbtn.png");
	map->inter_tex[12]->img = IMG_Load("/textures/interface/showuppanel.png");
	map->inter_tex[13]->img = IMG_Load("/textures/interface/showupbtn.png");
	map->inter_tex[14]->img = IMG_Load("/textures/interface/showdownbtn.png");
	map->inter_tex[15]->img = IMG_Load("/textures/interface/redsquare.png");
	map->inter_tex[16]->img = IMG_Load("/textures/interface/textureblock.png");
	map->inter_tex[17]->img = IMG_Load("/textures/interface/down.png");
	map->inter_tex[18]->img = IMG_Load("/textures/interface/downactive.png");
	map->inter_tex[19]->img = IMG_Load("/textures/interface/up.png");
	map->inter_tex[20]->img = IMG_Load("/textures/interface/upactive.png");
	map->inter_tex[21]->img = IMG_Load("/textures/interface/savebtn.png");
}

void	get_block_textures(t_map *map)
{
	map->block_tex[0]->img = IMG_Load("/textures/texture/square.png");
	map->block_tex[1]->img = IMG_Load("/textures/texture/pentagon.png");
	map->block_tex[2]->img = IMG_Load("/textures/texture/hexagon.png");
	map->block_tex[3]->img = IMG_Load("/textures/texture/octagon.png");
}

void	get_floorsky_textures(t_map *map)
{
	map->floorsky_tex[0]->img = IMG_Load("/textures/interface/blackblock.png");
	map->floorsky_tex[1]->img = IMG_Load("/textures/floor/floor1.png");
	map->floorsky_tex[2]->img = IMG_Load("/textures/floor/floor2.png");
	map->floorsky_tex[3]->img = IMG_Load("/textures/floor/floor3.png");
	map->floorsky_tex[4]->img = IMG_Load("/textures/floor/floor4.png");
	map->floorsky_tex[5]->img = IMG_Load("/textures/floor/floor5.png");
	map->floorsky_tex[6]->img = IMG_Load("/textures/floor/floor6.png");
	map->floorsky_tex[7]->img = IMG_Load("/textures/floor/floor7.png");
	map->floorsky_tex[8]->img = IMG_Load("/textures/floor/floor8.png");
	map->floorsky_tex[9]->img = IMG_Load("/textures/floor/sky1.png");
	map->floorsky_tex[10]->img = IMG_Load("/textures/floor/sky2.png");
	map->floorsky_tex[11]->img = IMG_Load("/textures/floor/sky3.png");
	map->floorsky_tex[12]->img = IMG_Load("/textures/floor/sky4.png");

}

void	get_wall_textures(t_map *map)
{
	map->wall_tex[0]->img = IMG_Load("/textures/interface/blackblock.png");
	map->wall_tex[1]->img = IMG_Load("/textures/walls/wall1.png");
	map->wall_tex[2]->img = IMG_Load("/textures/walls/wall2.png");
	map->wall_tex[3]->img = IMG_Load("/textures/walls/wall3.png");
	map->wall_tex[4]->img = IMG_Load("/textures/walls/wall4.png");
	map->wall_tex[5]->img = IMG_Load("/textures/walls/wall5.png");
	map->wall_tex[6]->img = IMG_Load("/textures/walls/wall6.png");
	map->wall_tex[7]->img = IMG_Load("/textures/walls/wall7.png");
	map->wall_tex[8]->img = IMG_Load("/textures/walls/wall8.png");
	map->wall_tex[9]->img = IMG_Load("/textures/walls/wall9.png");
	map->wall_tex[10]->img = IMG_Load("/textures/walls/wall10.png");
	map->wall_tex[11]->img = IMG_Load("/textures/walls/wall11.png");
	map->wall_tex[12]->img = IMG_Load("/textures/walls/wall12.png");
	map->wall_tex[13]->img = IMG_Load("/textures/walls/wall13.png");
	map->wall_tex[14]->img = IMG_Load("/textures/walls/wall14.png");
	map->wall_tex[15]->img = IMG_Load("/textures/walls/wall15.png");
	map->wall_tex[16]->img = IMG_Load("/textures/walls/wall16.png");
	map->wall_tex[17]->img = IMG_Load("/textures/walls/wall17.png");
	map->wall_tex[18]->img = IMG_Load("/textures/walls/wall18.png");
	map->wall_tex[19]->img = IMG_Load("/textures/walls/wall19.png");
}

void	get_liquid_textures(t_map *map)
{
	map->liquid_tex[0]->img = IMG_Load("/textures/interface/blackblock.png");
	map->liquid_tex[1]->img = IMG_Load("/textures/liquids/lava.png");
	map->liquid_tex[2]->img = IMG_Load("/textures/liquids/water.png");
	map->liquid_tex[3]->img = IMG_Load("/textures/liquids/nukage.png");
}