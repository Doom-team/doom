NAME = map

INC = -I ../SDL2/include
SDL_LIB = -L ../SDL2/lib -lSDL2

IMC = -I ../SDL2/include
IMG_LIB = -L ../SDL2/lib -lSDL2_image

CC = gcc

MLX = -lmlx -framework OpenGL -framework AppKit

COMP = $(CC) $(CFLAGS) $(INCLUDES)

LIBFT_DIR = libft/
LIBFT_H = -I $(LIBFT_DIR)
LIBFT_A = libft.a
LIBFT = $(LIBFT_DIR)$(LIBFT_A)

HEAD_DIR = include/
MAP_H = -I $(HEAD_DIR)
HEAD = $(HEAD_DIR)map.h

INCLUDES = $(LIBFT_H) $(RTV1_H)

SRC_DIR = src/
SRC_FILES =		main.c interface.c draw.c hooks.c interface_init.c

OBJ_DIR = obj/
OBJ_FILE =	$(SRC_FILES:.c=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILE))

.PHONY: all clean fclean re

all: lib $(NAME)

lib:
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ) $(HEAD)
	@$(COMP) $(LIBFT) $(SDL_LIB) $(INC) $(IMG_LIB) $(IMC) $(OBJ) -o $(NAME)
	@echo "\033[32m \tcompiled \t map \t\t finish \033[0m"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "\033[36m \tmkdir \t\t objects \t finish \033[0m"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEAD)
	@$(COMP) -c $< -o $@

clean:
	@$(MAKE) -sC $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "\033[35m \tclean \t\t\t\t finish \033[0m"

fclean: clean
	@rm -f $(LIBFT)
	@rm -f $(NAME)
	@echo "\033[35m \tfclean \t\t\t\t finish \033[0m"

re: fclean all
	@echo "\033[35m \tfclean \t\t all \t\t finish \033[0m"