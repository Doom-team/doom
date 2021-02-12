/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monster_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahusk <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 12:40:39 by ahusk             #+#    #+#             */
/*   Updated: 2021/02/12 12:40:42 by ahusk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static	void	monster_load_helper1(t_wolf *wolf)
{
	if (!(wolf->bon->monster[0] = IMG_Load("../textures/enemy/beam/0.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->monster[1] = IMG_Load("../textures/enemy/beam/1.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->monster[2] = IMG_Load("../textures/enemy/beam/2.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->monster[3] = IMG_Load("../textures/enemy/beam/3.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->monster[4] = IMG_Load("../textures/enemy/beam/4.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->monster[5] = IMG_Load("../textures/enemy/beam/5.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->monster[6] = IMG_Load("../textures/enemy/abbadon/0.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->monster[7] = IMG_Load("../textures/enemy/abbadon/1.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->monster[8] = IMG_Load("../textures/enemy/abbadon/2.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->monster[9] = IMG_Load("../textures/enemy/abbadon/3.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->monster[10] = IMG_Load("../textures/enemy/abbadon/4.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->monster[11] = IMG_Load("../textures/enemy/abbadon/5.png")))
		error(wolf, SDL_GetError());
}

static	void	monster_load_helper2(t_wolf *wolf)
{
	if (!(wolf->bon->monster[12] =
		IMG_Load("../textures/enemy/arachnophyte/0.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->monster[13] =
		IMG_Load("../textures/enemy/arachnophyte/1.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->monster[14] =
		IMG_Load("../textures/enemy/arachnophyte/2.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->monster[15] =
		IMG_Load("../textures/enemy/arachnophyte/3.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->monster[16] =
		IMG_Load("../textures/enemy/arachnophyte/4.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->monster[17] =
		IMG_Load("../textures/enemy/arachnophyte/5.png")))
		error(wolf, SDL_GetError());
}

static	void	monster_load_helper3(t_wolf *wolf)
{
	if (!(wolf->bon->monster[18] =
		IMG_Load("../textures/enemy/annihilator/0.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->monster[19] =
		IMG_Load("../textures/enemy/annihilator/1.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->monster[20] =
		IMG_Load("../textures/enemy/annihilator/2.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->monster[21] =
		IMG_Load("../textures/enemy/annihilator/3.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->monster[22] =
		IMG_Load("../textures/enemy/annihilator/4.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->monster[23] =
		IMG_Load("../textures/enemy/annihilator/5.png")))
		error(wolf, SDL_GetError());
}

void			monster_load(t_wolf *wolf)
{
	monster_load_helper1(wolf);
	monster_load_helper2(wolf);
	monster_load_helper3(wolf);
	if (!(wolf->bon->monster[24] =
		IMG_Load("../textures/enemy/hierophant/0.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->monster[25] =
		IMG_Load("../textures/enemy/hierophant/1.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->monster[26] =
		IMG_Load("../textures/enemy/hierophant/2.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->monster[27] =
		IMG_Load("../textures/enemy/hierophant/3.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->monster[28] =
		IMG_Load("../textures/enemy/hierophant/4.png")))
		error(wolf, SDL_GetError());
	if (!(wolf->bon->monster[29] =
		IMG_Load("../textures/enemy/hierophant/5.png")))
		error(wolf, SDL_GetError());
}
