/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toke_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:00:40 by riporth           #+#    #+#             */
/*   Updated: 2024/08/28 17:25:35 by riporth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*list_length_create(const char *str, const int *i)
{
	int		x;
	int		y;
	char	*list;

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
			list[j] = fill_word(str, list[j], &i);
		}
	}
	return (list);
}
