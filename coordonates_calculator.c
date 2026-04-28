#include "header.h"

typedef struct { float rx; float ry; float rz; } t_rot3d;

static t_rot3d rotate_3d(int x, int y, int z, t_mvt *mvt)
{
    float cx = cos(mvt->angle_x), sx = sin(mvt->angle_x);
    float cy = cos(mvt->angle_y), sy = sin(mvt->angle_y);
    float cz = cos(mvt->angle_z), sz = sin(mvt->angle_z);
    t_rot3d r;
    r.rx = x*cy*cz + (y*cx - z*sx)*(-sz) + (y*sx + z*cx)*sy*cz;
    r.ry = x*cy*sz + (y*cx - z*sx)*  cz  + (y*sx + z*cx)*sy*sz;
    r.rz = -x*sy   + (y*sx + z*cx)*cy;
    return r;
}

int make_iso_x(int x, int y, int z, t_data *data)
{
    t_rot3d r = rotate_3d(x, y, z, &data->mvt);
    return (int)((r.rx - r.ry) * cos(data->mvt.iso_angle));
}

int make_iso_y(int x, int y, int z, t_data *data)
{
    t_rot3d r = rotate_3d(x, y, z, &data->mvt);
    return (int)((r.rx + r.ry) * sin(data->mvt.iso_angle) - r.rz);
}

// z_scale applied here, not at call sites
static t_coords2d screen_pos(t_data *data, int col, int row)
{
    int        dist   = data->mvt.connection_distance;
    int        raw_z  = data->map->coords[row][col];
    int        proj_z = (int)(raw_z * data->mvt.z_scale);
    t_coords2d p;

    p.x = make_iso_x(col * dist, row * dist, proj_z, data) + data->mvt.width_translation;
    p.y = make_iso_y(col * dist, row * dist, proj_z, data) + data->mvt.height_translation;
    return p;
}

void make_connections(t_data *data, int col, int row)
{
    int        lod       = data->mvt.lod;
    t_coords2d cur       = screen_pos(data, col, row);
    int        cur_z     = data->map->coords[row][col];
    int        cur_color = height_to_color(cur_z, data->map->z_min, data->map->z_max, data->mvt.color_mode);

    if (row >= lod) {
        t_coords2d prev      = screen_pos(data, col, row - lod);
        int        prev_z    = data->map->coords[row - lod][col];
        int        prev_color = height_to_color(prev_z, data->map->z_min, data->map->z_max, data->mvt.color_mode);
        draw_line(data, cur, prev.x, prev.y, cur_color, prev_color);
    }
    if (col >= lod) {
        t_coords2d prev      = screen_pos(data, col - lod, row);
        int        prev_z    = data->map->coords[row][col - lod];
        int        prev_color = height_to_color(prev_z, data->map->z_min, data->map->z_max, data->mvt.color_mode);
        draw_line(data, cur, prev.x, prev.y, cur_color, prev_color);
    }
}
