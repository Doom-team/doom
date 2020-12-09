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

NAME=libft.a

SRC=arrays/ft_create2dchararr.c \
bint/ft_bintaddtn.c \
bint/ft_bintcmp.c \
bint/ft_bintdivsn.c \
bint/ft_bintfmt.c \
bint/ft_bintmltpl.c \
bint/ft_bintprepr.c \
bint/ft_bintround.c \
bint/ft_bintsubtrn.c \
conversion/ft_atoi.c \
conversion/ft_atoi_base.c \
conversion/ft_ctoi.c \
conversion/ft_dtoa.c \
conversion/ft_itoa.c \
conversion/ft_itoa_base.c \
conversion/ft_itoc.c \
conversion/ft_ldtoa.c \
conversion/ft_ltoa_base.c \
conversion/ft_uitoa_base.c \
conversion/ft_ultoa_base.c \
conversion/ft_utoa_base.c \
conversion/ft_uiptrtoa_base.c \
ctype/ft_isalnum.c \
ctype/ft_isalpha.c \
ctype/ft_isascii.c \
ctype/ft_isdigit.c \
ctype/ft_isprint.c \
ctype/ft_isinteger.c \
files/get_next_line.c \
list/ft_lstadd.c \
list/ft_lstadd.o \
list/ft_lstdel.c \
list/ft_lstdelone.c \
list/ft_lstiter.c \
list/ft_lstmap.c \
list/ft_lstnew.c \
math/ft_abs.c \
math/ft_ilen.c \
math/ft_imaxtmaxlen.c \
math/ft_pow.c \
math/ft_uimaxtmaxlen.c \
math/ft_imaxval.c \
math/ft_imaxlen.c \
math/ft_uimaxlen.c \
memory/ft_free2dchararr.c \
memory/ft_bzero.c \
memory/ft_free.c \
memory/ft_memalloc.c \
memory/ft_memccpy.c \
memory/ft_memchr.c \
memory/ft_memcmp.c \
memory/ft_memcpy.c \
memory/ft_memdel.c \
memory/ft_memmove.c \
memory/ft_memset.c \
memory/free2dchararr_terminated.c \
print/ft_putchar.c \
print/ft_putchar_fd.c \
print/ft_putendl.c \
print/ft_putendl_fd.c \
print/ft_putnbr.c \
print/ft_putnbr_fd.c \
print/ft_putstr.c \
print/ft_putstr_fd.c \
print/ft_putwchar.c \
print/ft_putwchar_fd.c \
string/ft_strjoinfree.c \
string/ft_strndup.c \
string/ft_strnlstrip.c \
string/ft_strtrimend.c \
string/ft_strtrimstart.c \
string/ft_strcat.c \
string/ft_strchr.c \
string/ft_strclr.c \
string/ft_strcmp.c \
string/ft_strcpy.c \
string/ft_strdel.c \
string/ft_strdup.c \
string/ft_strequ.c \
string/ft_striter.c \
string/ft_striteri.c \
string/ft_strjoin.c \
string/ft_strlcat.c \
string/ft_strlen.c \
string/ft_strlwr.c \
string/ft_strmap.c \
string/ft_strmapi.c \
string/ft_strncat.c \
string/ft_strncmp.c \
string/ft_strncpy.c \
string/ft_strnequ.c \
string/ft_strnew.c \
string/ft_strnewchr.c \
string/ft_strnlen.c \
string/ft_strnstr.c \
string/ft_strrchr.c \
string/ft_strrev.c \
string/ft_strsplit.c \
string/ft_strstr.c \
string/ft_strsub.c \
string/ft_strswap.c \
string/ft_strtrim.c \
string/ft_strupr.c \
string/ft_tolower.c \
string/ft_toupper.c \
string/ft_strchrset.c \
string/ft_strchrvar.c \
dlist/dlist.c \
dlist/dlist_node.c \
ft_printf/ft_printf.c \
ft_printf/ft_printf_cspr.c \
ft_printf/ft_printf_diouxxb_printer.c \
ft_printf/ft_printf_f.c \
ft_printf/ft_printf_diouxxb.c \
ft_printf/ft_printf_handle_format.c \
ft_printf/ft_printf_select_spec.c \
ft_printf/ft_printf_r.c \
ft_printf/t_buf.c \
ft_printf/ft_vprintf.c \

HEAD=includes/libft.h \
	includes/get_next_line.h

OBJ=$(SRC:.c=.o)
INCLUDES=-I./includes

CC=gcc -g -Wall -Wextra -Werror #-ffast-math -O3
A = $(find . -type f | wc -l)
X = 1
all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)  
	@echo =================================
	@echo $(NAME) HAS BEEN MADE          
	@echo =================================	

%.o:%.c $(HEAD)
	@$(CC) $(INCLUDES) -c $< -o $@
	@echo $<
		
clean:
	/bin/rm -f $(OBJ)
fclean: clean
	/bin/rm -f $(NAME)
re: fclean all
