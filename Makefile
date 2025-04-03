# linux
# CC = cc
# CFLAGS = -Wall -Wextra -Werror -Imlx -O2

# NAME = fractol
# LIBMLX = minilibx-linux/libmlx.a
# SRC_DIR = .
# OBJ_DIR = obj

# SRC = $(wildcard *.c)
# OBJ = $(SRC:.c=.o)

# $(NAME): $(LIBMLX) $(OBJ)
# 	$(CC) $(CFLAGS) $(OBJ) $(LIBMLX) -lXext -lX11 -lm -lz -o $(NAME)

# $(LIBMLX):
# 	$(MAKE) -C ./minilibx-linux

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# clean:
# 	rm -f $(OBJ)

# fclean: clean
# 	rm -f $(NAME)

# re: fclean all

# all: $(NAME)

# .PHONY: all clean fclean re

# macOS
CC = cc
CFLAGS = -Wall -Wextra -Werror -Imlx -O2

NAME = fractol
LIBMLX = minilibx_opengl/libmlx.a
SRC_DIR = .
OBJ_DIR = obj

SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

$(NAME): $(LIBMLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBMLX) -framework OpenGL -framework AppKit -o $(NAME)

$(LIBMLX):
	$(MAKE) -C ./minilibx_opengl

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

all: $(NAME)

.PHONY: all clean fclean re