/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft__new_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:50:03 by riporth           #+#    #+#             */
/*   Updated: 2024/09/06 17:35:37 by riporth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h> // used it for strcat

# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

int	pipe_count(const char *str, int i, int *count, int *in_word)
{
	*count += 1;
	*in_word = 1;
	if (str[i] == '>' && str[i + 1] == '>')
		i++;
	else if (str[i] == '<' && str[i + 1] == '<')
		i++;
	else if (str[i] == '>' && str[i + 1] == '|')
		i++;
	i++;
	return (i);
}

int	count_qoute(const char *str, int i, int *count, int	*in_word)
{
	char	a;

	a = str[i];
	i++;
	if (*in_word == 1)
		*count += 1;
	*in_word = 0;
	while (str[i] != '\0')
	{
		if (str[i] == a)
		{
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

int	count_word(const char *str, int i, int *count, int	*in_word)
{
	i++;
	if (*in_word == 1)
		*count += 1;
	*in_word = 0;
	while (str[i] != '\0')
	{
		if (strchr("|><\'\"", str[i]))
			break ;
		else if ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
			break ;
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
	in_word = 1;
	i = 0;
	while (str[i] != '\0')
	{
		if (strchr("|><", str[i]))
			i = pipe_count(str, i, &count, &in_word);
		else if (strchr("\'\"", str[i]))
			i = count_qoute(str, i, &count, &in_word);
		else if (!((str[i] <= 13 && str[i] >= 9) || str[i] == 32))
			i = count_word(str, i, &count, &in_word);
		else
		{
			in_word = 1;
			i++;
		}
	}
	return (count);
}

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------

int	count_string_length(const char *str, int i)
{
	int in_word;
	int	count;

	in_word = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (strchr("|><", str[i]))
			break ;
		else if (strchr("\'\"", str[i]))
			i = count_qoute(str, i, &count, &in_word);
		else if (!((str[i] <= 13 && str[i] >= 9) || str[i] == 32))
			i = count_word(str, i, &count, &in_word);
		else
			break ;
	}
	return (i);
}

char	*fill_word(const char *str, char *list, int *i)
{
	int	j;
	int	x;

	j = 0;
	x = 0;
	j = count_string_length(str, *i);
	j = j - *i;
	printf("j is %d",j);
	list = (char *)malloc(sizeof(char) * (j + 1));
	list[j] = '\0';
	while (x < j)
	{
		list[x] = str[*i];
		x++;
		*i += 1;
	}
	return (list);
}

char	*fill_direct(const char *str, char *list, int *i)
{
	int	x;

	x = 1;
	if (str[*i] == '>' && str[*i + 1] == '>')
		x++;
	else if (str[*i] == '<' && str[*i + 1] == '<')
		x++;
	else if (str[*i] == '>' && str[*i + 1] == '|')
		x++;
	list = (char *)malloc(sizeof(char) * (x + 1));
	if (!list)
		return (NULL);
	list[x] = '\0';
	list[0] = str[*i];
	if (x == 2)
	{
		(*i)++;
		list[1] = str[*i];
	}
	(*i)++;
	return (list);
}

char	**ft_token_fill(const char *str, char **list)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (((str[i] <= 13 && str[i] >= 9) || str[i] == 32))
		{
			i++;
			j--;
		}
		else if (strchr("|><", str[i]))
			list[j] = fill_direct(str, list[j], &i);
		else
			list[j] = fill_word(str, list[j], &i);
		j++;
	}
	return (list);
}

//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------

char	**ft_token_split(char const *s)
{
	int		word;
	char	**list;

	word = token_count_words(s);
	printf("-words = %d\n", word);
	list = (char **)malloc(sizeof(char *) * (word + 1));
	if (!list)
		return (NULL);
	list[word] = NULL;
	list = ft_token_fill(s, list);
	// cut function and $ fill
	return (list);
}


int	main(void)
{
	const char *test_str = "Hello 'world >'|test\"exam<ple\" <>";
	char **tokens;
	int i = 0;

	tokens = ft_token_split(test_str);

	// Print each token
	printf("Tokens:\n");
	while (tokens[i] != NULL)
	{
		printf("Token %d: %s\n", i + 1, tokens[i]);
		free(tokens[i]);
		i++;
	}
	free(tokens);
	return (0);
}
