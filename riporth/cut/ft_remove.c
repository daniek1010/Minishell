/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:51:13 by riporth           #+#    #+#             */
/*   Updated: 2024/08/23 10:46:49 by riporth          ###   ########.fr       */
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

char	*make(char *list, int i)
{
	list = (char *)malloc(sizeof(char) * i + 1);
	if (!list)
		return (NULL);
	list[i] = '\0';
	return (list);
}


/* this re,oves all " but it dosent handel the
	' " ' case in witch the " should not be removed!
*/
char	*
*ft_remove(char	*str)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '\"')
			j++;
		i++;
	}
	ret = make(ret, i - j);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '\"')
		{
			ret[j] = str[i];
			j++;
		}
		i++;
	}
	//free(str); this should be active but the main dosent use malloc
	return (ret);
}

int main() {
    // Example input string
    char list[] = "\"123456789\"Text"; // The new string will be "Sample"

    // Call the ft_cut function
    char *result = ft_remove(list);

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