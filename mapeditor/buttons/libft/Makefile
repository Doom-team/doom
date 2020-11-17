# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gordey <gordey@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/07 17:20:11 by grinko            #+#    #+#              #
#    Updated: 2020/11/04 14:19:14 by gordey           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c \
ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c \
ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_memalloc.c ft_memdel.c ft_strnew.c ft_strdel.c \
ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c \
ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c\
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c \
ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_selectionsort.c ft_lst_push_front.c ft_lst_push_back.c \
ft_binarysearch.c ft_bukovkiciferki.c ft_check_borders.c ft_arrlen.c ft_to_digit.c ft_izero.c \
ft_safe_free_arr.c ft_free_arr.c get_next_line.c

FT_O = $(SRC:.c=.o)

INC = libft.h

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(SRC) $(FT_O) $(INC)
	@ar rc $(NAME) $(FT_O)
	@ranlib $(NAME)
	@echo "\033[34m\tmake \t\t libft \t\t finish\033[0m"

$(FT_O): %.o: %.c
	@gcc -c -Wall -Wextra -Werror $< -I $(INC)

clean:
	@rm -rf $(FT_O)

fclean: clean
	@rm -rf $(NAME)

re: @fclean all
