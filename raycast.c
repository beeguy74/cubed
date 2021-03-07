/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 11:27:20 by tphung            #+#    #+#             */
/*   Updated: 2021/03/07 17:17:53 by tphung           ###   ########.fr       */
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

int		digital_diff_analys(t_rays *ray)//, char **map)
{
	printf("posX= %d posY= %d", ray->map.x, ray->map.y);
	/*
	while (ray->hit == 0 && ray->map.y < 1920)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if(ray->side.x < ray->side.y)
			{
				ray->side.x += ray->delta.x;
				ray->map.x += ray->step.x;
				ray->hit_side = 0;
				//sideDistX += deltaDistX;
				//mapX += stepX;
				//side = 0;
			}
			else
			{
				ray->side.y += ray->delta.y;
				ray->map.y += ray->step.y;
				ray->hit_side = 1;
				//sideDistY += deltaDistY;
				//mapY += stepY;
				//side = 1;
			}
			//Check if ray has hit a wall
			//if(worldMap[mapX][mapY] > 0) hit = 1;
	//		if (map[ray->map.y][ray->map.x] == 1)
	//			ray->hit = 1;
		}*/
	return (0);
}

int		raycast(t_vars *vars)
{
	int		i;
	double	x_cam;
	t_rays	ray;

	i = 0;
	while (i < vars->config->res_x)
	{
		x_cam = 2. * i / vars->config->res_x - 1;
		//if (x_cam < 0)
		//	printf("X_CAM =%f\n",x_cam);
		//double rayDirX = dirX + planeX * x_cam;
			//which box of the map we're in
		/*int mapX = int(posX);
		int mapY = int(posY);

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = std::abs(1 / rayDirX);
		double deltaDistY = std::abs(1 / rayDirY);
		double perpWallDist;

	//double rayDirY = dirY + planeY * x_cam;
*/
		ray_init_calc(&ray, vars->plr, x_cam);

/*		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		
*/
		ray_side_calc(&ray, vars->plr);
/*
		//perform DDA
			*/
		digital_diff_analys(&ray);//, vars->config->link_map);
		/*
		//Calculate distance projected on camera direction
		//(Euclidean distance will give fisheye effect!)
		if (side == 0)
			perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - posY + (2 - stepY) / 2) / rayDirY;
			*/
		i++;
	}
	return (0);
}
