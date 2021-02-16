/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 13:36:08 by tphung            #+#    #+#             */
/*   Updated: 2021/02/16 18:58:45 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

char	**copy_map(char **map)
{
	int		y;
	char	**copy;

	y = 0;
	while (map[y])
		y++;
	copy = (char**)malloc((y + 1) * sizeof(char*));
	if (!copy)
		err_exit(12);
	copy[y] = NULL;
	y = 0;
	while (*map)
	{
		copy[y++] = ft_strdup(*map++);
		if (!copy[y - 1])
			err_exit(12);
	}
	return (copy);
}

int		flood_fill(char **map, int x, int y)
{
	if (map[y][x] == '5' || map[y][x] == '1')
		return (0);
	if (!ft_strchr("02NSWE", map[y][x]))
		return (1);
	else
		map[y][x] = '5';
	return (flood_fill(map, x + 1, y) ||
			flood_fill(map, x - 1, y) ||
			flood_fill(map, x, y + 1) ||
			flood_fill(map, x, y - 1));
}

int		check_map(char **map, t_pers *plr)
{
	char	**copy;
	int		flag;
	int		i;

	flag = 0;
	i = 0;
	copy = copy_map(map);
	if (flood_fill(copy, plr->pos.x, plr->pos.y))
		flag = 1;
	while (copy[i] != 0)
		free(copy[i++]);
	free(copy);
	return (flag);
}
