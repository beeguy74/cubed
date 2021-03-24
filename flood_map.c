/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/07 13:36:08 by tphung            #+#    #+#             */
/*   Updated: 2021/03/24 17:14:50 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

int		count_sprite(char **map)
{
	int	i;
	int	j;
	int	res;

	i = 0;
	res = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '2')
				res++;
			j++;
		}
		i++;
	}
	return (res);
}

void	find_sprites(t_conf *config)
{
	t_sprite	*tmp;
	int			i;
	int			j;

	config->sprite_num = count_sprite(config->map);
	config->sprite_mas = malloc(sizeof(t_sprite *) * config->sprite_num);
	i = 0;
	while (config->map[i])
	{
		j = 0;
		while (config->map[i][j])
		{
			if (config->map[i][j] == '2')
			{
				if (!(tmp = malloc(sizeof(t_sprite))))
					err_exit(0);
				tmp->pos_y = i;
				tmp->pos_x = j;
				*config->sprite_mas++ = tmp;
			}
			j++;
		}
		i++;
	}
	config->sprite_mas -= config->sprite_num;
}

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
