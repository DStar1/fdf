NAME = mlx

LIBF = libft/

MAIN = main.c

SRC =	$(MAIN)

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	make all -C libft
	#gcc -g -o $(NAME) libft/libft.a $(SRC)
	gcc minilibx/libmlx.a libft/libft.a main.c -framework OpenGL -framework AppKit

cmain:
	gcc -o $(NAME) minilibx/libmlx.a libft/libft.a $(SRC) -framework OpenGL -framework AppKit
	./mlx test_maps/10-2.fdf

clean:
	/bin/rm -f *.o
	make clean -C libft

fclean: clean
	make fclean -C libft
	/bin/rm -f $(NAME)

re: fclean all

