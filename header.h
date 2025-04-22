/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:01:07 by scavalli          #+#    #+#             */
/*   Updated: 2025/04/22 13:02:16 by scavalli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <unistd.h>
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



#endif