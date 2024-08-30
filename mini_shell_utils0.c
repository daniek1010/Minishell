/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell_utils0.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 03:33:47 by danevans          #+#    #+#             */
/*   Updated: 2024/08/30 15:19:23 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_write_env(char *value)
{
	int		i;
	int		len;
	char	*env_key;

	i = 0;
	while (value[len] != ' ' && value[len] != '\''
		&& value[len] != '"' && value[len] != '\0')
		len++;
	env_key = (char *)malloc(sizeof (char) * (len + 1));
	if (!env_key)
		return (NULL);
	while (*value != ' ' && *value != '\'' && *value != '"'
		&& *value != '\0')
		env_key[i++] = *value++;
	env_key[i] = '\0';
	return (env_key);
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

char	*ft_special_char(char *args, char **before_env, char **after_env, t_infos *tokens)
{
	char	*value;
	char	*new_value;
	char	*get_env;
	char	*env_key;

	// printf("??? %s\n", args);

	
	value = ft_strchr(args, '$');
	// printf("after sserch%s\n", args);
	if (value)
	{
		*before_env = ft_substr(args, 0, (value - args));
		value++;
		if (ft_strncmp(value, "?", 1) == 0)
		{
			*after_env = ft_strdup(value + 1);
			new_value = ft_strdup(ft_itoa(tokens->e_code));
		}
		else
		{
			env_key = ft_write_env(value);
			get_env = get_env_var(*(tokens->envp), env_key);
			if (get_env == NULL)
				return ("");
			else
			{
				new_value = ft_strdup(get_env);
				*after_env = ft_strdup(value + ft_strlen(env_key));
			}
		}
		// return (new_value);
		printf("found\n");
		return (value);
	}
	return (NULL);
}

int	is_dollar_char(t_command *cmd, char *token_array, int *start, t_infos *tokens)
{
	char	*value;
	char	*before_env;
	char	*after_env;
	char	*new_args;

	value = ft_special_char(token_array, &before_env, &after_env, tokens);
	if (value)
	{
		printf("does it get here\n");
		new_args = ft_strjoin(before_env, value);
		cmd->args[cmd->i++] = ft_strjoin(new_args, after_env);
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

// int	is_dollar_char(t_command *cmd, char *token_array[], int *start,
// 		char *envp[], t_infos *tokens)
// {
// 	char	*value;

// 	value = ft_special_char(envp, token_array[*start], cmd, tokens);
// 	if (value)
// 	{
// 		cmd->args[cmd->i++] = value;
// 		*start = *start + 1;
// 		return (1);
// 	}
// 	return (0);
// }

// char	*ft_special_char(char *envp[], const char *str, t_command *cmd, t_infos *tokens)
// {
// 	char	*value;
// 	char	*new_value;
// 	char	*get_env;
// 	char	*env_key;

// 	value = ft_strchr(str, '$');
// 	if (value)
// 	{
// 		value++;
// 		if (ft_strncmp(value, "?", 1) == 0)
// 			new_value = ft_strdup(ft_itoa(tokens->e_code));
// 		else
// 		{
// 			env_key = ft_write_env(value);
// 			get_env = get_env_var(envp, env_key);
// 			if (get_env == NULL)
// 				new_value = ft_strdup("404");
// 			else
// 				new_value = ft_strdup(get_env);
// 		}
// 		return (new_value);
// 	}
// 	return (NULL);
// }