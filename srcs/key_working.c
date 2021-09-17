/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_working.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:28:35 by tphung            #+#    #+#             */
/*   Updated: 2021/04/24 15:30:52 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	plr_move(int keycode, t_vars *vars)
{
	double	m_speed;
	char	**map;

	m_speed = 0.2;
	map = vars->config->map;
	if (keycode == 125 || keycode == 1)
	{
		if (map[(int)(vars->plr->pos.y)][(int)(vars->plr->pos.x - \
									vars->plr->sight.x * m_speed)] != '1')
			vars->plr->pos.x -= vars->plr->sight.x * m_speed;
		if (map[(int)(vars->plr->pos.y - vars->plr->sight.y * \
								m_speed)][(int)(vars->plr->pos.x)] != '1')
			vars->plr->pos.y -= vars->plr->sight.y * m_speed;
	}
	if (keycode == 126 || keycode == 13)
	{
		if (map[(int)(vars->plr->pos.y)][(int)(vars->plr->pos.x + \
							vars->plr->sight.x * m_speed)] != '1')
			vars->plr->pos.x += vars->plr->sight.x * m_speed;
		if (map[(int)(vars->plr->pos.y + vars->plr->sight.y * \
						m_speed)][(int)(vars->plr->pos.x)] != '1')
			vars->plr->pos.y += vars->plr->sight.y * m_speed;
	}
	return (0);
}

/*rotate to the right*/
/*both camera direction and camera plane must be rotated*/
/*rotate to the left*/
int	plr_rotate(int keycode, t_pers *plr)
{
	double	old_sight_x;
	double	old_cam_x;
	double	speed;

	speed = 0.1;
	old_cam_x = plr->cam.x;
	old_sight_x = plr->sight.x;
	if (keycode == 123)
	{
		plr->sight.x = plr->sight.x * cos(-speed) - plr->sight.y * sin(-speed);
		plr->sight.y = old_sight_x * sin(-speed) + plr->sight.y * cos(-speed);
		plr->cam.x = plr->cam.x * cos(-speed) - plr->cam.y * sin(-speed);
		plr->cam.y = old_cam_x * sin(-speed) + plr->cam.y * cos(-speed);
	}
	if (keycode == 124)
	{
		plr->sight.x = plr->sight.x * cos(speed) - plr->sight.y * sin(speed);
		plr->sight.y = old_sight_x * sin(speed) + plr->sight.y * cos(speed);
		plr->cam.x = plr->cam.x * cos(speed) - plr->cam.y * sin(speed);
		plr->cam.y = old_cam_x * sin(speed) + plr->cam.y * cos(speed);
	}
	return (0);
}

void	plr_left(t_vars *vars)
{
	double	x;
	double	y;
	double	m_speed;
	char	**map;

	m_speed = 0.2;
	map = vars->config->map;
	x = vars->plr->pos.x + vars->plr->sight.y * m_speed;
	y = vars->plr->pos.y - vars->plr->sight.x * m_speed;
	if (!ft_strchr("1", map[(int)vars->plr->pos.y][(int)x]))
		vars->plr->pos.x = x;
	if (!ft_strchr("1", map[(int)y][(int)vars->plr->pos.x]))
		vars->plr->pos.y = y;
}

void	plr_right(t_vars *vars)
{
	double	x;
	double	y;
	double	m_speed;
	char	**map;

	m_speed = 0.2;
	map = vars->config->map;
	x = vars->plr->pos.x - vars->plr->sight.y * m_speed;
	y = vars->plr->pos.y + vars->plr->sight.x * m_speed;
	if (!ft_strchr("1", map[(int)vars->plr->pos.y][(int)x]))
		vars->plr->pos.x = x;
	if (!ft_strchr("1", map[(int)y][(int)vars->plr->pos.x]))
		vars->plr->pos.y = y;
}

int	key_events(int keycode, t_vars *vars)
{
	if (keycode == 125 || keycode == 126 || keycode == 13 || keycode == 1)
		plr_move(keycode, vars);
	if (keycode == 0)
		plr_left(vars);
	if (keycode == 2)
		plr_right(vars);
	if (keycode > 122 && keycode < 125)
		plr_rotate(keycode, vars->plr);
	if (keycode == 53)
		win_close(keycode, vars);
	return (0);
}
