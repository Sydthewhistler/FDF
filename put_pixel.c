#include "header.h"

// ---------------------------------------------------------------------------
// Color utilities
// ---------------------------------------------------------------------------

static int lerp_color(int c0, int c1, float t)
{
    int r = (int)(((c0 >> 16) & 0xFF) + (((c1 >> 16) & 0xFF) - ((c0 >> 16) & 0xFF)) * t);
    int g = (int)(((c0 >>  8) & 0xFF) + (((c1 >>  8) & 0xFF) - ((c0 >>  8) & 0xFF)) * t);
    int b = (int)(((c0      ) & 0xFF) + (((c1      ) & 0xFF) - ((c0      ) & 0xFF)) * t);
    return (r << 16) | (g << 8) | b;
}

// ---------------------------------------------------------------------------
// Hypsometric palette — 11-stop geographic tint
// ---------------------------------------------------------------------------
typedef struct { float t; int color; } t_stop;

static const t_stop HYPS[] = {
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
#define N_HYPS (int)(sizeof(HYPS) / sizeof(HYPS[0]))

static int color_hypsometric(float t)
{
    if (t <= 0.0f) return HYPS[0].color;
    if (t >= 1.0f) return HYPS[N_HYPS - 1].color;
    for (int i = 0; i < N_HYPS - 1; i++) {
        if (t <= HYPS[i + 1].t) {
            float lt = (t - HYPS[i].t) / (HYPS[i + 1].t - HYPS[i].t);
            return lerp_color(HYPS[i].color, HYPS[i + 1].color, lt);
        }
    }
    return HYPS[N_HYPS - 1].color;
}

// ---------------------------------------------------------------------------
// Monochrome — dark grey to white
// ---------------------------------------------------------------------------
static int color_mono(float t)
{
    int v = 55 + (int)(t * 200);
    return (v << 16) | (v << 8) | v;
}

// ---------------------------------------------------------------------------
// Thermal — cold blue → cyan → green → yellow → red
// ---------------------------------------------------------------------------
static const t_stop THERM[] = {
    { 0.00f, 0x0022CC },
    { 0.25f, 0x00CCFF },
    { 0.50f, 0x00FF88 },
    { 0.75f, 0xFFCC00 },
    { 1.00f, 0xFF1100 },
};
#define N_THERM (int)(sizeof(THERM) / sizeof(THERM[0]))

static int color_thermal(float t)
{
    if (t <= 0.0f) return THERM[0].color;
    if (t >= 1.0f) return THERM[N_THERM - 1].color;
    for (int i = 0; i < N_THERM - 1; i++) {
        if (t <= THERM[i + 1].t) {
            float lt = (t - THERM[i].t) / (THERM[i + 1].t - THERM[i].t);
            return lerp_color(THERM[i].color, THERM[i + 1].color, lt);
        }
    }
    return THERM[N_THERM - 1].color;
}

// ---------------------------------------------------------------------------
// Public: map a raw Z value to a color
// ---------------------------------------------------------------------------
int height_to_color(int z, int z_min, int z_max, int mode)
{
    float t = (float)(z - z_min) / (float)(z_max - z_min);
    if (mode == COLOR_MONO)  return color_mono(t);
    if (mode == COLOR_THERM) return color_thermal(t);
    return color_hypsometric(t);
}

// ---------------------------------------------------------------------------
// Pixel / line rendering
// ---------------------------------------------------------------------------

void put_pixel(t_data *data, int x, int y, int color)
{
    if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
        return;
    int i = y * data->line_len + x * (data->bpp / 8);
    data->addr[i + 0] = (color      ) & 0xFF;
    data->addr[i + 1] = (color >>  8) & 0xFF;
    data->addr[i + 2] = (color >> 16) & 0xFF;
}

// Project a 3D vertex and draw it — color from raw z, projection from scaled z
void put_pixel_iso(t_data *data, int x, int y, int raw_z)
{
    int color  = height_to_color(raw_z, data->map->z_min, data->map->z_max, data->mvt.color_mode);
    int proj_z = (int)(raw_z * data->mvt.z_scale);
    int iso_x  = make_iso_x(x, y, proj_z, data) + data->mvt.width_translation;
    int iso_y  = make_iso_y(x, y, proj_z, data) + data->mvt.height_translation;
    put_pixel(data, iso_x, iso_y, color);
}

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
