#include "header.h"

// ---------------------------------------------------------------------------
// Keyboard
// ---------------------------------------------------------------------------

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

// ---------------------------------------------------------------------------
// Mouse
// ---------------------------------------------------------------------------

// Redraw helper — destroy old image and render a new one
static void redraw(t_data *data)
{
    mlx_destroy_image(data->mlx, data->img);
    new_img(data);
}

int mouse_press(int button, int x, int y, t_data *data)
{
    // Scroll wheel: adaptive zoom (step proportional to current distance)
    if (button == MOUSE_SCROLL_UP || button == MOUSE_SCROLL_DN) {
        int step = data->mvt.connection_distance / 10;
        if (step < 1) step = 1;
        if (button == MOUSE_SCROLL_UP)
            data->mvt.connection_distance += step;
        else
            data->mvt.connection_distance -= step;
        if (data->mvt.connection_distance < 1)
            data->mvt.connection_distance = 1;
        redraw(data);
        return 0;
    }

    // Start drag (left = rotate, right = pan)
    if (button == MOUSE_LEFT || button == MOUSE_RIGHT) {
        data->mouse.button = button;
        data->mouse.last_x = x;
        data->mouse.last_y = y;
    }
    return 0;
}

int mouse_release(int button, int x, int y, t_data *data)
{
    (void)x;
    (void)y;
    if (button == data->mouse.button)
        data->mouse.button = 0;
    return 0;
}

int mouse_move(int x, int y, t_data *data)
{
    int dx;
    int dy;

    if (data->mouse.button == 0)
        return 0;

    dx = x - data->mouse.last_x;
    dy = y - data->mouse.last_y;
    data->mouse.last_x = x;
    data->mouse.last_y = y;

    if (data->mouse.button == MOUSE_LEFT) {
        // Left drag: rotate around X (tilt) and Z (spin)
        data->mvt.angle_x += dy * MOUSE_ROT_SENS;
        data->mvt.angle_z += dx * MOUSE_ROT_SENS;
    } else if (data->mouse.button == MOUSE_RIGHT) {
        // Right drag: pan
        data->mvt.width_translation  += dx;
        data->mvt.height_translation += dy;
    }

    redraw(data);
    return 0;
}

// ---------------------------------------------------------------------------
// Window close
// ---------------------------------------------------------------------------

int event_hook(t_data *data)
{
    mlx_destroy_image(data->mlx, data->img);
    mlx_destroy_window(data->mlx, data->win);
    mlx_loop_end(data->mlx);
    return 0;
}
