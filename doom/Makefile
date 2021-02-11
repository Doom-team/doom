# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wendell <wendell@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/15 16:58:46 by clala             #+#    #+#              #
#    Updated: 2021/02/04 21:11:12 by wendell          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ALL_C = main.c \
		error.c \
		sdl.c \
		init.c \
		aux.c \
		load_textures.c \
		distance.c \
		pseudo_3d.c \
		draw.c \
		render_text.c \
		guns_shot.c \
		move.c \
		init_bonus.c \
		set_sdl.c \
		render_aim.c \
		init_menu.c \
		menu.c \
		print_menu.c \
		parser.c \
		screens.c \
		parsing_walls.c \
		init_size.c \
		parsing_param2.c \
		parsing_param1.c \
		render_hud.c \
		check_valid.c \
		parsing_music.c \
		cof.c \
		thread_func.c

SRCDIR = ./src
OBJDIR = ./objs
ALL_OBJ = $(ALL_C:%.c=%.o)
OBJS = $(addprefix $(OBJDIR)/, $(ALL_OBJ))

NAME = wolf3d

INCLUDES = ./includes/wolf3d.h \
			./includes/const.h \
			./includes/colors.h \
			./includes/errors.h

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
COMP_LIB = make -C $(LIBFT_DIR)
CC = gcc
# FLAGS = -Ofast -mprefer-vector-width=512
FLAGS = -fmudflap -g
# FLAGS =
#-Wall -Wextra -Werror

SDL_INCS =	-F./frameworks \
			-I./frameworks/SDL2.framework/Headers \
			-I./frameworks/SDL2_image.framework/Headers \
			-I./frameworks/SDL2_mixer.framework/Headers \
			-I./frameworks/SDL2_ttf.framework/Headers
			 
FRAMEWORKS  = -F./frameworks \
				-rpath ./frameworks \
				-framework SDL2 \
				-framework SDL2_ttf \
				-framework SDL2_image \
				-framework SDL2_mixer


all: $(LIBFT) $(OBJDIR) $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -L $(LIBFT_DIR) -lft -o $@ $(SDL_INCS) $(FRAMEWORKS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INCLUDES) | $(OBJDIR)
	$(CC) $(FLAGS) -I./includes -I.$(LIBFT_DIR)/includes $(SDL_INCS)  -c $< -o $@ 

$(OBJDIR):
	/bin/mkdir -p $(OBJDIR)

$(LIBFT): lib

lib:
	@$(COMP_LIB)

clean:
	@/bin/rm -rf $(OBJDIR)
	@$(COMP_LIB) clean

fclean: clean
	@/bin/rm -rf $(NAME)
	@$(COMP_LIB) fclean

re: fclean all

go:
	$(MAKE) -j
	./wolf3d

rg: fclean go

.PHONY: lib clean fclean all re go rg