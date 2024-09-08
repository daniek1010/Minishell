/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell_utils5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:25:24 by danevans          #+#    #+#             */
/*   Updated: 2024/09/08 19:14:39 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_name_args(t_command *cmd)
{
	int	i;

	if (cmd->name)
	{
		free(cmd->name);
		cmd->name = NULL;
	}
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			free (cmd->args[i]);
			cmd->args[i] = NULL;
			i++;
		}
		free(cmd->args);
		cmd->args = NULL;
	}
}

void	free_command(t_command *cmd)
{
	int	i;

	if (cmd)
	{
		free_name_args(cmd);
		if (cmd->redir_cmd)
		{
			i = 0;
			while (cmd->redir_cmd[i])
			{
				if (cmd->redir_cmd[i]->file)
					free (cmd->redir_cmd[i]->file);
				free (cmd->redir_cmd[i]);
				cmd->redir_cmd[i] = NULL;
				i++;
			}
			free(cmd->redir_cmd);
			cmd->redir_cmd = NULL;
		}
		free(cmd);
		cmd = NULL;
	}
}

void	free_tokens(t_infos *tokens)
{
	int	i;

	if (tokens)
	{
		if (tokens->cmd_index > 0)
		{
			i = 0;
			while (i < tokens->cmd_index)
			{
				free_command(tokens->commands[i]);
				i++;
			}
		}
		free(tokens->commands);
		tokens->commands = NULL;
	}
}

char	*ft_strchr(const char *str, char c)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == c)
			return ((char *) str);
		str++;
	}
	return (NULL);
}

void	add_shlvl(t_infos *tokens)
{
	char	*shlvl_get;
	char	*shlvl_set;
	int		shlvl_i;

	shlvl_get = get_env_var(*(tokens->envp), "SHLVL");
	shlvl_i = atoi(shlvl_get);
	shlvl_i += 1;
	shlvl_set = ft_itoa(shlvl_i);
	set_env_var(tokens->envp, "SHLVL", shlvl_set);
	free(shlvl_set);
}
