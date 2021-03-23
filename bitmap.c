/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:06:16 by tphung            #+#    #+#             */
/*   Updated: 2021/03/23 15:59:02 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cube.h"

void	create_bmp_image(t_conf *config, t_data *img, int fd)
{
	int				i;
	int				j;
	int				end_lines;
	int				end_bytes;
	unsigned char	buf[config->res_x * config->res_y * 4];

	i = 0;
	end_lines = img->line_length * (config->res_y - 1);
	end_bytes = config->res_x * 4;
	while (end_lines >= 0)
	{
		j = 0;
		while (j < end_bytes)
		{
			buf[i] = (((unsigned char *)img->addr + end_lines)[j]);
			i++;
			j++;
		}
		end_lines -= img->line_length;
	}
	write(fd, buf, config->res_x * config->res_y * 4);
}

void	create_bmp_header(t_conf *config, int fd)
{
	unsigned char	buf[54];
	int				size;

	size = config->res_x * config->res_y * 4 + 54;
	ft_bzero(buf, 54);
	buf[0] = 'B';
	buf[1] = 'M';
	buf[2] = size;
	buf[3] = size >> 8;
	buf[4] = size >> 16;
	buf[5] = size >> 24;
	buf[10] = 54;
	buf[14] = 40;
	buf[18] = config->res_x;
	buf[19] = config->res_x >> 8;
	buf[20] = config->res_x >> 16;
	buf[21] = config->res_x >> 24;
	buf[22] = config->res_y;
	buf[23] = config->res_y >> 8;
	buf[24] = config->res_y >> 16;
	buf[25] = config->res_y >> 24;
	buf[26] = 1;
	buf[28] = 32;
	write(fd, buf, 54);
}

void	ft_bmp(t_data *img, t_conf *config, char *file_name)
{
	int		fd;

	fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND | O_TRUNC,
										S_IRWXU | S_IRWXG | S_IRWXO);
	create_bmp_header(config, fd);
	create_bmp_image(config, img, fd);
	close(fd);
}
