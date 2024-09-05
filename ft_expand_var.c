/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:41:40 by danevans          #+#    #+#             */
/*   Updated: 2024/09/04 22:19:46 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_substring(char *str, char *to_replace, char *replacement)
{
	char	*pos;
	char	*new_str;
	int		new_len;
	int		prefix_len;

	pos = ft_strstr(str, to_replace);
	if (!pos)
		return (str);
	new_len = ft_strlen(str) - ft_strlen(to_replace) + ft_strlen(replacement);
	new_str = malloc((new_len + 1) * sizeof(char));
	if (!new_str)
		return (str);
	prefix_len = pos - str;
	ft_strcpy(new_str, str);
	new_str[prefix_len] = '\0';
	strcat(new_str, replacement);
	strcat(new_str, pos + strlen(to_replace));
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
	strncpy(var, str + start, length);
	var[length] = '\0';
	return (var);
}

char	*expand_var(t_infos *tokens, char *str, int x, int *flag)
{
	char	*var;
	char	*replace;

	var = isolate_variable(str, x);
	x++;
	if (str[x] == '?')
	{
		replace = ft_strdup(ft_itoa(tokens->e_code));
		*flag = 1;
	}
	else
		replace = get_env_var(*(tokens->envp), var);
	return (replace);
}

char	*add_var(char *str, int *i, t_infos *tokens)
{
	char	*new;
	char	*var;
	char	*replace;
	int		flag;
	char	*new_var;

	flag = 0;
	var = isolate_variable(str, *i);
	replace = expand_var(tokens, str, *i, &flag);
	if (!replace)
	{
		*i += ft_strlen(var);
		return (str);
	}
	new_var = ft_strjoin("$", var);
	new = replace_substring(str, new_var, replace);
	free (var);
	free (new_var);
	*i += ft_strlen(replace);
	if (flag)
		free (replace);
	free(str);
	return (new);
}

char	*ft_extract_variables(char *str, t_infos *tokens)
{
	int		i;

	i = 0;
	if (str[0] == '\'' || (ft_strchr(str, '$')) == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			str = add_var(str, &i, tokens);
		else
			i++;
	}
	return (str);
}
