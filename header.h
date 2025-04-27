/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:01:07 by scavalli          #+#    #+#             */
/*   Updated: 2025/04/27 17:59:17 by scavalli         ###   ########.fr       */
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
#include <math.h>
#define TILE_WIDTH 32
#define TILE_HEIGHT 16
#define MAP_WIDTH 3
#define MAP_HEIGHT 3
#define ISO_ANGLE 0.523599 + 0.1
#define ESCAPE_KEY 65307
#define START_PLACE 600
#define KEY_UP     65362
#define KEY_DOWN   65364
#define KEY_LEFT   65361
#define KEY_RIGHT  65363
#define KEY_Z 122
#define KEY_X 120

typedef struct s_mvt {
	int	height_translation;
	int	width_translation;
	int	connection_distance;
	float	angle_x;
	float	angle_y;
	float	angle_z;
}	t_mvt;

typedef struct s_map {
	int	**coordonates;
	int	height;
	int	width;
	int size;
}	t_map;

typedef struct s_data {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	t_mvt mvt;
	t_map *map;
}	t_data;

typedef struct s_line {
	int steps;
	float x_inc;
	float y_inc;
	float x;
	float y;
}	t_line;

t_map *import_map(char *file);
void	ft_fdf(t_data *data);
void	new_img(t_data *data);

void	ft_free_tab(char **str);
void	ft_free_int(t_map *map);
int		key_hook(int	key, t_data *data);
int		event_hook();

void	put_pixel_iso(t_data *data, int x, int y, int z);
int		make_iso_x(int x, int y);
int		make_iso_y(int x, int y, int z);

void	make_connections(t_data *data, int x, int y);


#endif