/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:25:21 by tphung            #+#    #+#             */
/*   Updated: 2021/04/24 15:34:43 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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

int	win_close(int keycode, t_vars *vars)
{
	if (keycode == 53)
		mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
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
