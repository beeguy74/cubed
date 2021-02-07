/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 13:36:08 by tphung            #+#    #+#             */
/*   Updated: 2021/02/07 14:56:43 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

int		flood_fill(char **map, int x, int y)
{
	int flag;

	flag = 0;
	if (map[y] == NULL)
		return (1);
	else if (map[y][x] == '\0')
		return (1);
	else if (map[y][x] != '0' && map[y][x] != 'N')
		return (0);
	map[y][x] = '5';
	if (x != 0 && y != 0)
	{
		flag += flood_fill(map, x + 1, y);
		flag += flood_fill(map, x - 1, y);
		flag += flood_fill(map, x, y + 1);
		flag += flood_fill(map, x, y - 1);
	}
	return (flag);
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
