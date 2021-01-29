/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 19:15:46 by tphung            #+#    #+#             */
/*   Updated: 2021/01/29 20:53:11 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "includes/libft.h"
#include "includes/get_next_line.h"

typedef struct		s_conf
{
	int				res_x;
	int				res_y;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*sprite;
	int				floor_col;
	int				ceil_col;
	char			**map;
}					t_conf;

void				ft_putstr(void *data)
{
	char	*line;
	int		len;

	line = (char*)data;
	len = ft_strlen(line);
	write(0, line, len);
	ft_putstr((void*)"\n");
}

t_conf				*ft_open_file(char *file)
{
	int		i;
	int		fd;
	char	*line;
	t_list	*list;
	t_conf	config;
	void	(*func)(void *str);

	func = &ft_putstr;

	i = 0;
	fd = open(file, O_RDONLY);
	while ((i = get_next_line(fd, &line)))
	{
		ft_lstadd_back(&list, ft_lstnew(ft_strdup(line)));
		free (line);
	}
	ft_lstiter(list, func);
	close(fd);
	return (0);
}

int					main(int argc, char **argv)
{
	if (argc == 2)
	{
		ft_open_file(argv[1]);
	}
	else
		printf("SHit!\n");
	return (0);
}
