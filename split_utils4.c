/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:51:00 by riporth           #+#    #+#             */
/*   Updated: 2024/09/10 14:10:07 by riporth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_var(t_infos *tokens, char *str, int x)
{
	char	*var;
	char	*replace;

	var = isolate_variable(str, x);
	x++;
	if (str[x] == '?')
	{
		replace = ft_itoa(tokens->e_code);
		return (replace);
	}
	replace = get_env_var(*(tokens->envp), var);
	if (!replace)
	{
		free (var);
		return (replace);
	}
	replace = ft_strdup(get_env_var(*(tokens->envp), var));
	return (replace);
}

char	*remove_char_at_position(char *str, int pos)
{
	int		len;
	char	*new_str;

	len = ft_strlen(str);
	new_str = (char *)malloc((len) * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strncpy(new_str, str, pos);
	ft_strcpy(new_str + pos, str + pos + 1);
	free (str);
	return (new_str);
}

char	*remove_substring(const char *str, const char *to_rep, int *i)
{
	char	*pos;
	char	*new_str;
	int		new_len;
	int		prefix_len;
	int		to_rep_len;

	to_rep_len = strlen(to_rep);
	pos = (char *)str + *i;
	prefix_len = pos - str;
	new_len = ft_strlen(str) - to_rep_len;
	new_str = malloc(new_len + 1);
	if (!new_str)
		return (NULL);
	ft_strncpy(new_str, str, prefix_len);
	new_str[prefix_len] = '\0';
	ft_strcat(new_str, pos + to_rep_len);
	return (new_str);
}

char	*add_var(char *str, int *i, t_infos *tokens)
{
	char	*new;
	char	*var;
	char	*replace;
	char	*new_var;

	var = isolate_variable(str, *i);
	replace = expand_var(tokens, str, *i);
	if (var == NULL)
		new_var = ft_strjoin("$", "?");
	else
		new_var = ft_strjoin("$", var);
	if (!replace)
		new = remove_substring(str, new_var, i);
	else
	{
		new = replace_substring(str, new_var, replace, i);
		*i += ft_strlen(replace);
	}
	if (replace)
		free (replace);
	free (var);
	free (new_var);
	free(str);
	return (new);
}

char	*ft_extract_variables(char *str, t_infos *tokens)
{
	int	i;
	int	in_single_qoute;
	int	in_double_qoute;

	i = 0;
	in_single_qoute = 0;
	in_double_qoute = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' && in_single_qoute == 0)
			in_double_qoute = !in_double_qoute;
		else if (str[i] == '\'' && in_double_qoute == 0)
			in_single_qoute = !in_single_qoute;
		if (str[i] == '$' && in_single_qoute == 0)
		{
			if (is_valid_var_char(str[i + 1]) || str[i + 1] == '?')
				str = add_var(str, &i, tokens);
			else
				i++;
		}
		else
			i++;
	}
	return (str);
}
