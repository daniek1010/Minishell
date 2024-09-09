# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: riporth <riporth@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 13:51:19 by riporth           #+#    #+#              #
#    Updated: 2024/01/19 14:28:14 by riporth          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC_FILES = ft_calloc.c     \
			ft_isascii.c    \
			ft_isascii.c    \
			ft_memchr.c     \
			ft_memmove.c    \
			ft_strdup.c     \
			ft_strlen.c     \
			ft_strrchr.c    \
			ft_atoi.c       \
			ft_isalnum.c    \
			ft_isdigit.c    \
			ft_memcmp.c     \
			ft_strlcat.c    \
			ft_memset.c     \
			ft_strlcat.c    \
			ft_strncmp.c    \
			ft_tolower.c    \
			ft_bzero.c      \
			ft_isalpha.c    \
			ft_isprint.c    \
			ft_memcpy.c     \
			ft_strchr.c     \
			ft_strlcpy.c    \
			ft_strnstr.c    \
			ft_toupper.c    \
			ft_substr.c     \
			ft_strjoin.c    \
			ft_strtrim.c    \
			ft_split.c      \
			ft_strmapi.c    \
			ft_striteri.c   \
			ft_putchar_fd.c \
			ft_putstr_fd.c  \
			ft_putendl_fd.c \
			ft_putnbr_fd.c  \
			ft_itoa.c  \
	
HEADER_FILE = printf/ft_printf.h
PRINTFBS	 = -L./printf -lft
PRINTF	 = libftprintf.a

OBJ_FILES = $(SRC_FILES:.c=.o)
HEADER_FILE = libft.h
CC = cc
CFLAGS = -Wall -Wextra -Werror

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all: $(PRINTF) $(NAME)

$(PRINTF) : 
	@make -C printf

$(NAME): $(OBJ_FILES)
	@ar rc $(NAME) $(OBJ_FILES)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$ rm -f $(OBJ_FILES)
	@make -C printf clean

fclean: clean
	@$ rm -f $(NAME)
	@make -C printf fclean

re: fclean all

norm:
	norminette

.PHONY: all clean fclean re
