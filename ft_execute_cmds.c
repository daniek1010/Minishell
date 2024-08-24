/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:41:40 by danevans          #+#    #+#             */
/*   Updated: 2024/08/24 16:41:18 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* cchek and create the number of pipes we have in our token*/
int	iterate_pipe_index(t_infos *tokens, char **envp[])
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

/* check for redir, then handles redir before exit */
int	handle_builtin_exit(t_command *cmd, t_infos *tokens, char **envp[])
{
	cmd->e_status = -5;
	if (is_builtin(cmd->name))
	{
		if (cmd->redir_count > 0)
			handle_redirections(cmd, tokens);
		cmd->e_status = ft_execute(cmd, envp, tokens);
	}
	return (cmd->e_status);
}

/* helper for execute_command to handle the child process if created*/
int	run_child(t_infos *tokens, char **envp[])
{
	if (tokens->commands[0]->redir_count > 0)
		handle_redirections(tokens->commands[0], tokens);
	tokens->commands[0]->e_status = ft_execute(tokens->commands[0], envp, tokens);
	printf("return from assignment not found %d\n", tokens->commands[0]->e_status);
	return (tokens->commands[0]->e_status);
}

/* my data was stored in cmd , but if pipe exist then we store in
pipe->cmd1(start < pipe(position) and cmd2(pipe(position + 1) < NULL || next_pipe)) 
sso if (pipe exist), we use pipe to process the cmds and exectute but if(!pipe exist)
we use the copy of cmd and then set up child fork is necessary and then execute */
int	execute_command(t_infos *tokens, char **envp[])
{
	pid_t	pid;
	// int		status;

	if (tokens->pipe_index > 0)
		iterate_pipe_index(tokens, envp);
		// tokens->e_code = iterate_pipe_index(tokens, envp);
	else
	{
		tokens->commands[0]->e_status = handle_builtin_exit(tokens->commands[0], tokens, envp);
		if (tokens->commands[0]->e_status != -5)
			return (tokens->commands[0]->e_status);
		pid = fork();
		if (pid == 0)
		{
			tokens->commands[0]->e_status = run_child(tokens, envp);
			printf("from child process %d\n", tokens->commands[0]->e_status);
			exit (tokens->commands[0]->e_status);
		}
		else if (pid > 0)
		{
			tokens->e_code = tokens->commands[0]->e_status;
			waitpid(pid, &tokens->commands[0]->e_status, 0);
			printf("parent assignment not found %d\n", tokens->commands[0]->e_status);
			return (tokens->e_code);
		}
	}
	return (tokens->commands[0]->e_status);
}

/* Checks if execution is builtin function and then handle it
if(!builtin) it check if path is in Path and then execute.*/
int	ft_execute(t_command *command, char **envp[], t_infos *tokens)
{
	char	*path;

	if (is_builtin(command->name))
		command->e_status = ft_check_builtin(command, envp);
	else
	{
		path = ft_access(command->name, (*envp));
		if (path == NULL)
		{
			printf("Command \'%s\' not found\n", command->name);
			command->e_status = 127;
			return (command->e_status);
		}
		if (execve(path, command->args, (*envp)) == -1)
		{
			perror("EXECVE");
			free(path);
			command->e_status = 13;
			return (command->e_status);
		}
	}
	return (command->e_status);
}
