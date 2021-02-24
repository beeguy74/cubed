/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 13:54:46 by tphung            #+#    #+#             */
/*   Updated: 2021/02/20 13:53:53 by tphung           ###   ########.fr       */
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
	float			y;
	float			x;
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
}				t_vars;

int					flood_fill(char **map, int x, int y);
int					check_map(char **map, t_pers *plr);
int					find_plr(t_pers *plr, char **map);
int					painting(t_conf *config, t_pers *plr);
void				err_exit(int err);

#endif
