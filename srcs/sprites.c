/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 17:21:40 by tphung            #+#    #+#             */
/*   Updated: 2021/04/22 15:47:03 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

//spr_mas_x and _y translate sprite position to relative to camera
//inv_det required for correct matrix multiplication
//transf_x _y transform sprite with the inverse camera matrix
//transf_y this is actually the depth inside the screen, that what Z is in 3D
//calculate height of the sprite on screen
//using 'spr_calc->transf_y' instead of the real distance prevents fisheye
//calculate lowest and highest pixel to fill in current spr_calc->start_x
//calculate width of the sprite
void	sprite_to_camera(t_sprite *sprite_mas, \
										t_spr_calc *spr_calc,	t_vars *vars)
{
	double	inv_det;
	double	transf_x;

	sprite_mas->x = sprite_mas->pos_x - vars->plr->pos.x;
	sprite_mas->y = sprite_mas->pos_y - vars->plr->pos.y;
	inv_det = 1.0 / (vars->plr->cam.x * vars->plr->sight.y - \
							vars->plr->sight.x * vars->plr->cam.y);
	transf_x = inv_det * (vars->plr->sight.y * sprite_mas->x - \
								vars->plr->sight.x * sprite_mas->y);
	spr_calc->transf_y = inv_det * (-vars->plr->cam.y * sprite_mas->x + \
										vars->plr->cam.x * sprite_mas->y);
	spr_calc->spr_screen_x = (int)((vars->config->res_x / 2) * \
								(1. + transf_x / spr_calc->transf_y));
	spr_calc->spr_height = abs((int)(vars->config->res_y / \
												(spr_calc->transf_y)));
}

void	draw_borders_calc(t_spr_calc *spr_calc,	t_vars *vars)
{
	spr_calc->start_y = -spr_calc->spr_height / 2 + vars->config->res_y / 2;
	if (spr_calc->start_y < 0)
		spr_calc->start_y = 0;
	spr_calc->end_y = spr_calc->spr_height / 2 + vars->config->res_y / 2;
	if (spr_calc->end_y >= vars->config->res_y)
		spr_calc->end_y = vars->config->res_y - 1;
	spr_calc->spr_width = abs((int)(vars->config->res_y / \
											(spr_calc->transf_y)));
	spr_calc->start_x = -spr_calc->spr_width / 2 + spr_calc->spr_screen_x;
	if (spr_calc->start_x < 0)
		spr_calc->start_x = 0;
	spr_calc->end_x = spr_calc->spr_width / 2 + spr_calc->spr_screen_x;
	if (spr_calc->end_x >= vars->config->res_x)
		spr_calc->end_x = vars->config->res_x - 1;
}

//for every pixel of the current spr_calc->start_x
//256 and 128 factors to avoid floats
//paint pixel if it isn't black, black is the invisible color
void	sprite_pixel_put(t_text *sprite, t_spr_calc *spr_calc,	\
												t_vars *vars, int y)
{
	int	*sprite_img;
	int	color;
	int	d;

	sprite_img = (int *)sprite->img->addr;
	d = y * 256 - vars->config->res_y * 128 + spr_calc->spr_height * 128;
	spr_calc->tex_y = ((d * sprite->height) / spr_calc->spr_height) / 256;
	color = sprite_img[sprite->width * spr_calc->tex_y + spr_calc->tex_x];
	if ((color & 0x00FFFFFF) != 0)
		my_mlx_pixel_put(vars->img, spr_calc->start_x, y, color);
}

//the conditions in the if are:
//1) it's in front of camera plane so you don't see things behind you
//2) it's on the screen (left)
//3) it's on the screen (right)
//4) ZBuffer, with perpendicular distancep
void	sprite_final_put(t_text *sprite, t_spr_calc *spr_calc,	t_vars *vars)
{
	int	y;

	while (spr_calc->start_x < spr_calc->end_x)
	{
		spr_calc->tex_x = (int)(256 * (spr_calc->start_x - (-spr_calc->spr_width / 2 + \
		spr_calc->spr_screen_x)) * sprite->width / spr_calc->spr_width) / 256;
		if (spr_calc->transf_y > 0 && spr_calc->start_x > 0 && spr_calc->start_x < \
				vars->config->res_x && \
					spr_calc->transf_y < spr_calc->z_buffer[spr_calc->start_x])
		{
			y = spr_calc->start_y;
			while (y < spr_calc->end_y)
			{
				sprite_pixel_put(sprite, spr_calc, vars, y);
				y++;
			}
		}
		spr_calc->start_x++;
	}
}

//SPRITE CASTING
//sort sprites from far to close
//after sorting the sprites, do the projection and draw them
void	draw_sprite(t_vars *vars, double *z_buffer)
{
	int			i;
	t_spr_calc	spr_calc;

	spr_calc_init(&spr_calc, z_buffer);
	sprite_dist_calc(vars->config, vars->plr, vars->config->sprite_mas);
	sprite_sort(vars->config, vars->config->sprite_mas);
	i = 0;
	while (i < vars->config->sprite_num)
	{
		sprite_to_camera(vars->config->sprite_mas[i++], &spr_calc, vars);
		draw_borders_calc(&spr_calc, vars);
		sprite_final_put(vars->file->sprite, &spr_calc, vars);
	}
	free(z_buffer);
}
