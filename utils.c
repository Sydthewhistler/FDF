/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 4025/04/23 15:44:08 by scavalli          #+#    #+#             */
/*   Updated: 2025/04/27 18:35:37 by scavalli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	event_hook(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_loop_end(data->mlx);
	return (0);
}

int	key_hook(int	key, t_data *data)
{
	if (key == ESCAPE_KEY)
	{
		mlx_destroy_image(data->mlx, data->img);
		mlx_destroy_window(data->mlx, data->win);
		mlx_loop_end(data->mlx);
		return (1);
	}
	if(key == KEY_DOWN || key == KEY_UP || key == KEY_LEFT || key == KEY_RIGHT || key == KEY_X || key == KEY_Z || key == KEY_A || key == KEY_Q|| key == KEY_S || key == KEY_W || key == KEY_D || key == KEY_E)
	{
		if(key == KEY_DOWN)
			data->mvt.height_translation += 40;
		if(key == KEY_UP)
			data->mvt.height_translation -= 40;
		if(key == KEY_LEFT)
			data->mvt.width_translation -= 40;
		if(key == KEY_RIGHT)
			data->mvt.width_translation += 40;
		if(key == KEY_Z)
			data->mvt.connection_distance += 5;
		if(key == KEY_X)
			data->mvt.connection_distance -= 5;
		if (key == KEY_A)
			data->mvt.angle_x += 0.1;
		if (key == KEY_Q)
			data->mvt.angle_x -= 0.1;
		if (key == KEY_S)
			data->mvt.angle_y += 0.1;
		if (key == KEY_W)
			data->mvt.angle_y -= 0.1;
		if (key == KEY_D)
			data->mvt.angle_z += 0.1;
		if (key == KEY_E)
			data->mvt.angle_z -= 0.1;
		
		mlx_destroy_image(data->mlx, data->img);
		new_img(data);
	}
	
	return 0;
}

void	ft_free_tab(char **str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
void	ft_free_int(t_map *map)
{
	int	i;

	i = 0;
	while(i < map->height)
	{
		free(map->coordonates[i]);
		i++;
	}
	free(map->coordonates);
}
