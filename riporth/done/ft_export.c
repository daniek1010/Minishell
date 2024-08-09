/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:40:29 by riporth           #+#    #+#             */
/*   Updated: 2024/08/09 16:12:09 by riporth          ###   ########.fr       */
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

/* Function to export an environment variable */
int	export_env(const char *name, const char *value)
{
	// Check for null pointers
	if (name == NULL || value == NULL)
	{
		fprintf(stderr, "Error: Name and value must be non-null.\n");
		return (1);
	}
	// Set the environment variable
	if (setenv(name, value, 1) != 0)
	{
		perror("setenv");
		return (1);
	}
	return (0);
}

int	main(void)
{
	// Example usage
	export_env("MY_VAR", "HelloWorld");
	//Verify by printing the environment variable
	printf("MY_VAR = %s\n", getenv("MY_VAR"));
	return 0;
}
