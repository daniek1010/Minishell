/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:44:50 by riporth           #+#    #+#             */
/*   Updated: 2024/09/10 13:46:24 by riporth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (ft_strchr("|><", str[i]))
			i = pipe_count(str, i, &count, &in_word);
		else if (ft_strchr("\'\"", str[i]))
			i = count_qoute(str, i, &count, &in_word);
		else if (!((str[i] <= 13 && str[i] >= 9) || str[i] == 32))
			i = count_word_2(str, i, &count, &in_word);
		else
		{
			in_word = 1;
			i++;
		}
	}
	return (count);
}

int	count_string_length(const char *str, int i)
{
	int	in_word;
	int	count;

	in_word = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (ft_strchr("|><", str[i]))
			break ;
		else if (ft_strchr("\'\"", str[i]))
			i = count_qoute(str, i, &count, &in_word);
		else if (!((str[i] <= 13 && str[i] >= 9) || str[i] == 32))
			i = count_word_2(str, i, &count, &in_word);
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
		if ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
		{
			i++;
			j--;
		}
		else if (ft_strchr("|><", str[i]))
			list[j] = fill_direct(str, list[j], &i);
		else
			list[j] = fill_word(str, list[j], &i);
		j++;
	}
	return (list);
}
