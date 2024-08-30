/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:13:08 by riporth           #+#    #+#             */
/*   Updated: 2024/08/30 11:56:23 by riporth          ###   ########.fr       */
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
} */