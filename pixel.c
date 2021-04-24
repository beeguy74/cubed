/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:49:52 by tphung            #+#    #+#             */
/*   Updated: 2021/04/24 15:36:02 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cube.h"

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
