/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 20:41:05 by tphung            #+#    #+#             */
/*   Updated: 2020/11/03 18:08:35 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_words_num(const char *str, char c)
{
	int		i;
	int		sym;
	int		count;

	i = 0;
	sym = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (str[i] != c && str[i])
		{
			i++;
			sym = 1;
		}
		if (str[i] == c || str[i] == '\0')
		{
			count += (sym == 1) ? 1 : 0;
			sym = 0;
			i++;
		}
	}
	return (count);
}

static int	ft_words_len(const char *str, int i, char c)
{
	int		count;

	count = 0;
	while (str[i] != c && str[i])
	{
		count++;
		i++;
	}
	return (count);
}

static char	*mem_all_ordel(char **res, int j, int len)
{
	char	*str;

	str = (char*)malloc(sizeof(char) * len + 1);
	if (!str)
	{
		while (j >= 0)
		{
			free(res[j]);
			j--;
		}
		free(res);
		return (NULL);
	}
	return (str);
}

char		**ft_split(char const *s, char c)
{
	char	**res;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	if (!s || !(res = malloc(sizeof(char*) * (ft_words_num(s, c) + 1))))
		return (NULL);
	while (s[i])
	{
		while ((s[i] == c) && s[i])
			i++;
		if (s[i] && (k = 0) == 0)
		{
			if (!(res[j] = mem_all_ordel(res, j, ft_words_len(s, i, c))))
				return (res = NULL);
			while (s[i] != c && s[i])
				res[j][k++] = s[i++];
			res[j++][k] = '\0';
		}
	}
	res[j] = NULL;
	return (res);
}
