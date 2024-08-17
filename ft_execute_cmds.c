/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:41:40 by danevans          #+#    #+#             */
/*   Updated: 2024/08/17 01:12:56 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_builtin(t_command *command, char *envp[])
{
	int	e_status;

	e_status = 0;
	if (ft_strcmp("echo", command->name) == 0)
		e_status = builtin_echo(command);
	else if (ft_strcmp("env", command->name) == 0)
		e_status = builtin_env(envp);
	else if (ft_strcmp("export", command->name) == 0)
		e_status = builtin_export(envp, command->args[1], command->args[2]);
	else if (ft_strcmp("unset", command->name) == 0)
		e_status = builtin_unset(&envp, command->args[1]);
	else if (ft_strcmp("cd", command->name) == 0)
		e_status = builtin_cd(envp, command->args[1]);
	else if (ft_strcmp("pwd", command->name) == 0)
		e_status = builtin_pwd();
	else if (ft_strcmp("exit", command->name) == 0)
	{	printf("here?\n");
		exit (0);
	}
	return (e_status);
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
			if (tokens->commands[0]->redir_count > 0)
				handle_redirections(tokens->commands[0], tokens);
			e_status = ft_execute(tokens->commands[0], envp, tokens);
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
