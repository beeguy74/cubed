/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:50:17 by tphung            #+#    #+#             */
/*   Updated: 2021/03/04 17:20:48 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

t_vect	get_dir(char c)
{
	t_vect	sight;

	sight.x = 0;
	if (c == 'N')
		sight.y = -1;
	else if (c == 'S')
		sight.y = 1;
	else
	{
		sight.y = 0;
		if (c == 'W')
			sight.x = -1;
		else if (c == 'E')
			sight.x = 1;
	}
	return (sight);
}

int		check_pos(t_pers *plr, int x, int y)
{
	if (plr->pos.x == 0 && plr->pos.y == 0)
	{
		plr->pos.x = x;
		plr->pos.y = y;
		return (1);
	}
	return (0);
}

int		plr_position(t_pers *plr, char **map)
{
	int		x;
	int		y;

	y = 0;
	while (map[y] != 0)
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (ft_strchr("NSWE", map[y][x]))
			{
				if (check_pos(plr, x, y))
					plr->sight = get_dir(map[y][x]);
				else
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

void	pers_init(t_pers *plr)
{
	t_vect	cam;
	t_vect	pos;

	cam.x = 1;
	cam.y = 0;
	pos.x = 0;
	pos.y = 0;
	plr->pos = pos;
	plr->cam = cam;
	return ;
}

int		find_plr(t_pers *plr, char **map)
{
	pers_init(plr);
	if (plr_position(plr, map))
		err_exit(12);
	return (0);
}
