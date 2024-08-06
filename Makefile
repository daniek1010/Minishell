NAME = minishell

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS =  -Wall -I.
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
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re