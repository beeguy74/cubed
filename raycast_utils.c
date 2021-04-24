/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 15:16:39 by tphung            #+#    #+#             */
/*   Updated: 2021/04/24 15:17:46 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cube.h"

//length of ray from current position to next x or y-side
int	ray_init_calc(t_rays *ray, t_pers *plr, double x_cam)
{
	t_vect	dir;
	t_vect	delta;

	ray->hit = 0;
	ray->map.x = (int)plr->pos.x;
	ray->map.y = (int)plr->pos.y;
	dir.x = plr->sight.x + plr->cam.x * x_cam;
	dir.y = plr->sight.y + plr->cam.y * x_cam;
	ray->dir = dir;
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

int	ray_side_calc(t_rays *ray, t_pers *plr)
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
