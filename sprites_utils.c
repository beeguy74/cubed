/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 12:32:03 by tphung            #+#    #+#             */
/*   Updated: 2021/04/22 13:09:37 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

void	spr_calc_init(t_spr_calc *spr_calc, double *z_buffer)
{
	spr_calc->z_buffer = z_buffer;
	spr_calc->transf_y = 0.;
	spr_calc->spr_screen_x = 0;
	spr_calc->spr_height = 0;
	spr_calc->spr_width = 0;
	spr_calc->start_y = 0;
	spr_calc->end_y = 0;
	spr_calc->start_x = 0;
	spr_calc->end_x = 0;
}

void	sprite_dist_calc(t_conf *config, t_pers *plr, t_sprite **sprite_mas)
{
	int		i;

	i = 0;
	if (plr && sprite_mas)
	{
		while (i < config->sprite_num)
		{
			sprite_mas[i]->dist = ((plr->pos.x - sprite_mas[i]->pos_x) * \
									(plr->pos.x - sprite_mas[i]->pos_x) + \
									(plr->pos.y - sprite_mas[i]->pos_y) * \
									(plr->pos.y - sprite_mas[i]->pos_y));
			i++;
		}
	}
}

void	sprite_sort(t_conf *config, t_sprite **sprite_mas)
{
	int			i;
	int			j;
	int			tmp;
	t_sprite	*s_tmp;

	i = 0;
	tmp = 0;
	s_tmp = 0;
	while (i < config->sprite_num)
	{
		j = 0;
		while (j < config->sprite_num)
		{
			if (sprite_mas[i]->dist > sprite_mas[j]->dist)
			{
				s_tmp = sprite_mas[i];
				sprite_mas[i] = sprite_mas[j];
				sprite_mas[j] = s_tmp;
			}
			j++;
		}
		i++;
	}
}