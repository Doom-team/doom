NAME = doom
SRCS = main.c valid.c draw.c draw1.c dda.c hooks.c
OBJS = main.o valid.o draw.o draw1.o dda.o hooks.o

INC = -I ./SDL2/include
SDL_LIB = -L ./SDL2/lib/ -lSDL2

IMC = -I ./SDL2/include
IMG_LIB = -L ./SDL2/lib/ -lSDL2_image
# INC = -I ~/.brew/include
# SDL_LIB = -L ~/.brew/lib/ -lSDL2

all: $(NAME)

$(OBJS): %.o: %.c doom.h
	gcc -c -g $(FLAGS) $< -o $@ $(INC)

$(NAME): $(OBJS)
	gcc $(OBJS) $(SDL_LIB) $(INC) $(IMG_LIB) $(IMC) -o $(NAME)

clean:
	/bin/rm -f $(OBJS)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all