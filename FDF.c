/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FDF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:04:55 by scavalli          #+#    #+#             */
/*   Updated: 2025/04/27 18:19:12 by scavalli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	create_img(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while(x < data->map->height)
	{
		int y = 0;
		while(y < data->map->width)
		{
			put_pixel_iso(data,(y * data->mvt.connection_distance) + START_PLACE, x * data->mvt.connection_distance, data->map->coordonates[x][y]); //inversion x/y
			make_connections(data, y, x); //inversion x/y
			y++;
		}
		x++;
	}
}
void	new_img(t_data *data)
{
	data->img = mlx_new_image(data->mlx, 1920, 1080);
	data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_len, &data->endian);
	
	create_img(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void	ft_fdf(t_data *data)
{
	data->mvt.height_translation = 0;
	data->mvt.width_translation = 0;
	data->mvt.connection_distance = 30;
	data->mvt.angle_x = 0.0;
    data->mvt.angle_y = 0.0;
    data->mvt.angle_z = 0.0;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, 1920, 1080, "FDF");
	new_img(data); // image de base
	mlx_key_hook(data->win, key_hook, data);
	mlx_hook(data->win, 17, 0, event_hook, data);
	mlx_loop(data->mlx);
}