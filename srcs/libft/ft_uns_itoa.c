/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uns_itoa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:50:39 by tphung            #+#    #+#             */
/*   Updated: 2021/01/19 15:34:52 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*check_zero_and_fillit(unsigned int a, int size)
{
	char	*res;
	long	i;

	i = a;
	if (i == 0)
		size = 1;
	if (!(res = (char*)malloc(sizeof(char) * (1 + size))))
		return (NULL);
	res[0] = '0';
	res[size] = '\0';
	while (i)
	{
		res[--size] = 48 + i % 10;
		i = i / 10;
	}
	return (res);
}

char		*ft_uns_itoa(unsigned int n)
{
	char			*res;
	unsigned int	tmp;
	int				size;

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
