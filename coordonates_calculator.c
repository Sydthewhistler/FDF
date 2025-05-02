/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordonates_calculator.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:37:53 by scavalli          #+#    #+#             */
/*   Updated: 2025/05/02 16:50:36 by scavalli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	make_iso_x(int x, int y, int z, t_data *data)
{
	float	final_x;
	float	final_y;

	final_x = (x * cos(data->mvt.angle_y) * cos(data->mvt.angle_z) + (y
				* cos(data->mvt.angle_x) - z * sin(data->mvt.angle_x))
			* (-sin(data->mvt.angle_z)) + (y * sin(data->mvt.angle_x) + z
				* cos(data->mvt.angle_x)) * sin(data->mvt.angle_y)
			* cos(data->mvt.angle_z));
	final_y = (x * cos(data->mvt.angle_y) * sin(data->mvt.angle_z) + (y
				* cos(data->mvt.angle_x) - z * sin(data->mvt.angle_x))
			* cos(data->mvt.angle_z) + (y * sin(data->mvt.angle_x) + z
				* cos(data->mvt.angle_x)) * sin(data->mvt.angle_y)
			* sin(data->mvt.angle_z));
	return ((int)((final_x - final_y) * cos(ISO_ANGLE)));
}

int	make_iso_y(int x, int y, int z, t_data *data)
{
	float	final_x;
	float	final_y;
	float	final_z;

	final_x = (x * cos(data->mvt.angle_y) * cos(data->mvt.angle_z) + (y
				* cos(data->mvt.angle_x) - z * sin(data->mvt.angle_x))
			* (-sin(data->mvt.angle_z)) + (y * sin(data->mvt.angle_x) + z
				* cos(data->mvt.angle_x)) * sin(data->mvt.angle_y)
			* cos(data->mvt.angle_z));
	final_y = (x * cos(data->mvt.angle_y) * sin(data->mvt.angle_z) + (y
				* cos(data->mvt.angle_x) - z * sin(data->mvt.angle_x))
			* cos(data->mvt.angle_z) + (y * sin(data->mvt.angle_x) + z
				* cos(data->mvt.angle_x)) * sin(data->mvt.angle_y)
			* sin(data->mvt.angle_z));
	final_z = (-x * sin(data->mvt.angle_y) + (y * sin(data->mvt.angle_x) + z
				* cos(data->mvt.angle_x)) * cos(data->mvt.angle_y));
	return ((int)((final_x + final_y) * sin(ISO_ANGLE) - final_z));
}

void	connection_y_calculate(t_data *data, int x, int y)
{
	t_coordonates	coordonates;

	coordonates.x = make_iso_x((x * data->mvt.connection_distance), y
			* data->mvt.connection_distance, data->map->coordonates[y][x], data)
		+ data->mvt.width_translation;
	coordonates.y = make_iso_y((x * data->mvt.connection_distance), y
			* data->mvt.connection_distance, data->map->coordonates[y][x], data)
		+ data->mvt.height_translation;
	if (y != 0)
		draw_line(data, coordonates, make_iso_x((x
					* data->mvt.connection_distance), (y - 1)
				* data->mvt.connection_distance, data->map->coordonates[y
				- 1][x], data) + data->mvt.width_translation, make_iso_y((x
					* data->mvt.connection_distance), (y - 1)
				* data->mvt.connection_distance, data->map->coordonates[y
				- 1][x], data) + data->mvt.height_translation);
}

void	connection_x_calculate(t_data *data, int x, int y)
{
	t_coordonates	coordonates;

	coordonates.x = make_iso_x((x * data->mvt.connection_distance), y
			* data->mvt.connection_distance, data->map->coordonates[y][x], data)
		+ data->mvt.width_translation;
	coordonates.y = make_iso_y((x * data->mvt.connection_distance), y
			* data->mvt.connection_distance, data->map->coordonates[y][x], data)
		+ data->mvt.height_translation;
	if (x != 0)
		draw_line(data, coordonates, make_iso_x(((x - 1)
					* data->mvt.connection_distance), y
				* data->mvt.connection_distance, data->map->coordonates[y][x
				- 1], data) + data->mvt.width_translation, make_iso_y(((x - 1)
					* data->mvt.connection_distance), y
				* data->mvt.connection_distance, data->map->coordonates[y][x
				- 1], data) + data->mvt.height_translation);
}

void	make_connections(t_data *data, int x, int y)
{
	connection_y_calculate(data, x, y);
	connection_x_calculate(data, x, y);
}
