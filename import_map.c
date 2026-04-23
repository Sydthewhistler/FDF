#include "header.h"

static int count_lines(const char *file)
{
    int   fd = open(file, O_RDONLY);
    int   count = 0;
    char *line;

    while ((line = get_next_line(fd)) != NULL) {
        free(line);
        count++;
    }
    close(fd);
    return count;
}

static void parse_row(char **tokens, t_map *map, int row)
{
    // First row: determine map width from token count
    if (map->width < 0) {
        int n = 0;
        while (tokens[n])
            n++;
        map->width = n;
    }

    map->coords[row] = malloc(sizeof(int) * map->width);
    for (int col = 0; tokens[col] && col < map->width; col++) {
        int val = ft_atoi(tokens[col]);
        map->coords[row][col] = val;
        if (val < map->z_min) map->z_min = val;
        if (val > map->z_max) map->z_max = val;
    }
}

t_map *import_map(char *file)
{
    int fd = open(file, O_RDONLY);
    if (fd < 0)
        return NULL;

    t_map *map = malloc(sizeof(t_map));
    if (!map)
        return NULL;

    map->height = count_lines(file);
    map->width  = -1;
    map->z_min  = INT_MAX;
    map->z_max  = INT_MIN;
    map->coords = malloc(sizeof(int *) * map->height);

    int   row = 0;
    char *line;
    while ((line = get_next_line(fd)) != NULL) {
        char **tokens = ft_split(line, " \n");
        free(line);
        if (!tokens[0]) {
            ft_free_tab(tokens);
            break;
        }
        parse_row(tokens, map, row);
        ft_free_tab(tokens);
        row++;
    }
    map->height = row;

    // Flat map edge case: set range to [0, 1] to avoid division by zero in color
    if (map->z_min == map->z_max)
        map->z_max = map->z_min + 1;

    close(fd);
    return map;
}
