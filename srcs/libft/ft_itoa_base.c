/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 19:24:44 by tphung            #+#    #+#             */
/*   Updated: 2021/01/20 13:06:51 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*check_zero_and_fillit(unsigned int a, int size, int base)
{
	char	*res;
	long	i;
	char	*tmpl;

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
		res[--size] = tmpl[i % base];
		i = i / base;
	}
	return (res);
}

char		*ft_itoa_base(unsigned int n, int base)
{
	char			*res;
	unsigned int	tmp;
	int				size;

	size = 0;
	tmp = n;
	while (tmp)
	{
		size++;
		tmp = tmp / base;
	}
	res = check_zero_and_fillit(n, size, base);
	if (!res)
		return (NULL);
	return (res);
}
