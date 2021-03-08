/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 11:27:20 by tphung            #+#    #+#             */
/*   Updated: 2021/03/08 18:56:51 by tphung           ###   ########.fr       */
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

int		digital_diff_analys(t_rays *ray, char **map, t_data *img)
{
	//printf("%c\n", map[ray.map.y][ray.map.x]);
	//printf("posX= %d posY= %d", ray->map.x, ray->map.y);
	//t_point	point;
	int		i;

	while (ray->hit == 0)
	{
		i = 0;
		//draw some shitty rays
		/*while (i <= 6)
		{
			point.y = (int)(ray->map.y * SCALE + i);
			point.x = (int)(ray->map.x * SCALE + i);
			my_mlx_pixel_put(img, point.x, point.y, 0x000000FF);
			i++;
		}*/
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
		if (map[ray->map.y][ray->map.x] == '1')
		{
			//printf("posX= %d posY= %d", ray->map.x, ray->map.y);
			ray->hit = 1;
		}
	}
	return (0);
}

int		raycast(t_vars *vars)
{
	int		i;
	double	x_cam;
	t_rays	ray;

	i = 0;
	vars->ray = &ray;
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
		
		digital_diff_analys(&ray, vars->config->link_map, vars->img);
		/*
		//Calculate distance projected on camera direction
		//(Euclidean distance will give fisheye effect!)
		if (side == 0)
			perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - posY + (2 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
      int lineHeight = (int)(h / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + h / 2;
      if(drawStart < 0)drawStart = 0;
      int drawEnd = lineHeight / 2 + h / 2;
      if(drawEnd >= h)drawEnd = h - 1;

      //choose wall color
      ColorRGB color;
      switch(worldMap[mapX][mapY])
      {
        case 1:  color = RGB_Red;    break; //red
        case 2:  color = RGB_Green;  break; //green
        case 3:  color = RGB_Blue;   break; //blue
        case 4:  color = RGB_White;  break; //white
        default: color = RGB_Yellow; break; //yellow
      }

      //give x and y sides different brightness
      if(side == 1) {color = color / 2;}

      //draw the pixels of the stripe as a vertical line
      verLine(x, drawStart, drawEnd, color);
			*/
		i++;
	}
	return (0);
}
