NAME = map
SRCS = main.c nodes.c draw.c
OBJS = main.o nodes.o draw.o

SDL_LIB = -L ../SDL2/lib -lSDL2
IMG_LIB = -L ../SDL2/lib -lSDL2_image

all: $(NAME)

$(OBJS): %.o: %.c map.h
	gcc -c -g $(FLAGS) $< -o $@

$(NAME): $(OBJS)
	gcc $(OBJS) $(SDL_LIB) $(IMG_LIB) -o $(NAME)

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all