NAME = minishell

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
FILES = $(wildcard *.txt)

CC = gcc
CFLAGS =  -Wall -g -I.
LDFLAGS = -lreadline -lncurses
RM = rm -f
INCLUDE = minishell.h

$(NAME): $(OBJS)
		$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) $(FILES)

re: fclean all

leaks : re
	valgrind --leak-check=full ./$(NAME)

valgrind : re
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

.PHONY: all clean fclean re