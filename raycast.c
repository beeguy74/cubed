/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 11:27:20 by tphung            #+#    #+#             */
/*   Updated: 2021/03/23 18:27:28 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cube.h"

int		ray_init_calc(t_rays *ray, t_pers *plr, double x_cam)
{
	t_vect dir;
	t_vect delta;

	ray->hit = 0;
	ray->map.x = (int)plr->pos.x;
	ray->map.y = (int)plr->pos.y;
	dir.x = plr->sight.x + plr->cam.x * x_cam;
	dir.y = plr->sight.y + plr->cam.y * x_cam;
	ray->dir = dir;
	//length of ray from current position to next x or y-side
	if (dir.x == 0.)
		delta.x = 1.;
	else
		delta.x = fabs(1 / dir.x);
	if (dir.y == 0.)
		delta.y = 1;
	else
		delta.y = fabs(1 / dir.y);
	ray->delta = delta;
	return (0);
}

int		ray_side_calc(t_rays *ray, t_pers *plr)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side.x = (plr->pos.x - ray->map.x) * ray->delta.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side.x = (-plr->pos.x + ray->map.x + 1.) * ray->delta.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side.y = (plr->pos.y - ray->map.y) * ray->delta.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side.y = (-plr->pos.y + ray->map.y + 1.) * ray->delta.y;
	}
	return (0);
}

int		digital_diff_analys(t_rays *ray, char **map)
{
	int		i;

	while (ray->hit == 0)
	{
		i = 0;
		//jump to next map square, OR in x-direction, OR in y-direction
		if (ray->side.x < ray->side.y)
		{
			ray->side.x += ray->delta.x;
			ray->map.x += ray->step.x;
			ray->hit_side = 0;
		}
		else
		{
			ray->side.y += ray->delta.y;
			ray->map.y += ray->step.y;
			ray->hit_side = 1;
		}
		//Check if ray has hit a wall
		if (map[ray->map.y][ray->map.x] == '1')
		{
			ray->hit = 1;
		}
	}
	return (0);
}

int		vert_line_calc(t_rays *ray, t_pers *plr, int res_y)
{
	double	wall_dist;
	int		line_height;

	if (ray->hit_side == 0)
		wall_dist = (ray->map.x - plr->pos.x +\
				(1 - ray->step.x) / 2) / ray->dir.x;
	else
		wall_dist = (ray->map.y - plr->pos.y +\
				(2 - ray->step.y) / 2) / ray->dir.y;
	//Calculate height of line to draw on screen
	ray->wall_dist = wall_dist;
	line_height = (int)(res_y / wall_dist);
	ray->line_height = line_height;
	//calculate lowest and highest pixel to fill in current stripe
	ray->line_start.y = -line_height / 2 + res_y / 2;
	if (ray->line_start.y < 0)
		ray->line_start.y = 0;
	ray->line_end.y = line_height / 2 + res_y / 2;
	if (ray->line_end.y >= res_y)
		ray->line_end.y = res_y - 1;
	return (0);
}

t_text	*ch_text(t_rays *ray, t_files *file)
{
	if (ray->hit_side == 1)
	{
		if (ray->dir.y < 0)
			return (file->n_text);
		return (file->s_text);
	}
	else
	{
		if (ray->dir.x < 0)
			return (file->w_text);
		return (file->e_text);
	}
}

void	calc_x(t_calc *calc, t_vars *vars, t_text *text)
{
	if (vars->ray->hit_side == 0)
		calc->wall_x = vars->plr->pos.y + vars->ray->wall_dist *
															vars->ray->dir.y;
	else
		calc->wall_x = vars->plr->pos.x + vars->ray->wall_dist *
															vars->ray->dir.x;
	calc->wall_x -= floor((calc->wall_x));
	//x coordinate on the texture
	calc->tex_x = (int)(calc->wall_x * (double)(text->width));
	if (vars->ray->hit_side == 0 && vars->ray->dir.x > 0)
		calc->tex_x = text->width - calc->tex_x - 1;
	if (vars->ray->hit_side == 1 && vars->ray->dir.y < 0)
		calc->tex_x = text->width - calc->tex_x - 1;
}

int		text_calc(t_vars *vars, int x)
{
	t_calc	calc;
	t_text	*text;
	int		*img;
	int		y;

	y = vars->ray->line_start.y;
	text = ch_text(vars->ray, vars->file);
	img = (int*)text->img->addr;
	calc_x(&calc, vars, text);
	// How much to increase the texture coordinate per screen pixel
	calc.step = 1.0 * text->height / vars->ray->line_height;
	// Starting texture coordinate
	calc.tex_pos = (vars->ray->line_start.y - vars->config->res_y / 2
									+ vars->ray->line_height / 2) * calc.step;
	while (y < vars->ray->line_end.y)
	{
		calc.tex_y = (int)calc.tex_pos & (text->height - 1);
		calc.tex_pos += calc.step;
		calc.color = img[text->width * calc.tex_y + calc.tex_x];
		if (vars->ray->hit_side == 0)
			calc.color = (calc.color >> 1) & 8355711;
		my_mlx_pixel_put(vars->img, x, y++, calc.color);
	}
	return (0);
}

int		raycast(t_vars *vars)
{
	int				i;
	double			x_cam;
	double			z_buffer[vars->config->res_x];
	t_rays			ray;

	i = 0;
	vars->ray = &ray;
	while (i < vars->config->res_x)
	{
		x_cam = 2. * i / vars->config->res_x - 1;
		ray_init_calc(&ray, vars->plr, x_cam);
		ray_side_calc(&ray, vars->plr);
		digital_diff_analys(&ray, vars->config->link_map);
		ray.line_start.x = i;
		ray.line_end.x = i;
		vert_line_calc(&ray, vars->plr, vars->config->res_y);
		z_buffer[i] = ray.wall_dist;
		text_calc(vars, i);
		i++;
	}
	return (0);
}
