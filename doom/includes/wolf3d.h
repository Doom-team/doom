/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clala <clala@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:31:45 by clala             #+#    #+#             */
/*   Updated: 2020/10/24 22:09:35 by clala            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "../frameworks/SDL2.framework/Headers/SDL.h"
# include "../frameworks/SDL2_ttf.framework/Headers/SDL_ttf.h"
# include "../frameworks/SDL2_image.framework/Headers/SDL_image.h"
# include "../frameworks/SDL2_mixer.framework/Headers/SDL_mixer.h"
# include <stdbool.h>
# include <fcntl.h>
# include "../libft/includes/ft_printf.h"
# include <math.h>
# include "const.h"
# include "colors.h"
# include "errors.h"

typedef struct	s_map
{
	char		*map;
	int			w;
	int			h;
	int			w_pix;
	int			h_pix;
	t_point		mm_start;
	int			mm_cube;
	int			mm_show;
	int			mm_w;
	int			mm_h;
	int			mm_p_size;
	float		mm_map_coef;
	float		mm_cube_coef;
	int			player_start;
}				t_map;

typedef struct	s_float2
{
	float		x;
	float		y;
}				t_float2;

typedef struct	s_distance
{
	float		dist;
	char		tex;
	int			offsetx;
	int			side;
	t_float2	coords;
	int			y;
}				t_distance;

typedef struct	s_player
{
	float		x;
	float		y;
	float		speed;
	int			size;
	float		fov;
	float		dir;
	int			dir_y;
	float		dist_to_canvas;
	float		step;
	int			floor_offset;
	t_distance	*distance[W];
	t_distance	*distance_horiz[W];
	t_distance	*distance_vert[W];
}				t_player;

typedef	struct	s_sprite_calc
{
	float		angle;
	float		dist;
	float		temp_1;
	float		temp_2;
	float		temp_3;
	float		temp_4;
	float		temp_5;
	int			i;
	int			flag_1;
	int			flag_2;
	int			flag_i;
	int			count;
	SDL_Rect	cut_vertical_img;
	SDL_Rect	img_location;
}				t_sprite_calc;

typedef struct	s_bonus
{
	int			music_flag;
	Mix_Music	*music;
	Mix_Chunk	*music_guns;
	Mix_Chunk	*music_coin;
	int			fps;
	Uint32		start_time;
	int			fps_count;
	int			guns_fire;
	SDL_Surface	*image_1;
	SDL_Surface	*image_2;
	SDL_Surface	*image_3;
	SDL_Surface	*image_4;
	SDL_Surface	*image_5;
	// SDL_Surface	*image_coin;
	SDL_Surface *image_aim;
	SDL_Rect	img_location;
	int			flag_guns;
	Uint32		start_guns;
	TTF_Font	*my_font;
}				t_bonus;

typedef struct	s_sdl
{
	SDL_Surface	*scrs;
	SDL_Surface	*textures;
	SDL_Surface	*sky;
	SDL_Surface	*icon;
	SDL_Window	*win;
	int			tex_arr[0xff];
	const Uint8	*state;
	int			skybox_offset;
	int			run;
	int			sides_mode;
	int			menu;
	int			interlaced_rendering;
}				t_sdl;

typedef struct	s_monster
{
	SDL_Surface	*image_monster[4];
	int			count_monster;
	t_sprite_calc		data[4];
	t_float2	monster_pos[4];
	int			sort_arr[4];
	int			penetration_flag;
	int			score_coin;
}				t_monster;


typedef struct	s_wolf
{
	t_map		*map;
	t_player	*player;
	t_sdl		*sdl;
	SDL_Surface	*surface;
	t_bonus		*bon;
	t_monster	*monster;
}				t_wolf;

/*
** draw.c
*/
void			draw_background(SDL_Surface *surface);
int				draw_minimap(t_wolf *wolf, t_map *map, t_player *p);
void			draw_ray(t_wolf *wolf, float player, int x, int y);
void			draw_line(SDL_Surface *surface, t_point start, t_point end,
				int color);
void			draw_rectangle(SDL_Surface *surface, t_point start,
				t_point width_height, int color);

/*
** sdl.c
*/
void			wolf_loop(t_wolf *wolf);

/*
** main.c
*/
t_point			dot(int x, int y);
int				max(int a, int b);

/*
** move.c
*/
void			calc_move(t_map *map, t_player *p, float dy, float dx);
void			rotate(t_wolf *wolf, SDL_Event *event);
void			add_skybox_offset(t_sdl *sdl, int to_add);

/*
** load_textures.c
*/
void			set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
Uint32			get_pixel(SDL_Surface *surface, int x, int y);
int				is_texture(t_map *map, int x, int y, char texture);

/*
** debug_print.c
*/
void			debug_map(t_map *map);
void			debug_player(t_player *p);

/*
** map.c
*/
void			init_map(t_wolf *wolf, char *b);

/*
** error.q
*/
int				error_free_s(t_wolf *wolf, char *s);
int				error(t_wolf *wolf, const char *s);
int				error_inv_c(t_wolf *wolf, char *s, char inv_char);
int				error_inv_n(t_wolf *wolf, char *s, int inv_num);

/*
** init.c
*/
void			init_player(t_wolf *wolf, t_player *player, t_map *map);
void			init_sdl(t_wolf *wolf);
void			init_mm(t_map *map);
void			init_tex_arr(t_wolf *wolf);

/*
** init_bonus.c
*/
void			init_bonus(t_wolf *wolf);
void			init_bonus_load(t_wolf *wolf);

/*
** init_monster.c
*/
void			init_monster(t_wolf *wolf);

/*
** aux.c
*/
int				draw_menu(t_wolf *wolf);
int				draw_menu_text(t_wolf *wolf, SDL_Color f_b_color[2]);
int				add_arc(float *arc, float to_add);
int				is_angle(float angle, float rad);
int				float_is_equal(float a, float b);

/*
** render_text.c
*/
void			render_text(t_wolf *wolf, char *text, SDL_Rect location,
				SDL_Color f_b_color[2]);
void			render_score_coin(t_wolf *wolf);
void			render_fps(t_wolf *wolf, t_bonus *bon);
int				get_fps_time(t_bonus *bon);

/*
** distance.c
*/
t_distance		*dist_to_wall(t_wolf *wolf, float angle, int count_distance);
t_distance		*t_distance_new(t_wolf *wolf);
void			t_distance_clear(t_distance *dist);
void			all_get_distance(t_wolf *wolf);
void			free_dist_arr(t_wolf *wolf);

/*
** render_coin.c
*/

void			render_monster(t_wolf *wolf, SDL_Surface *surface);

/*
** render_coin.c
*/
// void			render_coin(t_wolf *wolf, SDL_Surface *surface);
// int				score_coin(t_wolf *wolf, t_sprite_calc *coin);
// int				search_angle(t_wolf *wolf, t_sprite_calc *coin);
// void			through_zero(t_wolf *wolf, t_sprite_calc *coin);
// void			wall_check_coin(t_wolf *wolf, t_sprite_calc *coin);

/*
** render_aim.c
*/
void			render_aim(t_wolf *wolf);
void			penetration_check(t_wolf *wolf, SDL_Rect img_location);

/*
** set_sdl.c
*/
SDL_Color		set_color_sdl(int a, int b, int c);
SDL_Rect		set_rect_sdl(int x, int y, int w, int h);

/*
** pseudo_3d.c
*/
void			pseudo_3d(t_wolf *wolf, t_player *player, SDL_Surface *surface);
void			draw_sky(t_wolf *wolf, int x, int y);
void			draw_floor(SDL_Surface *surface, int x, int y);
void			draw_column(t_wolf *wolf, t_point point,
t_distance *dist, int size);

/*
** distance_horiz.c
*/
t_distance		*find_horizontal_intersection(t_wolf *wolf,
float angle, t_distance *dist);

/*
** distance_vert.c
*/
t_distance		*find_vertical_intersection(t_wolf *wolf,
float angle, t_distance *dist);

/*
** guns_shot.c
*/
void			guns_shot(SDL_Surface *screen, int flag, t_bonus *bon);
void			render_shot(t_wolf *wolf, SDL_Surface *surface);

/*
** music.c
*/
void			music(t_bonus *bon);

#endif
