#include "header.h"

static void create_img(t_data *data)
{
    for (int row = 0; row < data->map->height; row++) {
        for (int col = 0; col < data->map->width; col++) {
            int wx = col * data->mvt.connection_distance;
            int wy = row * data->mvt.connection_distance;
            put_pixel_iso(data, wx, wy, data->map->coords[row][col]);
            make_connections(data, col, row);
        }
    }
}

void new_img(t_data *data)
{
    data->img  = mlx_new_image(data->mlx, WIN_W, WIN_H);
    data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_len, &data->endian);
    create_img(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

void ft_fdf(t_data *data)
{
    data->mvt.height_translation  = 200;
    data->mvt.width_translation   = 800;
    data->mvt.connection_distance = 30;
    data->mvt.angle_x = 0.0f;
    data->mvt.angle_y = 0.0f;
    data->mvt.angle_z = 0.0f;

    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIN_W, WIN_H, "FDF");
    new_img(data);
    mlx_key_hook(data->win, key_hook, data);
    mlx_hook(data->win, 17, 0, event_hook, data);
    mlx_loop(data->mlx);
}
