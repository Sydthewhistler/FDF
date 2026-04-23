NAME    = fdf
CC      = clang
CFLAGS  = -Wall -Wextra -Werror
LDFLAGS = -lXext -lX11 -lm -lz

SRCS    = main.c FDF.c import_map.c put_pixel.c coordonates_calculator.c event.c utils.c
OBJS    = $(SRCS:.c=.o)
LIBS    = libft/libft.a minilibx-linux/libmlx.a

.PHONY: all clean fclean re start download superclean debug

all: $(NAME)

$(NAME): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(LDFLAGS) -o $(NAME)

%.o: %.c header.h
	$(CC) $(CFLAGS) -c $< -o $@

# Build with debug symbols and AddressSanitizer
debug: CFLAGS  += -g3 -fsanitize=address
debug: LDFLAGS += -fsanitize=address
debug: re

# Download and build dependencies (MinilibX + sample maps)
start: download
	cd libft && make && make clean

download:
	wget https://cdn.intra.42.fr/document/document/26936/minilibx-linux.tgz
	tar -xf minilibx-linux.tgz && rm -f minilibx-linux.tgz
	cd minilibx-linux && make
	wget https://cdn.intra.42.fr/document/document/26933/maps.zip
	unzip maps.zip && rm -f maps.zip
	rm -rf __MACOSX

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

# Remove all generated files including libraries and downloaded assets
superclean: fclean
	rm -rf minilibx-linux maps libft/libft.a

re: fclean all
