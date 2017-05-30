NAME = fractal

SRCS = ./src/main.c \
		./src/fractals.c \
		./src/tools.c \
		./src/keys.c \
		./src/hooks.c \
		./src/init.c \
		./src/zoom.c \

HEADER = ./includes/fractal.h

FLAGS = -Wall -Wextra -Werror -I./fractal.h

OBJ = $(SRCS:.c=.o)

$(NAME): $(OBJ)
	@gcc -o $(NAME) $(FLAGS) $(SRCS) -lmlx -framework OpenGL -framework AppKit
	@echo "Fractol compilation done"

all: $(NAME)

clean:
		@rm -f $(OBJ)
		@rm -f ./includes/fractal.h.gch

fclean: clean
		@rm -f $(NAME)

re: fclean all