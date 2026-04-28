NAME    = fdf
CC      = clang
CFLAGS  = -Wall -Wextra -Werror
LDFLAGS = -lXext -lX11 -lm -lz

SRCS    = main.c FDF.c import_map.c put_pixel.c coordonates_calculator.c event.c utils.c
OBJS    = $(SRCS:.c=.o)
LIBS    = libft/libft.a minilibx-linux/libmlx.a

.PHONY: all clean fclean re start superclean debug

all: $(NAME)

$(NAME): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(LDFLAGS) -o $(NAME)

%.o: %.c header.h
	$(CC) $(CFLAGS) -c $< -o $@

start:
	cd libft && make && make clean
	cd minilibx-linux && make
	rm -rf __MACOSX

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	cd libft && make fclean
	cd minilibx-linux && make clean

re: fclean all
