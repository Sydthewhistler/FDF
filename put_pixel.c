/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:18:43 by scavalli          #+#    #+#             */
/*   Updated: 2025/05/02 16:49:07 by scavalli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	put_pixel_iso(t_data *data, int x, int y, int z)
{
	int	i;
	int	iso_x;
	int	iso_y;
	int	color;

	color = 0x00FFFFFF;
	iso_x = make_iso_x(x, y, z, data) + data->mvt.width_translation;
	iso_y = make_iso_y(x, y, z, data) + data->mvt.height_translation;
	if (iso_x < 0 || iso_x >= 1920 || iso_y < 0 || iso_y >= 1080)
		return ;
	i = (iso_y * data->line_len) + (iso_x * (data->bpp / 8));
	data->addr[i + 0] = color & 0xFF;
	data->addr[i + 1] = (color >> 8) & 0xFF;
	data->addr[i + 2] = (color >> 16) & 0xFF;
}

void	put_pixel(t_data *data, int x, int y)
{
	int	i;
	int	color;

	color = 0x00FFFFFF;
	if (x < 0 || x >= 1920 || y < 0 || y >= 1080)
		return ;
	i = (y * data->line_len) + (x * (data->bpp / 8));
	data->addr[i + 0] = color & 0xFF;
	data->addr[i + 1] = (color >> 8) & 0xFF;
	data->addr[i + 2] = (color >> 16) & 0xFF;
}

void	draw_line(t_data *data, t_coordonates coordonates, int x1, int y1)
{
	t_line	line;
	int		i;

	if (abs(x1 - coordonates.x) > abs(y1 - coordonates.y))
		line.steps = abs(x1 - coordonates.x);
	else
		line.steps = abs(y1 - coordonates.y);
	if (line.steps == 0)
		return ;
	line.x_inc = (float)(x1 - coordonates.x) / line.steps;
	line.y_inc = (float)(y1 - coordonates.y) / line.steps;
	line.x = coordonates.x;
	line.y = coordonates.y;
	i = 0;
	while (i <= line.steps)
	{
		put_pixel(data, (int)line.x, (int)line.y);
		line.x += line.x_inc;
		line.y += line.y_inc;
		i++;
	}
}
