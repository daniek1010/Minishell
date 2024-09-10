/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:49:09 by riporth           #+#    #+#             */
/*   Updated: 2024/09/10 13:50:33 by riporth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fill_part_one(const char *str, int *j, int i)
{
	char	*new_str;
	int		len;

	len = ft_strlen(str);
	new_str = (char *)malloc((len + 1) * sizeof(char));
	new_str[len] = '\0';
	if (!new_str)
		return (NULL);
	while (*j < i)
	{
		new_str[*j] = str[*j];
		*j += 1;
	}
	return (new_str);
}

char	*fill_part_two(const char *str, char *new_str, int j, int i)
{
	while (str[i] != '\0')
	{
		new_str[j] = str[i];
		j++;
		i++;
	}
	return (new_str);
}

char	*remove_char( char *str, char to_remove, int i)
{
	char	*new_str;
	int		j;

	j = 0;
	new_str = fill_part_one(str, &j, i);
	if (!new_str)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] != to_remove)
		{
			new_str[j] = str[i];
			j++;
		}
		else
			break ;
		i++;
	}
	if (str[i] != '\0')
		new_str = fill_part_two(str, new_str, j, i);
	free(str);
	return (new_str);
}

char	*replace_substring(char *str, char *to_rep, char *repment, int *i)
{
	char	*pos;
	char	*new_str;
	int		new_len;
	int		prefix_len;

	pos = str + (*i);
	prefix_len = pos - str;
	new_len = (ft_strlen(str) - ft_strlen(to_rep)) + ft_strlen(repment);
	if (new_len == 0)
		return (str);
	new_str = malloc((new_len + 1) * sizeof(char));
	if (!new_str)
		return (str);
	ft_strncpy(new_str, str, prefix_len);
	new_str[prefix_len] = '\0';
	ft_strcat(new_str, repment);
	ft_strcat(new_str, pos + ft_strlen(to_rep));
	return (new_str);
}

char	*isolate_variable(char *str, int i)
{
	int		length;
	int		start;
	char	*var;

	if (str[i] != '$')
		return (NULL);
	i++;
	start = i;
	while (is_valid_var_char(str[i]))
		i++;
	length = i - start;
	if (length == 0)
		return (NULL);
	var = malloc((length + 1) * sizeof(char));
	if (!var)
		return (NULL);
	ft_strncpy(var, str + start, length);
	var[length] = '\0';
	return (var);
}
