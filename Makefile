# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 22:51:05 by scavalli          #+#    #+#              #
#    Updated: 2025/04/25 17:50:10 by scavalli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILE = main.c FDF.c import_map.c put_pixel.c utils.c
LIBRARIES = libft/libft.a minilibx-linux/libmlx.a
NAME=fdf
CC=clang
CFLAGS=-Wall -Wextra -Werror
ADDITIONAL_FLAGS = -lXext -lX11 -lm -lz -g3
SRCS = $(FILE)
OBJS = ${SRCS:.c=.o}

.PHONY: all clean fclean re

all : $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(ADDITIONAL_FLAGS) $(OBJS) $(LIBRARIES) -o $(NAME)

start : download
	@cd libft && make && make clean

download :
	@wget https://cdn.intra.42.fr/document/document/26936/minilibx-linux.tgz
	@tar -xvf minilibx-linux.tgz && rm -rf minilibx-linux.tgz
	@cd minilibx-linux && make
	@wget https://cdn.intra.42.fr/document/document/26933/maps.zip
	@unzip maps.zip && rm -rf maps.zip __MACOSX


clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all



