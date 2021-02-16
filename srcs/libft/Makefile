# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tphung <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/28 13:18:04 by tphung            #+#    #+#              #
#    Updated: 2021/02/16 14:32:45 by tphung           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS=-c -Wall -Wextra -Werror

SOURCES = ft_memchr.c	ft_memmove.c	ft_strdup.c	ft_strrchr.c ft_bzero.c	\
		ft_memcmp.c	ft_memset.c	ft_strlcat.c ft_memccpy.c ft_memcpy.c \
		ft_strchr.c	ft_strlen.c ft_strlcpy.c ft_strnstr.c ft_strncmp.c \
		ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
		ft_isprint.c ft_toupper.c ft_tolower.c ft_calloc.c \
		ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
		ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
		ft_putnbr_fd.c ft_uns_itoa.c ft_itoa_base.c ft_itoa_hex.c \
		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
		 ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
		 ft_lstmap.c

OBJECTS = $(SOURCES:.c=.o)

NAME=libft.a

.PHONY: all bonus clean fclean re

all: $(SOURCES) $(NAME)

$(NAME): $(OBJECTS)
	ar rc $(NAME) $(OBJECTS)
	ranlib $(NAME)

.c.o: 
	gcc $(FLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all
