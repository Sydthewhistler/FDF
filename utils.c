/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 15:44:08 by scavalli          #+#    #+#             */
/*   Updated: 2025/04/23 18:53:22 by scavalli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_free_tab(char **str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
void	ft_free_int(t_map *map)
{
	int	i;

	i = 0;
	while(i < map->height)
	{
		free(map->coordonates[i]);
		i++;
	}
	free(map->coordonates);
}
