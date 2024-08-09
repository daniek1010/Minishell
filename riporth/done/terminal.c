/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:50:27 by riporth           #+#    #+#             */
/*   Updated: 2024/08/09 16:24:57 by riporth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <curses.h>
#include <term.h>

#define MAX_INPUT_SIZE 2097152

typedef	struct
{
	char buffer[MAX_INPUT_SIZE];
	int index;
} InputState;

/*
	char	**items;   Dynamic array to store strings
	int		size;      Current number of elements
	int		capacity;  Current capacity of the array
	int		current;   Current index for moving up/down
*/
typedef struct
{
	char	**items;
	int		size;
	int		capacity;
	int		current;
} ExpandingList;

void initList(ExpandingList *list) 
{
	list->items = malloc(2 * sizeof(char *));
	list->size = 0;
	list->capacity = 2;
	list->current = -1;
	// No current item initially
}

// Function to expand the list's capacity
void	expandList(ExpandingList *list)
{
	list->capacity *= 2;
	list->items = realloc(list->items, list->capacity * sizeof(char *));
	if (list->items == NULL)
	{
		perror("Failed to expand list");
		exit(EXIT_FAILURE);
	}
}

// Function to add a string to the list
void addToList(ExpandingList *list, const char *item)
{
	if (list->size >= list->capacity)
	{
		expandList(list);
	}
	list->items[list->size] = strdup(item);
	list->size++;
	list->current = list->size - 1;
	// Set the current index to the last item added
}

// Function to move up in the list
void	moveUp(ExpandingList *list)
{
	if (list->current > 0)
	{
		printf("Moved up to: %s\n", list->items[list->current]);
		list->current--;
	}
	else
	{
		printf("Already at the top of the list.\n");
	}
}

// Function to move down in the list
void	moveDown(ExpandingList *list)
{
	if (list->current < list->size - 1)
	{
		list->current++;
		printf("Moved down to: %s\n", list->items[list->current]);
	}
	else
	{
		printf("Already at the bottom of the list.\n");
	}
}

// Function to free the list's memory
void	freeList(ExpandingList *list)
{
	int	i;

	i = 0;
	while (i < list->size)
	{
		free(list->items[i]);
		i++;
	}
	free(list->items);
}

// Function to set terminal in raw mode
void	enableRawMode()
{
	struct termios raw;

	tcgetattr(STDIN_FILENO, &raw);
	raw.c_lflag &= ~(ICANON | ECHO);
	// Disable canonical mode and echo
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

// Function to reset terminal to original state
void	disableRawMode()
{
	struct termios	original;

	tcgetattr(STDIN_FILENO, &original);
	original.c_lflag |= (ICANON | ECHO);
	// Enable canonical mode and echo
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &original);
}

void	handle_sigint(int sig)
{
	printf("Ctrl+C pressed! ...\n");
}


int	main()
{
	ExpandingList list;
	char	key;
	char	seq[2];
	InputState	state;

	state.index = 0;
	initList(&list);
	//Enable raw mode
	enableRawMode();
	signal(SIGINT, (void (*)(int))handle_sigint);
	printf("Enter text (press 'Ctrl+D' to exit):\n");

	while (1)
	{
		// Read a single character
		if (read(STDIN_FILENO, &key, 1) == -1)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}
		// Check for Ctrl+D (EOF) to exit the program
		if (key == '\x03')
		{
			printf("Ctrl+key pressed!\n");
		}
		// Detect Ctrl+D (ASCII 4) - usually indicates end of input
		else if (key == '\x04')
		{
			printf("Ctrl+D pressed! Exiting...\n");
			break ;
			// Exit the loop
		}
		// Detect Ctrl+/ (ASCII 31)
		else if (key == '\x1f')
		{
			printf("Ctrl+/ pressed!\n");
		}
		// Check if the character is the escape sequence (start of arrow keys)
		if (key == 27)
		{
			// Check the next two characters for arrow key detection
			if (read(STDIN_FILENO, &seq[0], 1) == -1
				|| read(STDIN_FILENO, &seq[1], 1) == -1)
			{
				perror("read");
				exit(EXIT_FAILURE);
			}
			// Check for up arrow key (Escape sequence for up arrow is '\x1b[A')
			if (seq[0] == 91 && seq[1] == 65)
			{
				moveUp(&list);
				printf("Up arrow key pressed!\n");
			}
			if (seq[0] == 91 && seq[1] == 66) 
			{
				moveDown(&list);
				printf("Down arrow key pressed!\n");
			}
		}
		else if (key == 10) // If Enter key is pressed
		{
			state.buffer[state.index] = '\0';
			// Null-terminate the string
			addToList(&list, state.buffer);
			printf("\ntext received: %s\n", state.buffer);
			state.index = 0;
			// Reset the state.buffer state.index
		}
		else
		{
			// Add character to state.buffer and echo it
			if (state.index < MAX_INPUT_SIZE - 1)
			{
				state.buffer[state.index++] = key;
				putchar(key);
				fflush(stdout);
				// Flush the output state.buffer
			}
		}
	}
	// end Terminal
	disableRawMode();
	freeList(&list);
	// free the rest
	printf("\nExiting...\n");
	return (0);
}
