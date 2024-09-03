/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 11:55:55 by riporth           #+#    #+#             */
/*   Updated: 2024/09/03 16:02:20 by riporth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalnum(int c)
{
	return (((c > 96 && c < 123) || (c > 64 && c < 91))
		|| (c >= 48 && c <= 57));
}

char	*replace_substring(char *str, char *to_replace, char *replacement)
{
	char	*pos;
	char	*new_str;
	int		new_len;
	int		prefix_len;

	*pos = ft_strstr(str, to_replace);
	new_len = ft_strlen(str) - ft_strlen(to_replace) + ft_strlen(replacement);
	new_str = malloc((new_len + 1) * sizeof(char *));
	if (!new_str)
		return (NULL);
	prefix_len = pos - str;
	ft_strcpy(new_str, str);
	new_str[prefix_len] = '\0';
	ft_strcat(new_str, replacement);
	ft_strcat(new_str, pos + strlen(to_replace));
	return (new_str);
}

int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
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
	var = malloc((length + 1) * sizeof(char *));
	if (!var)
		return (NULL);
	ft_strncpy(var, str + start, length);
	var[length] = '\0';
	return (var);
}

char	*addvar(char *str, int *i, t_infos *tokens)
{
	char	*new;
	char	*var;
	char	*replace;
	int		x;

	x += i + 1;
	var = isolate_variable(str, i);
	if (str[x] == '?')
		replace = ft_strdup(ft_itoa(tokens->e_code));
	else
		replace = get_env_var(*(tokens->envp), var);
	if (!replace)
	{
		i += ft_strlen(var);
		return (str);
	}
	new = replace_substring(str, var, replace);
	i += strlen(replace);
	free (str);
	return (new);
}

char	*ft_extract_variables(char *str, t_infos *tokens)
{
	char	*new;
	int		i;
	char	*var;

	i = 0;
	if (str[0] == '\'' || (ft_strchr(str, '$')) == 0)
		return (str);
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			new = add_var(str, &i, tokens);
		else
			i++;
	}
	free (str);
	return (new);
}
