/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 20:52:47 by tphung            #+#    #+#             */
/*   Updated: 2020/12/29 20:42:04 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char			*ft_strjoin(char const *s1, char const *s2)
{
	char		*dest;
	size_t		dest_size;

	if (!s1 || !s2)
		return (NULL);
	dest_size = (1 + ft_strlen((char*)s1) + ft_strlen((char*)s2));
	dest = (char *)malloc(dest_size * sizeof(char));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s1, dest_size);
	ft_strlcat(dest, s2, dest_size);
	return (dest);
}

char			*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*substr;
	size_t		s_len;
	size_t		i;

	i = 0;
	s_len = (size_t)ft_strlen((char*)s);
	if (!s)
		return (NULL);
	substr = (char*)malloc(sizeof(char) * len + 1);
	if (!substr)
		return (NULL);
	if (!(start >= s_len))
	{
		while (i < len)
		{
			substr[i++] = s[start++];
		}
	}
	substr[i] = '\0';
	return (substr);
}

int				read_fd(int fd, char **tmp)
{
	char		*buf;
	char		*tmp_new;
	int			res;

	res = -1;
	tmp_new = *tmp;
	if (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	if ((res = read(fd, buf, BUFFER_SIZE)) >= 0)
	{
		buf[res] = '\0';
		if (*tmp)
			*tmp = ft_strjoin(*tmp, buf);
		else
			*tmp = ft_substr(buf, 0, res);
	}
	ft_memdel((void **)&tmp_new);
	ft_memdel((void **)&buf);
	if (!(*tmp))
		return (-1);
	return (res);
}

int				ft_swap(char **lost, char **line)
{
	char		*tmp;
	size_t		siz;

	tmp = 0;
	siz = 0;
	if ((tmp = ft_strchr(*lost, 10)))
	{
		siz = tmp - *lost;
		*line = ft_substr(*lost, 0, siz);
		tmp = *lost;
		*lost = ft_substr(*lost, (unsigned int)(siz + 1),\
				(size_t)(ft_strlen(*lost) - siz));
		ft_memdel((void **)&tmp);
		if (!(*line) || !(*lost))
		{
			ft_memdel((void **)lost);
			ft_memdel((void **)line);
			return (-1);
		}
		return (1);
	}
	return (0);
}

int				get_next_line(int fd, char **line)
{
	static char	*lost;
	int			er;

	er = 0;
	if (BUFFER_SIZE < 1 || fd < 0 || !line)
		return (-1);
	while ((er = read_fd(fd, &lost)) > 0)
	{
		if ((er = ft_swap(&lost, line)) > 0)
			return (1);
	}
	if (lost && er >= 0)
	{
		if ((er = ft_swap(&lost, line)) > 0)
			return (1);
		else if (er == 0)
		{
			if (!(*line = ft_substr(lost, 0, (size_t)ft_strlen(lost))))
				return (-1);
			ft_memdel((void **)&lost);
		}
	}
	if (er < 0)
		return (-1);
	return (0);
}
