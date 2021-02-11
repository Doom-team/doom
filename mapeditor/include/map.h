/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grinko <grinko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 13:38:12 by grinko            #+#    #+#             */
/*   Updated: 2021/02/12 01:04:18 by grinko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "../frameworks/SDL2.framework/Headers/SDL.h"
# include "../frameworks/SDL2_ttf.framework/Headers/SDL_ttf.h"
# include "../frameworks/SDL2_image.framework/Headers/SDL_image.h"

# include "../frameworks/SDL2_mixer.framework/Headers/SDL_mixer.h"
# include "../libft/includes/libft.h"

# include "../../doom/libft/includes/ft_printf.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# define APPLEGREY (t_color){33, 33, 33}
# define GREY (t_color){74, 74, 74}
# define WHITE (t_color){255, 255, 255}
# define RED (t_color){255, 0, 0}
# define GREEN (t_color){0, 255, 0}
# define YELLOW (t_color){255, 255, 0}
# define BLUE (t_color){0, 0, 255}
# define HOTPINK (t_color){255, 105, 180}

# define REDFONT (SDL_Color){255, 0, 0}
# define WHITEFONT (SDL_Color){255, 255, 255}
# define SABF (SDL_Color){244, 164, 96}
# define BLACKFONT (SDL_Color){0, 0, 0}
# define ERM "Malloc Error"

# define WIDTH 1424
# define HEIGHT 1020
# define SCALE 30

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct		s_texinfo
{
	//int vector_len;
	char			*texture_name[2];
	char			*type_name;
	// char			*floor_name;
	// char			*ceiling_name;
}					t_texinfo;

typedef struct		s_nod
{
	short			x1;
	short			y1;
	short			x2;
	short			y2;
	int				wallh;
	int				type;
	int				grnum;
	int				index;
	t_texinfo		*texture;
	struct s_nod	*nxt;
}					t_nod;

typedef struct		s_win
{
	int				xpos;
	int				ypos;
	int				h;
	int				w;
}					t_win;

typedef struct		s_image
{
	SDL_Surface		*img;
	unsigned char	*s;
	unsigned char	pixb;
	int				strb;
	int				active;
}					t_image;

typedef struct		s_info
{
	int				x;
	int				y;
	int				w;
	int				h;
}					t_info;

typedef struct		s_removeinfo
{
	int				*x;
	int				*y;
}					t_removeinfo;

typedef struct		s_object
{
	char			*player;
	char			*items[5];
	char			**guns[3];
	char			**enem[5];
	char			*light;
	char			**sdoors;
	char			**bdoors;
	char			**ydoors;
	char			**rdoors;
	char			*exit;
}					t_object;

typedef struct		s_cursor
{
	t_image			*curosr_img;// структура изобр курсора
}					t_cursor;

typedef struct		s_tempnod
{
	int				x1;
	int				y1;
	int				x2;
	int				y2;
	int				dx;
	int				dy;
	int				er;
	int				de;
	int				i;
	int				j;
	int				diry;
	int				di;
}					t_tempnod;

typedef struct		s_objdots
{
	int				x[1000];
	int				y[1000];
}					t_objdots;

typedef struct		s_map
{
	SDL_Window		*win;
	t_image			*inter_tex[22]; // 0 - window, 1-5 - inblock & (block, texture, object), 6-8 - tools 9-11 widget panel & widgets
	t_image			*block_tex[9]; // структура текстур раздела блоки
	t_image			*wall_tex[20];
	t_image			*floorsky_tex[13];
	t_image			*liquid_tex[4];
	t_image			*enemy_tex[5];
	t_image			*player_tex[3];
	t_image			*gun_tex[6];
	t_image			*door_tex[11];
	t_image			*curosr_img[7];// структура изобр курсора 7 элементов
	t_image			*font; // шрифт
	SDL_Cursor		*cursor;// крусор
	Mix_Music		*music[4];
	TTF_Font		*fontclasic;
	TTF_Font		*fontdoom;
	t_nod			*nod; // все узлы на карте
	t_removeinfo	*remove; // tmp труктура для функции удаления готовых блоков
	t_object		*obj;
	t_tempnod		*tem;
	t_objdots		dots;
	int				wclick; // коэф + - виджета размера
	int				whclick; // коэф + - виджета высоты
	int				stclick; // коэф + - виджета высоты ступенек
	id_t			sclick; // хз че за тема
	int				z_x; // половина окна по x
	int				z_y; // половина окна по y
	int				click; // клик первый раз
	int				tmpclick; // клик для фигур
	int				x_c; // x первого клика
	int				y_c; // y первого клика
	int				showactive; // флаг активности панели 1- walls 2 flor & sky 3 - liquids
	int				musicflag;
	int				errorflag;
	int				change_x;
	int				change_y;
	id_t			index_tex;
	int				validflag;
	int				index_wall;

	int				floor_x; /// мб не нужно
	int				floor_y; /// мб не нужно
	int				tmpfloor_x; /// мб не нужно
	int				tmpfloor_y;/// мб не нужно
	char			*floorstr;
	char			*ceilingstr;
	char			*objects;
	char			*temporary;/// мб не нужно

	char 			*stairstr;
	char			*stairsoutput;
	int				stirsgroup;
	int				musicoutput;
	int				objnum;
	int				plus_objects;
	// int			floor_active;
}					t_map;

int					init_all(t_map *map);
void				init_all2(t_map *map);
void				init_interface(t_map *map);
void				init_texture(SDL_Surface *tex, unsigned char **s,
						unsigned char *pixb, int *strb);

void				get_inter_textures(t_map *map);
void				get_block_textures(t_map *map);
void				get_liquid_textures(t_map *map);
void				get_wall_textures(t_map *map);
void				get_floorsky_textures(t_map *map);
void				get_cursor(t_map *map);
void				get_wall_cord(t_map *map, int x, int y);
void				get_floor_cord(t_map *map, int x, int y);
void				get_floor_cordi(t_map *map, int x, int y);
void				get_enemy_textures(t_map *map);
void				get_player_textures(t_map *map);
void				get_gun_textures(t_map *map);
void				get_door_textures(t_map *map);
void				get_door(t_map *map, int x, int y);

void				malloc_block_texture(t_map *map);
void				malloc_interface(t_map *map);
void				malloc_floorsky_texture(t_map *map);
void				malloc_wall_texture(t_map *map);
void				malloc_liquid_texture(t_map *map);
void				malloc_wall_texture(t_map *map);
void				malloc_cursor(t_map *map);
void				malloc_enemy_texture(t_map *map);
void				malloc_player_texture(t_map *map);
void				malloc_gun_texture(t_map *map);
void				malloc_door_texture(t_map *map);

void				draw(t_map *map);
void				draw_color(t_map *map, int pixel, t_color color);
void				draw_pixel(t_map *map, int x, int y, t_color color);
void				draw_point(t_map *map, int x, int y, t_color color);
void				draw_grid(t_map *map);
void				draw_img(t_map *map, t_info *info, t_image *st);
void				draw_nodes(t_map *map);
void				draw_node(t_map *map, t_nod *n);
void				draw_gr(t_map *map, int x, int y, t_color color);
void				draw_line(t_map *map, t_info *info, t_color color);
void				draw_slider(t_map *map);
void				draw_block_textures(t_map *map);
void				draw_wall_textures(t_map *map);
void				draw_floor_textures(t_map *map);
void				draw_liquid_textures(t_map *map);
void				draw_sky_textures(t_map *map);
void				draw_hlider(t_map *map);
void				draw_stairs(t_map *map);
void				draw_tests(t_map *map);
void				draw_music(t_map *map);
void				draw_showuppanel(t_map *map, int x, int y, int inx);
void				draw_small_panel_tex(t_map *map);
int					draw_changer_texture(t_map *map);
void				draw_floor_line(t_map *map, t_info *cor);
void				draw_mapstairs(t_map *map, int x, int y, int i);
void				draw_player(t_map *map);
void				draw_guns(t_map *map);
void				draw_enemy(t_map *map);
void				draw_door_win(t_map *map);
void				draw_door_winp1(t_map *map);
void				draw_door_winp2(t_map *map);
void				draw_door_winp3(t_map *map);
void				draw_door_light_exit(t_map *map);
void				tmp_draw2(t_map *map, int w, int i, t_nod *nod); //
void				tmp_draw(t_map *map, int index, t_nod *nod); //
void				draw_standartpanel(t_map *map);
void				draw_music(t_map *map);
void				draw_basic_interface(t_map *map);

void				one_n(t_map *map, t_color color);
void				two_n(t_map *map, t_color color);
void				zerotem(t_map *map);
void				add_node(t_map *mp, int x, int y);
void				wichonemusic(t_map *map);

void				bigdot(t_map *map, int x, int y, t_color color);
t_nod				*n_cr(t_info *info, int type);

int					sq(int x1, int y1, int x2, int y2);
int					nod_len(t_nod *nod);
void				whichone_tool(t_map *map);

int					events(t_map *map);
int					mmove(int x, int y, t_map *map, SDL_Event event);
int					ukey(int key, t_map *map);
int					pkey(int key, t_map *map);
int					mkey(int key, int x, int y, t_map *map);

void				edit_tool(t_map *map, int index);
void				edit_blocktexture(t_map *map, int index);
void				edit_walltexture(t_map *map, int index);
void				edit_liquidtexture(t_map *map, int index);
void				edit_floortexture(t_map *map, int index);

void				wall_editor(t_map *map, int x, int y);
void				remove_tool(t_map *map, int x, int y);

void				remove_blocks(t_map *map);
void				showup_lick(t_map *map, int x, int y);
int					clickevent(t_map *map, int x, int y, SDL_Event event);
int					interface_click(t_map *map, int x, int y);
void				section_click(t_map *map, int x, int y);
int					catch_click(t_map *map, int x, int y);
void				catch_click2(t_map *map, int x, int y);
void				catch_click3(t_map *map, int x, int y);
int					widget_click(t_map *map, int x, int y);
void				tools_click(t_map *map, int x, int y);
void				blockterxture_click(t_map *map, int x, int y);
void				blockterxture_click2(t_map *map, int x, int y);
void				walltx_click(t_map *map, int x, int y);
void				walltx_click2(t_map *map, int x, int y);
void				floortx_click(t_map *map, int x, int y);
void				skytx_click(t_map *map, int x, int y);
void				hwidget_click(t_map *map, int x, int y);
void				terxtures_click(t_map *map, int x, int y);
void				objects_click(t_map *map, int x, int y);
void				objects_click2(t_map *map, int x, int y);
void				change_texture_click(t_map *map, int x, int y);
void				change_floor_click(t_map *map, int x, int y);
void				zerroother(t_map *map);
void				zerroothero(t_map *map);
void				rewrite(t_map *map, int inx, int x, int y);
void				rewrite2(t_map *map, char *str, char *tmp, int inx);
void				floorker(t_map *map, int x, int y);
int					searchelem(char *str1, char *str2);
void				set_door(t_map *map, int indx);


void				add_my_node(t_map *map, t_info *info, int type);
void				made_blocks(t_map *map, int x, int y);

void				square(t_map *map, int x, int y);
void				pentagon(t_map *map, int x, int y);
void				hexagon(t_map *map, int x, int y);
void				octagon(t_map *map, int x, int y);
void				wtf(t_map *map);

void				cursor(t_map *map, int index, int hot_x, int hot_y);
void				fonts(t_map *map, char *str, int x, int y);
void				fonts_classic(t_map *map, char *str, t_info *info,
						SDL_Color color);
void				fonts_doom(t_map *map, char *str, t_info *info,
						SDL_Color color);
int					struppercase(char *str);


void				showtexture(t_map *map);
void				showfloorsky(t_map *map);
void				showupcontent(t_map *map);

int					some_texture_active(t_map *map);
void				texture_block(t_map *map);

void				changer(t_map *map, int x, int y);
void				change_texture(t_map *map, int x, int y);
void				change_text_inter(t_map *map);
void				change_text_inter2(t_map *map);
int					change_floor_inter(t_map *map);

void				save_texture(t_map *map, int index, int num);
void				save_obj_tmp1(t_map *map, int x, int y);
void				save_obj_tmp2(t_map *map, int x, int y);
void				save_obj_tmp3(t_map *map, int x, int y);
void				save_objects(t_map *map, t_info *inf, char *textstr);


void				open_texture_win(t_map *map);
void				open_floor_win(t_map *map);

int					find_nod(t_map *map, int x, int y);
int					find_texture_name(char *str);
void				findfloornod(t_map *map);
void				findceilingnod(t_map *map);
void				find_coord(t_map *mp, int *x, int *y);
void				find_help(t_nod *nod, t_info *inf, int *x, int *y);

void				find_remove(t_map *map, int x, int y);

void				flooor(t_map *map);

void				writedown_floor(t_map *map);
int					writedown_map(t_map *map);
void				write_music(t_map *map, int fd);

void				objectsblock(t_map *map);
void				dot_forobject(t_map *map, int x, int y);

void				edit_object(t_map *map, t_image **name, int n, int index);
void				stairs_editor(t_map *map, int x, int y);
void				stairswhile(t_map *map, int x, int y);

int					xyround(t_map *map, int x, int y);
void				doorshit(t_map *map);
void				doorshit2(t_map *map);


int					check_scene(t_info *info, t_map *map);
int					valid_map(t_map *map);

int					range_click(t_info *info, int w, int h);
int					lstdelone(t_nod **fd_lst, t_nod *fd);

char				*count_floor(t_map *map, int fd);
void	free_panel1(t_map *map);
void	free_panel2(t_map *map);

void	free_nodes(t_map *map);

void		error_free_s(t_map *map, char *s);
void		error(char *s);
SDL_Surface		*load_image(char *path);
char	*add_text(char *s1, char *s2, int f);

#endif
