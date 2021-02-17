/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:49:52 by tphung            #+#    #+#             */
/*   Updated: 2021/02/17 18:48:00 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cube.h"

void			my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char		*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void			line_put(t_data *img, int x0, int y0, int x1, int y1)
{
	int		deltax = 0;
	int		deltay = 0;
	int		diry = 0;
	int		error = 0;
	int		deltaerr = 0;

	diry = y1 - y0;
	deltax = abs(x1 - x0);
	deltay = abs(y1 - y0);
	deltaerr = (deltay + 1);
	if (diry > 0)
		diry = 1;
	if (diry < 0)
		diry = -1;
	while (x0 < x1)
	{
		my_mlx_pixel_put(img, x0, y0, 0x00FF0000);
		error = error + deltaerr;
		if (error >= (deltax + 1))
		{
			y0 = y0 + diry;
			error = error - deltax;
		}
		x0++;
	}
}

int				key_hook(int keycode, t_vars *vars)
{
	printf("the key_code is %d\n", keycode);
	if (vars)
		return (0);
	else
		return (0);
}

int				mouse_hook(int button, int x, int y, t_vars *vars)
{
	printf("mouse x is %d, y is %d\n", x, y);
	if (vars && button)
		return (0);
	else
		return (0);
}

void			square_put(t_data *img, int x, int y, int len)
{
	int			i;
	int			j;

	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len)
		{
			my_mlx_pixel_put(img, x + i, y + j, 0x00FF0000);
			j++;
		}
		i++;
	}
}

int				drow_map(t_vars *vars)
{
	vars->y = 0;
	while (vars->config->link_map[vars->y] != NULL)
	{
		vars->x = 0;
		while (vars->config->link_map[vars->y][vars->x] != '\0')
		{
			if (vars->config->link_map[vars->y][vars->x] == '1')
				square_put(vars->img, vars->x * 10, vars->y * 10, 10);
			if (ft_strchr("0", vars->config->link_map[vars->y][vars->x]))
				square_put(vars->img, vars->x * 10, vars->y * 10, 10);
			vars->x++;
		}
		vars->y++;
	}
	return (0);
}

int				render_next_frame(t_vars *vars)
{
/*	square_put(vars->img, vars->x, vars->y, 64);
	if (vars->x < vars->config->res_x)
		vars->x += 64;*/
	drow_map(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (1);
}

int				painting(t_conf *config, t_pers *plr)
{
	t_vars		vars;
	t_data		img;

	vars.config = config;
	vars.plr = plr;
	vars.x = 0;
	vars.y = 0;
	vars.x1 = 64;
	vars.y1 = 64;

	vars.img = &img;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, config->res_y, config->res_x,
			"Hello world map!");
	vars.img->img = mlx_new_image(vars.mlx, config->res_y, config->res_x);
	vars.img->addr = mlx_get_data_addr(vars.img->img, &vars.img->bits_per_pixel,
			&vars.img->line_length, &vars.img->endian);

	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);
	return (0);
}

