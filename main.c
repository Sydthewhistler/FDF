/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:02:45 by scavalli          #+#    #+#             */
/*   Updated: 2025/04/25 12:06:49 by scavalli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"



int main(int argc, char **argv)
{
	t_map	*map;
	
	if (argc != 2)
		return (-1);
	map = import_map(argv[1]);
	if (map == NULL)
	{
		printf("error map");
		return (-1);
	}
	// int x = 0;
	// while(x < map->height)
	// {
	// 	int y = 0;
	// 	while(y < map->width)
	// 	{
	// 		printf("%d ", map->coordonates[x][y]);
	// 		y++;
	// 	}
	// 	x++;
	// 	printf("\n");
	// }

	ft_fdf(map);

	ft_free_int(map);
	free(map);
	return (0);
}