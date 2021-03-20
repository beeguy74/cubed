/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 11:27:20 by tphung            #+#    #+#             */
/*   Updated: 2021/03/20 19:45:32 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cube.h"

int		ray_init_calc(t_rays *ray, t_pers *plr, double x_cam)
{
	t_vect dir;
	t_vect delta;
	//t_vect side;
	
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
	if(ray->dir.x < 0)
		{
			ray->step.x = -1;
			ray->side.x = (plr->pos.x - ray->map.x) * ray->delta.x;
		}
		else
		{
			ray->step.x = 1;
			ray->side.x = (-plr->pos.x + ray->map.x + 1.) * ray->delta.x;
		}
		if(ray->dir.y < 0)
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
		if(ray->side.x < ray->side.y)
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
	if(ray->line_start.y < 0)
		ray->line_start.y = 0;
	ray->line_end.y = line_height / 2 + res_y / 2;
	if(ray->line_end.y >= res_y)
		ray->line_end.y = res_y - 1;
	return (0);
}

/*void	ver_line_put(t_data *img, t_point start, t_point end, unsigned int col)
{
	while (start.y < end.y)
	{
		my_mlx_pixel_put(img, start.x, start.y, col);
		start.y++;
	}
}
*/

int		text_calc(t_vars *vars, int x)
{		
	double	wall_x; //where exactly the wall was hit
	double	step; // How much to increase the texture coordinate per screen pixel
	double	tex_pos; // Starting texture coordinate
	int		tex_x; //x coordinate on the texture
	int		color;
	int		*img;

	img = (int*)vars->file->n_text->img->addr;

	if (vars->ray->hit_side == 0)
		wall_x = vars->plr->pos.y + vars->ray->wall_dist * vars->ray->dir.y;
	else
		wall_x = vars->plr->pos.x + vars->ray->wall_dist * vars->ray->dir.x;
	wall_x -= round((wall_x));

	//x coordinate on the texture
	tex_x = (int)wall_x * (double)(vars->file->n_text->width);
	if(vars->ray->hit_side == 0 && vars->ray->dir.x > 0)
		tex_x = vars->file->n_text->width - tex_x - 1;
	if(vars->ray->hit_side == 1 && vars->ray->dir.y < 0)
		tex_x = vars->file->n_text->width - tex_x - 1;
	// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
	// How much to increase the texture coordinate per screen pixel
	step = 1.0 * vars->file->n_text->height / vars->ray->line_height;
	// Starting texture coordinate
	tex_pos = (vars->ray->line_start.y - vars->config->res_y / 2\
										+ vars->ray->line_height / 2) * step;
	for(int y = vars->ray->line_start.y; y < vars->ray->line_end.y; y++)
	{
		// Cast the texture coordinate to integer, and mask with (vars->file->n_text->height - 1) in case of overflow
		int texY = (int)tex_pos & (vars->file->n_text->height - 1);
		tex_pos += step;

		//Uint32
		//color = texture[texNum][vars->file->n_text->height * texY + tex_x];
		color = img[vars->file->n_text->height * texY + tex_x];
		my_mlx_pixel_put(vars->img, x, y, color);

		//make color darker for y-vars->ray->hit_sides: R, G and B byte each divided through two with a "shift" and an "and"
		/*if(vars->ray->hit_side == 1)
			color = (color >> 1) & 8355711;*/
		//buffer[y][x] = color;

	}

	/*drawBuffer(buffer[0]);
	for(int y = 0; y < h; y++) for(int x = 0; x < w; x++) buffer[y][x] = 0; //clear the buffer instead of cls()
	*/
	return (0);
}

int		raycast(t_vars *vars)
{
	int				i;
	unsigned int	wall_col;
	double			x_cam;
	t_rays			ray;

	i = 0;
	vars->ray = &ray;
	while (i < vars->config->res_x)
	{
		x_cam = 2. * i / vars->config->res_x - 1;
		//which box of the map we're in
		//length of ray from current position to next x or y-side
		//length of ray from one x or y-side to next x or y-side
		ray_init_calc(&ray, vars->plr, x_cam);
		//what direction to step in x or y-direction (either +1 or -1)
		//calculate step and initial sideDist
		ray_side_calc(&ray, vars->plr);
		//perform DDA
		digital_diff_analys(&ray, vars->config->link_map);
		//Calculate distance projected on camera direction
		//(Euclidean distance will give fisheye effect!)
		//Calculate height of line to draw on screen
		//calculate lowest and highest pixel to fill in current stripe
		ray.line_start.x = i;
		ray.line_end.x = i;
		vert_line_calc(&ray, vars->plr, vars->config->res_y);
		//give x and y sides different brightness
		wall_col = 0x004291FF;
		if(ray.hit_side == 1)
			wall_col = wall_col / 2;
		//draw the pixels of the stripe as a vertical line
		//ver_line_put(vars->img, ray.line_start, ray.line_end, wall_col);
		
		//texturing calculations
		//int texNum = worldMap[mapX][mapY] - 1;
		////1 subtracted from it so that texture 0 can be used!

		//calculate value of wallX
		text_calc(vars, i);

		i++;
	}
	return (0);
}
