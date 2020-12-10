# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahusk <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/13 19:54:33 by ahusk             #+#    #+#              #
#    Updated: 2020/08/13 19:54:35 by ahusk            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJS = main.c init.c print_menu.c

CC = gcc

SDL_INCS =	-F../doom/frameworks \
			-I../doom/frameworks/SDL2.framework/Headers

FRAMEWORKS  = -F../doom/frameworks \
				-rpath ../doom/frameworks \
				-framework SDL2

OBJ_NAME = menu

all : $(OBJS)
	$(CC) -g $(OBJS) -o $(OBJ_NAME) $(SDL_INCS) $(FRAMEWORKS)
