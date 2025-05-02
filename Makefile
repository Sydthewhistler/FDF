# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 22:51:05 by scavalli          #+#    #+#              #
#    Updated: 2025/05/02 16:51:19 by scavalli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILE = main.c FDF.c import_map.c put_pixel.c utils.c event.c coordonates_calculator.c
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
	rm -f $(NAME)\

superclean : fclean
	rm -rf minilibx-linux test_maps libft/libft.a

re : fclean all



