/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:57:17 by tphung            #+#    #+#             */
/*   Updated: 2020/11/03 15:57:18 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s1)
{
	int		i;
	char	*res;

	i = 0;
	while (s1[i] != '\0')
	{
		i++;
	}
	res = (char*)malloc(sizeof(char) * (++i));
	if (!res)
		return (NULL);
	res[i] = '\0';
	while (i--)
	{
		res[i] = s1[i];
	}
	return (res);
}
