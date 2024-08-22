/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:35:46 by riporth           #+#    #+#             */
/*   Updated: 2024/08/22 17:02:58 by riporth          ###   ########.fr       */
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


/* this function expect that at the position list[0] is a "
	and return only the cut out part of in " this" 
	it does not change the list part
*/
char	*ft_cut(char *list)
{
	int		i;
	char	*new;

	i = 1;
	while (list[i] != '\0' && list[i] != '"')
		i++;
	new = (char *)malloc(sizeof(char) * i);
	if (!new)
		return (NULL);
	i--;
	new[i] = '\0';
	i = 1;
	while (list[i] != '\0' && list[i] != '"')
	{
		new[i - 1] = list[i];
		i++;
	}
	return (new);
}

int main() {
    // Example input string
    char list[] = "\"123456789\"Text"; // The new string will be "Sample"

    // Call the ft_cut function
    char *result = ft_cut(list);

    // Check if the result is not NULL
    if (result) {
        // Print the result
        printf("Cut string: %s\n", result);

        // Free the dynamically allocated memory
        free(result);
    } else {
        printf("Memory allocation failed!\n");
    }

    return 0;
}