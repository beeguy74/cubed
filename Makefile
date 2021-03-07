# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tphung <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/19 18:37:57 by tphung            #+#    #+#              #
#    Updated: 2021/03/07 11:40:40 by tphung           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -c -Wall -Wextra -Werror
AR = ar
ARFLAGS = rcs

SRCS = parser.c pixel.c find_player.c flood_map.c raycast.c\
	   srcs/get_next_line.c srcs/get_next_line_utils.c
OBJ = $(SRCS:.c=.o)
NAME = cub3d
LIBFT = libft.a
LIBFT_DIR = srcs/libft/
MLX = libmlx.dylib
MLX_DIR = mlx/
INCLUDES = includes/

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
		make -C $(LIBFT_DIR)
		make -C $(MLX_DIR)
		cp $(LIBFT_DIR)$(LIBFT) .
		cp $(MLX_DIR)$(MLX) .
		$(CC) -Lmlx -lmlx -framework OpenGL -framework AppKit $(OBJ) $(LIBFT) -o $(NAME) -I $(INCLUDES)

.c.o: 
		gcc $(FLAGS) -Imlx $< -o $@ -I $(INCLUDES)

clean:
		rm -rf $(OBJ)
		make clean -C $(LIBFT_DIR)
		make clean -C $(MLX_DIR)

fclean: clean
		rm -rf $(NAME)
		make fclean -C $(LIBFT_DIR)
		make fclean -C $(MLX_DIR)

re: fclean all
