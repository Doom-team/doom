/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wendell <wendell@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:31:45 by clala             #+#    #+#             */
/*   Updated: 2021/02/08 20:58:23 by wendell          ###   ########.fr       */
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
# include <stdio.h>
# include "../libft/includes/ft_printf.h"
# include <math.h>
# include "const.h"
# include "colors.h"
# include "errors.h"
# include <pthread.h>

typedef struct		s_wall
{
	float			x1;
	float			y1;
	float			x2;
	float			y2;
	float			length;
	int				vert;
	int				h;
	int				type_flag;
	int				squad_stage;
	SDL_Surface		*texture1;
}					t_wall;

typedef struct		s_param2
{
	int				x;
	int				y;
}					t_param2;

typedef struct		s_param3
{
	int				type;
	int				x;
	int				y;
}					t_param3;

typedef struct		s_buff
{
	int				w;
	int				h;
	int				a;
	int				g;
	int				b;
	int				e;
	int				l;
	int				p;
	bool			f;
	bool			s;
	bool			c;
}					t_buff;

typedef struct		s_parser
{
	t_wall			*walls;
	t_param2		*armors;
	t_param3		*guns;
	t_param3		*bullets;
	t_param3		*enemys;
	t_param2		*healths;
	t_param2		*lights;
	t_param2		player;
	SDL_Surface		*floor_texture;
	SDL_Surface		*sky_texture;
	SDL_Surface		*ceiling_texture;
	t_buff			buff;
	int				count_walls;
	int				count_guns;
	int				count_bullets;
	int				count_enemys;
	int				count_healths;
	int				count_armors;
	int				count_lights;
}					t_parser;

typedef struct		s_way
{
	float			dist;
	t_wall			wall;
}					t_way;

typedef struct		s_map
{
	char			*map;
	int				w;
	int				h;
	int				w_pix;
	int				h_pix;
	t_point			mm_start;
	int				mm_cube;
	int				mm_show;
	int				mm_w;
	int				mm_h;
	int				mm_p_size;
	float			mm_map_coef;
	float			mm_cube_coef;
	int				player_start;
}					t_map;

typedef struct		s_float2
{
	float			x;
	float			y;
}					t_float2;

typedef struct		s_distance
{
	float			dist[1000];
	int				number_wall[1000]; //номер стены для того чтобы узнать ее длину при отрисовке текстур для колличества репликаций текстуры на стене
	float			offsetx[1000];
	t_float2		coords[1000];
	// int			type_flag[1000]; // 0 стена, 1 ступенька, 2 двер?
	// int			squad_stage[1000]; // номер блока ступеньки состоит из 3 и более стен
	// int			y[100]; // что это ?
	int				count;
	// char		tex;
	// int			side;
}					t_distance;

typedef struct		s_player
{
	float			x;
	float			y;
	float			speed;
	int				size;
	float			hp;
	float			fov;
	float			dir;
	int				dir_y;
	int				fly;
	float			dist_to_canvas;
	float			step;
	int				floor_offset;
	t_distance		*distance[W];
	t_distance		*distance_horiz[W];
	t_distance		*distance_vert[W];
	t_way			*up_d;
	t_way			*down_d;
	t_way			*rght_d;
	t_way			*left_d;
	int				flying;
	int				inside_step;
	int				in_jump;

	int				run_f;
	int				run_b;
	int				run_r;
	int				run_l;
}					t_player;

typedef	struct		s_sprite_calc
{
	float			angle;
	float			dist;
	float			temp_1;
	float			temp_2;
	float			temp_3;
	float			temp_4;
	float			temp_5;
	int				i;
	int				flag_1;
	int				flag_2;
	int				flag_i;
	int				count;
	SDL_Rect		cut_vertical_img;
	SDL_Rect		img_location;
}					t_sprite_calc;

typedef struct		s_bonus
{
	int				music_flag;
	Mix_Music		*music;
	Mix_Chunk		*music_guns;
	Mix_Chunk		*music_coin;
	int				fps;
	Uint32			start_time;
	int				fps_count;
	int				guns_fire;
	SDL_Surface		*image_1;
	SDL_Surface		*image_2;
	SDL_Surface		*image_3;
	SDL_Surface		*image_4;
	SDL_Surface		*image_5;
	// SDL_Surface	*image_6; //text.jpg
	// SDL_Surface	*image_coin;
	SDL_Surface		*image_aim;
	SDL_Rect		img_location;
	int				flag_guns;
	Uint32			start_guns;
	TTF_Font		*my_font;
}					t_bonus;

typedef struct		s_sdl
{
	// SDL_Surface	*scrs; //menu** scrs
	// int				ufshfadk;
	// SDL_Surface		*textures;
	// SDL_Surface		*sky;
	SDL_Surface		*icon;
	SDL_Window		*win; //menu** window
	int				tex_arr[0xff];
	const Uint8		*state;
	float			skybox_offset;
	float			skybox_offset_y;
	int				run;
	int				sides_mode;
	int				menu;
	int				interlaced_rendering;
	SDL_Renderer	*render;
	SDL_Texture		*window_texture;
	SDL_Event		e;
	unsigned char	*bytes;
	int				pitch;
	bool			run_menu;
	bool			run_screen;
	int				button_flag;
}					t_sdl;

typedef struct		s_monster
{
	SDL_Surface		*image_monster[4];
	int				count_monster;
	t_sprite_calc	data[4];
	t_float2		monster_pos[4];
	float			monster_upscale[4];
	int				sort_arr[4];
	int				penetration_flag;
	int				score_coin;
}					t_monster;

typedef struct		s_position
{
	int				x1;
	int				x2;
	int				y1;
	int				y2;
}					t_position;

typedef struct		s_background
{
	SDL_Surface		*srcs;
	SDL_Surface		*texture;
	t_position		pos;
	unsigned char	*bytes_texture;
}					t_background;

typedef struct		s_button
{
	SDL_Surface		*srcs;
	SDL_Surface		*texture;
	t_position		pos;
	unsigned char	*bytes_texture;
	int				check;
	double			coefficient_x;
	double			coefficient_y;
}					t_button;

typedef struct		s_menu
{
	Mix_Music		*menu_music;
	Mix_Chunk		*move_button;
	Mix_Chunk		*click_button;
	t_background	background;
	t_background	screen_start;
	t_background	screen_death;
	t_background	screen_win;
	t_background	hp;
	t_background	hp_bar;
	t_button		logo;
	t_button		start;
	t_button		settings;
	t_button		exit;
}					t_menu;

typedef struct		s_floor_up
{
	int				y1[1000];
	int				y2[1000];
	float			dist[1000];
	int				h[1000];
	int				count; // храним номер
}					t_floot_up;

typedef struct		s_wolf
{
	t_map			*map;
	t_parser		*p;
	t_player		*player;
	t_sdl			*sdl;
	SDL_Surface		*surface;
	t_bonus			*bon;
	t_monster		*monster;
	t_menu			*menu;
	bool			z_buff[W * H];
	bool			z_buff_2[W * H];
	float			t_cof; // для отладки и тестов
}					t_wolf;

/*
** draw.c
*/

typedef struct
{
	int				number;
	t_wolf			*wolf;
	t_point			point;
	int				interlaced_rendering;
	int				count_distance;
}					pthrData;

/*
** render_hud.c
*/
void				render_hud(t_wolf *wolf);

/*
** parser.c
*/
void				parser(t_wolf *wolf);
void				slice(char s[100], char *a, int from, int to);
void				parsing_walls(t_parser *parser, char **arr);
SDL_Surface			*parsing_param1(t_parser *parser, char **arr, bool *b);
void				parsing_param2(t_param2 *obj, char **arr, int *buff);
void				parsing_param3(t_param3 *obj, char **arr, int *buff);
void				init_size(t_parser *parser, char *l);
void				size_param3(int count, int *buff, t_param3 *object, t_parser *parser);
void				size_param2(int count, int *buff, t_param2 *object, t_parser *parser);
void				size_param1(char **arr, bool *b, int i);
void				parsing_player(t_param2 *obj, char **arr, int *buff);

void				draw_background(SDL_Surface *surface);
int					draw_minimap(t_wolf *wolf, t_map *map, t_player *p);
void				draw_ray(t_wolf *wolf, float player, int x, int y);
void				draw_line(SDL_Surface *surface, t_point start, t_point end,
					int color);
void				draw_rectangle(SDL_Surface *surface, t_point start,
					t_point width_height, int color);

/*
** sdl.c
*/
void				wolf_loop(t_wolf *wolf);
void				handle_event(t_wolf *wolf, SDL_Event *event);
void				recalc(t_wolf *wolf);
void				handle_phisics(t_wolf *wolf, t_player *p);
/*
** menu.c
*/
void				menu_loop(t_wolf *wolf);
void				hooks(t_sdl *sdl, t_menu *menu);
void				check_pos_button(t_sdl *sdl, t_button *button, int k, t_menu *menu);
void				quit(t_sdl *sdl);

/*
** screens.c
*/
void				screen_start(t_wolf *wolf);
void				screen_death(t_wolf *wolf);
void				screen_win(t_wolf *wolf);

/*
** print_menu.c
*/
void				print_menu(t_wolf *wolf);
void				draw_button(t_sdl *sdl, t_button *button);
void				draw_texture(t_sdl *sdl, t_button *button, t_position *pos);

/*
** main.c
*/
t_point				dot(int x, int y);
int					max(int a, int b);

/*
** move.c
*/
void				calc_move(t_wolf *wolf, float dy, float dx);
void				rotate(t_wolf *wolf, SDL_Event *event);
void				add_skybox_offset(t_wolf *wolf, float to_add);
void				jump(t_wolf *wolf);
void	falling(t_wolf *wolf);

/*
** load_textures.c
*/
void				set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
Uint32				get_pixel(SDL_Surface *surface, int x, int y);
int					get_pixel1(SDL_Surface *surface, int x, int y);
void				set_pixel1(SDL_Surface *surface, SDL_Surface *surface1, int x, int y, int pixel);
int					is_texture(t_map *map, int x, int y, char texture);

/*
** map.c
*/
void				init_map(t_wolf *wolf, char *b);

/*
** error.q
*/
int					error_free_s(t_wolf *wolf, char *s);
int					error(t_wolf *wolf, const char *s);
int					error_inv_c(t_wolf *wolf, char *s, char inv_char);
int					error_inv_n(t_wolf *wolf, char *s, int inv_num);

/*
** init.c
*/
void				init_player(t_wolf *wolf, t_player *player, t_map *map);
void				init_sdl(t_wolf *wolf);

/*
** init_bonus.c
*/
void				init_bonus(t_wolf *wolf);
void				init_bonus_load(t_wolf *wolf);

/*
** init_monster.c
*/
void				init_monster(t_wolf *wolf);

/*
** init_menu.c
*/
void				init_menu(t_menu *menu);
void				create_background(t_background *background, char *file);
void				create_button(t_button *button, char *file, int k);
void				create_pos_button(t_button *button, int k);

/*
** aux.c
*/
int					draw_menu(t_wolf *wolf);
int					draw_menu_text(t_wolf *wolf, SDL_Color f_b_color[2]);
int					add_arc(float *arc, float to_add);
int					is_angle(float angle, float rad);
int					float_is_equal(float a, float b);

/*
** render_text.c
*/
void				render_text(t_wolf *wolf, char *text, SDL_Rect location,
					SDL_Color f_b_color[2]);
void				render_score_coin(t_wolf *wolf);
void				render_fps(t_wolf *wolf, t_bonus *bon);
int					get_fps_time(t_bonus *bon);

/*
** distance.c
*/
t_distance			*dist_to_wall(t_wolf *wolf, float angle, int count_distance);
t_distance			*t_distance_new(t_wolf *wolf);
void				t_distance_clear(t_distance *dist);
void				all_get_distance(t_wolf *wolf);
void				free_dist_arr(t_wolf *wolf);

/*
** render_coin.c
*/

void				render_monster(t_wolf *wolf, SDL_Surface *surface);

/*
** render_aim.c
*/
void				render_aim(t_wolf *wolf);
void				penetration_check(t_wolf *wolf, SDL_Rect img_location);

/*
** set_sdl.c
*/
SDL_Color			set_color_sdl(int a, int b, int c);
SDL_Rect			set_rect_sdl(int x, int y, int w, int h);

/*
** pseudo_3d.c
*/
void				pseudo_3d(t_wolf *wolf, t_player *player, SDL_Surface *surface);
void				floorcast_up(t_wolf *wolf, t_distance *dist, int x, int count_distance, t_floot_up stage, int j);
void				floorcast_up_fly(t_wolf *wolf, t_distance *dist, int x, int count_distance, t_floot_up stage, int j);
void				draw_sky(t_wolf *wolf, int x, int y);
void				draw_column(t_wolf *wolf, t_point point,
					t_distance *dist, int count_distance);
void				draw_column_fly(t_wolf *wolf, t_point point, t_distance *dist, int count_distance);
int					fly_correction_from_dist(t_wolf	*wolf, int	j, int count_distance);
int					diry_correction_from_fly(int fly);

/*
** guns_shot.c
*/
void				guns_shot(SDL_Surface *screen, int flag, t_bonus *bon);
void				render_shot(t_wolf *wolf, SDL_Surface *surface);

/*
** music.c
*/
void				music(t_bonus *bon);

#endif
