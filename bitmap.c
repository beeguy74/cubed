/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 16:06:16 by tphung            #+#    #+#             */
/*   Updated: 2021/03/22 17:54:49 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cube.h"
/*
const int bytesPerPixel = 4; /// red, green, blue
const int fileHeaderSize = 14;
const int infoHeaderSize = 40;

void generateBitmapImage(unsigned char *image, int height, int width,
									int pitch, const char* imageFileName)*/

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
	int				size;
	unsigned char	buf[54];

	ft_bzero(buf, 54);
	buf[0] = 'B';
	buf[1] = 'M';
	buf[2] = config->res_x * config->res_y * 4 + 54;
	buf[10] = 54;
	buf[14] = 40;
	buf[18] = all->resolution->width;
	buf[22] = all->resolution->height;
	buf[26] = 1;
	buf[28] = 32;
    write(image_fd, buf, 54);
}

void	ft_bmp(t_data *img, t_conf *config, char *file_name)
{
    int				fd;
    unsigned char	buf;

    fd = open(file_name, O_CREAT | O_WRONLY| O_TRUNC);

    buf = create_bmp_header(config, fd);
	create_bmp_image(config, img, fd)
    fclose(image_fd);
}
