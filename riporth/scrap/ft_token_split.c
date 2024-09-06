/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:13:08 by riporth           #+#    #+#             */
/*   Updated: 2024/09/05 16:08:33 by riporth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_qoute(const char *str, int i, int *count, int	*in_word)
{
	char	a;

	a = str[i];
	i++;
	*in_word = 1;
	*count += 1;
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

int	pipe_count(const char *str, int i, int *count, int *in_word)
{
	*count += 1;
	in_word = 0;
	if (str[i] == '>' && str[i + 1] == '>')
		i++;
	else if (str[i] == '<' && str[i + 1] == '<')
		i++;
	else if (str[i] == '>' && str[i + 1] == '|')
		i++;
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
			i = count_qoute(str, i, &count, &in_word);
		if (str[i] == '|' || str[i] == '>' || str[i] == '<')
			i = pipe_count(str, i, &count, &in_word);
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