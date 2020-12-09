#include "../includes/wolf3d.h"

static int	check_free_position(t_wolf *wolf, int i, int x, int y)
{
	int j;

	j = 0;
	while (j < wolf->monster->count_monster)
	{
		if (i != j)
		{
			if (wolf->monster->monster_pos[j].x == x &&
				wolf->monster->monster_pos[j].y == y)
			{
				return (0);
			}
		}
		j++;
	}
	return (1);
}

static void	score_monster(t_wolf *wolf, int i)
{
	float	x;
	float	y;
	int		flag;

	flag = 0;
	if (wolf->monster->data[i].dist < 20 || wolf->monster->penetration_flag == 1)
	{
		Mix_Volume(0, 32);
		Mix_PlayChannel(2, wolf->bon->music_coin, 0);
		Mix_VolumeMusic(5);
		wolf->monster->score_coin++;
		wolf->monster->penetration_flag = 0;
		while (flag != 1)
		{
			y = rand() % wolf->map->h;
			x = rand() % wolf->map->w;
			if (wolf->map->map[(int)(y * wolf->map->w + x)] == TEX_FLOOR && check_free_position(wolf, i, (x + 0.5) * CUBE, (y + 0.5) * CUBE))
			{
				wolf->monster->monster_pos[i].x = (x + 0.5) * CUBE;
				wolf->monster->monster_pos[i].y = (y + 0.5) * CUBE;
				flag = 1;
			}
		}
	}
}

static void		search_angle_monster(t_wolf *wolf, int i)
{
	wolf->monster->data[i].dist = sqrtf(powf((wolf->monster->monster_pos[i].x - wolf->player->x), 2)
		+ powf((wolf->monster->monster_pos[i].y - wolf->player->y), 2));
	if (wolf->monster->monster_pos[i].x - wolf->player->x > 0
		&& wolf->monster->monster_pos[i].y - wolf->player->y < 0)
		wolf->monster->data[i].angle = asin((wolf->player->y - wolf->monster->monster_pos[i].y)
			/ wolf->monster->data[i].dist);
	else if (wolf->monster->monster_pos[i].x - wolf->player->x < 0
		&& wolf->monster->monster_pos[i].y - wolf->player->y < 0)
		wolf->monster->data[i].angle = asin((wolf->monster->monster_pos[i].y - wolf->player->y)
			/ wolf->monster->data[i].dist) + RAD_180;
	else if (wolf->monster->monster_pos[i].x - wolf->player->x < 0
		&& wolf->monster->monster_pos[i].y - wolf->player->y > 0)
		wolf->monster->data[i].angle = asin((wolf->monster->monster_pos[i].y - wolf->player->y)
			/ wolf->monster->data[i].dist) + RAD_180;
	else if (wolf->monster->monster_pos[i].x - wolf->player->x > 0
		&& wolf->monster->monster_pos[i].y - wolf->player->y > 0)
		wolf->monster->data[i].angle = asin((wolf->player->y - wolf->monster->monster_pos[i].y)
			/ wolf->monster->data[i].dist) + RAD_360;
}

static void    wall_check_monster(t_wolf *wolf, int i)
{
	wolf->monster->data[i].i = (int)((W / wolf->player->fov) * ( wolf->monster->data[i].temp_3)
		- ((W / 32) * (wolf->player->dist_to_canvas /  wolf->monster->data[i].dist)) / 2);
	while ( wolf->monster->data[i].i < (W / wolf->player->fov) * ( wolf->monster->data[i].temp_3)
		+ ((W / 32) * (wolf->player->dist_to_canvas /  wolf->monster->data[i].dist)) / 2)
	{
		if ( wolf->monster->data[i].i > 0 &&  wolf->monster->data[i].i <= W)
		{
			if ( wolf->monster->data[i].dist < wolf->player->distance[W -  wolf->monster->data[i].i]->dist
				/ cosf(wolf->player->fov / 2))
			{
				if (wolf->monster->data[i].flag_1 == 0)
				{
					wolf->monster->data[i].flag_i = wolf->monster->data[i].i;
					wolf->monster->data[i].flag_1 = wolf->monster->data[i].count;
				}
			}
			else if (wolf->monster->data[i].flag_2 == 0 && wolf->monster->data[i].flag_1 != 0)
				wolf->monster->data[i].flag_2 = wolf->monster->data[i].count;
		}
		wolf->monster->data[i].i++;
		wolf->monster->data[i].count++;
	}
	wolf->monster->data[i].count--;
	if (wolf->monster->data[i].flag_1 != 0 && (wolf->monster->data[i].flag_2 == 0 || wolf->monster->data[i].flag_2 == 1))
		wolf->monster->data[i].flag_2 = wolf->monster->data[i].count;
}

static void    through_zero_monster(t_wolf *wolf, int i)
{
   wolf->monster->data[i].temp_1 = wolf->player->dir - wolf->player->fov / 2;
	if (wolf->player->dir - wolf->player->fov / 2 < RAD_0)
		wolf->monster->data[i].temp_1 = wolf->player->dir + RAD_360 - wolf->player->fov / 2;
	wolf->monster->data[i].temp_2 = wolf->monster->data[i].angle - (wolf->monster->data[i].temp_1);
	if (wolf->monster->data[i].temp_2 < RAD_0)
		wolf->monster->data[i].temp_2 = wolf->monster->data[i].angle + RAD_360 - (wolf->monster->data[i].temp_1);
	wolf->monster->data[i].temp_3 = wolf->player->fov - (wolf->monster->data[i].temp_2);
	wolf->monster->data[i].temp_4 = wolf->player->dir;
	wolf->monster->data[i].temp_5 = wolf->monster->data[i].angle;
	if (wolf->monster->data[i].angle < RAD_90 && wolf->player->dir > RAD_270)
	{
		if (wolf->monster->data[i].angle < wolf->player->dir)
			wolf->monster->data[i].temp_4 = wolf->player->dir - RAD_360;
		if (wolf->monster->data[i].angle > wolf->player->dir)
			wolf->monster->data[i].temp_5 = wolf->monster->data[i].angle - RAD_360;
	}
	if (wolf->player->dir < RAD_90 && wolf->monster->data[i].angle > RAD_270)
	{
		if (wolf->monster->data[i].angle < wolf->player->dir)
			wolf->monster->data[i].temp_4 = wolf->player->dir - RAD_360;
		if (wolf->monster->data[i].angle > wolf->player->dir)
			wolf->monster->data[i].temp_5 = wolf->monster->data[i].angle - RAD_360;
	}
	if (wolf->monster->data[i].temp_3 < RAD_0 && wolf->monster->data[i].temp_5 < wolf->monster->data[i].temp_4)
		wolf->monster->data[i].temp_3 = wolf->player->fov + RAD_360 - (wolf->monster->data[i].temp_2);
}

static void	buble_sort(t_wolf *wolf)
{
	int i;
	int j;

	i = -1;
	while(++i < wolf->monster->count_monster)
		wolf->monster->sort_arr[i] = i;
	i = 0;
	while (i < wolf->monster->count_monster - 1)
	{
		j = wolf->monster->count_monster - 1;
		while (j > i)
		{
			if (wolf->monster->data[j - 1].dist < wolf->monster->data[j].dist)
			{
				int temp = wolf->monster->sort_arr[j - 1];
				float f_temp = wolf->monster->data[j - 1].dist;
				wolf->monster->sort_arr[j - 1] = wolf->monster->sort_arr[j];
				wolf->monster->data[j - 1].dist = wolf->monster->data[j].dist;
				wolf->monster->sort_arr[j] = temp;
				wolf->monster->data[j].dist = f_temp;

			}
			j--;
		}
		i++;
	}
}

void    render_monster(t_wolf *wolf, SDL_Surface *surface)
{
	buble_sort(wolf);
	int i = 0;
	while (i < wolf->monster->count_monster)
	{
		ft_bzero(&(wolf->monster->data[wolf->monster->sort_arr[i]]), sizeof(t_sprite_calc));
		search_angle_monster(wolf, wolf->monster->sort_arr[i]);
		through_zero_monster(wolf, wolf->monster->sort_arr[i]);
		wall_check_monster(wolf, wolf->monster->sort_arr[i]);
		wolf->monster->data[wolf->monster->sort_arr[i]].cut_vertical_img.w = (int)((wolf->monster->data[wolf->monster->sort_arr[i]].flag_2 - wolf->monster->data[wolf->monster->sort_arr[i]].flag_1)
			* (wolf->monster->image_monster[wolf->monster->sort_arr[i]]->w) / ((W / 32)
			* (wolf->player->dist_to_canvas / wolf->monster->data[wolf->monster->sort_arr[i]].dist)));
		wolf->monster->data[wolf->monster->sort_arr[i]].cut_vertical_img.h = (wolf->monster->image_monster[wolf->monster->sort_arr[i]]->w);
		wolf->monster->data[wolf->monster->sort_arr[i]].cut_vertical_img.x = (int)(wolf->monster->data[wolf->monster->sort_arr[i]].flag_1 * (wolf->monster->image_monster[wolf->monster->sort_arr[i]]->w)
			/ ((W / 32) * (wolf->player->dist_to_canvas / wolf->monster->data[wolf->monster->sort_arr[i]].dist)));
		wolf->monster->data[wolf->monster->sort_arr[i]].cut_vertical_img.y = 0;
		wolf->monster->data[wolf->monster->sort_arr[i]].img_location.w = (wolf->monster->data[wolf->monster->sort_arr[i]].flag_2 - wolf->monster->data[wolf->monster->sort_arr[i]].flag_1) * wolf->monster->monster_upscale[wolf->monster->sort_arr[i]];
		wolf->monster->data[wolf->monster->sort_arr[i]].img_location.h = (W / 32) * wolf->monster->monster_upscale[wolf->monster->sort_arr[i]] * (wolf->player->dist_to_canvas / wolf->monster->data[wolf->monster->sort_arr[i]].dist);
		wolf->monster->data[wolf->monster->sort_arr[i]].img_location.x = wolf->monster->data[wolf->monster->sort_arr[i]].flag_i;
		wolf->monster->data[wolf->monster->sort_arr[i]].img_location.y = (H / 2) - ((W / 32) * (wolf->player->dist_to_canvas / wolf->monster->data[wolf->monster->sort_arr[i]].dist)) / 2 - wolf->player->dir_y; //сюда динамическое изменение высоты постановки прикрутить
		SDL_BlitScaled(wolf->monster->image_monster[wolf->monster->sort_arr[i]], &(wolf->monster->data[wolf->monster->sort_arr[i]].cut_vertical_img), 
			surface, &(wolf->monster->data[wolf->monster->sort_arr[i]].img_location));
		penetration_check(wolf, wolf->monster->data[wolf->monster->sort_arr[i]].img_location);
		score_monster(wolf, wolf->monster->sort_arr[i]);
		i++;
	}
}