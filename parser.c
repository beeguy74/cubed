/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 19:15:46 by tphung            #+#    #+#             */
/*   Updated: 2021/04/24 15:58:39 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"
#include "includes/libft.h"

int	proc_resolution(t_conf *config)
{
	char	*line;
	int		i;

	i = 0;
	line = *config->map;
	if (line[i++] != 'R')
		return (0);
	if (check_digi_args(&line[i + 1], ' ', 2))
		err_exit(11);
	else
	{
		while (line[i] == ' ')
			i++;
		config->res_x = ft_atoi(&line[i]);
		while (ft_isdigit(line[i]))
			i++;
		config->res_y = ft_atoi(&line[i]);
	}
	return (0);
}

int	proc_textures(t_conf *config)
{
	char	*line;
	char	**tmp;
	int		i;

	i = 0;
	line = *config->map;
	if (line[i] == 'N' && line[i + 1] == 'O')
		tmp = &config->no;
	else if (line[i] == 'S' && line[i + 1] == 'O')
		tmp = &config->so;
	else if (line[i] == 'W' && line[i + 1] == 'E')
		tmp = &config->we;
	else if (line[i] == 'E' && line[i + 1] == 'A')
		tmp = &config->ea;
	else if (line[i] == 'S' && line[i + 1] == ' ')
		tmp = &config->sprite;
	else
		return (0);
	i += 2;
	while (line[i++] == ' ')
		;
	*tmp = &line[--i];
	tmp = NULL;
	return (0);
}

int	proc_colors(t_conf *config)
{
	char			*line;
	unsigned int	*tmp;
	int				i;

	i = 0;
	line = *config->map;
	if (line[i] == 'F' && line[i + 1] == ' ')
		tmp = &config->floor_col;
	else if (line[i] == 'C' && line[i + 1] == ' ')
		tmp = &config->ceil_col;
	else
		return (0);
	if (check_digi_args(&line[i + 1], ',', 3))
		err_exit(11);
	while (line[i++] != '\0')
	{
		if (ft_isdigit(line[i]) > 0 || line[i] == '-')
		{
			*tmp = *tmp << 8;
			*tmp = *tmp + do_atoi(&line[i]);
			while (ft_isdigit(line[i]) > 0)
				i++;
		}
	}
	return (0);
}

int	parser(t_conf *config)
{
	if (check_param(config->map) != 8)
		err_exit(11);
	while (*config->map)
	{
		proc_resolution(config);
		proc_textures(config);
		proc_colors(config);
		if (proc_map(config))
		{
			find_sprites(config);
			return (0);
		}
		config->map++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_conf	config;
	t_pers	plr;
	char	**map;
	int		flag;

	flag = 0;
	errno = 0;
	config.s_shot_flag = 0;
	if (argc == 3)
	{
		if (!ft_strncmp("--save", argv[2], 6))
			config.s_shot_flag = 1;
	}
	if ((argc != 2 & argc != 3) || !ft_strnstr(argv[1] + ft_strlen(argv[1]) - 4, \
											".cub", ft_strlen(argv[1])))
		err_exit(11);
	else
		config.map = ft_open_file(argv[1]);
	map = config.map;
	flag += parser(&config);
	flag += find_plr(&plr, config.link_map);
	flag += check_map(config.link_map, &plr);
	if (flag == 0)
		painting(&config, &plr);
	return (0);
}
