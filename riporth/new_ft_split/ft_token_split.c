/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:13:08 by riporth           #+#    #+#             */
/*   Updated: 2024/08/30 12:35:46 by riporth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		{
			count++;
			in_word = 0;
			if(str[i + 1] == '>' || str[i + 1] == '<')
				i++;
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
		else if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		{
			j++;
			list[j] = fill_direct(str, list[j], &i);
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
    const char *input = "echo\"hello      \'is\'    world\"|grep'lo'<<>>output.txt";

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