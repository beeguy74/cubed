/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 13:07:36 by tphung            #+#    #+#             */
/*   Updated: 2021/03/20 17:37:31 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cube.h"

void	img_open(t_files *file, t_conf *config, void *mlx)
{
	file->n_text->img->img = mlx_xpm_file_to_image(mlx, config->no,\
						&(file->n_text->width),	&(file->n_text->height));
	file->s_text->img->img = mlx_xpm_file_to_image(mlx, config->so,\
						&(file->s_text->width),	&(file->s_text->height));
	file->w_text->img->img = mlx_xpm_file_to_image(mlx, config->we,\
						&(file->w_text->width),	&(file->w_text->height));
	file->e_text->img->img = mlx_xpm_file_to_image(mlx, config->ea,\
						&(file->e_text->width),	&(file->e_text->height));
	file->sprite->img->img = mlx_xpm_file_to_image(mlx, config->sprite,\
						&(file->sprite->width),	&(file->sprite->height));
}

void	file_init(t_files *file)
{
	file->n_text = (t_text*)malloc(sizeof(t_text));
	file->s_text = (t_text*)malloc(sizeof(t_text));
	file->w_text = (t_text*)malloc(sizeof(t_text));
	file->e_text = (t_text*)malloc(sizeof(t_text));
	file->sprite = (t_text*)malloc(sizeof(t_text));
	file->n_text->img = (t_data*)malloc(sizeof(t_data));
	file->s_text->img = (t_data*)malloc(sizeof(t_data));
	file->w_text->img = (t_data*)malloc(sizeof(t_data));
	file->e_text->img = (t_data*)malloc(sizeof(t_data));
	file->sprite->img = (t_data*)malloc(sizeof(t_data));
}

void	get_addr(t_data *img)
{
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}

void	img_addr(t_files *file)
{
	get_addr(file->n_text->img);
	get_addr(file->s_text->img);
	get_addr(file->w_text->img);
	get_addr(file->e_text->img);
	get_addr(file->sprite->img);
}

void	text_collect(t_vars *vars)
{
	vars->file = (t_files*)malloc(sizeof(t_files));
	file_init(vars->file);

	img_open(vars->file, vars->config, vars->mlx);
	img_addr(vars->file);
}
