/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:01:07 by scavalli          #+#    #+#             */
/*   Updated: 2025/05/02 16:49:56 by scavalli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# define TILE_WIDTH 32
# define TILE_HEIGHT 16
# define MAP_WIDTH 3
# define MAP_HEIGHT 3
# define ISO_ANGLE 0.623599
# define ESCAPE_KEY 65307
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_Z 122
# define KEY_X 120
# define KEY_A 97
# define KEY_Q 113
# define KEY_S 115
# define KEY_W 119
# define KEY_D 100
# define KEY_E 101

typedef struct s_mvt
{
	int		height_translation;
	int		width_translation;
	int		connection_distance;
	float	angle_x;
	float	angle_y;
	float	angle_z;
}			t_mvt;

typedef struct s_map
{
	int		**coordonates;
	int		height;
	int		width;
	int		size;
}			t_map;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	t_mvt	mvt;
	t_map	*map;
}			t_data;

typedef struct s_line
{
	int		steps;
	float	x_inc;
	float	y_inc;
	float	x;
	float	y;
}			t_line;

typedef struct s_coordonates
{
	int		x;
	int		y;
}			t_coordonates;

t_map		*import_map(char *file);
void		ft_fdf(t_data *data);
void		new_img(t_data *data);

void		ft_free_tab(char **str);
void		ft_free_int(t_map *map);
int			key_hook(int key, t_data *data);
int			event_hook(t_data *data);

void		put_pixel_iso(t_data *data, int x, int y, int z);

int			make_iso_x(int x, int y, int z, t_data *data);
int			make_iso_y(int x, int y, int z, t_data *data);
void		make_connections(t_data *data, int x, int y);
void		draw_line(t_data *data, t_coordonates coordonates, int x1, int y1);

#endif