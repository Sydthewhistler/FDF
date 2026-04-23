#include "header.h"

void ft_free_tab(char **str)
{
    for (int i = 0; str[i]; i++)
        free(str[i]);
    free(str);
}

void ft_free_int(t_map *map)
{
    for (int i = 0; i < map->height; i++)
        free(map->coords[i]);
    free(map->coords);
}
