#ifndef HEADER_H
#define HEADER_H

#include "minilibx-linux/mlx.h"
#include "libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include <limits.h>

// Window dimensions
#define WIN_W       1920
#define WIN_H       1080

// Control panel width (left strip)
#define PANEL_W     192

// Keyboard keycodes (X11)
#define ESCAPE_KEY  65307
#define KEY_UP      65362
#define KEY_DOWN    65364
#define KEY_LEFT    65361
#define KEY_RIGHT   65363
#define KEY_Z       122
#define KEY_X       120
#define KEY_A       97
#define KEY_Q       113
#define KEY_S       115
#define KEY_W       119
#define KEY_D       100
#define KEY_E       101

// Mouse button codes (X11)
#define MOUSE_LEFT      1
#define MOUSE_MIDDLE    2
#define MOUSE_RIGHT     3
#define MOUSE_SCROLL_UP 4
#define MOUSE_SCROLL_DN 5

// Mouse drag sensitivity
#define MOUSE_ROT_SENS  0.007f

// Hypsometric color palette is defined in put_pixel.c (multi-stop gradient)

// Camera / view parameters
typedef struct s_mvt {
    int     height_translation;
    int     width_translation;
    int     connection_distance;
    float   angle_x;
    float   angle_y;
    float   angle_z;
    float   iso_angle;   // isometric projection angle (runtime-adjustable)
} t_mvt;

// Mouse drag state
typedef struct s_mouse {
    int button;
    int last_x;
    int last_y;
} t_mouse;

// Height map data
typedef struct s_map {
    int   **coords;
    int     height;
    int     width;
    int     z_min;
    int     z_max;
} t_map;

// Main application state
typedef struct s_data {
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int      bpp;
    int      line_len;
    int      endian;
    t_mvt    mvt;
    t_mouse  mouse;
    t_map   *map;
} t_data;

// Line drawing helper
typedef struct s_line {
    int     steps;
    float   x_inc;
    float   y_inc;
    float   x;
    float   y;
} t_line;

// 2D projected coordinates
typedef struct s_coords2d {
    int x;
    int y;
} t_coords2d;

// import_map.c
t_map       *import_map(char *file);

// FDF.c
void         ft_fdf(t_data *data);
void         new_img(t_data *data);

// put_pixel.c
int          height_to_color(int z, int z_min, int z_max);
void         put_pixel(t_data *data, int x, int y, int color);
void         put_pixel_iso(t_data *data, int x, int y, int z);
void         draw_line(t_data *data, t_coords2d start, int x1, int y1, int c0, int c1);

// coordonates_calculator.c
int          make_iso_x(int x, int y, int z, t_data *data);
int          make_iso_y(int x, int y, int z, t_data *data);
void         make_connections(t_data *data, int x, int y);

// panel.c
void         draw_panel(t_data *data);
void         draw_panel_text(t_data *data);
int          panel_click(int x, int y, t_data *data);

// utils.c
void         ft_free_tab(char **str);
void         ft_free_int(t_map *map);

// event.c
int          event_hook(t_data *data);
int          key_hook(int key, t_data *data);
int          mouse_press(int button, int x, int y, t_data *data);
int          mouse_release(int button, int x, int y, t_data *data);
int          mouse_move(int x, int y, t_data *data);

#endif
