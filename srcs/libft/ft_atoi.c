/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 13:37:41 by tphung            #+#    #+#             */
/*   Updated: 2020/11/03 15:22:56 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_atoi(const char *str)
{
	long long int	i;
	long long int	mp;
	long long int	res;

	i = 0;
	res = 0;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		i++;
	mp = (str[i] == '-') ? -1 : 1;
	i = (str[i] == '-' || str[i] == '+') ? (i + 1) : i;
	while (str[i] > 47 && str[i] < 58)
	{
		res = (str[i] > 47 && str[i] < 58) ? ((str[i] - '0') + 10 * res) : res;
		if ((res * mp) > 2147483647 || (res * mp) < -2147483648)
		{
			if ((res * mp) < -2147483648)
				res = 0;
			else
				res = -1;
			break ;
		}
		i++;
	}
	return (res * mp);
}
