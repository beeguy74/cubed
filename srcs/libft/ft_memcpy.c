/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 20:59:44 by tphung            #+#    #+#             */
/*   Updated: 2020/11/02 11:27:13 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*tmp;
	unsigned char	*res;

	tmp = (unsigned char*)src;
	res = (unsigned char*)dst;
	if (n == 0 || src == dst)
	{
		return (dst);
	}
	while (n--)
	{
		res[n] = tmp[n];
	}
	return (dst);
}
