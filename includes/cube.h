/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tphung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 13:54:46 by tphung            #+#    #+#             */
/*   Updated: 2021/01/31 18:41:49 by tphung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "libft.h"
#include "get_next_line.h"

typedef struct		s_conf
{
	int				res_x;
	int				res_y;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*sprite;
	unsigned int	floor_col;
	unsigned int	ceil_col;
	char			**map;
}					t_conf;

#endif
