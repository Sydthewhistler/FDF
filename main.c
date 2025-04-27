/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:02:45 by scavalli          #+#    #+#             */
/*   Updated: 2025/04/27 16:50:02 by scavalli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"



int main(int argc, char **argv)
{
	t_data	data;
	
	if (argc != 2)
		return (-1);
	data.map = import_map(argv[1]);
	if (data.map == NULL)
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

	ft_fdf(&data);

	ft_free_int(data.map);
	free(data.map);
	return (0);
}