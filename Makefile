NAME = fdf

LIBF = libft/

LIB = mlx.a

MAIN = main.c

TEST = fdf1/maps/elem-col.fdf

SRC =	rot.c \
		parse.c \
		scale.c \
		keys.c \
		draw.c \
		$(MAIN)

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	make all -C libft
	gcc $(FALGS) -g -c $(SRC)
	ar rc $(LIB) *.o
	ranlib $(LIB)
	gcc $(FALGS) -g -o $(NAME) $(LIB) minilibx/libmlx.a libft/libft.a -framework OpenGL -framework AppKit

cmain:
	gcc -g -o $(NAME) minilibx/libmlx.a libft/libft.a $(SRC) -framework OpenGL -framework AppKit
	./$(NAME) $(TEST)

clean:
	/bin/rm -f *.o
	make clean -C libft

fclean: clean
	make fclean -C libft
	/bin/rm -f $(NAME)

re: fclean all

