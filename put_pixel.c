#include "header.h"

// Linear interpolation between two packed RGB colors
static int lerp_color(int c0, int c1, float t)
{
    int r = (int)(((c0 >> 16) & 0xFF) + (((c1 >> 16) & 0xFF) - ((c0 >> 16) & 0xFF)) * t);
    int g = (int)(((c0 >>  8) & 0xFF) + (((c1 >>  8) & 0xFF) - ((c0 >>  8) & 0xFF)) * t);
    int b = (int)(((c0      ) & 0xFF) + (((c1      ) & 0xFF) - ((c0      ) & 0xFF)) * t);
    return (r << 16) | (g << 8) | b;
}

// Map a height value to a color using a 3-stop gradient:
//   z_min → COLOR_LOW (blue)
//   midpoint → COLOR_MID (green)
//   z_max → COLOR_HIGH (red)
int height_to_color(int z, int z_min, int z_max)
{
    float t = (float)(z - z_min) / (float)(z_max - z_min); // [0.0, 1.0]
    if (t < 0.5f)
        return lerp_color(COLOR_LOW, COLOR_MID, t * 2.0f);
    return lerp_color(COLOR_MID, COLOR_HIGH, (t - 0.5f) * 2.0f);
}

// Write a single pixel directly into the image buffer
void put_pixel(t_data *data, int x, int y, int color)
{
    if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
        return;
    int i = y * data->line_len + x * (data->bpp / 8);
    data->addr[i + 0] = (color      ) & 0xFF;
    data->addr[i + 1] = (color >>  8) & 0xFF;
    data->addr[i + 2] = (color >> 16) & 0xFF;
}

// Project a 3D point to screen and draw it with a height-based color
void put_pixel_iso(t_data *data, int x, int y, int z)
{
    int color = height_to_color(z, data->map->z_min, data->map->z_max);
    int iso_x = make_iso_x(x, y, z, data) + data->mvt.width_translation;
    int iso_y = make_iso_y(x, y, z, data) + data->mvt.height_translation;
    put_pixel(data, iso_x, iso_y, color);
}

// Draw a line from (start.x, start.y) to (x1, y1) with interpolated color
void draw_line(t_data *data, t_coords2d start, int x1, int y1, int c0, int c1)
{
    t_line line;

    int dx = abs(x1 - start.x);
    int dy = abs(y1 - start.y);
    line.steps = (dx > dy) ? dx : dy;
    if (line.steps == 0)
        return;

    line.x_inc = (float)(x1 - start.x) / line.steps;
    line.y_inc = (float)(y1 - start.y) / line.steps;
    line.x     = start.x;
    line.y     = start.y;

    for (int i = 0; i <= line.steps; i++) {
        float t    = (float)i / line.steps;
        int   color = lerp_color(c0, c1, t);
        put_pixel(data, (int)line.x, (int)line.y, color);
        line.x += line.x_inc;
        line.y += line.y_inc;
    }
}
