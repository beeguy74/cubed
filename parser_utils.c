/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <tphung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 19:15:46 by tphung            #+#    #+#             */
/*   Updated: 2021/04/24 17:07:49 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"
#include "includes/libft.h"

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

int	do_atoi(char *line)
{
	int	res;

	res = 0;
	res = ft_atoi(line);
	if (res < 0 || res > 250)
		err_exit(11);
	return (res);
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
