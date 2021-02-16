/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 19:15:46 by tphung            #+#    #+#             */
/*   Updated: 2021/02/16 14:04:05 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cube.h"

void				ft_putstr(void *data)
{
	char	*line;
	char	end;
	int		len;

	end = '\n';
	line = (char*)data;
	len = ft_strlen(line);
	write(0, line, len);
	write(0, &end, 1);
}

void				err_exit(int err)
{
	char	*msg;
	char	*msg_errno;

	msg = "Error";
	if (errno == 0 && err == 0)
		return ;
	if (errno != 0)
		msg_errno = strerror(errno);
	else if (err == 12)
		msg_errno = "memory for list wasnt allocated";
	ft_putstr((void*)(msg));
	ft_putstr((void*)(msg_errno));
	exit(0);
}

t_list				*gnl_to_list(int fd)
{
	int		err;
	char	*line;
	t_list	*list;

	err = 0;
	line = 0;
	list = 0;
	while ((err = get_next_line(fd, &line)) > 0)
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

char				**list_to_map(t_list *list)
{
	char	**map;
	int		len;
	int		i;
	t_list	*tmp;

	i = 0;
	len = ft_lstsize(list);
	map = malloc(sizeof(char*) * (len + 1));
	if (!map)
		err_exit(0);
	map[len] = NULL;
	while (i < len)
	{
		map[i] = (char*)list->content;
		tmp = list;
		list = list->next;
		free(tmp);
		i++;
	}
	free(list);
	list = 0;
	return (map);
}

char				**ft_open_file(char *file)
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

int					proc_resolution(t_conf *config)
{
	char	*line;
	int		i;

	i = 0;
	line = *config->map;
	if (line[i++] != 'R')
		return(0);
	else
	{
		while(line[i] == ' ')
			i++;
		config->res_x = ft_atoi(&line[i]);
		while(ft_isdigit(line[i]))
			i++;
		config->res_y = ft_atoi(&line[i]);
	}
	return (0);
}

int					proc_textures(t_conf *config)
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
	while (line[i++] == ' ') ;
	*tmp = &line[--i];
	tmp = NULL;
	return (0);
}

int					proc_colors(t_conf *config)
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
	while (line[i++] != '\0')
	{
		if (ft_isdigit(line[i]) > 0)
		{
			*tmp = *tmp << 8;
			*tmp = *tmp + ft_atoi(&line[i]);
			while (ft_isdigit(line[i]) > 0)
				i++;
		}
	}
	tmp = NULL;
	return (0);
}

int					proc_map(t_conf *config)
{
	int 			i;

	i = 0;
	if (ft_isdigit(*config->map[i]) > 0)
	{
		config->link_map = config->map;
		return (1);
	}
	return (0);
}

int					parser(t_conf *config)
{
	char	**map;

	map = config->map;
	while (*config->map)
	{
		proc_resolution(config);
		proc_textures(config);
		proc_colors(config);
		if (proc_map(config))
			return (1);
		config->map++;
	}
	return (0);
}

int					main(int argc, char **argv)
{
	t_conf	config;
	char	**map;
	
	if (argc == 2)
		config.map = ft_open_file(argv[1]);
	else
		printf("SHit!\n");
	map = config.map;
	parser(&config);
	//check_map(config.link_map);
	printf("res_x = %i\n", config.res_x);
	printf("res_y = %i\n", config.res_y);
	printf("NO texture = %s\n", config.no);
	printf("SO texture = %s\n", config.so);
	printf("WE texture = %s\n", config.we);
	printf("EA texture = %s\n", config.ea);
	printf("Sprite texture = %s\n", config.sprite);
	printf("ceil color = %u\n", config.ceil_col);
	printf("floor color = %u\n", config.floor_col);

	printf("\nMAP_FILE:\n");
	while (*config.link_map != 0)
		printf("%s\n", *config.link_map++);
	return (0);
}
