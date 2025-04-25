/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:44:08 by scavalli          #+#    #+#             */
/*   Updated: 2025/04/25 16:59:22 by scavalli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	event_hook(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	//mlx_destroy_display(data->mlx);
	//free(data->mlx);
	mlx_loop_end(data->mlx);
	return (0);
}

int	key_hook(int	key, t_data *data)
{
	if (key == ESCAPE_KEY)
	{
		mlx_destroy_image(data->mlx, data->img);
		mlx_destroy_window(data->mlx, data->win);
		//mlx_destroy_display(data->mlx);
		//free(data->mlx);
		mlx_loop_end(data->mlx);
		return (1);
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
