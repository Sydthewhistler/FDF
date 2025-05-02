/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:25:36 by scavalli          #+#    #+#             */
/*   Updated: 2025/05/02 15:44:34 by scavalli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	translate_map(char **a_map, t_map *map)
{
	int	x;
	int	new_line_size;

	if (map->width < 0)
	{
		new_line_size = 0;
		while (a_map[new_line_size])
			new_line_size++;
		map->width = new_line_size;
	}
	map->coordonates[map->height] = malloc(sizeof(int) * map->width);
	x = 0;
	while (a_map[x])
	{
		map->coordonates[map->height][x] = ft_atoi(a_map[x]);
		x++;
	}
}

int	parameter_initialising(t_map *map, char *file)
{
	int		map_total_height;
	int		test_fd;
	char	*line;

	map->height = 0;
	map->width = -1;
	map_total_height = 0;
	test_fd = open(file, O_RDONLY);
	while (1)
	{
		line = get_next_line(test_fd);
		if (line == NULL)
			break ;
		free(line);
		map_total_height++;
	}
	map->coordonates = malloc(sizeof(int *) * map_total_height);
	close(test_fd);
	return (0);
}

t_map	*import_map(char *file)
{
	int		fd;
	t_map	*map;
	char	**a_map;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 1)
		return (NULL);
	map = malloc(sizeof(t_map));
	parameter_initialising(map, file);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		a_map = ft_split(line, " \n");
		free(line);
		if (!a_map[0])
			break ;
		translate_map(a_map, map);
		map->height++;
		ft_free_tab(a_map);
	}
	close(fd);
	return (map);
}
