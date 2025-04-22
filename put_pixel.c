/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:18:43 by scavalli          #+#    #+#             */
/*   Updated: 2025/04/22 17:53:54 by scavalli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	put_pixel(t_data *data, int x, int y, int color)
{
	int i;

	if (x < 0 || x >= 1920 || y < 0 || y >= 1080)
		return;
	i = (y * data->line_len) + (x * (data->bpp / 8));
	data->addr[i + 0] = color & 0xFF;
	data->addr[i + 1] = (color >> 8) & 0xFF;
	data->addr[i + 2] = (color >> 16) & 0xFF;
}