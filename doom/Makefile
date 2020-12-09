# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clala <clala@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/15 16:58:46 by clala             #+#    #+#              #
#    Updated: 2020/02/15 21:53:21 by clala            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ALL_C = main.c \
		map.c \
		error.c \
		sdl.c \
		init.c \
		debug_print.c \
		aux.c \
		load_textures.c \
		distance.c \
		pseudo_3d.c \
		draw.c \
		music.c \
		render_text.c \
		guns_shot.c \
		distance_horiz.c \
		distance_vert.c \
		move.c \
		init_bonus.c \
		set_sdl.c \
		render_aim.c \
		render_monster.c \
		init_monster.c

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
FLAGS = -g -Ofast -mprefer-vector-width=512
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

.PHONY: lib clean fclean all re
