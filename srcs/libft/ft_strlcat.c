/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:56:06 by tphung            #+#    #+#             */
/*   Updated: 2020/11/03 18:42:58 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
