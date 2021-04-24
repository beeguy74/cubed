/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:50:17 by tphung            #+#    #+#             */
/*   Updated: 2021/04/24 17:54:18 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

void	get_dir(char c, t_pers *plr)
{
	plr->sight.x = 0;
	plr->cam.x = 1;
	plr->cam.y = 0;
	if (c == 'N')
		plr->sight.y = -1;
	else if (c == 'S')
	{
		plr->sight.y = 1;
		plr->cam.x = -1;
	}
	else
	{
		plr->sight.y = 0;
		plr->cam.x = 0;
		plr->cam.y = 1;
		if (c == 'W')
		{
			plr->sight.x = -1;
			plr->cam.y = -1;
		}
		else if (c == 'E')
			plr->sight.x = 1;
	}
}

int	check_pos(t_pers *plr, int x, int y)
{
	if (plr->pos.x == 0.5 && plr->pos.y == 0.5)
	{
		plr->pos.x += x;
		plr->pos.y += y;
		return (1);
	}
	return (0);
}

int	plr_position(t_pers *plr, char **map)
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
					get_dir(map[y][x], plr);
				else
					return (1);
			}
			x++;
		}
		y++;
	}
	if (plr->pos.x == 0.5 || plr->pos.y == 0.5)
		err_exit(11);
	return (0);
}

int	find_plr(t_pers *plr, char **map)
{
	double	old_sight_x;
	double	old_cam_x;

	plr->pos.x = 0.5;
	plr->pos.y = 0.5;
	if (plr_position(plr, map))
		err_exit(11);
	old_cam_x = plr->cam.x;
	old_sight_x = plr->sight.x;
	plr->sight.x = plr->sight.x * cos(-0.001) \
					- plr->sight.y * sin(-0.001);
	plr->sight.y = old_sight_x * sin(-0.001) \
					+ plr->sight.y * cos(-0.001);
	plr->cam.x = plr->cam.x * cos(-0.001) \
					- plr->cam.y * sin(-0.001);
	plr->cam.y = old_cam_x * sin(-0.001) \
					+ plr->cam.y * cos(-0.001);
	return (0);
}
