# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tphung <tphung@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/19 18:37:57 by tphung            #+#    #+#              #
#    Updated: 2021/04/24 17:58:26 by tphung           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FLAGS = -c -Wall -Wextra -Werror -g
AR = ar
ARFLAGS = rcs

SRCPATH = srcs/
SRCS =  $(SRCPATH)parser.c  $(SRCPATH)parser_utils.c  $(SRCPATH)open_error.c\
		 $(SRCPATH)pixel.c  $(SRCPATH)pixel_utils.c  $(SRCPATH)key_working.c\
		 $(SRCPATH)find_player.c  $(SRCPATH)flood_map.c \
		 $(SRCPATH)raycast.c  $(SRCPATH)raycast_utils.c\
		 $(SRCPATH)texture.c  $(SRCPATH)bitmap.c\
		 $(SRCPATH)sprites.c  $(SRCPATH)sprites_utils.c\
		 srcs/get_next_line.c srcs/get_next_line_utils.c
OBJ = $(SRCS:.c=.o)
NAME = cub3D
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
		rm -rf $(LIBFT)
		make clean -C $(LIBFT_DIR)
		make clean -C $(MLX_DIR)

fclean: clean
		rm -rf $(NAME)
		rm -rf $(MLX)
		make fclean -C $(LIBFT_DIR)

re: fclean all
