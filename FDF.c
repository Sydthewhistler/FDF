/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FDF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:04:55 by scavalli          #+#    #+#             */
/*   Updated: 2025/04/25 16:56:40 by scavalli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	create_img(t_data *data, t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while(x < map->height)
	{
		int y = 0;
		while(y < map->width)
		{
			put_pixel_iso(data,(y * CONNECTION_DISTANCE) + START_PLACE, x * CONNECTION_DISTANCE, map->coordonates[x][y]); //inversion x/y
			make_connections(data, y, x, map); //inversion x/y
			y++;
		}
		x++;
	}
}

void	ft_fdf(t_map *map)
{
	t_data data;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 1920, 1080, "FDF");
	data.img = mlx_new_image(data.mlx, 1920, 1080);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.line_len, &data.endian);
	
	create_img(&data, map);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_hook(data.win, 17, 0, event_hook, &data);
	mlx_loop(data.mlx);
}