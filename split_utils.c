/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:38:57 by riporth           #+#    #+#             */
/*   Updated: 2024/09/18 09:47:17 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

char	*ft_strcat(char *dest, const char *src)
{
	char	*dest_end;

	dest_end = dest;
	while (*dest_end != '\0')
	{
		dest_end++;
	}
	while (*src != '\0')
	{
		*dest_end = *src;
		dest_end++;
		src++;
	}
	*dest_end = '\0';
	return (dest);
}

int	pipe_count(const char *str, int i, int *count, int *in_word)
{
	*count += 1;
	*in_word = 1;
	if (str[i] == '>' && str[i + 1] == '>')
		i += 2;
	else if (str[i] == '<' && str[i + 1] == '<')
		i += 2;
	else if (str[i] == '>' && str[i + 1] == '|')
		i += 2;
	else if (str[i] == '|' && str[i + 1] == '|')
	{
		while (str[i] == '|')
			i++;
	}
	else
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

int	count_word_2(const char *str, int i, int *count, int	*in_word)
{
	i++;
	if (*in_word == 1)
		*count += 1;
	*in_word = 0;
	while (str[i] != '\0')
	{
		if (ft_strchr("|><\'\"", str[i]))
			break ;
		else if ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
			break ;
		i++;
	}
	return (i);
}
