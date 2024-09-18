/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell_utils0.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 23:45:26 by danevans          #+#    #+#             */
/*   Updated: 2024/09/18 12:25:37 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_n_handeler(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	if (str[1] != 'n')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	count_heredoc(t_command *cmd)
{
	int		i;
	int		last_heredoc;

	i = 0;
	while (i < cmd->redir_count)
	{
		if (cmd->redir_cmd[i]->type == HEREDOC)
			last_heredoc = i;
		i++;
	}
	return (last_heredoc);
}

int	handle_heredoc(t_command *cmd, t_infos *tokens)
{
	int	i;

	i = 0;
	while (i < cmd->redir_count)
	{
		if (cmd->redir_cmd[i]->type == HEREDOC)
			redir_here_docs(cmd->redir_cmd[i]->file, tokens, cmd, i);
		i++;
	}
	return (0);
}

void	close_pipefd(int pipefd[2])
{
	close_fd(pipefd[0]);
	close_fd(pipefd[1]);
}

void	exec_child_process(t_infos *tokens, t_command *cmd,
			int is_last_command)
{
	handle_heredoc(cmd, tokens);
	redirect_io(is_last_command, tokens);
	handle_redirections(cmd, tokens);
	if (cmd->name == NULL)
	{
		if (tokens->pipefd[1] != -1)
			write(tokens->pipefd[1], "", STDOUT_FILENO);
		exit (0);
	}
	exec_builtin_path(cmd, tokens);
	exit (tokens->e_code);
}
