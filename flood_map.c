/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 13:36:08 by tphung            #+#    #+#             */
/*   Updated: 2021/02/16 14:04:08 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

int		flood_fill(char **map, int x, int y)
{
	if (map[y][x] == '5' || map[y][x] == '1')
		return (0);
	if (!ft_strchr("02", map[y][x]))
		return (1);
	else
		map[y][x] = '5';
	return (flood_fill(map, x + 1, y) || 
			flood_fill(map, x - 1, y) ||
			flood_fill(map, x, y + 1) ||
			flood_fill(map, x, y - 1));
}

int		check_map(char **map)
{
	int x;
	int y;
	int flag;

	y = 0;
	flag = 0;
	while (map[y] != 0)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == 'N')
			{
				printf("\nFIND N\n x : %i y : %i \n", x, y);
				map[y][x] = 0;
				flag = flood_fill(map, x, y);
				break ;
			}
			x++;
		}
		y++;
	}
	printf("\nFLAG: %i\n", flag);
	return (0);
}
