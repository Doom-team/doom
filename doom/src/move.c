/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:32:04 by clala             #+#    #+#             */
/*   Updated: 2021/01/26 20:27:00 by wendell          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	add_skybox_offset_y(t_sdl *sdl, int to_add)
{
	sdl->skybox_offset_y += to_add;
	while (sdl->skybox_offset_y > sdl->sky->h)
		sdl->skybox_offset_y -= sdl->sky->h;
	while (sdl->skybox_offset_y < 0)
		sdl->skybox_offset_y += sdl->sky->h;
}

void	add_skybox_offset(t_sdl *sdl, float to_add)
{
	sdl->skybox_offset += to_add;
	while (sdl->skybox_offset > sdl->sky->w)
		sdl->skybox_offset -= sdl->sky->w;
	while (sdl->skybox_offset < 0)
		sdl->skybox_offset += sdl->sky->w;
}

void	rotate(t_wolf *wolf, SDL_Event *event)
{
	if (-event->motion.xrel * 0.001 > 0.05 || -event->motion.xrel * 0.001 < -0.05)
	{
		if (-event->motion.xrel > 0)
		{
			add_arc(&(wolf->player->dir), 0.05);
			add_skybox_offset(wolf->sdl, W / (float)wolf->sdl->sky->w * -60.0);
		}
		else
		{
			add_arc(&(wolf->player->dir), -0.05);
			add_skybox_offset(wolf->sdl, W / (float)wolf->sdl->sky->w * 60.0);
		}
	}
	else
	{
		add_arc(&(wolf->player->dir), -event->motion.xrel * 0.005);
		add_skybox_offset(wolf->sdl, event->motion.xrel * W / (float)wolf->sdl->sky->w * 6.0);
		// printf("%f\n", event->motion.xrel * W / (float)wolf->sdl->sky->w * 6.0);
	}
	// printf("%d\n", wolf->sdl->sky->w);
	wolf->player->dir_y += (int)(H / 200.0 * event->motion.yrel / 5.0);
	if (wolf->player->dir_y > H / 4 * 3)
		wolf->player->dir_y = H / 4 * 3;
	if (wolf->player->dir_y < -H / 4 * 3)
		wolf->player->dir_y = -H / 4 * 3;
	// printf("%f\n", wolf->sdl->skybox_offset_y);
	if (wolf->player->dir_y != -H / 4 * 3 && wolf->player->dir_y != H / 4 * 3)
		add_skybox_offset_y(wolf->sdl, (int)(H / 200.0 * event->motion.yrel / 5.0));
}

void	calc_move(t_wolf *wolf, float dy, float dx)
{
	recalc(wolf);
	if (dx > 0) 
	{
		if (wolf->player->rght_d->dist > dx + 6.51)
			wolf->player->x += dx;
		else if(wolf->player->rght_d->wall.type_flag == 1 && UP_LENGTH * wolf->player->rght_d->wall.h + wolf->player->fly <= UP_LENGTH)
		{
			printf("1\n");
			wolf->player->x += dx;
			if (UP_LENGTH * wolf->player->rght_d->wall.h + wolf->player->fly >= 0)
				wolf->player->fly = -UP_LENGTH * wolf->player->rght_d->wall.h;
			// else
			// {
			// 	wolf->player->fly = UP_LENGTH * wolf->player->rght_d->wall.h;
			// }
			
		}
	}
	else if(dx < 0)
	{
		if (wolf->player->left_d->dist > fabs(dx) + 6.51)
			wolf->player->x += dx;
		else if(wolf->player->left_d->wall.type_flag == 1 && UP_LENGTH * wolf->player->left_d->wall.h + wolf->player->fly <= UP_LENGTH)
		{
			printf("2\n");
			wolf->player->x += dx;
			if (UP_LENGTH * wolf->player->left_d->wall.h + wolf->player->fly >= 0)
				wolf->player->fly = -UP_LENGTH * wolf->player->left_d->wall.h;
			// else
			// {
			// 	wolf->player->fly += UP_LENGTH * wolf->player->left_d->wall.h;
			// }
			
		}
	}
	if (wolf->player->fly > 0)
		wolf->player->fly = 0;
	recalc(wolf);
	if (dy > 0) 
	{
		if (wolf->player->up_d->dist > dy + 6.51)
			wolf->player->y += dy;
		else if(wolf->player->up_d->wall.type_flag && UP_LENGTH * wolf->player->up_d->wall.h + wolf->player->fly <= UP_LENGTH)
		{
			printf("3\n");
			wolf->player->y += dy;
			if (UP_LENGTH * wolf->player->up_d->wall.h + wolf->player->fly >= 0)
				wolf->player->fly = -UP_LENGTH * wolf->player->up_d->wall.h;
			// else
			// {
			// 	wolf->player->fly += UP_LENGTH * wolf->player->up_d->wall.h;
			// }
			
		}
	}
	else if(dy < 0)
	{
		if (wolf->player->down_d->dist > fabs(dy) + 6.51)
			wolf->player->y += dy;
		else if(wolf->player->down_d->wall.type_flag && UP_LENGTH * wolf->player->down_d->wall.h + wolf->player->fly <= UP_LENGTH)
		{
			// printf("4\n");
			wolf->player->y += dy;
			if (UP_LENGTH * wolf->player->down_d->wall.h + wolf->player->fly >= 0)
				wolf->player->fly = -UP_LENGTH * wolf->player->down_d->wall.h;
			// else
			// {
			// 	wolf->player->fly += UP_LENGTH * wolf->player->down_d->wall.h;
			// }
			
		}
	}
	if (wolf->player->fly > 0)
		wolf->player->fly = 0;
	// printf("u:%3f d:%f r:%f l:%f\n", wolf->player->up_d->dist, wolf->player->down_d->dist, wolf->player->rght_d->dist, wolf->player->left_d->dist);
	// printf("%d\n", wolf->player->fly);
	recalc(wolf);
}
