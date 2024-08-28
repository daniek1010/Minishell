/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:13:08 by riporth           #+#    #+#             */
/*   Updated: 2024/08/28 16:56:46 by riporth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int	count_qoute(const char *str, int i, char a)
{
	i++;
	while (str[i] != '\0')
	{
		if (str[i] == a)
		{
			break ;
		}
		i++;
	}
	return (i);
}

int	token_count_words(const char *str)
{
	int	count;
	int	in_word;
	int	i;

	count = 0;
	in_word = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			count++;
			in_word = 1;
			i = count_qoute(str, i, str[i]);
		}
		if (((str[i] <= 13 && str[i] >= 9) || str[i] == 32))
			in_word = 0;
		else if (in_word == 0)
		{
			in_word = 1;
			count++;
		}
		i++;
	}
	return (count);
}

// fill function
//
//
// -----------------------------------------------------------------------
// ------------------------------------ add count word length function
//

char	*list_length_create(const char *str, const int *i)
{
	int	x;
	int	y;
	char *list;

	y = *i;
	if (str[*i] == '\'' || str[*i] == '\"')
		y = count_qoute (str, y, str[*i]);
	else
	{
		while (!((str[y] <= 13 && str[y] >= 9) || str[y] == 32)
			&& str[y] != '\0')
			y ++;
	}
	x = y - *i;
	list = (char *)malloc(sizeof(char) * (x + 1));
	if (!list)
		return (NULL);
	list[x] = '\0';
	return (list);
}

char	*fill_qoute_case(const char *str, char *list, int *i, char a)
{
	int	x;

	x = 0;
	list = list_length_create(str, i);
	(*i)++;
	if (!list)
		return (NULL);
	while (str[*i] != '\0' && str[*i] != a)
	{
		list[x] = str[*i];
		x++;
		(*i)++;
	}
	(*i)++;
	return (list);
}

char	*fill_word(const char *str, char *list, int *i)
{
	int	x;

	x = 0;
	list = list_length_create(str, i);
	while (str[*i] != '\0')
	{
		if (str[*i] == '\'' || str[*i] == '\"')
			break ;
		if ((str[*i] <= 13 && str[*i] >= 9) || str[*i] == 32)
			break ;
		list[x] = str[*i];
		x++;
		(*i)++;
	}
	return (list);
}

char	**ft_token_fill(const char *str, char **list)
{
	int	i;
	int	j;
	int	in_word;

	i = 0;
	j = -1;
	in_word = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			j++;
			list[j] = fill_qoute_case(str, list[j], &i, str[i]);
		}
		else if ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
			i++;
		else
		{
			j++;
			list[j] = fill_word(str, list[j], &i);
		}
	}
	return (list);
}

// -----------------------------------------------------------

char	**ft_split(char const *s)
{
	int		i;
	char	**list;

	i = token_count_words(s);
	printf("i is %d\n",i);
	list = (char **)malloc(sizeof(char *) * (i + 1));
	if (!list)
		return (NULL);
	list[i] = NULL;
	list = ft_token_fill(s, list);
	return (list);
}

int main()
{
    // Example input string
    const char *str = "Hello 'world of quotes' this is \"a test\" of split";
    // Use the ft_split function to split the string into tokens
    char **result = ft_split(str);
    // Print the tokens
    int i = 0;
    while (result[i] != NULL)
    {
        printf("Token %d: -%s-\n", i + 1, result[i]);
        free(result[i]); // Free each token after printing it
        i++;
    }

    free(result); // Free the array of tokens
    return 0;
}