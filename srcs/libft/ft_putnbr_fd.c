/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:03:00 by tphung            #+#    #+#             */
/*   Updated: 2020/11/03 17:32:48 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	fill_str(long tmp, int i, int fd)
{
	char	str[i + 1];

	str[i--] = '\0';
	while (tmp)
	{
		str[i--] = 48 + tmp % 10;
		tmp = tmp / 10;
	}
	ft_putstr_fd(str, fd);
	return (0);
}

void		ft_putnbr_fd(int n, int fd)
{
	int		i;
	long	tmp;

	i = 0;
	tmp = n;
	tmp = (n < 0) ? tmp * -1 : tmp;
	(n < 0) ? ft_putchar_fd('-', fd) : n;
	if (n == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	while (n)
	{
		n = n / 10;
		i++;
	}
	fill_str(tmp, i, fd);
}
