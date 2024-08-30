/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:13:08 by riporth           #+#    #+#             */
/*   Updated: 2024/08/30 13:49:18 by riporth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_special_char(const char *str, int i)
{
	if (str[i] == '|' || str[i] == '>' || str[i] == '<')
	{
		i++;
		if (str[i] == '>' || str[i] == '<')
			i++;
	}
	else
	{
		i++;
		i = count_qoute(str, i, str[i]);
	}
	return (i);
}

int	check_special_char(const char *str, int i)
{
	if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		return (1);
	else if (str[i] == '\'' || str[i] == '\"')
		return (1);
	return (0);
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
		if (check_special_char(str, i))
		{
			count++;
			in_word = 1;
			i = token_special_char(str, i);
		}
		else if (((str[i] <= 13 && str[i] >= 9) || str[i] == 32))
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

char	**ft_token_fill(const char *str, char **list)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
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
			if (str[i] == '|' || str[i] == '>' || str[i] == '<')
				list[j] = fill_direct(str, list[j], &i);
			else
				list[j] = fill_word(str, list[j], &i);
		}
	}
	return (list);
}

char	**ft_token_split(char const *s)
{
	int		i;
	char	**list;

	i = token_count_words(s);
	list = (char **)malloc(sizeof(char *) * (i + 1));
	if (!list)
		return (NULL);
	list[i] = NULL;
	list = ft_token_fill(s, list);
	return (list);
}

/*
int main() 
{
    // Test string that includes quotes, pipes, redirections, and whitespace
    const char *input = "echo\"hello \'is\'    world\"|grep'lo'<<>>output.txt";

    // Tokenize the input string
    char **tokens = ft_token_split(input);

    // Print out the tokens
    if (tokens) {
        printf("Tokens:\n");
        for (int i = 0; tokens[i] != NULL; i++) {
            printf("[%d]: %s\n", i, tokens[i]);
            free(tokens[i]); // Don't forget to free each token after use
        }
        free(tokens); // Free the array of tokens
    }

    return 0;
}

/*
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
*/