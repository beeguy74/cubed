/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 21:00:00 by tphung            #+#    #+#             */
/*   Updated: 2020/11/03 11:08:31 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;

	i = 0;
	while (n > 0)
	{
		(*(unsigned char*)dst) = (*(unsigned char*)src);
		if ((*(unsigned char*)src) == (unsigned char)c)
			return (dst + 1);
		dst++;
		src++;
		n--;
	}
	return (NULL);
}
