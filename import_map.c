/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scavalli <scavalli@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:25:36 by scavalli          #+#    #+#             */
/*   Updated: 2025/04/22 18:04:58 by scavalli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int *translate_map(char **a_map, t_coordonates *map, int *i, int y)
{
	int	j;
	t_coordonates *new_map;
	
	j = 0;
	while(a_map[j])
		j++;
	new_map = malloc(sizeof(int) * (j + *i + 1));
	j = 0;
	while (j < i)
	{
		new_map[j] = map[j];
		j++;
	}
	j = 0;
	while (a_map[j])
	{
		new_map[*i].h = ft_atoi(a_map[j]);
		new_map[*i].x = j;
		new_map[*i].y = y;
		j++;
		(*i)++;
	}
	free(map);
	return (new_map);
}

void	ft_free(char **str)
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

t_coordonates import_map(char *file)
{
	int fd;
	t_coordonates *map;
	char **a_map;
	int	i;
	int	y;

	fd = open(file, O_RDONLY);
	if(fd < 1)
		return (NULL);
	i = 0;
	y = -1;
	while(1)
	{
		a_map = ft_split(get_next_line(fd), " \n");
		if (a_map[0] == NULL)
			break ;
		y++;
		map = translate_map(a_map, &map, &i, &y);
		ft_free(a_map);
	}
	return (map);
}
