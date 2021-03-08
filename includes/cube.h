/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 13:54:46 by tphung            #+#    #+#             */
/*   Updated: 2021/03/08 18:49:09 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "mlx.h"
#include "libft.h"
#include <math.h>
#include "get_next_line.h"

# define SCALE 10

typedef struct		s_vect
{
	double			y;
	double			x;
}					t_vect;

typedef struct		s_point
{
	int				y;
	int				x;
}					t_point;

typedef struct		s_pers
{
	t_vect			pos;
	t_vect			sight;
	t_vect			cam;
}					t_pers;

typedef struct		s_rays
{
	t_vect			dir;
	t_vect			delta;
	t_vect			side;
	t_point			step;
	t_point			map;
	int				hit_side;
	int				hit;
}					t_rays;

typedef struct		s_conf
{
	int				res_x;
	int				res_y;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*sprite;
	char			**map;
	char			**link_map;
	unsigned int	floor_col;
	unsigned int	ceil_col;
}					t_conf;

typedef	struct	s_data
{
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	void		*img;
}				t_data;

typedef struct	s_vars
{
	void		*mlx;
	void		*win;
	t_data		*img;
	t_conf		*config;
	t_pers		*plr;
	t_rays		*ray;
}				t_vars;

void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
void				line_put(t_data *img, int x0, int y0, int x1, int y1);
int					flood_fill(char **map, int x, int y);
int					check_map(char **map, t_pers *plr);
int					find_plr(t_pers *plr, char **map);
int					painting(t_conf *config, t_pers *plr);
int					raycast(t_vars *vars);
void				err_exit(int err);

#endif
