/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell_utils5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:25:24 by danevans          #+#    #+#             */
/*   Updated: 2024/08/16 20:34:51 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_name_args(t_command *cmd)
{
	int	i;

	if (cmd->name)
		free(cmd->name);
	cmd->name = NULL;
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

void	free_pipes(t_infos *tokens)
{
	int	i;

	i = 0;
	while (i < tokens->pipe_index)
	{
		free_command(tokens->pipes[i]->cmd1);
		free_command(tokens->pipes[i]->cmd2);
		free(tokens->pipes[i]);
		tokens->pipes[i] = NULL;
		i++;
	}
}

void	free_tokens(t_infos *tokens)
{
	int	i;

	if (!tokens)
		return ;
	if (tokens->pipe_index > 0)
		free_pipes(tokens);
	if (tokens->cmd_index > 0)
	{
		i = 0;
		while (i < tokens->cmd_index)
		{
			free_command(tokens->commands[i]);
			i++;
		}
	}
	free(tokens->pipes);
	tokens->pipes = NULL;
	free(tokens->commands);
	tokens->commands = NULL;
	free(tokens);
	tokens = NULL;
}
