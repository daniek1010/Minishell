/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 03:33:47 by danevans          #+#    #+#             */
/*   Updated: 2024/09/04 22:34:46 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection_char(t_command *cmd, char *token_array[], int *start)
{
	t_redir	*redir_command;

	if (is_redir(token_array, *start))
	{
		if (token_array[*start + 1])
		{
			redir_command = ft_create_redir(token_array[*start],
					token_array[*start + 1]);
			cmd->redir_cmd[cmd->redir_count++] = redir_command;
			*start += 2;
			return (1);
		}
		else
			return (-1);
	}
	return (0);
}

char	*ft_strstr(char *haystack, char *needle)
{
	char	*h;
	char	*n;

	if (!*needle)
	{
		return ((char *)haystack);
	}
	while (*haystack)
	{
		h = haystack;
		n = needle;
		while (*h && *n && (*h == *n))
		{
			h++;
			n++;
		}
		if (!*n)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}

int	is_dollar_char(t_command *cmd, char *token_array, int *start,
	t_infos *tokens)
{
	char	*value;

	value = ft_extract_variables(token_array, tokens);
	if (value)
	{
		if (value[0] == '"')
			value++;
		cmd->args[cmd->i++] = value;
		(*start)++;
		return (1);
	}
	return (0);
}

int	ft_isalnum(int c)
{
	return (((c > 96 && c < 123) || (c > 64 && c < 91))
		|| (c >= 48 && c <= 57));
}

int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}
