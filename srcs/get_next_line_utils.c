/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 20:52:47 by tphung            #+#    #+#             */
/*   Updated: 2020/12/29 20:42:14 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void			ft_memdel(void **po)
{
	if (!po || !*po)
		return ;
	free(*po);
	*po = NULL;
}

int				ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char			*ft_strchr(const char *s, int c)
{
	int	i;
	int j;

	j = ft_strlen((char*)s);
	i = 0;
	while (i <= j)
	{
		if (s[i] == c)
			return ((char*)&s[i]);
		i++;
	}
	return (NULL);
}

size_t			ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		i;
	size_t		dest_len;
	const char	*begin_src;
	const char	*begin_dst;

	i = dstsize;
	begin_src = src;
	begin_dst = dst;
	while (i-- != 0 && *dst != '\0')
		dst++;
	dest_len = dst - begin_dst;
	i = dstsize - dest_len;
	if (i-- == 0)
		return (dest_len + ft_strlen((char *)src));
	while (*src != '\0')
	{
		if (i != 0)
		{
			*dst++ = *src;
			i--;
		}
		src++;
	}
	*dst = '\0';
	return (dest_len + (src - begin_src));
}

size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;

	i = 0;
	if (!dst || !src)
		return (0);
	if (dstsize > 0)
	{
		while (--dstsize && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}
