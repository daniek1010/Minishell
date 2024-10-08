/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 00:53:50 by danevans          #+#    #+#             */
/*   Updated: 2024/09/19 00:14:41 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_io(int is_last_command, t_infos *tokens)
{
	if (tokens->prev_pipefd[0] != -1)
	{
		close_fd(tokens->prev_pipefd[1]);
		if (dup2(tokens->prev_pipefd[0], STDIN_FILENO) == -1)
		{
			perror ("dup2 failed");
			exit(EXIT_FAILURE);
		}
		close_fd(tokens->prev_pipefd[0]);
	}
	if (!is_last_command)
	{
		close_fd(tokens->pipefd[0]);
		tokens->save_fdout = dup(STDOUT_FILENO);
		if (dup2(tokens->pipefd[1], STDOUT_FILENO) == -1)
		{
			perror ("dup2 stdout failed");
			exit(EXIT_FAILURE);
		}
		close_fd(tokens->pipefd[1]);
	}
}

void	exec_cmd_builtin(t_command *cmd, int is_last_command, t_infos *tokens,
		int flag)
{
	pid_t	pid;

	if ((is_last_command) && (flag == 0))
		builtin_handler(cmd, tokens, is_last_command);
	else
	{
		signal_handlers_child();
		pid = fork_process();
		if (pid == 0)
		{
			builtin_handler(cmd, tokens, is_last_command);
			exit (tokens->e_code);
		}
		else if (pid > 0)
			wait_for_child(pid, tokens, is_last_command);
	}
}

void	exec_cmd(t_command *cmd, int is_last_command, t_infos *tokens, int flag)
{
	pid_t	pid;

	tokens->e_code = 0;
	if (is_builtin(cmd->name))
		exec_cmd_builtin(cmd, is_last_command, tokens, flag);
	else
	{
		signal_handlers_child();
		pid = fork();
		if (pid == 0)
			exec_child_process(tokens, cmd, is_last_command);
		else if (pid > 0)
			wait_for_child(pid, tokens, is_last_command);
	}
}

int	execute_commander(t_infos *tokens)
{
	int	i;
	int	is_last_cmd;
	int	flag;

	init_pipe(tokens);
	i = 0;
	while (i < tokens->cmd_index)
	{
		is_last_cmd = (i == tokens->cmd_index - 1);
		setup_pipes(tokens, is_last_cmd, &flag);
		exec_cmd(tokens->commands[i], is_last_cmd, tokens, flag);
		if (!flag)
			break ;
		if (!is_last_cmd)
		{
			tokens->prev_pipefd[0] = tokens->pipefd[0];
			tokens->pipefd[0] = -1;
			tokens->pipefd[1] = -1;
		}
		else
			close_pipe(tokens, 2);
		i++;
	}
	return (tokens->e_code);
}

/* Checks if execution is builtin function and then handle it
if(!builtin) it check if path is in Path and then execute.*/
int	exec_builtin_path(t_command *command, t_infos *tokens)
{
	char	*path;

	if (is_builtin(command->name))
		ft_check_builtin(command, tokens);
	else
	{
		path = ft_access(command->name, *(tokens->envp));
		if (command->name[0] == '|')
			tokens->e_code = pipe_start_error();
		else if (path == NULL)
			tokens->e_code = path_not_found(command);
		else if (execve(path, command->args, *(tokens->envp)) == -1)
		{
			perror("EXECVE");
			free(path);
			tokens->e_code = 13;
		}
	}
	return (tokens->e_code);
}
