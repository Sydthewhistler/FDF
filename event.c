#include "header.h"

static void apply_move(int key, t_data *data)
{
    if (key == KEY_DOWN)  data->mvt.height_translation -= 40;
    if (key == KEY_UP)    data->mvt.height_translation += 40;
    if (key == KEY_LEFT)  data->mvt.width_translation  += 40;
    if (key == KEY_RIGHT) data->mvt.width_translation  -= 40;
    if (key == KEY_Z)     data->mvt.connection_distance += 5;
    if (key == KEY_X)     data->mvt.connection_distance -= 5;
    if (key == KEY_A)     data->mvt.angle_x += 0.1f;
    if (key == KEY_Q)     data->mvt.angle_x -= 0.1f;
    if (key == KEY_S)     data->mvt.angle_y += 0.1f;
    if (key == KEY_W)     data->mvt.angle_y -= 0.1f;
    if (key == KEY_D)     data->mvt.angle_z += 0.1f;
    if (key == KEY_E)     data->mvt.angle_z -= 0.1f;
}

static int is_view_key(int key)
{
    return (key == KEY_DOWN || key == KEY_UP   || key == KEY_LEFT  || key == KEY_RIGHT
         || key == KEY_X    || key == KEY_Z
         || key == KEY_A    || key == KEY_Q
         || key == KEY_S    || key == KEY_W
         || key == KEY_D    || key == KEY_E);
}

int key_hook(int key, t_data *data)
{
    if (key == ESCAPE_KEY) {
        mlx_destroy_image(data->mlx, data->img);
        mlx_destroy_window(data->mlx, data->win);
        mlx_loop_end(data->mlx);
        return 1;
    }
    if (is_view_key(key)) {
        apply_move(key, data);
        mlx_destroy_image(data->mlx, data->img);
        new_img(data);
    }
    return 0;
}

int event_hook(t_data *data)
{
    mlx_destroy_image(data->mlx, data->img);
    mlx_destroy_window(data->mlx, data->win);
    mlx_loop_end(data->mlx);
    return 0;
}
