/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:49:52 by tphung            #+#    #+#             */
/*   Updated: 2021/04/24 12:35:39 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cube.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, \
		unsigned int color)
{
	char		*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	square_put(t_data *img, t_point *point, int len, int color)
{
	int			i;
	int			j;

	i = 0;
	if (len < 6)
		return ;
	while (i < len)
	{
		j = 0;
		while (j < len)
		{
			my_mlx_pixel_put(img, point->x * len + i, \
					point->y * len + j, color);
			j++;
		}
		i++;
	}
}

int	drow_map(t_vars *vars)
{
	t_point	point;

	point.y = 0;
	if (vars->config->scale < 6)
		return (0);
	while (vars->config->link_map[point.y] != NULL)
	{
		point.x = 0;
		while (vars->config->link_map[point.y][point.x] != '\0')
		{
			if (vars->config->link_map[point.y][point.x] == '1')
				square_put(vars->img, &point, vars->config->scale, 0x00FF0000);
			if (ft_strchr("02SNWE", vars->config->link_map[point.y][point.x]))
				square_put(vars->img, &point, vars->config->scale, 0x0000FF00);
			point.x++;
		}
		point.y++;
	}
	return (0);
}

int	drow_plr(t_vars *vars)
{
	t_point	point;

	if (vars->config->scale < 6)
		return (0);
	point.y = (int)(vars->plr->pos.y * vars->config->scale);
	point.x = (int)(vars->plr->pos.x * vars->config->scale);
	my_mlx_pixel_put(vars->img, point.x, point.y, 0x000000FF);
	return (0);
}

void	floor_ceiling(t_vars *vars)
{
	int		i;
	int		end;
	int		*img;

	i = 0;
	img = (int *)vars->img->addr;
	end = vars->img->line_length / 4 * vars->config->res_y / 2;
	while (i < end)
	{
		img[i] = vars->config->ceil_col;
		i++;
	}
	end *= 2;
	while (i < end)
	{
		img[i] = vars->config->floor_col;
		i++;
	}
}

int	render_next_frame(t_vars *vars)
{
	floor_ceiling(vars);
	raycast(vars);
	drow_map(vars);
	drow_plr(vars);
	if (vars->config->s_shot_flag == 1)
	{
		ft_bmp(vars->img, vars->config, "screenshot.bmp");
		err_exit(111);
	}
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	mlx_do_sync(vars->mlx);
	return (1);
}

int	win_close(int keycode, t_vars *vars)
{
	if (keycode == 53)
		mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

int	plr_move(int keycode, t_vars *vars)
{
	double	m_speed;
	char	**map;

	m_speed = 0.2;
	map = vars->config->map;
	if (keycode == 125)
	{
		if (map[(int)(vars->plr->pos.y)][(int)(vars->plr->pos.x - \
									vars->plr->sight.x * m_speed)] != '1')
			vars->plr->pos.x -= vars->plr->sight.x * m_speed;
		if (map[(int)(vars->plr->pos.y - vars->plr->sight.y * \
								m_speed)][(int)(vars->plr->pos.x)] != '1')
			vars->plr->pos.y -= vars->plr->sight.y * m_speed;
	}
	if (keycode == 126)
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

int	key_events(int keycode, t_vars *vars)
{
	if (keycode > 124 && keycode < 127)
		plr_move(keycode, vars);
	if (keycode > 122 && keycode < 125)
		plr_rotate(keycode, vars->plr);
	if (keycode == 53)
		win_close(keycode, vars);
	return (0);
}

void	do_screen_size(void *mlx, t_conf *config)
{
	int	screen_x;
	int	screen_y;

	screen_x = 0;
	screen_y = 0;
	mlx_get_screen_size(mlx, &screen_x, &screen_y);
	if (screen_x < config->res_x)
		config->res_x = screen_x;
	if (screen_y < config->res_y)
		config->res_y = screen_y;
	config->scale = (config->res_x + config->res_y) / 100;
	if (config->res_x < 1 || config->res_y < 1)
		err_exit(11);
	if (config->scale >= 6 && config->scale <= 10)
		config->scale = 6;
	else if (config->scale < 6)
		config->scale = 0;
	else
		config->scale = 10;
}

int	painting(t_conf *config, t_pers *plr)
{
	t_vars		vars;
	t_data		img;

	vars = (t_vars){.config = config, .plr = plr, .img = &img,
		.mlx = mlx_init()};
	errno = 0;
	do_screen_size(vars.mlx, vars.config);
	if (config->s_shot_flag == 0)
		vars.win = mlx_new_window(vars.mlx, config->res_x, config->res_y,
				"Hello world map!");
	vars.img->img = mlx_new_image(vars.mlx, config->res_x, config->res_y);
	vars.img->addr = mlx_get_data_addr(vars.img->img, &vars.img->bits_per_pixel,
			&vars.img->line_length, &vars.img->endian);
	text_collect(&vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	if (config->s_shot_flag == 0)
	{
		mlx_hook(vars.win, 2, 1l << 0, key_events, &vars);
		mlx_hook(vars.win, 17, 0, win_close, NULL);
	}
	mlx_loop(vars.mlx);
	return (0);
}
