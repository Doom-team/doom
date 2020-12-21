ALL_C =	main.c draw.c draw2.c hooks.c interface_init.c nodes.c event.c key.c tools.c cursor.c blocks.c font.c \
		textureblock.c malloc_texture.c get_texture.c draw3.c validation.c writemap.c showtexture.c floor_text.c \
		draw4.c wall_text.c ceiling_text.c

SRCDIR = ./src
OBJDIR = ./objs
ALL_OBJ = $(ALL_C:%.c=%.o)
OBJS = $(addprefix $(OBJDIR)/, $(ALL_OBJ))

NAME = map

INCLUDES = ./include/map.h


LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a
COMP_LIB = make -C $(LIBFT_DIR)
CC = gcc
FLAGS = 
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
	$(CC) $(FLAGS) -I./includes -I.$(LIBFT_DIR)/ $(SDL_INCS)  -c $< -o $@ 

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
