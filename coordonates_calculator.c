#include "header.h"

// Intermediate result of the full 3D rotation matrix
typedef struct {
    float rx;
    float ry;
    float rz;
} t_rot3d;

// Apply Euler rotations (X then Y then Z) to a 3D point
static t_rot3d rotate_3d(int x, int y, int z, t_mvt *mvt)
{
    float cx = cos(mvt->angle_x), sx = sin(mvt->angle_x);
    float cy = cos(mvt->angle_y), sy = sin(mvt->angle_y);
    float cz = cos(mvt->angle_z), sz = sin(mvt->angle_z);

    t_rot3d r;
    r.rx = x * cy * cz + (y * cx - z * sx) * (-sz) + (y * sx + z * cx) * sy * cz;
    r.ry = x * cy * sz + (y * cx - z * sx) *   cz  + (y * sx + z * cx) * sy * sz;
    r.rz = -x * sy     + (y * sx + z * cx) * cy;
    return r;
}

// Project rotated point to isometric screen X
int make_iso_x(int x, int y, int z, t_data *data)
{
    t_rot3d r = rotate_3d(x, y, z, &data->mvt);
    return (int)((r.rx - r.ry) * cos(data->mvt.iso_angle));
}

// Project rotated point to isometric screen Y
int make_iso_y(int x, int y, int z, t_data *data)
{
    t_rot3d r = rotate_3d(x, y, z, &data->mvt);
    return (int)((r.rx + r.ry) * sin(data->mvt.iso_angle) - r.rz);
}

// Compute the screen position of a map vertex (col, row)
static t_coords2d screen_pos(t_data *data, int col, int row)
{
    int        dist = data->mvt.connection_distance;
    int        z    = data->map->coords[row][col];
    t_coords2d p;

    p.x = make_iso_x(col * dist, row * dist, z, data) + data->mvt.width_translation;
    p.y = make_iso_y(col * dist, row * dist, z, data) + data->mvt.height_translation;
    return p;
}

// Draw edges from (col, row) to its left and top neighbours, with color interpolation
void make_connections(t_data *data, int col, int row)
{
    t_coords2d cur       = screen_pos(data, col, row);
    int        cur_z     = data->map->coords[row][col];
    int        cur_color = height_to_color(cur_z, data->map->z_min, data->map->z_max);

    if (row > 0) {
        t_coords2d prev      = screen_pos(data, col, row - 1);
        int        prev_z    = data->map->coords[row - 1][col];
        int        prev_color = height_to_color(prev_z, data->map->z_min, data->map->z_max);
        draw_line(data, cur, prev.x, prev.y, cur_color, prev_color);
    }
    if (col > 0) {
        t_coords2d prev      = screen_pos(data, col - 1, row);
        int        prev_z    = data->map->coords[row][col - 1];
        int        prev_color = height_to_color(prev_z, data->map->z_min, data->map->z_max);
        draw_line(data, cur, prev.x, prev.y, cur_color, prev_color);
    }
}
