#include "header.h"

// ---------------------------------------------------------------------------
// Panel colors
// ---------------------------------------------------------------------------
#define COL_BG          0x0E0E1C
#define COL_BORDER      0x2A2A50
#define COL_SEC_TITLE   0x7070A0
#define COL_TITLE       0x6080FF
#define COL_BTN         0x1A2040
#define COL_BTN_BORDER  0x3040A0
#define COL_BTN_TEXT    0xCCCCEE
#define COL_VALUE       0xFFCC44
#define COL_DIVIDER     0x1E1E38

// ---------------------------------------------------------------------------
// Button layout  (x1, y1 = top-left   x2, y2 = bottom-right)
// ---------------------------------------------------------------------------
// Section: Relief — ISO angle
#define ISO_M_X1  12
#define ISO_M_Y1  86
#define ISO_M_X2  58
#define ISO_M_Y2  110

#define ISO_P_X1  130
#define ISO_P_Y1  86
#define ISO_P_X2  176
#define ISO_P_Y2  110

// Section: View presets
#define V_FRONT_X1  12
#define V_FRONT_Y1  148
#define V_FRONT_X2  176
#define V_FRONT_Y2  172

#define V_TOP_X1    12
#define V_TOP_Y1    180
#define V_TOP_X2    176
#define V_TOP_Y2    204

#define V_ISO_X1    12
#define V_ISO_Y1    212
#define V_ISO_X2    176
#define V_ISO_Y2    236

// Section: Zoom
#define ZOOM_M_X1  12
#define ZOOM_M_Y1  286
#define ZOOM_M_X2  58
#define ZOOM_M_Y2  310

#define ZOOM_P_X1  130
#define ZOOM_P_Y1  286
#define ZOOM_P_X2  176
#define ZOOM_P_Y2  310

// ---------------------------------------------------------------------------
// Drawing helpers
// ---------------------------------------------------------------------------

static void draw_rect(t_data *data, int x1, int y1, int x2, int y2, int color)
{
    for (int y = y1; y <= y2; y++)
        for (int x = x1; x <= x2; x++)
            put_pixel(data, x, y, color);
}

static void draw_button(t_data *data, int x1, int y1, int x2, int y2)
{
    draw_rect(data, x1, y1, x2, y2, COL_BTN);
    // Border
    for (int x = x1; x <= x2; x++) {
        put_pixel(data, x, y1, COL_BTN_BORDER);
        put_pixel(data, x, y2, COL_BTN_BORDER);
    }
    for (int y = y1; y <= y2; y++) {
        put_pixel(data, x1, y, COL_BTN_BORDER);
        put_pixel(data, x2, y, COL_BTN_BORDER);
    }
}

static void draw_divider(t_data *data, int y)
{
    for (int x = 8; x < PANEL_W - 8; x++)
        put_pixel(data, x, y, COL_DIVIDER);
    for (int x = 8; x < PANEL_W - 8; x++)
        put_pixel(data, x, y + 1, COL_BORDER);
}

// ---------------------------------------------------------------------------
// draw_panel — called before blit (draws into image buffer)
// ---------------------------------------------------------------------------

void draw_panel(t_data *data)
{
    // Background
    draw_rect(data, 0, 0, PANEL_W - 2, WIN_H - 1, COL_BG);

    // Right border line
    for (int y = 0; y < WIN_H; y++) {
        put_pixel(data, PANEL_W - 2, y, COL_BORDER);
        put_pixel(data, PANEL_W - 1, y, 0x070710);
    }

    // Section dividers
    draw_divider(data, 32);    // below title
    draw_divider(data, 122);   // below Relief
    draw_divider(data, 252);   // below Views
    draw_divider(data, 326);   // below Zoom

    // ISO angle buttons
    draw_button(data, ISO_M_X1, ISO_M_Y1, ISO_M_X2, ISO_M_Y2);
    draw_button(data, ISO_P_X1, ISO_P_Y1, ISO_P_X2, ISO_P_Y2);

    // View preset buttons
    draw_button(data, V_FRONT_X1, V_FRONT_Y1, V_FRONT_X2, V_FRONT_Y2);
    draw_button(data, V_TOP_X1,   V_TOP_Y1,   V_TOP_X2,   V_TOP_Y2);
    draw_button(data, V_ISO_X1,   V_ISO_Y1,   V_ISO_X2,   V_ISO_Y2);

    // Zoom buttons
    draw_button(data, ZOOM_M_X1, ZOOM_M_Y1, ZOOM_M_X2, ZOOM_M_Y2);
    draw_button(data, ZOOM_P_X1, ZOOM_P_Y1, ZOOM_P_X2, ZOOM_P_Y2);
}

// ---------------------------------------------------------------------------
// draw_panel_text — called after mlx_put_image_to_window
// mlx_string_put draws directly onto the window surface (above the image)
// ---------------------------------------------------------------------------

void draw_panel_text(t_data *data)
{
    char buf[24];

    // Title
    mlx_string_put(data->mlx, data->win, 40, 16, COL_TITLE,    "FDF Controls");

    // --- Relief ---
    mlx_string_put(data->mlx, data->win, 10, 44,  COL_SEC_TITLE, "RELIEF");
    mlx_string_put(data->mlx, data->win, 10, 70,  COL_BTN_TEXT,  "ISO angle");

    mlx_string_put(data->mlx, data->win, 22,  95, COL_BTN_TEXT, " - ");
    snprintf(buf, sizeof(buf), "%.2f", data->mvt.iso_angle);
    mlx_string_put(data->mlx, data->win, 70,  95, COL_VALUE,    buf);
    mlx_string_put(data->mlx, data->win, 142, 95, COL_BTN_TEXT, " + ");

    // --- View presets ---
    mlx_string_put(data->mlx, data->win, 10, 134, COL_SEC_TITLE, "VIEW PRESET");
    mlx_string_put(data->mlx, data->win, 52, 157, COL_BTN_TEXT,  "Front view");
    mlx_string_put(data->mlx, data->win, 55, 189, COL_BTN_TEXT,  "Top / Plan");
    mlx_string_put(data->mlx, data->win, 55, 221, COL_BTN_TEXT,  "Isometric");

    // --- Zoom ---
    mlx_string_put(data->mlx, data->win, 10, 264, COL_SEC_TITLE, "ZOOM");
    mlx_string_put(data->mlx, data->win, 22,  295, COL_BTN_TEXT, " - ");
    snprintf(buf, sizeof(buf), "%d", data->mvt.connection_distance);
    mlx_string_put(data->mlx, data->win, 78,  295, COL_VALUE,    buf);
    mlx_string_put(data->mlx, data->win, 142, 295, COL_BTN_TEXT, " + ");
}

// ---------------------------------------------------------------------------
// panel_click — returns 1 if a panel button was hit, 0 otherwise
// ---------------------------------------------------------------------------

static int in_btn(int x, int y, int x1, int y1, int x2, int y2)
{
    return (x >= x1 && x <= x2 && y >= y1 && y <= y2);
}

int panel_click(int x, int y, t_data *data)
{
    if (x >= PANEL_W)
        return 0;

    // ISO angle −
    if (in_btn(x, y, ISO_M_X1, ISO_M_Y1, ISO_M_X2, ISO_M_Y2)) {
        data->mvt.iso_angle -= 0.05f;
        if (data->mvt.iso_angle < 0.05f)
            data->mvt.iso_angle = 0.05f;
        return 1;
    }
    // ISO angle +
    if (in_btn(x, y, ISO_P_X1, ISO_P_Y1, ISO_P_X2, ISO_P_Y2)) {
        data->mvt.iso_angle += 0.05f;
        if (data->mvt.iso_angle > 1.55f)
            data->mvt.iso_angle = 1.55f;
        return 1;
    }
    // View: Front
    if (in_btn(x, y, V_FRONT_X1, V_FRONT_Y1, V_FRONT_X2, V_FRONT_Y2)) {
        data->mvt.angle_x = 0.0f;
        data->mvt.angle_y = 0.0f;
        data->mvt.angle_z = 0.0f;
        return 1;
    }
    // View: Top / Plan
    if (in_btn(x, y, V_TOP_X1, V_TOP_Y1, V_TOP_X2, V_TOP_Y2)) {
        data->mvt.angle_x = (float)(M_PI / 2.0);
        data->mvt.angle_y = 0.0f;
        data->mvt.angle_z = 0.0f;
        return 1;
    }
    // View: Isometric (classic 35.26° tilt + 45° spin)
    if (in_btn(x, y, V_ISO_X1, V_ISO_Y1, V_ISO_X2, V_ISO_Y2)) {
        data->mvt.angle_x = 0.6155f;
        data->mvt.angle_y = 0.0f;
        data->mvt.angle_z = 0.7854f;
        return 1;
    }
    // Zoom −
    if (in_btn(x, y, ZOOM_M_X1, ZOOM_M_Y1, ZOOM_M_X2, ZOOM_M_Y2)) {
        int step = data->mvt.connection_distance / 10;
        if (step < 1) step = 1;
        data->mvt.connection_distance -= step;
        if (data->mvt.connection_distance < 1)
            data->mvt.connection_distance = 1;
        return 1;
    }
    // Zoom +
    if (in_btn(x, y, ZOOM_P_X1, ZOOM_P_Y1, ZOOM_P_X2, ZOOM_P_Y2)) {
        int step = data->mvt.connection_distance / 10;
        if (step < 1) step = 1;
        data->mvt.connection_distance += step;
        return 1;
    }

    return 1; // click absorbed by panel even if no button hit
}
