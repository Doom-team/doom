/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_coin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:26:06 by clala             #+#    #+#             */
/*   Updated: 2020/10/18 18:26:22 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int		score_coin(t_wolf *wolf, t_sprite_calc *coin)
{
	// float	x;
	// float	y;
	// int		flag;

	// flag = 0;
	// if (coin->dist < 20 || wolf->monster->penetration_flag == 1)
	// {
	// 	Mix_Volume(0, 32);
	// 	Mix_PlayChannel(2, wolf->bon->music_coin, 0);
	// 	Mix_VolumeMusic(5);
	// 	wolf->monster->score_coin++;
	// 	wolf->monster->penetration_flag = 0;
	// 	while (flag != 1)
	// 	{
	// 		y = rand() % wolf->map->h;
	// 		x = rand() % wolf->map->w;
	// 		if (wolf->map->map[(int)(y * wolf->map->w + x)] == TEX_FLOOR)
	// 		{
	// 			wolf->monster->monster_pos[3].x = (x + 0.5) * CUBE;
	// 			wolf->monster->monster_pos[3].y = (y + 0.5) * CUBE;
	// 			flag = 1;
	// 		}
	// 	}
	// }
	// return (0);
}

int		search_angle(t_wolf *wolf, t_sprite_calc *coin)
{
	// coin->dist = sqrtf(powf((wolf->monster->monster_pos[3].x - wolf->player->x), 2)
	// 	+ powf((wolf->monster->monster_pos[3].y - wolf->player->y), 2));
	// if (score_coin(wolf, coin))
	// 	return (1);
	// if (wolf->monster->monster_pos[3].x - wolf->player->x > 0
	// 	&& wolf->monster->monster_pos[3].y - wolf->player->y < 0)
	// 	coin->angle = asin((wolf->player->y - wolf->monster->monster_pos[3].y)
	// 		/ coin->dist);
	// else if (wolf->monster->monster_pos[3].x - wolf->player->x < 0
	// 	&& wolf->monster->monster_pos[3].y - wolf->player->y < 0)
	// 	coin->angle = asin((wolf->monster->monster_pos[3].y - wolf->player->y)
	// 		/ coin->dist) + RAD_180;
	// else if (wolf->monster->monster_pos[3].x - wolf->player->x < 0
	// 	&& wolf->monster->monster_pos[3].y - wolf->player->y > 0)
	// 	coin->angle = asin((wolf->monster->monster_pos[3].y - wolf->player->y)
	// 		/ coin->dist) + RAD_180;
	// else if (wolf->monster->monster_pos[3].x - wolf->player->x > 0
	// 	&& wolf->monster->monster_pos[3].y - wolf->player->y > 0)
	// 	coin->angle = asin((wolf->player->y - wolf->monster->monster_pos[3].y)
	// 		/ coin->dist) + RAD_360;
	// return (0);
}

void	through_zero(t_wolf *wolf, t_sprite_calc *coin)
{
	// coin->temp_1 = wolf->player->dir - wolf->player->fov / 2;
	// if (wolf->player->dir - wolf->player->fov / 2 < RAD_0)
	// 	coin->temp_1 = wolf->player->dir + RAD_360 - wolf->player->fov / 2;
	// coin->temp_2 = coin->angle - (coin->temp_1);
	// if (coin->temp_2 < RAD_0)
	// 	coin->temp_2 = coin->angle + RAD_360 - (coin->temp_1);
	// coin->temp_3 = wolf->player->fov - (coin->temp_2);
	// coin->temp_4 = wolf->player->dir;
	// coin->temp_5 = coin->angle;
	// if (coin->angle < RAD_90 && wolf->player->dir > RAD_270)
	// {
	// 	if (coin->angle < wolf->player->dir)
	// 		coin->temp_4 = wolf->player->dir - RAD_360;
	// 	if (coin->angle > wolf->player->dir)
	// 		coin->temp_5 = coin->angle - RAD_360;
	// }
	// if (wolf->player->dir < RAD_90 && coin->angle > RAD_270)
	// {
	// 	if (coin->angle < wolf->player->dir)
	// 		coin->temp_4 = wolf->player->dir - RAD_360;
	// 	if (coin->angle > wolf->player->dir)
	// 		coin->temp_5 = coin->angle - RAD_360;
	// }
	// if (coin->temp_3 < RAD_0 && coin->temp_5 < coin->temp_4)
	// 	coin->temp_3 = wolf->player->fov + RAD_360 - (coin->temp_2);
}

void	wall_check_coin(t_wolf *wolf, t_sprite_calc *coin)
{
	// coin->i = (int)((W / wolf->player->fov) * (coin->temp_3)
	// 	- ((W / 32) * (wolf->player->dist_to_canvas / coin->dist)) / 2);
	// while (coin->i < (W / wolf->player->fov) * (coin->temp_3)
	// 	+ ((W / 32) * (wolf->player->dist_to_canvas / coin->dist)) / 2)
	// {
	// 	if (coin->i > 0 && coin->i <= W)
	// 	{
	// 		if (coin->dist < wolf->player->distance[W - coin->i]->dist
	// 			/ cosf(wolf->player->fov / 2))
	// 		{
	// 			if (coin->flag_1 == 0)
	// 			{
	// 				coin->flag_i = coin->i;
	// 				coin->flag_1 = coin->count;
	// 			}
	// 		}
	// 		else if (coin->flag_2 == 0 && coin->flag_1 != 0)
	// 			coin->flag_2 = coin->count;
	// 	}
	// 	coin->i++;
	// 	coin->count++;
	// }
	// coin->count--;
	// if (coin->flag_1 != 0 && (coin->flag_2 == 0 || coin->flag_2 == 1))
	// 	coin->flag_2 = coin->count;
}

void	render_coin(t_wolf *wolf, SDL_Surface *surface)
{
	// t_sprite_calc	coin;

	// if (wolf->monster->monster_pos[3].y == 0 && wolf->monster->monster_pos[3].x == 0)
	// 	return ;
	// ft_bzero(&coin, sizeof(t_sprite_calc));
	// if (search_angle(wolf, &coin))
	// 	return ;
	// through_zero(wolf, &coin);
	// wall_check_coin(wolf, &coin);
	// coin.cut_vertical_img.w = (int)((coin.flag_2 - coin.flag_1)
	// 	* (wolf->bon->image_coin->w + 1) / ((W / 32)
	// 	* (wolf->player->dist_to_canvas / coin.dist)));
	// coin.cut_vertical_img.h = (wolf->bon->image_coin->w + 1);
	// coin.cut_vertical_img.x = (int)(coin.flag_1 * (wolf->bon->image_coin->w + 1)
	// 	/ ((W / 32) * (wolf->player->dist_to_canvas / coin.dist)));
	// coin.cut_vertical_img.y = 0;
	// coin.img_location.w = (coin.flag_2 - coin.flag_1);
	// coin.img_location.h = (W / 32) * (wolf->player->dist_to_canvas / coin.dist);
	// coin.img_location.x = coin.flag_i;
	// coin.img_location.y = (H / 2) - ((W / 32)
	// 	* (wolf->player->dist_to_canvas / coin.dist)) / 2 - wolf->player->dir_y;
	// // printf("%d  %d\n", coin.img_location.x, coin.img_location.y);
	// SDL_BlitScaled(wolf->bon->image_coin, &coin.cut_vertical_img,
	// 	surface, &coin.img_location);
	// penetration_check(wolf, coin.img_location);
}
