/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell_utils0.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 03:33:47 by danevans          #+#    #+#             */
/*   Updated: 2024/08/21 13:25:16 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_write_env(char *value)
{
	int		i;
	int		len;
	char	*env_key;

	i = 0;
	while (value[len] != ' ' && value[len] != '\0')
		len++;
	env_key = (char *)malloc(sizeof (char) * (len + 1));
	if (!env_key)
		return (NULL);
	while (*value != ' ' && *value != '\0')
		env_key[i++] = *value++;
	env_key[i] = '\0';
	return (env_key);
}

char	*ft_special_char(char *envp[], const char *str)
{
	char	*value;
	char	*new_value;
	char	*get_env;
	char	*env_key;

	value = ft_strchr(str, '$');
	if (value)
	{
		value++;
		if (ft_strncmp(value, "?", 1) == 0)
			printf("what do i do ??\n");
		else
		{
			env_key = ft_write_env(value);
			get_env = get_env_var(envp, env_key);
			if (get_env == NULL)
				new_value = ft_strdup("404");
			else
				new_value = ft_strdup(get_env);
		}
		return (new_value);
	}
	return (NULL);
}

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

int	is_dollar_char(t_command *cmd, char *token_array[], int *start, 
		char *envp[])
{
	char	*value;

	value = ft_special_char(envp, token_array[*start]);
	if (value)
	{
		cmd->args[cmd->i++] = value;
		*start = *start + 1;
		return (1);
	}
	return (0);
}

void	destroy_cmd_use_pipe_cmd(t_infos *tokens)
{
	int	k;

	k = 0;
	while (k < tokens->cmd_index)
	{
		free_command(tokens->commands[k]);
		k++;
	}
	free(tokens->commands);
}
