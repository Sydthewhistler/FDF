#include "header.h"

// ---------------------------------------------------------------------------
// Panel colors
// ---------------------------------------------------------------------------
#define COL_BG          0x0E0E1C
#define COL_BORDER      0x2A2A50
#define COL_SEC         0x7070A0
#define COL_TITLE       0x6080FF
#define COL_BTN         0x1A2040
#define COL_BTN_ON      0x2A4888
#define COL_BTN_EDGE    0x3040A0
#define COL_TEXT        0xCCCCEE
#define COL_VALUE       0xFFCC44
#define COL_DIV         0x1E1E38
#define COL_DIV2        0x333366

// ---------------------------------------------------------------------------
// Button X layout
// ---------------------------------------------------------------------------
#define BX_L1   12
#define BX_L2   56
#define BX_R1   132
#define BX_R2   176
#define BX_F1   12
#define BX_F2   176

// ---------------------------------------------------------------------------
// Section Y positions
// ---------------------------------------------------------------------------

// Z Scale
#define Y_DIV0      32
#define Y_S0_LBL    42
#define Y_ZSC_Y1    57
#define Y_ZSC_Y2    81

// Color mode
#define Y_DIV1      93
#define Y_S1_LBL    103
#define Y_CHYP_Y1   118
#define Y_CHYP_Y2   138
#define Y_CMNO_Y1   144
#define Y_CMNO_Y2   164
#define Y_CTHR_Y1   170
#define Y_CTHR_Y2   190

// Density (LOD)
#define Y_DIV2      202
#define Y_S2_LBL    212
#define Y_LOD_Y1    227
#define Y_LOD_Y2    251

// Zoom
#define Y_DIV3      263
#define Y_S3_LBL    273
#define Y_ZOM_Y1    288
#define Y_ZOM_Y2    312

// View controls
#define Y_DIV4      324
#define Y_S4_LBL    334
#define Y_RST_Y1    349
#define Y_RST_Y2    371
#define Y_CTR_Y1    377
#define Y_CTR_Y2    399

// Map info
#define Y_DIV5      411
#define Y_S5_LBL    421
#define Y_INFO_MAP  436
#define Y_INFO_Z    451
#define Y_INFO_AX   466
#define Y_INFO_AY   481
#define Y_INFO_AZ   496

// ---------------------------------------------------------------------------
// Drawing helpers
// ---------------------------------------------------------------------------

static void draw_rect(t_data *data, int x1, int y1, int x2, int y2, int color)
{
    for (int y = y1; y <= y2; y++)
        for (int x = x1; x <= x2; x++)
            put_pixel(data, x, y, color);
}

static void draw_button(t_data *data, int x1, int y1, int x2, int y2, int active)
{
    int bg = active ? COL_BTN_ON : COL_BTN;
    draw_rect(data, x1, y1, x2, y2, bg);
    for (int x = x1; x <= x2; x++) {
        put_pixel(data, x, y1, COL_BTN_EDGE);
        put_pixel(data, x, y2, COL_BTN_EDGE);
    }
    for (int y = y1; y <= y2; y++) {
        put_pixel(data, x1, y, COL_BTN_EDGE);
        put_pixel(data, x2, y, COL_BTN_EDGE);
    }
}

static void draw_divider(t_data *data, int y)
{
    for (int x = 6; x < PANEL_W - 6; x++)
        put_pixel(data, x, y, COL_DIV);
    for (int x = 6; x < PANEL_W - 6; x++)
        put_pixel(data, x, y + 1, COL_DIV2);
}

// ---------------------------------------------------------------------------
// draw_panel — into image buffer (before blit)
// ---------------------------------------------------------------------------
void draw_panel(t_data *data)
{
    draw_rect(data, 0, 0, PANEL_W - 2, WIN_H - 1, COL_BG);
    for (int y = 0; y < WIN_H; y++) {
        put_pixel(data, PANEL_W - 2, y, COL_BORDER);
        put_pixel(data, PANEL_W - 1, y, 0x070710);
    }

    draw_divider(data, Y_DIV0);
    draw_divider(data, Y_DIV1);
    draw_divider(data, Y_DIV2);
    draw_divider(data, Y_DIV3);
    draw_divider(data, Y_DIV4);
    draw_divider(data, Y_DIV5);

    // Z scale buttons
    draw_button(data, BX_L1, Y_ZSC_Y1, BX_L2, Y_ZSC_Y2, 0);
    draw_button(data, BX_R1, Y_ZSC_Y1, BX_R2, Y_ZSC_Y2, 0);

    // Color mode buttons (highlight active)
    draw_button(data, BX_F1, Y_CHYP_Y1, BX_F2, Y_CHYP_Y2, data->mvt.color_mode == COLOR_HYPS);
    draw_button(data, BX_F1, Y_CMNO_Y1, BX_F2, Y_CMNO_Y2, data->mvt.color_mode == COLOR_MONO);
    draw_button(data, BX_F1, Y_CTHR_Y1, BX_F2, Y_CTHR_Y2, data->mvt.color_mode == COLOR_THERM);

    // LOD buttons
    draw_button(data, BX_L1, Y_LOD_Y1, BX_L2, Y_LOD_Y2, 0);
    draw_button(data, BX_R1, Y_LOD_Y1, BX_R2, Y_LOD_Y2, 0);

    // Zoom buttons
    draw_button(data, BX_L1, Y_ZOM_Y1, BX_L2, Y_ZOM_Y2, 0);
    draw_button(data, BX_R1, Y_ZOM_Y1, BX_R2, Y_ZOM_Y2, 0);

    // Reset / Center buttons
    draw_button(data, BX_F1, Y_RST_Y1, BX_F2, Y_RST_Y2, 0);
    draw_button(data, BX_F1, Y_CTR_Y1, BX_F2, Y_CTR_Y2, 0);
}

// ---------------------------------------------------------------------------
// draw_panel_text — after blit
// ---------------------------------------------------------------------------
void draw_panel_text(t_data *data)
{
    char buf[32];

    mlx_string_put(data->mlx, data->win, 38, 16, COL_TITLE, "FDF Controls");

    // Z Scale
    mlx_string_put(data->mlx, data->win, 10, Y_S0_LBL, COL_SEC, "Z SCALE");
    mlx_string_put(data->mlx, data->win, 22,  Y_ZSC_Y1 + 11, COL_TEXT, "-");
    snprintf(buf, sizeof(buf), "x%.2f", data->mvt.z_scale);
    mlx_string_put(data->mlx, data->win, 60,  Y_ZSC_Y1 + 11, COL_VALUE, buf);
    mlx_string_put(data->mlx, data->win, 148, Y_ZSC_Y1 + 11, COL_TEXT, "+");

    // Color mode
    mlx_string_put(data->mlx, data->win, 10, Y_S1_LBL, COL_SEC, "COLOR MODE");
    mlx_string_put(data->mlx, data->win, 40, Y_CHYP_Y1 + 11, COL_TEXT, "Hypsometric");
    mlx_string_put(data->mlx, data->win, 50, Y_CMNO_Y1 + 11, COL_TEXT, "Monochrome");
    mlx_string_put(data->mlx, data->win, 62, Y_CTHR_Y1 + 11, COL_TEXT, "Thermal");

    // Density
    mlx_string_put(data->mlx, data->win, 10, Y_S2_LBL, COL_SEC, "DENSITY");
    mlx_string_put(data->mlx, data->win, 22,  Y_LOD_Y1 + 11, COL_TEXT, "-");
    snprintf(buf, sizeof(buf), "1/%d", data->mvt.lod);
    mlx_string_put(data->mlx, data->win, 72,  Y_LOD_Y1 + 11, COL_VALUE, buf);
    mlx_string_put(data->mlx, data->win, 148, Y_LOD_Y1 + 11, COL_TEXT, "+");

    // Zoom
    mlx_string_put(data->mlx, data->win, 10, Y_S3_LBL, COL_SEC, "ZOOM");
    mlx_string_put(data->mlx, data->win, 22,  Y_ZOM_Y1 + 11, COL_TEXT, "-");
    snprintf(buf, sizeof(buf), "%d", data->mvt.connection_distance);
    mlx_string_put(data->mlx, data->win, 68,  Y_ZOM_Y1 + 11, COL_VALUE, buf);
    mlx_string_put(data->mlx, data->win, 148, Y_ZOM_Y1 + 11, COL_TEXT, "+");

    // View
    mlx_string_put(data->mlx, data->win, 10, Y_S4_LBL, COL_SEC, "VIEW");
    mlx_string_put(data->mlx, data->win, 55, Y_RST_Y1 + 11, COL_TEXT, "Reset");
    mlx_string_put(data->mlx, data->win, 50, Y_CTR_Y1 + 11, COL_TEXT, "Center");

    // Map info
    mlx_string_put(data->mlx, data->win, 10, Y_S5_LBL, COL_SEC, "MAP INFO");
    snprintf(buf, sizeof(buf), "%d x %d", data->map->width, data->map->height);
    mlx_string_put(data->mlx, data->win, 10, Y_INFO_MAP, COL_TEXT, buf);
    snprintf(buf, sizeof(buf), "Z %d / %d", data->map->z_min, data->map->z_max);
    mlx_string_put(data->mlx, data->win, 10, Y_INFO_Z, COL_TEXT, buf);
    snprintf(buf, sizeof(buf), "Rx %.2f", data->mvt.angle_x);
    mlx_string_put(data->mlx, data->win, 10, Y_INFO_AX, COL_SEC, buf);
    snprintf(buf, sizeof(buf), "Ry %.2f", data->mvt.angle_y);
    mlx_string_put(data->mlx, data->win, 10, Y_INFO_AY, COL_SEC, buf);
    snprintf(buf, sizeof(buf), "Rz %.2f", data->mvt.angle_z);
    mlx_string_put(data->mlx, data->win, 10, Y_INFO_AZ, COL_SEC, buf);
}

// ---------------------------------------------------------------------------
// Auto-center / Reset
// ---------------------------------------------------------------------------
static void auto_center(t_data *data)
{
    int dist   = data->mvt.connection_distance;
    int mid_col = data->map->width  / 2;
    int mid_row = data->map->height / 2;
    int proj_z  = (int)(data->map->coords[mid_row][mid_col] * data->mvt.z_scale);

    data->mvt.width_translation  = 0;
    data->mvt.height_translation = 0;

    int cx = make_iso_x(mid_col * dist, mid_row * dist, proj_z, data);
    int cy = make_iso_y(mid_col * dist, mid_row * dist, proj_z, data);

    data->mvt.width_translation  = WIN_W / 2 - cx;
    data->mvt.height_translation = WIN_H / 2 - cy;
}

static void reset_view(t_data *data)
{
    data->mvt.angle_x             = 0.0f;
    data->mvt.angle_y             = 0.0f;
    data->mvt.angle_z             = 0.0f;
    data->mvt.iso_angle           = 0.6236f;
    data->mvt.z_scale             = 1.0f;
    data->mvt.lod                 = 1;
    data->mvt.connection_distance = 30;
    auto_center(data);
}

// ---------------------------------------------------------------------------
// panel_click
// ---------------------------------------------------------------------------
static int in_btn(int x, int y, int x1, int y1, int x2, int y2)
{
    return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}

int panel_click(int x, int y, t_data *data)
{
    if (x >= PANEL_W)
        return 0;

    // Z scale
    if (in_btn(x, y, BX_L1, Y_ZSC_Y1, BX_L2, Y_ZSC_Y2)) {
        data->mvt.z_scale -= 0.25f;
        if (data->mvt.z_scale < 0.1f) data->mvt.z_scale = 0.1f;
        return 1;
    }
    if (in_btn(x, y, BX_R1, Y_ZSC_Y1, BX_R2, Y_ZSC_Y2)) {
        data->mvt.z_scale += 0.25f;
        if (data->mvt.z_scale > 10.0f) data->mvt.z_scale = 10.0f;
        return 1;
    }

    // Color mode
    if (in_btn(x, y, BX_F1, Y_CHYP_Y1, BX_F2, Y_CHYP_Y2)) {
        data->mvt.color_mode = COLOR_HYPS;  return 1;
    }
    if (in_btn(x, y, BX_F1, Y_CMNO_Y1, BX_F2, Y_CMNO_Y2)) {
        data->mvt.color_mode = COLOR_MONO;  return 1;
    }
    if (in_btn(x, y, BX_F1, Y_CTHR_Y1, BX_F2, Y_CTHR_Y2)) {
        data->mvt.color_mode = COLOR_THERM; return 1;
    }

    // LOD
    if (in_btn(x, y, BX_L1, Y_LOD_Y1, BX_L2, Y_LOD_Y2)) {
        if (data->mvt.lod > 1) data->mvt.lod--;
        return 1;
    }
    if (in_btn(x, y, BX_R1, Y_LOD_Y1, BX_R2, Y_LOD_Y2)) {
        if (data->mvt.lod < 8) data->mvt.lod++;
        return 1;
    }

    // Zoom
    if (in_btn(x, y, BX_L1, Y_ZOM_Y1, BX_L2, Y_ZOM_Y2)) {
        int step = data->mvt.connection_distance / 10;
        if (step < 1) step = 1;
        data->mvt.connection_distance -= step;
        if (data->mvt.connection_distance < 1) data->mvt.connection_distance = 1;
        return 1;
    }
    if (in_btn(x, y, BX_R1, Y_ZOM_Y1, BX_R2, Y_ZOM_Y2)) {
        int step = data->mvt.connection_distance / 10;
        if (step < 1) step = 1;
        data->mvt.connection_distance += step;
        return 1;
    }

    // Reset / Center
    if (in_btn(x, y, BX_F1, Y_RST_Y1, BX_F2, Y_RST_Y2)) {
        reset_view(data);  return 1;
    }
    if (in_btn(x, y, BX_F1, Y_CTR_Y1, BX_F2, Y_CTR_Y2)) {
        auto_center(data); return 1;
    }

    return 1;
}
