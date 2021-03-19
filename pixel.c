/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:49:52 by tphung            #+#    #+#             */
/*   Updated: 2021/03/19 20:00:38 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cube.h"

void			my_mlx_pixel_put(t_data *data, int x, int y,\
		unsigned int color)
{
	char		*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void			line_put(t_data *img, t_point start, t_point end,\
		unsigned int color)
{
	int		deltax = 0;
	int		deltay = 0;
	int		diry = 0;
	int		error = 0;
	int		deltaerr = 0;

	diry = end.y - start.y;
	deltax = abs(end.x - start.x);
	deltay = abs(end.y - start.y);
	deltaerr = (deltay + 1);
	if (diry > 0)
		diry = 1;
	if (diry < 0)
		diry = -1;
	while (start.x < end.x)
	{
		my_mlx_pixel_put(img, start.x, start.y, color);
		error = error + deltaerr;
		if (error >= (deltax + 1))
		{
			start.y = start.y + diry;
			error = error - deltax;
		}
		start.x++;
	}
}

void			square_put(t_data *img, t_point *point, int len, int color)
{
	int			i;
	int			j;

	i = 0;
	len = (len > 0) ? len : 1;
	while (i < len)
	{
		j = 0;
		while (j < len)
		{
			my_mlx_pixel_put(img, point->x * SCALE + i,
					point->y * SCALE + j, color);
			j++;
		}
		i++;
	}
}

int				drow_map(t_vars *vars)
{
	t_point	point;

	point.y = 0;
	while (vars->config->link_map[point.y] != NULL)
	{
		point.x = 0;
		while (vars->config->link_map[point.y][point.x] != '\0')
		{
			if (vars->config->link_map[point.y][point.x] == '1')
				square_put(vars->img, &point, 10, 0x00FF0000);
			if (ft_strchr("02SNWE", vars->config->link_map[point.y][point.x]))
				square_put(vars->img, &point, 10, 0x0000FF00);
			point.x++;
		}
		point.y++;
	}
	return (0);
}

int				drow_plr(t_vars *vars)
{
	t_point	point;

	point.y = (int)(vars->plr->pos.y * SCALE);
	point.x = (int)(vars->plr->pos.x * SCALE);
	my_mlx_pixel_put(vars->img, point.x, point.y, 0x000000FF);
	return (0);
}

void			floor_ceiling(t_vars *vars)
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

int				render_next_frame(t_vars *vars)
{
	floor_ceiling(vars);
	raycast(vars);
	drow_map(vars);
	drow_plr(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	mlx_do_sync(vars->mlx);
	return (1);
}

int				win_close(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
	return (0);
}

int				plr_move(int keycode, t_vars *vars)
{
    //move forward if no wall in front of you
	double	m_speed;
	char	**map;
	
	m_speed = 0.2;
	map = vars->config->map;
    //move backwards if no wall behind you
	if (keycode == 125)
    {
      if (map[(int)(vars->plr->pos.y)][(int)(vars->plr->pos.x -\
				  vars->plr->sight.x * m_speed)] != '1')
		  vars->plr->pos.x -= vars->plr->sight.x * m_speed;
      if (map[(int)(vars->plr->pos.y - vars->plr->sight.y *\
				  m_speed)][(int)(vars->plr->pos.x)] != '1')
		  vars->plr->pos.y -= vars->plr->sight.y * m_speed;
	}
    //move forward if no wall behind you
	if (keycode == 126)
    {
      if (map[(int)(vars->plr->pos.y)][(int)(vars->plr->pos.x +\
				  vars->plr->sight.x * m_speed)] != '1')
		  vars->plr->pos.x += vars->plr->sight.x * m_speed;
      if (map[(int)(vars->plr->pos.y + vars->plr->sight.y *\
				  m_speed)][(int)(vars->plr->pos.x)] != '1')
		  vars->plr->pos.y += vars->plr->sight.y * m_speed;
    }
	return (0);
}

int				plr_rotate(int keycode, t_pers *plr)
{
	double	old_sight_x;
	double	old_cam_x;
	double	speed;

	speed = 0.1;
	old_cam_x = plr->cam.x;
	old_sight_x = plr->sight.x;
    //rotate to the right
    if (keycode == 123)
    {
      //both camera direction and camera plane must be rotated
      plr->sight.x = plr->sight.x * cos(-speed) - plr->sight.y * sin(-speed);
      plr->sight.y = old_sight_x * sin(-speed) + plr->sight.y * cos(-speed);
      plr->cam.x = plr->cam.x * cos(-speed) - plr->cam.y * sin(-speed);
      plr->cam.y = old_cam_x * sin(-speed) + plr->cam.y * cos(-speed);
	}
    //rotate to the left
    if (keycode == 124)
    {
      //both camera direction and camera plane must be rotated
      plr->sight.x = plr->sight.x * cos(speed) - plr->sight.y * sin(speed);
      plr->sight.y = old_sight_x * sin(speed) + plr->sight.y * cos(speed);
      plr->cam.x = plr->cam.x * cos(speed) - plr->cam.y * sin(speed);
      plr->cam.y = old_cam_x * sin(speed) + plr->cam.y * cos(speed);
    }
	return (0);
}

int				key_events(int keycode, t_vars *vars)
{
	if (keycode > 124 && keycode < 127)
		plr_move(keycode, vars);
	if (keycode > 122 && keycode < 125)
		plr_rotate(keycode, vars->plr);
	if (keycode == 53)
		win_close(vars);
	return (0);
}

int				painting(t_conf *config, t_pers *plr)
{
	t_vars		vars;
	t_data		img;
	//int			width;
	//int			height;
	//void		*text_img;

	vars = (t_vars){.config = config, .plr = plr, .img = &img,
		.mlx = mlx_init()};
	vars.win = mlx_new_window(vars.mlx, config->res_x, config->res_y,
			"Hello world map!");
	vars.img->img = mlx_new_image(vars.mlx, config->res_x, config->res_y);
	vars.img->addr = mlx_get_data_addr(vars.img->img, &vars.img->bits_per_pixel,
			&vars.img->line_length, &vars.img->endian);


	//text_img = mlx_xpm_file_to_image(vars.mlx, config->no, &width, &height);
	//vars.file = text_img;

	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_hook(vars.win, 2, 1l<<0, key_events, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
