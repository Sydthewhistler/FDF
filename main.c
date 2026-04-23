#include "header.h"

int main(int argc, char **argv)
{
    if (argc != 2) {
        ft_printf("Usage: %s <map_file>\n", argv[0]);
        return 1;
    }

    t_data data;
    data.map = import_map(argv[1]);
    if (!data.map) {
        ft_printf("Error: could not load map '%s'\n", argv[1]);
        return 1;
    }

    ft_fdf(&data);

    mlx_destroy_display(data.mlx);
    free(data.mlx);
    ft_free_int(data.map);
    free(data.map);
    return 0;
}
