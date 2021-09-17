/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 12:43:17 by tphung            #+#    #+#             */
/*   Updated: 2020/11/03 17:33:38 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*check_zero_and_fillit(int a, int size)
{
	char	*res;
	char	tmp;
	long	i;

	i = a;
	tmp = 0;
	if (i == 0)
		size = 1;
	else if (i < 0)
	{
		size = size + 1;
		tmp = 1;
		i = -i;
	}
	if (!(res = (char*)malloc(sizeof(char) * (1 + size))))
		return (NULL);
	res[0] = (tmp == 1) ? '-' : '0';
	res[size] = '\0';
	while (i)
	{
		res[--size] = 48 + i % 10;
		i = i / 10;
	}
	return (res);
}

char		*ft_itoa(int n)
{
	char	*res;
	int		tmp;
	int		size;

	size = 0;
	tmp = n;
	while (tmp)
	{
		size++;
		tmp = tmp / 10;
	}
	res = check_zero_and_fillit(n, size);
	if (!res)
		return (NULL);
	return (res);
}
