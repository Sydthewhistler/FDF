/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:18:43 by scavalli          #+#    #+#             */
/*   Updated: 2025/04/27 18:07:24 by scavalli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	make_iso_x(int x, int y)
{
	return ((int)((x-y) * cos(ISO_ANGLE)));
}
int	make_iso_y(int x, int y, int z)
{
	return ((int)((x + y) * sin(ISO_ANGLE) - z));
}

void	put_pixel_iso(t_data *data, int x, int y, int z)
{
	int i;
	int iso_x;
	int	iso_y;
	int color;

	color = 0x00FFFFFF;
	iso_x = make_iso_x(x, y) + data->mvt.width_translation;
	iso_y = make_iso_y(x, y, z) + data->mvt.height_translation;
	if (iso_x < 0 || iso_x >= 1920 || iso_y < 0 || iso_y >= 1080)
		return;
	i = (iso_y * data->line_len) + (iso_x * (data->bpp / 8));
	data->addr[i + 0] = color & 0xFF;
	data->addr[i + 1] = (color >> 8) & 0xFF;
	data->addr[i + 2] = (color >> 16) & 0xFF;
}
void	put_pixel(t_data *data, int x, int y)
{
	int i;
	int color;

	color = 0x00FFFFFF;
	if (x < 0 || x >= 1920 || y < 0 || y >= 1080)
		return;
	i = (y * data->line_len) + (x * (data->bpp / 8));
	data->addr[i + 0] = color & 0xFF;
	data->addr[i + 1] = (color >> 8) & 0xFF;
	data->addr[i + 2] = (color >> 16) & 0xFF;
}

void draw_line(t_data *data, int x0, int y0, int x1, int y1)
{
	t_line line;
	int i;

	if(abs(x1 - x0) > abs(y1 - y0))
		line.steps = abs(x1 - x0);
	else
		line.steps = abs(y1 - y0);
	if(line.steps == 0)
		return ;
	line.x_inc = (float)(x1 - x0) / line.steps;
	line.y_inc = (float)(y1 - y0) / line.steps;
	line.x = x0;
	line.y = y0;
	i = 0;
	while(i <= line.steps)
	{
		put_pixel(data, (int)line.x, (int)line.y);
		line.x += line.x_inc;
		line.y += line.y_inc;
		i++;
	}
}


void	make_connections(t_data *data, int x, int y)
{
	if(y != 0)
		draw_line(data, make_iso_x((x * data->mvt.connection_distance) + START_PLACE, y * data->mvt.connection_distance) + data->mvt.width_translation, make_iso_y((x * data->mvt.connection_distance) + START_PLACE, y * data->mvt.connection_distance,
			 data->map->coordonates[y][x]) + data->mvt.height_translation, make_iso_x((x * data->mvt.connection_distance) + START_PLACE, (y - 1) * data->mvt.connection_distance) + data->mvt.width_translation, 
			 	make_iso_y((x * data->mvt.connection_distance) + START_PLACE, (y - 1) * data->mvt.connection_distance, data->map->coordonates[y - 1][x]) + data->mvt.height_translation); // liaison celui de haut
	if(x != 0)
	draw_line(data, make_iso_x((x * data->mvt.connection_distance) + START_PLACE, y * data->mvt.connection_distance) + data->mvt.width_translation, make_iso_y((x * data->mvt.connection_distance) + START_PLACE, y * data->mvt.connection_distance,
		data->map->coordonates[y][x]) + data->mvt.height_translation, make_iso_x(((x - 1) * data->mvt.connection_distance) + START_PLACE, y * data->mvt.connection_distance) + data->mvt.width_translation, 
			make_iso_y(((x - 1) * data->mvt.connection_distance) + START_PLACE, y * data->mvt.connection_distance, data->map->coordonates[y][x - 1]) + data->mvt.height_translation); //liaison celui gauche
	
}