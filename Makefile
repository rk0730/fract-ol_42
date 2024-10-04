UNAME_S = $(shell uname -s)

CC = cc
CFLAGS=-Wall -Wextra -Werror
RM = rm -f

# macOS用の設定
ifeq ($(UNAME_S), Darwin)
	MINILIBX_DIR = minilibx_opengl_20191021
endif
# Ubuntu用の設定
ifeq ($(UNAME_S), Linux)
	MINILIBX_DIR = minilibx-linux
endif

MINILIBX = $(MINILIBX_DIR)/libmlx.a

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

FTPRINTF_DIR = ft_printf
FTPRINTF = $(FTPRINTF_DIR)/libftprintf.a

SRCDIR = src
SRCS = $(SRCDIR)/ft_main.c \
	$(SRCDIR)/ft_mandelbrot.c \
	$(SRCDIR)/ft_zoom.c \
	$(SRCDIR)/ft_arg.c \

# SRCS = $(SRCDIR)/gpt.c

OBJDIR = obj
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

INCLUDES = -I$(MINILIBX_DIR) -I$(SRCDIR) -I$(LIBFT_DIR) -I$(FTPRINTF_DIR)

NAME = fractol

all: $(NAME)

$(NAME): $(OBJS) $(MINILIBX) $(LIBFT) $(FTPRINTF)
# macOS用の設定
ifeq ($(UNAME_S), Darwin)
	$(CC) $(INCLUDES) -framework OpenGL -framework AppKit -o $@ $^
endif
# Ubuntu用の設定
ifeq ($(UNAME_S), Linux)
	$(CC) $(INCLUDES) -o $@ $^ -lX11 -lXext
endif

$(MINILIBX):
	make -C $(MINILIBX_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(FTPRINTF):
	make -C $(FTPRINTF_DIR)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	make -C $(MINILIBX_DIR) clean
	make -C $(LIBFT_DIR) clean
	make -C $(FTPRINTF_DIR) clean
	$(RM) -r $(OBJDIR)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	make -C $(FTPRINTF_DIR) fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
