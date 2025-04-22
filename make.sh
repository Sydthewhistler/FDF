rm exe
cc -Wall -Wextra -Werror -Iminilibx-linux -Lminilibx-linux test.c minilibx-linux/libmlx.a -lmlx -lXext -lX11 -lm -o exe
