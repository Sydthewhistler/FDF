#include "header.h"

// ---------------------------------------------------------------------------
// Color gradient — hypsometric tint (geographic elevation palette)
//
//   t = 0.00  deep water    #002880
//   t = 0.18  shallow water #0066CC
//   t = 0.28  coast / lagoon #55AAEE
//   t = 0.33  beach / sand   #E8D5A3
//   t = 0.42  lowland plain  #A8D878
//   t = 0.55  grassland      #4CA840
//   t = 0.67  upland forest  #2D7D32
//   t = 0.77  highland brown #8C6B3E
//   t = 0.87  rocky terrain  #706050
//   t = 0.93  mountain grey  #AAAAAA
//   t = 1.00  snow cap       #F0F0FF
// ---------------------------------------------------------------------------

typedef struct {
    float t;
    int   color;
} t_stop;

static const t_stop STOPS[] = {
    { 0.00f, 0x002880 },
    { 0.18f, 0x0066CC },
    { 0.28f, 0x55AAEE },
    { 0.33f, 0xE8D5A3 },
    { 0.42f, 0xA8D878 },
    { 0.55f, 0x4CA840 },
    { 0.67f, 0x2D7D32 },
    { 0.77f, 0x8C6B3E },
    { 0.87f, 0x706050 },
    { 0.93f, 0xAAAAAA },
    { 1.00f, 0xF0F0FF },
};

#define N_STOPS (int)(sizeof(STOPS) / sizeof(STOPS[0]))

// Linear interpolation between two packed RGB colors
static int lerp_color(int c0, int c1, float t)
{
    int r = (int)(((c0 >> 16) & 0xFF) + (((c1 >> 16) & 0xFF) - ((c0 >> 16) & 0xFF)) * t);
    int g = (int)(((c0 >>  8) & 0xFF) + (((c1 >>  8) & 0xFF) - ((c0 >>  8) & 0xFF)) * t);
    int b = (int)(((c0      ) & 0xFF) + (((c1      ) & 0xFF) - ((c0      ) & 0xFF)) * t);
    return (r << 16) | (g << 8) | b;
}

// Map a height value to a color using the hypsometric multi-stop palette
int height_to_color(int z, int z_min, int z_max)
{
    float t = (float)(z - z_min) / (float)(z_max - z_min);
    if (t <= 0.0f) return STOPS[0].color;
    if (t >= 1.0f) return STOPS[N_STOPS - 1].color;

    for (int i = 0; i < N_STOPS - 1; i++) {
        if (t <= STOPS[i + 1].t) {
            float local_t = (t - STOPS[i].t) / (STOPS[i + 1].t - STOPS[i].t);
            return lerp_color(STOPS[i].color, STOPS[i + 1].color, local_t);
        }
    }
    return STOPS[N_STOPS - 1].color;
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
    int    dx = abs(x1 - start.x);
    int    dy = abs(y1 - start.y);

    line.steps = (dx > dy) ? dx : dy;
    if (line.steps == 0)
        return;

    line.x_inc = (float)(x1 - start.x) / line.steps;
    line.y_inc = (float)(y1 - start.y) / line.steps;
    line.x     = start.x;
    line.y     = start.y;

    for (int i = 0; i <= line.steps; i++) {
        float t     = (float)i / line.steps;
        int   color = lerp_color(c0, c1, t);
        put_pixel(data, (int)line.x, (int)line.y, color);
        line.x += line.x_inc;
        line.y += line.y_inc;
    }
}
