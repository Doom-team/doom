/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pseudo_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:31:45 by clala             #+#    #+#             */
/*   Updated: 2020/10/24 21:56:30 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	draw_column(t_wolf *wolf,
t_point point, t_distance *dist, int size)
{
	int	color;
	int	i;
	int	height;

	i = 0;
	height = H - point.y * 2;
	// поинт y начало отрисовки стены сайз конец
	// point.y -= wolf->player->dir_y;
	// size -= wolf->player->dir_y;
	while (point.y < size)
	{
		color = get_pixel(wolf->sdl->textures, dist->offsetx + \
		wolf->sdl->tex_arr[(int)dist->tex], i * CUBE / height);
		if (point.y - wolf->player->dir_y > 0 && point.y - wolf->player->dir_y < H)
			set_pixel(wolf->surface, point.x, point.y - wolf->player->dir_y, color);
		point.y++;
		i++;
	}
}

void	draw_floor(SDL_Surface *surface, int x, int y)
{
	if (y < 0)
		y = 0;
	while (y < H)
	{
		set_pixel(surface, x, y, COLOR_GREY_LIGHT);
		y++;
	}
}

void	draw_sky(t_wolf *wolf, int x, int y)
{
	int		i;
	int		to_draw;

	i = -1;
	if (y < 0)
		y = 0;
	if (y > H)
		y = H;
	while (++i < y)
	{
		to_draw = i < wolf->sdl->sky->h - 1 ? i : wolf->sdl->sky->h / 2;
		set_pixel(wolf->surface, x, i, get_pixel(wolf->sdl->sky,
			x + wolf->sdl->skybox_offset, to_draw));
	}
}

static void	floorcast(t_wolf *wolf, t_distance *dist, int x, int y)
{
	float curr_dist;
	float weight;
	float currFloorX;
	float currFloorY;
	int textx;
	int texty;
	int color;

	int temp_y;

	temp_y = y - wolf->player->dir_y;
	while (temp_y < H)
	{
		curr_dist = (float)H / (float)(2 * y - H);
		
		weight = curr_dist / (dist->dist);
		
		currFloorX = weight * dist->coords.x + (1.f - weight) * wolf->player->x;
		currFloorY = weight * dist->coords.y + (1.f - weight) * wolf->player->y;
		
		textx = (int)(currFloorX * CUBE) % CUBE;
		texty = (int)(currFloorY * CUBE) % CUBE;
		
		if (textx < 0)
			textx = 0;
		if (texty < 0)
			texty = 0;
		
		color = get_pixel(wolf->sdl->textures, textx, texty);
		set_pixel(wolf->surface, x, temp_y, color);
		// color = get_pixel(wolf->sdl->textures, textx + CUBE * 5, texty);
		// set_pixel(wolf->surface, x, H - y, color);
		temp_y++;
		y++;
	}
}

/*{

	https://lodev.org/cgtutor/raycasting2.html
	
	for(int x = 0; x < w; x++)
    {
      
	// ЛИТЬЕ НА СТЕНУ
      // [СНиП ... код заливки пола находится в том же x-цикле, что и заливка стен, код заливки стен здесь не дублируется]

      // ЛИТЬЕ ПОЛА (вертикальный вариант, сразу после рисования вертикальной полосы стены для текущего x)
      double floorXWall, floorYWall; // x, y положение текселя пола в нижней части стены

      // wallX - где именно стена была поражена = dist->coords.x
	// Возможны 4 разных направления стены
      if(side == 0 && rayDirX > 0)
      {
        floorXWall = mapX;
        floorYWall = mapY + wallX;
      }
      else if(side == 0 && rayDirX < 0)
      {
        floorXWall = mapX + 1.0;
        floorYWall = mapY + wallX;
      }
      else if(side == 1 && rayDirY > 0)
      {
        floorXWall = mapX + wallX;
        floorYWall = mapY;
      }
      else
      {
        floorXWall = mapX + wallX;
        floorYWall = mapY + 1.0;
      }

      double distWall, distPlayer, currentDist;

      distWall = perpWallDist;
      distPlayer = 0.0;

      if (drawEnd < 0) drawEnd = h; // становится <0, когда целое число переполняется

      // рисуем пол от drawEnd до нижней части экрана
      for(int y = drawEnd + 1; y < h; y++)
      {
        currentDist = h / (2.0 * y - h); // вместо этого вы можете сделать небольшую таблицу поиска

        double weight = (currentDist - distPlayer) / (distWall - distPlayer);

        double currentFloorX = weight * floorXWall + (1.0 - weight) * posX;
        double currentFloorY = weight * floorYWall + (1.0 - weight) * posY;

        int floorTexX, floorTexY;
        floorTexX = int(currentFloorX * texWidth) % texWidth;
        floorTexY = int(currentFloorY * texHeight) % texHeight;

        //floor
        buffer[y][x] = (texture[3][texWidth * floorTexY + floorTexX] >> 1) & 8355711;
        //ceiling (symmetrical!)
        buffer[h - y][x] = texture[6][texWidth * floorTexY + floorTexX];
      }
    }
}*/

void	pseudo_3d(t_wolf *wolf, t_player *player, SDL_Surface *surface)
{
	t_point	point;
	int		count_distance;
	float	dir;

	count_distance = W - 1;
	dir = player->dir;
	add_arc(&dir, player->fov / 2);
	point.y = 0;
	if (wolf->sdl->interlaced_rendering == 0)
		point.x = 0;
	else
		point.x = 1;
	while (point.x < W)
	{
		if (player->distance[count_distance]->dist != 0)
		{
			point.y = ceilf((CUBE * player->dist_to_canvas)
				/ player->distance[count_distance]->dist);
			point.y = (H - point.y) / 2; // сколько отступ сверху и снизу
			draw_column(wolf, point,
				player->distance[count_distance], H - point.y);
			draw_sky(wolf, point.x, point.y - wolf->player->dir_y);
			floorcast(wolf, player->distance[count_distance], point.x, H - (point.y) + 1);
			// draw_floor(surface, point.x, H - (point.y + wolf->player->dir_y));
		}
		count_distance -= 2;
		point.x += 2;
		add_arc(&dir, -player->step);
	}
	if (wolf->sdl->interlaced_rendering == 0)
		wolf->sdl->interlaced_rendering = 1;
	else
		wolf->sdl->interlaced_rendering = 0;
}