/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cut_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 17:00:04 by riporth           #+#    #+#             */
/*   Updated: 2024/08/22 17:48:00 by riporth          ###   ########.fr       */
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


char	*fill_0(char *list, char *new)
{
	int	i;

	i = 1;
	while (list[i] != '\0' && list[i] != '"')
	{
		new[i - 1] = list[i];
		i++;
	}
	return (new);
}

char	*fill(char *ret, char *list, int x)
{
	int	i;

	i = 0;
	x += 1;
	while (list[x] != '\0')
	{
		ret[i] = list[x];
		i++;
		x++;
	}
	return (ret);
}

char	*make(char *list, int i)
{
	list = (char *)malloc(sizeof(char) * i + 1);
	if (!list)
		return (NULL);
	list[i] = '\0';
	return (list);
}


/* this function prints the cut out but dont handel the $ case */
char	*ft_cut_print(char *list)
{
	int		i;
	int		x;
	int		re;
	char	*new;
	char	*ret;

	i = 1;
	while (list[i] != '\0' && list[i] != '"')
		i++;
	x = i;
	while (list[x] != '\0')
	{
		x++;
		re++;
	}
	new = make(new, i - 1);
	ret = make(new, x);
	new = fill_0(list, new);
	// here should the $ case be handelt
	printf("%s", new);
	free(new);
	ret = fill(ret, list, i);
	return (ret);
}

int main() {
    // Example input string
    char list[] = "\"123456789\n\"Text"; // The new string will be "Sample"

    // Call the ft_cut function
    char *result = ft_cut_print(list);

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