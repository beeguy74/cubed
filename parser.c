/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 19:15:46 by tphung            #+#    #+#             */
/*   Updated: 2021/01/30 15:36:47 by tphung           ###   ########.fr       */
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
	while (*map != 0)
	{
		ft_putstr((void*)(*map));
		map++;
	}
	err_exit(0);
	close(fd);
	return (map);
}

int					parser(t_conf *config)
{
	char	**map;
	int		i;

	i = 0;
	map = config->map;
	while (*config->map != 0)
	{
		i++;
	}
	return (i);
}

int					main(int argc, char **argv)
{
	t_conf	config;


	if (argc == 2)
		config.map = ft_open_file(argv[1]);
	else
		printf("SHit!\n");
	parser(&config);
	return (0);
}
