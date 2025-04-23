/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:01:07 by scavalli          #+#    #+#             */
/*   Updated: 2025/04/23 15:50:36 by scavalli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
#include "minilibx-linux/mlx.h"
#include "libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#define TILE_WIDTH 32
#define TILE_HEIGHT 16
#define MAP_WIDTH 3
#define MAP_HEIGHT 3

typedef struct s_data {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_data;

typedef struct s_map {
	int	**coordonates;
	int	height;
	int	width;
	int size;
}	t_map;

t_map *import_map(char *file);

void	ft_free_tab(char **str);
void	ft_free_int(t_map *map);


#endif