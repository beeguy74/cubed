/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 13:09:01 by tphung            #+#    #+#             */
/*   Updated: 2021/01/20 13:12:33 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*check_zero_and_fillit(unsigned long a, int size)
{
	char		*res;
	long long	i;
	char		*tmpl;

	i = a;
	tmpl = "0123456789abcdef";
	if (i == 0)
		size = 1;
	if (!(res = (char*)malloc(sizeof(char) * (1 + size))))
		return (NULL);
	res[0] = '0';
	res[size] = '\0';
	while (i)
	{
		res[--size] = tmpl[i % 16];
		i = i / 16;
	}
	return (res);
}

char		*ft_itoa_hex(unsigned long n)
{
	char			*res;
	unsigned long	tmp;
	int				size;

	size = 0;
	tmp = n;
	while (tmp)
	{
		size++;
		tmp = tmp / 16;
	}
	res = check_zero_and_fillit(n, size);
	if (!res)
		return (NULL);
	return (res);
}
