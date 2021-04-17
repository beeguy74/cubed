/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 13:54:46 by tphung            #+#    #+#             */
/*   Updated: 2021/04/17 15:43:26 by tphung           ###   ########.fr       */
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
	double			wall_dist;
	t_vect			dir;
	t_vect			delta;
	t_vect			side;
	t_point			step;
	t_point			map;
	t_point			line_start;
	t_point			line_end;
	int				line_height;
	int				hit_side;
	int				hit;
}					t_rays;

typedef struct	s_sprite
{
	double		pos_x;
	double		pos_y;
	double		dist;
	double		x;
	double		y;
}				t_sprite;

typedef struct		s_conf
{
	int				s_shot_flag;
	int				res_x;
	int				res_y;
	int				sprite_num;
	int				*sprite_order;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*sprite;
	char			**map;
	char			**link_map;
	unsigned int	floor_col;
	unsigned int	ceil_col;
	t_sprite		**sprite_mas;
}					t_conf;

typedef	struct	s_data
{
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	void		*img;
}				t_data;

typedef struct	s_text
{
	t_data		*img;
	int			width;
	int			height;
}				t_text;

typedef struct	s_files
{
	t_text		*n_text;
	t_text		*s_text;
	t_text		*w_text;
	t_text		*e_text;
	t_text		*sprite;
}				t_files;

typedef struct	s_vars
{
	void		*mlx;
	void		*win;
	t_data		*img;
	t_conf		*config;
	t_files		*file;
	t_pers		*plr;
	t_rays		*ray;
}				t_vars;

typedef struct	s_calc
{
	double		wall_x; //where exactly the wall was hit
	double		step; // How much to increase the texture coordinate per screen pixel
	double		tex_pos; // Starting texture coordinate
	int			tex_x; //x coordinate on the texture
	int			color;
	int			tex_y;
}				t_calc;

void				draw_sprite(t_vars *vars, double *z_buffer);
void				my_mlx_pixel_put(t_data *data, int x, int y,\
		unsigned int color);
void				line_put(t_data *img, t_point start, t_point end,\
		unsigned int color);
int					flood_fill(char **map, int x, int y);
int					check_map(char **map, t_pers *plr);
int					find_plr(t_pers *plr, char **map);
int					painting(t_conf *config, t_pers *plr);
int					raycast(t_vars *vars);
void				err_exit(int err);
void				text_collect(t_vars *vars);
void				ft_bmp(t_data *img, t_conf *config, char *file_name);
void				find_sprites(t_conf *config);

#endif
