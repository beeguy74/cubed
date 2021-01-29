#include "./includes/mlx.h"
#include "./includes/libft.h"
#include <math.h>
#include <stdio.h>

typedef	struct	s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct	s_vars
{
	void		*mlx;
	void		*win;
	t_data		*img;
	int			x;
	int			y;
	int			x1;
	int			y1;
}				t_vars;

void			my_mlx_pixel_put(t_data	*data,	int	x,	int	y,	int	color)
{
	char		*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void			square_put(t_data *img, int x, int y, int len)
{
	int			i;
	int			j;

	i = 0;
	while (i < len)
	{
		j = 0;
		while (j < len)
		{
			my_mlx_pixel_put(img, x + i, y + j, 0x00FF0000);
			j++;
		}
		i++;
	}
}

void			line_put(t_data *img, int x0, int y0, int x1, int y1)
{
	int		deltax = 0;
	int		deltay = 0;
	int		diry = 0;
	int		error = 0;
	int		deltaerr = 0;

	diry = y1 - y0;
	deltax = abs(x1 - x0);
	deltay = abs(y1 - y0);
	deltaerr = (deltay + 1);
	if (diry > 0)
		diry = 1;
	if (diry < 0)
		diry = -1;
	while (x0 < x1)
	{
		my_mlx_pixel_put(img, x0, y0, 0x00FF0000);
		error = error + deltaerr;
		if (error >= (deltax + 1))
		{
			y0 = y0 + diry;
			error = error - deltax;
		}
		x0++;
	}
}

int				key_hook(int keycode, t_vars *vars)
{

	printf("the key_code is %d\n", keycode);
	if (vars)
		return (0);
	else
		return (0);
}

int				mouse_hook(int button, int x, int y, t_vars *vars)
{
	printf("mouse x is %d, y is %d\n", x, y);
	if (vars && button)
		return (0);
	else
		return (0);
}

int				render_next_frame(t_vars *vars)
{
	//vars->img->img = mlx_new_image(vars->mlx, 640, 480);
	//vars->img->addr = mlx_get_data_addr(vars->img->img, &(vars->img->bits_per_pixel),\
	//		&(vars->img->line_length), &(vars->img->endian));
	line_put(vars->img, vars->x, vars->y, vars->x1, vars->y1);
	if (vars->x < 630)
		vars->x += 20;
	else 
		vars->x -= 20;
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	return (1);
}

int				main(void)
{
	t_vars		vars;
	t_data		img;

	vars.x = 10;
	vars.y = 10;
	vars.x1 = 630;
	vars.y1 = 470;
	vars.img = &img;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello world!");
	mlx_key_hook(vars.win, key_hook, &vars);
	//mlx_mouse_hook(vars.win, mouse_hook, &vars);
	//mlx_mouse_get_pos(vars.win, &x, &y);
	//printf("mouse x is %d, y is %d\n", x, y);

	//square_put(&img, 580, 15, 50);
	//line_put(&img, 580, 100, 600, 180);
	
	vars.img->img = mlx_new_image(vars.mlx, 640, 480);
	vars.img->addr = mlx_get_data_addr(vars.img->img, &vars.img->bits_per_pixel,\
			&vars.img->line_length, &vars.img->endian);

	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
/*	
	line_put(vars.img, vars.x, vars.y, vars.x1, vars.y1);
	if (vars.x < 630)
		vars.x += 20;
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img->img, 0, 0);
*/
	mlx_loop(vars.mlx);
	return (0);
}
