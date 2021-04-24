/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 19:15:46 by tphung            #+#    #+#             */
/*   Updated: 2021/04/24 14:30:01 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"
#include "includes/libft.h"

void	ft_putstr(void *data)
{
	char	*line;
	char	end;
	int		len;

	end = '\n';
	line = (char *)data;
	len = ft_strlen(line);
	write(0, line, len);
	write(0, &end, 1);
}

void	err_exit(int err)
{
	char	*msg;
	char	*msg_errno;

	msg_errno = NULL;
	msg = "Error";
	if (errno == 0 && err == 0)
		return ;
	if (errno != 0)
		msg_errno = strerror(errno);
	else if (err == 12)
		msg_errno = "memory for list wasnt allocated";
	else if (err == 11)
		msg_errno = "wrong arguments";
	else if (err == 111)
	{
		msg = ":-)";
		msg_errno = "screenshot.bmp created!";
	}
	ft_putstr((void *)(msg));
	ft_putstr((void *)(msg_errno));
	exit(0);
}

t_list	*gnl_to_list(int fd)
{
	char	*line;
	t_list	*list;

	line = 0;
	list = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (!list)
			list = ft_lstnew(ft_strdup(line));
		else
			ft_lstadd_back(&list, ft_lstnew(ft_strdup(line)));
		if (!list || !line)
			err_exit(12);
		free(line);
	}
	err_exit(0);
	ft_lstadd_back(&list, ft_lstnew(ft_strdup(line)));
	free(line);
	if (!list || !line)
		err_exit(12);
	return (list);
}

char	**list_to_map(t_list *list)
{
	char	**map;
	int		len;
	int		i;
	t_list	*tmp;

	i = 0;
	len = ft_lstsize(list);
	map = malloc(sizeof(char *) * (len + 1));
	if (!map)
		err_exit(0);
	map[len] = NULL;
	while (i < len)
	{
		map[i] = (char *)list->content;
		tmp = list;
		list = list->next;
		free(tmp);
		i++;
	}
	free(list);
	list = 0;
	return (map);
}

char	**ft_open_file(char *file)
{
	int		fd;
	t_list	*list;
	char	**map;

	list = 0;
	fd = open(file, O_RDONLY);
	err_exit(0);
	list = gnl_to_list(fd);
	map = list_to_map(list);
	err_exit(0);
	close(fd);
	return (map);
}

int	check_digi_args(char *line, char sep, int num)
{
	int	i;
	int	count;
	int	save;

	i = 0;
	count = 0;
	save = 0;
	while (line[i])
	{
		if (save && ((line[i] == sep && ft_isdigit(line[i + 1])) \
													|| !line[i + 1]))
			count++;
		save = ft_isdigit(line[i]);
		i++;
	}
	if (count == num)
		return (0);
	return (1);
}

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

int	do_atoi(char *line)
{
	int	res;

	res = 0;
	res = ft_atoi(line);
	if (res < 0 || res > 250)
		err_exit(11);
	return (res);
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

int	proc_map(t_conf *config)
{
	int	i;

	i = 0;
	if (ft_isdigit(*config->map[i]) > 0)
	{
		config->link_map = config->map;
		return (1);
	}
	return (0);
}

int	count_right_params(char *where, char *what)
{
	if (ft_strnstr(where, what, 3) == where)
		return (1);
	return (0);
}

int	check_param(char **map)
{
	int	i;

	i = 0;
	while (*map)
	{
		i += count_right_params(*map, "R ");
		i += count_right_params(*map, "NO ");
		i += count_right_params(*map, "SO ");
		i += count_right_params(*map, "WE ");
		i += count_right_params(*map, "EA ");
		i += count_right_params(*map, "S ");
		i += count_right_params(*map, "F ");
		i += count_right_params(*map, "C ");
		i += !ft_strchr("RNSWESFC102 ", *map[0]);
		map++;
	}
	return (i);
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
