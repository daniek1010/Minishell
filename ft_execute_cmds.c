/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:41:40 by danevans          #+#    #+#             */
/*   Updated: 2024/08/21 13:18:00 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	iterate_pipe_index(t_infos *tokens, char *envp[])
{
	int		i;
	int		e_status;
	t_pipe	*pipe;

	i = 0;
	while (i < tokens->pipe_index)
	{
		pipe = tokens->pipes[i];
		e_status = ft_create_pipe(pipe, envp, tokens);
		i++;
	}
	return (e_status);
}

int	handle_builtin_exit(t_command *cmd, t_infos *tokens, char *envp[])
{
	int	e_status;

	e_status = -5;
	if (is_builtin(cmd->name))
	{
		if (cmd->redir_count > 0)
			handle_redirections(cmd, tokens);
		e_status = ft_execute(cmd, envp, tokens);
	}
	return (e_status);
}

int	run_child(t_infos *tokens, char *envp[])
{
	int	e_status;

	if (tokens->commands[0]->redir_count > 0)
		handle_redirections(tokens->commands[0], tokens);
	e_status = ft_execute(tokens->commands[0], envp, tokens);
	return (e_status);
}

int	execute_command(t_infos *tokens, char *envp[])
{
	pid_t	pid;
	int		e_status;

	e_status = 0;
	if (tokens->pipe_index > 0)
		e_status = iterate_pipe_index(tokens, envp);
	else
	{
		e_status = handle_builtin_exit(tokens->commands[0], tokens, envp);
		if (e_status != -5)
			return (e_status);
		pid = fork();
		if (pid == 0)
		{
			e_status = run_child(tokens, envp);
			exit (e_status);
		}
		else if (pid > 0)
		{
			waitpid(pid, &e_status, 0);
			return (e_status);
		}
	}
	return (e_status);
}

int	ft_execute(t_command *command, char *envp[], t_infos *tokens)
{
	char	*path;
	int		e_status;

	e_status = 0;
	if (is_builtin(command->name))
		e_status = ft_check_builtin(command, envp);
	else
	{
		path = ft_access(command->name, envp);
		if (path == NULL)
		{
			perror("PATH");
			e_status = 2;
			return (e_status);
		}
		if (execve(path, command->args, envp) == -1)
		{
			perror("EXECVE");
			free(path);
			e_status = 13;
			return (e_status);
		}
	}
	return (e_status);
}
