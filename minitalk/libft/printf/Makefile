# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: riporth <riporth@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/01 16:01:47 by riporth           #+#    #+#              #
#    Updated: 2024/01/19 13:20:50 by riporth          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
SRC_FILES = ft_print.c    	    \
			ft_string_flags.c	\
			ft_int_flags.c

OBJ_FILES = $(SRC_FILES:.c=.o)

HEADER_FILE = ft_printf.h
CC = cc
CFLAGS = -Wall -Wextra -Werror

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@ar rc $(NAME) $(OBJ_FILES)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$ rm -f $(OBJ_FILES)

fclean: clean
	@$ rm -f $(NAME)

re: fclean all

norm:
	norminette

.PHONY: all clean fclean re
