CC = cc
CFLAGS = -I. 

NAME = fract-ol.a
LIBMLX = minilibx-linux/libmlx.a
SRC_DIR = .
OBJ_DIR = obj

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

$(NAME): $(LIBMLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBMLX) -lXext -lX11 -lm -lz

$(LIBMLX):
	$(MAKE) -C ./minilibx-linux

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

all: $(NAME)

.PHONY: all clean fclean re

so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRC)
	gcc -nostartfiles -shared -o libft.so $(OBJ)