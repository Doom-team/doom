/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcast_up_fly.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 18:01:14 by ahusk             #+#    #+#             */
/*   Updated: 2021/02/12 18:01:17 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		floorcast_up_fly_help1(t_helper *h, t_floot_up *stage, int j)
{
	if (stage->y1[j] == 0 && stage->y2[j] != 0)
	{
		h->tmp = stage->y2[j];
		stage->y2[j] = H;
		stage->y1[j] = h->tmp;
		h->temp_y = stage->y1[j];
	}
	else if (stage->y1[j] == -1 && stage->y2[j] != 0)
	{
		stage->y1[j] = stage->y2[j];
		if (stage->count % 2 == 0)
		{
			h->tmp = stage->y2[j];
			stage->y2[j] = 0;
			stage->y1[j] = h->tmp;
			h->temp_y = stage->y1[j];
		}
		else
		{
			h->tmp = stage->y2[j];
			stage->y2[j] = H;
			stage->y1[j] = h->tmp;
			h->temp_y = stage->y1[j];
		}
	}
}

static void		floorcast_up_fly_help2(t_helper *h,
				t_distance *dist, t_wolf *wolf, t_helper *hel)
{
	if (h->temp_y >= 0 && h->temp_y <= H)
	{
		h->curr_dist = (H - wolf->player->fly) / (2.0 *
			(h->y + wolf->player->fly) - (H - wolf->player->fly));
		h->weight = h->curr_dist /
			(dist->dist[wolf->player->distance[hel->count_distance]->count - 1]
				/ (h->cof * h->cof_h));
		h->curr_floorx = h->weight *
			(dist->coords[wolf->player->distance[hel->count_distance]->count
				- 1].x / (h->cof * h->cof_h)) + (1.0 - h->weight)
					* (wolf->player->x / (h->cof * h->cof_h));
		h->curr_floory = h->weight *
			(dist->coords[wolf->player->distance[hel->count_distance]->count
				- 1].y / (h->cof * h->cof_h)) + (1.0 - h->weight)
					* (wolf->player->y / (h->cof * h->cof_h));
		h->textx = (int)(h->curr_floorx * wolf->p->floor_texture->w
			* h->cof * h->cof_h) % wolf->p->floor_texture->w;
		h->texty = (int)(h->curr_floory * wolf->p->floor_texture->h
			* h->cof * h->cof_h) % wolf->p->floor_texture->h;
		if (h->textx > 0 && h->texty > 0)
		{
			h->color = get_pixel(wolf->p->floor_texture, h->textx, h->texty);
			set_pixel(wolf->surface, hel->x, h->temp_y, h->color);
		}
	}
}

void			floorcast_up_fly(t_wolf *wolf, t_distance *dist,
				t_floot_up stage, t_helper hel)
{
	t_helper	h;

	ft_memset(&h, 0, sizeof(t_helper));
	if ((stage.y1[hel.j] == 0 && stage.y2[hel.j] == 0))
		return ;
	h.cof = cof_size_displ();
	h.cof_h = -0.4 * stage.h[hel.j] + 1.0 +
		correct_cof_h(wolf) * stage.h[hel.j];
	floorcast_up_fly_help1(&h, &stage, hel.j);
	h.temp_y = stage.y1[hel.j] - (wolf->player->dir_y +
		diry_correction_from_fly(wolf->player->fly));
	h.y = stage.y1[hel.j];
	while (h.temp_y < stage.y2[hel.j])
	{
		floorcast_up_fly_help2(&h, dist, wolf, &hel);
		h.temp_y++;
		h.y++;
	}
}
