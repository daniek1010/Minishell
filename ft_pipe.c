/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:39:57 by danevans          #+#    #+#             */
/*   Updated: 2024/09/11 11:46:52 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_create(int pipefd[2])
{
	if (pipe(pipefd) == -1)
		errors("Couldnt create pipe\n");
}

void	init_pipe(t_infos *tokens)
{
	tokens->pipefd[0] = -1;
	tokens->pipefd[1] = -1;
	tokens->prev_pipefd[0] = -1;
	tokens->prev_pipefd[1] = -1;
}

void	close_pipe(t_infos *tokens, int flag)
{
	if (flag == 0)
	{
		close_fd (tokens->pipefd[0]);
		close_fd (tokens->pipefd[1]);
	}
	else if (flag == 1)
	{
		close_fd (tokens->prev_pipefd[0]);
		close_fd (tokens->prev_pipefd[1]);
	}
	else
	{
		close_fd (tokens->pipefd[0]);
		close_fd (tokens->pipefd[1]);
		close_fd (tokens->prev_pipefd[0]);
		close_fd(tokens->prev_pipefd[1]);
	}
}

void	setup_pipes(t_infos *tokens, int is_last_command, int *flag)
{
	if (tokens->pipefd[0] > 0)
		close_pipe(tokens, 0);
	if (!is_last_command)
	{
		pipe_create(tokens->pipefd);
		*flag = 1;
	}
	else
		*flag = 0;
}

void	builtin_handler(t_command *cmd, t_infos *tokens)
{
	if (is_builtin(cmd->name))
	{
		if (cmd->redir_count > 0)
			handle_redirections(cmd, tokens);
		if (tokens->e_code == 1)
			return ;
		exec_builtin_path(cmd, tokens);
		restore_stdout(tokens);
	}
}
