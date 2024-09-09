# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: riporth <riporth@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 13:51:19 by riporth           #+#    #+#              #
#    Updated: 2024/01/24 18:36:18 by riporth          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER   = server
CLIENT   = client
CC	     = cc
FLAGS    = -Wall -Werror -Wextra

LIBS	 = -L./libft -lft
LIBFT	 = libft.a

SRC_FILES_SERVER = ft_server.c		
SRC_FILES_CLIENT = ft_client.c     

SERVER_OBJ_FILES = $(SRC_FILES_SERVER:.c=.o)
CLIENT_OBJ_FILES = $(SRC_FILES_CLIENT:.c=.o)

HEADER_FILE = libft/libft.h
CC = cc
CFLAGS = -Wall -Wextra -Werror

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all: $(LIBFT) $(SERVER) $(CLIENT)

$(LIBFT) : 
	@make -C libft

$(SERVER) : $(SERVER_OBJ_FILES)
	@echo "$(GREEN)Building my_Server...$(RESET)"
	@$(CC) $(CFLAGS) -o $(SERVER) $(SERVER_OBJ_FILES) $(LIBS)
	@echo "$(GREEN)Build successful!$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ 

$(CLIENT) : $(CLIENT_OBJ_FILES)
	@echo "$(GREEN)Building my_Client...$(RESET)"
	@$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT_OBJ_FILES) $(LIBS)
	@echo "$(GREEN)Build successful!$(RESET)"
	
%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: all

clean:
	@echo "$(RED)Removing (clean)...$(RESET)"
	@$ rm -f $(SERVER_OBJ_FILES)
	@$ rm -f $(CLIENT_OBJ_FILES)
	@make -C libft clean
	@echo "$(GREEN)Removing successful!$(RESET)"

fclean: clean
	@echo "$(RED)Removing (fclean)...$(RESET)"
	@$ rm -f $(SERVER)
	@$ rm -f $(CLIENT)
	@make -C libft fclean
	@echo "$(GREEN)Removing successful!$(RESET)"

re: fclean all

norm:
	norminette

.PHONY: all clean fclean re
