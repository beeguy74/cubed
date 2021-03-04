/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 15:49:52 by tphung            #+#    #+#             */
/*   Updated: 2021/03/04 17:23:14 by tphung           ###   ########.fr       */
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

/*int				key_hook(int keycode, t_vars *vars)
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
*/
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

	point.y = (int)(vars->plr->pos.y * SCALE) + SCALE / 2;
	point.x = (int)(vars->plr->pos.x * SCALE) + SCALE / 2;
	my_mlx_pixel_put(vars->img, point.x, point.y, 0x000000FF);
	return (0);
}

int				render_next_frame(t_vars *vars)
{
	drow_map(vars);
	drow_plr(vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
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
	if (keycode == 126)
	{
		vars->plr->pos.y -= 0.2;
	}
	if (keycode == 125)
	{
		vars->plr->pos.y += 0.2;
	}
	return (0);
}

int				key_events(int keycode, t_vars *vars)
{
	if (keycode > 122 && keycode < 127)
		plr_move(keycode, vars);
	if (keycode == 53)
		win_close(vars);
	return (0);
}

int				painting(t_conf *config, t_pers *plr)
{
	t_vars		vars;
	t_data		img;

	vars = (t_vars){.config = config, .plr = plr, .img = &img,
		.mlx = mlx_init()};
	vars.win = mlx_new_window(vars.mlx, config->res_x, config->res_y,
			"Hello world map!");
	vars.img->img = mlx_new_image(vars.mlx, config->res_x, config->res_y);
	vars.img->addr = mlx_get_data_addr(vars.img->img, &vars.img->bits_per_pixel,
			&vars.img->line_length, &vars.img->endian);

	//mlx_key_hook(vars.win, key_hook, &vars);
	//mlx_hook(vars.win, 2, 1L<<0, win_close, &vars);
	mlx_hook(vars.win, 2, 1l<<0, key_events, &vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
