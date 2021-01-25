/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:59:55 by tphung            #+#    #+#             */
/*   Updated: 2020/11/03 15:01:04 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*tmp;
	unsigned char	i;
	size_t			j;

	i = (unsigned char)c;
	tmp = (unsigned char*)s;
	j = 0;
	while (j < n)
	{
		if (tmp[j] == i)
			return ((void*)&tmp[j]);
		j++;
	}
	return (NULL);
}
