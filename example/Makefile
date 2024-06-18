CC = cc
CFLAGS=-Wall -Wextra -Werror
RM = rm -f

MINILIBX_DIR = minilibx_opengl_20191021
MINILIBX = $(MINILIBX_DIR)/libmlx.a

SRCDIR = src
SRCS = $(SRCDIR)/ft_main.c

INCLUDES = -I$(MINILIBX_DIR)

NAME = sample

all: $(NAME)

$(NAME): $(SRCS) $(MINILIBX)
	$(CC) $(INCLUDES) -framework OpenGL -framework AppKit -o $@ $^

$(MINILIBX):
	make -C $(MINILIBX_DIR)

clean:
	make -C $(MINILIBX_DIR) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(MINILIBX_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
