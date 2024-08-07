/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:28:36 by riporth           #+#    #+#             */
/*   Updated: 2024/08/07 14:32:07 by riporth          ###   ########.fr       */
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

/*Use the unsetenv function to remove the environment variable*/
int my_unset(const char *name)
{
	if (unsetenv(name) != 0)
	{
		perror("unsetenv");
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
/*	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <variable_name>\n", argv[0]);
		return 1;
    }
*/
	//const char *var_name = argv[1];

	if (my_unset("MY_VAR") != 0)
	{
		fprintf(stderr, "Failed to unset variable: %s\n", "MY_VAR");
		return (1);
	}

	printf("Unset variable: %s\n", "MY_VAR");
	return (0);
}
