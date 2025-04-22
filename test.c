/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:02:26 by scavalli          #+#    #+#             */
/*   Updated: 2025/04/22 13:02:34 by scavalli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	put_pixel(t_data *data, int x, int y, int color)
{
	if (x < 0 || x >= 800 || y < 0 || y >= 600)
		return;
	int i = (y * data->line_len) + (x * (data->bpp / 8));
	data->addr[i + 0] = color & 0xFF;
	data->addr[i + 1] = (color >> 8) & 0xFF;
	data->addr[i + 2] = (color >> 16) & 0xFF;
}

// Dessine une tuile en losange (très simple)
void draw_tile(t_data *data, int x, int y, int color)
{
	for (int i = 0; i < TILE_HEIGHT; i++) {
		for (int j = 0; j < TILE_WIDTH; j++) {
			if (abs(j - TILE_WIDTH / 2) <= i)
				put_pixel(data, x + j, y + i, color);
		}
	}
}

void draw_map(t_data *data)
{
	int offset_x = 400;
	int offset_y = 50;

	for (int y = 0; y < MAP_HEIGHT; y++) {
		for (int x = 0; x < MAP_WIDTH; x++) {
			if (map[y][x]) {
				int iso_x = (x - y) * TILE_WIDTH / 2 + offset_x;
				int iso_y = (x + y) * TILE_HEIGHT / 2 + offset_y;
				draw_tile(data, iso_x, iso_y, 0x00FF00); // Vert
			}
		}
	}
}

int	main(void)
{
	t_data	data;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 1920, 1080, "Vue isométrique");
	data.img = mlx_new_image(data.mlx, 1920, 1080);
	data.addr = mlx_get_data_addr(data.img, &data.bpp, &data.line_len, &data.endian);

	draw_map(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
}