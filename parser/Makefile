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
		parser.c

SRCDIR = ./src
OBJDIR = ./objs
ALL_OBJ = $(ALL_C:%.c=%.o)
OBJS = $(addprefix $(OBJDIR)/, $(ALL_OBJ))

NAME = parser

INCLUDES = ./includes/doom.h

LIBFT_DIR = ../doom/libft
LIBFT = $(LIBFT_DIR)/libft.a
COMP_LIB = make -C $(LIBFT_DIR)
CC = gcc
FLAGS = -Ofast -mprefer-vector-width=512
#-Wall -Wextra -Werror

SDL_INCS =	-F../doom/frameworks \
			-I../doom/frameworks/SDL2.framework/Headers

FRAMEWORKS  = -F../doom/frameworks \
				-rpath ../doom/frameworks \
				-framework SDL2


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
