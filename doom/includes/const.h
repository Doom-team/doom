/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:31:45 by clala             #+#    #+#             */
/*   Updated: 2020/10/18 18:31:46 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONST_H
# define CONST_H

# define DEBUG 1
# define SHOW_FPS 1

# define INTBUF_INIT_SIZE 64
# define INTBUF_RESIZE_COEF 4
# define MAP_MAX_SIZE 204800
# define MAP_MIN_SIZE 16
# define MAP_MIN_ROW_NUM 3
# define MAP_MIN_COL_NUM 4
# define MAP_FILEPATH "maps/map.txt"

# define CHARSET " *#012345S$"
# define WALLSET "*#012345"
# define FLOORSET " S"
# define TEX_BORDER '*'
# define TEX_FLOOR ' '
# define TEX_COIN '$'
# define TEX_WALL '#'
# define TEX_INF '8'
# define TEX_START 'S'
# define TEX_SOUTH 's'
# define TEX_NORTH 'n'
# define TEX_WEST 'w'
# define TEX_EAST 'e'
# define TEX_BLOOD '0'
# define TEX_PANEL '1'
# define TEX_BOULD '2'
# define TEX_CORALL '3'
# define TEX_EYES '4'
# define TEX_ISLE '5'

# define W 800
# define H 600
# define W_MAX 1920
# define H_MAX 1080
# define CUBE 64

# define PLAYER_MM_SIZE 4
# define KLUDGE 0.0001
# define RAD_360 6.28319f
# define RAD_1 0.0174533f
# define RAD_60 1.047200f
# define RAD_30 0.523599f
# define RAD_180 M_PI
# define RAD_0 0.
# define RAD_90 1.570800f
# define RAD_45 0.785398f
# define RAD_270 4.71239f

# define TEXTURE_PATH "textures/tex.bmp"
# define ICON_PATH "textures/icon.bmp"
# define SKY_PATH "textures/sky.bmp"

#endif
