/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:31:45 by skaren            #+#    #+#             */
/*   Updated: 2021/02/12 15:34:19 by grinko           ###   ########.fr       */
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
	float			realx;
	float			realy;
	float			length;
	float			h;
	float			angle;
	int				active;
	int				vert;
	int				type_flag;
	int				squad_stage;
	int				type_stage;
	int				opening;
	SDL_Surface		*texture1;
}					t_wall;

typedef struct		s_param2
{
	float			x;
	float			y;
}					t_param2;

typedef struct		s_buff
{
	int				w;
	bool			m;
	bool			p;
	bool			f;
	bool			s;
	bool			c;
}					t_buff;

typedef struct		s_parser
{
	t_wall			*walls;
	t_param2		player;
	Mix_Music		*music;
	Mix_Chunk		*take_damage;
	SDL_Surface		*floor_texture;
	SDL_Surface		*sky_texture;
	SDL_Surface		*ceiling_texture;
	t_buff			buff;
	int				count_walls;
}					t_parser;

typedef struct		s_way
{
	float			dist;
	t_wall			wall;
}					t_way;

typedef struct		s_float2
{
	float			x;
	float			y;
}					t_float2;

typedef struct		s_distance
{
	float			dist[1000];
	int				number_wall[1000];
	float			offsetx[1000];
	t_float2		coords[1000];
	int				count;
}					t_distance;

typedef struct		s_player
{
	float			x;
	float			y;
	float			speed;
	int				size;
	int				num_ammo;
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
	float			dist_obj;
	int				indx_obj;
	float			dist_mon;
	int				indx_mon;
}					t_player;

typedef struct		s_bonus
{
	int				set_gun;
	int				fps;
	Uint32			start_time;
	int				fps_count;
	int				guns_fire;
	SDL_Surface		*pistol_image[5];
	SDL_Surface		*ak_image[4];
	SDL_Surface		*shotgun_image[7];
	SDL_Surface		*monster[30];
	SDL_Surface		*key_red_tex;
	SDL_Surface		*key_yellow_tex;
	SDL_Surface		*key_blue_tex;
	Mix_Chunk		*music_pistol;
	Mix_Chunk		*music_ak;
	Mix_Chunk		*music_shotgan;
	SDL_Surface		*image_aim;
	SDL_Rect		img_location;
	int				flag_play_chunk;
	int				flag_guns;
	Uint32			start_guns;
	TTF_Font		*my_font;
	int				score;
	int				key_blue;
	int				key_yellow;
	int				key_red;
}					t_bonus;

typedef struct		s_sdl
{
	SDL_Surface		*icon;
	SDL_Window		*win;
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
	t_background	ammo;
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
	int				count;
}					t_floot_up;

typedef struct		s_helper
{
	int				j;
	int				x;
	float			angle;
	int				prikol;
}					t_helper;

typedef struct		s_wolf
{
	t_parser		*p;
	t_player		*player;
	t_sdl			*sdl;
	SDL_Surface		*surface;
	t_bonus			*bon;
	t_menu			*menu;
	t_helper		helper;
	bool			z_buff[W * H];
}					t_wolf;

typedef struct		s_pthrdata
{
	int				number;
	t_wolf			*wolf;
	t_point			point;
	int				interlaced_rendering;
	int				count_distance;
}					t_pthrdata;

typedef struct		s_data_floor
{
	float	curr_dist;
	float	weight;
	float	curr_floorx;
	float	curr_floory;
	float	cof;
	float	cof_h;
	int		textx;
	int		texty;
	int		color;
	int		temp_y;
	int		y;
	int		tmp;
}					t_data_floor;

typedef	struct		s_data_column
{
	t_distance				*dist;
	t_floot_up				stage;
	t_floot_up				sub_stage;
	signed long long int	temp_y;
	double					fractpart_2;
	double					intpart_2;
	double					fractpart;
	double					intpart;
	float					offsety;
	float					tex_2;
	float					pos_y;
	float					koof;
	float					tex_1;
	float					pos;
	int						begin_y;
	int						len;
	int						flag;
	int						color;
	int						count;
	int						j;
	int						size;
	int						flagg;
}					t_data_column;

/*
** cof.c
*/
float				cof_size_displ(void);
int					fly_correct_fuf(t_wolf *wolf);
int					fly_correction_from_dist(t_wolf	*wolf,
					int	j, int count_distance);
float				correct_cof_h(t_wolf *wolf);
int					diry_correction_from_fly(int fly);
/*
** render_hud.c
*/
void				render_hud(t_wolf *wolf);

/*
** parser.c
*/
void				parser(t_wolf *wolf);
void				parsing_walls(t_parser *parser, char **arr);
SDL_Surface			*parsing_param1(t_parser *parser, char **arr, bool *b);
void				parsing_param2(t_param2 *obj, char **arr, bool *b);
void				init_size(t_parser *parser, char *l);
Mix_Music			*parsing_music(t_parser *parser, char **arr, bool *b);

/*
** check_valid.c
*/
void				check_valid(t_buff *buff);

/*
** sdl.c
*/
void				wolf_loop(t_wolf *wolf);
void				handle_event(t_wolf *wolf, SDL_Event *event);
void				recalc(t_wolf *wolf);
void				handle_phisics(t_wolf *wolf, t_player *p);
void				handle_keys(t_wolf *wolf, SDL_Event *event);
float				search_angle(t_wall w, t_wolf *wolf, int i);
t_wall				rotate_wall(t_wall w, t_wolf *wolf, int i);

/*
** menu.c
*/
void				menu_loop(t_wolf *wolf);
void				hooks(t_sdl *sdl, t_menu *menu);
void				check_pos_button(t_sdl *sdl, t_button *button,
					int k, t_menu *menu);
void				quit(t_sdl *sdl);

/*
** screens.c
*/
void				screen_start(t_wolf *wolf);
void				screen_death(t_wolf *wolf, SDL_Event *event);
void				screen_win(t_wolf *wolf, SDL_Event *event);

/*
** print_menu.c
*/
void				print_menu(t_wolf *wolf);
void				draw_button(t_sdl *sdl, t_button *button);
void				draw_texture(t_sdl *sdl, t_button *button, t_position *pos);

/*
** move.c
*/
void				calc_move(t_wolf *wolf, float dy, float dx);
void				rotate(t_wolf *wolf, SDL_Event *event);
void				add_skybox_offset(t_wolf *wolf, float to_add);
void				jump(t_wolf *wolf);
void				falling(t_wolf *wolf);
void				falling2(t_wolf *wolf, SDL_Event *event);
void				jump2(t_wolf *wolf, SDL_Event *event, int f);
void				take_damage(t_wolf *wolf, int dmg);

/*
** load_textures.c
*/
void				set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
Uint32				get_pixel(SDL_Surface *surface, int x, int y);

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
void				init_player(t_wolf *wolf, t_player *player);
void				init_sdl(t_wolf *wolf);

/*
** init_bonus.c
*/
void				init_bonus(t_wolf *wolf);
void				monster_load(t_wolf *wolf);

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
int					add_arc(float *arc, float to_add);

/*
** render_text.c
*/
void				render_text(t_wolf *wolf, char *text, SDL_Rect location,
					SDL_Color f_b_color);
void				render_score_coin(t_wolf *wolf);
void				render_fps(t_wolf *wolf, t_bonus *bon);
int					get_fps_time(t_bonus *bon);

/*
** distance.c
*/
t_distance			*dist_to_wall(t_wolf *wolf, t_helper *h);
t_distance			*t_distance_new(t_wolf *wolf);
void				t_distance_clear(t_distance *dist);
void				all_get_distance(t_wolf *wolf);
void				free_dist_arr(t_wolf *wolf);

/*
** render_aim.c
*/
void				render_aim(t_wolf *wolf);

/*
** set_sdl.c
*/
SDL_Color			set_color_sdl(int a, int b, int c);
SDL_Rect			set_rect_sdl(int x, int y, int w, int h);

/*
** thread_func.c
*/
void				pseudo_3d(t_wolf *wolf);

/*
** pseudo_3d.c
*/
void				floorcast_up_fly(t_wolf *wolf, t_distance *dist, int x,
					int count_distance, t_floot_up stage, int j);
void				draw_sky(t_wolf *wolf, int x, int y);
void				draw_column(t_wolf *wolf, t_point point,
					t_distance *dist, int count_distance);
void				brute_column_fly_1_1(t_wolf *wolf, t_point point,
					int count_distance, t_data_column *d);
void				upper_level_draw_3(t_wolf *wolf, t_point point,
					int count_distance, t_data_column *d);

/*
** guns_shot.c
*/
void				guns_shot(SDL_Surface *screen, int flag, t_bonus *bon);
void				render_shot(t_wolf *wolf, SDL_Surface *surface);
void				render_shot1(t_wolf *wolf, SDL_Surface *surface);
void				render_shot2(t_wolf *wolf, SDL_Surface *surface);
void				render_shot3(t_wolf *wolf, SDL_Surface *surface);

/*
** floorcast.c
*/
void				floorcast(t_wolf *wolf, t_distance *dist,
					t_point point, int count_distance);
void				floorcast_up(t_wolf *wolf, t_distance *dist,
					int count_distance, t_floot_up stage);
int					floorcast_up_escape(t_wolf *wolf, t_floot_up *stage,
					t_data_floor *d, int j);

/*
** draw_column_fly.c
*/
void				draw_column_fly(t_wolf *wolf, t_point point,
					int count_distance);
void				upper_level_draw(t_wolf *wolf, t_point point,
					int count_distance, t_data_column *d);
void				upper_level_draw_2(t_wolf *wolf, t_point point,
					int count_distance, t_data_column *d);
int					upper_level_draw_1(t_wolf *wolf, t_point point,
					int count_distance, t_data_column *d);
void				cut_ctage(t_wolf *wolf, t_point point,
					int count_distance, t_data_column *d);

/*
** draw_column_fly2.c
*/
void				brute_column_fly(t_wolf *wolf, t_point point,
					int count_distance, t_data_column *d);
void				brute_column_fly_2(t_wolf *wolf, t_point point,
					int count_distance, t_data_column *d);
void				brute_column_fly_2_1(t_wolf *wolf, t_point point,
					int count_distance, t_data_column *d);
void				brute_column_fly_2_2(t_wolf *wolf, t_point point,
					int count_distance, t_data_column *d);
void				brute_column_fly_1(t_wolf *wolf, t_point point,
					int count_distance, t_data_column *d);

/*
** move1.c
*/
void				jump(t_wolf *wolf);
void				falling(t_wolf *wolf);
void				calc_move3(t_wolf *wolf, t_way *way, float dy);
void				calc_move2(t_wolf *wolf, t_way *way, float dx);
void				calc_move(t_wolf *wolf, float dy, float dx);

/*
** move1.c
*/
void				falling2(t_wolf *wolf, SDL_Event *event);
void				take_damage(t_wolf *wolf, int dmg);
void				jump2(t_wolf *wolf, SDL_Event *event, int f);

#endif
