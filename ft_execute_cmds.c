/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:41:40 by danevans          #+#    #+#             */
/*   Updated: 2024/09/03 11:57:53 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// /* cchek and create the number of pipes we have in our token*/
// int	iterate_pipe_index(t_infos *tokens, char ***envp)
// {
// 	int		i;
// 	int		e_status;
// 	t_pipe	*pipe;

// 	i = 0;
// 	while (i < tokens->pipe_index)
// 	{
// 		pipe = tokens->pipes[i];
// 		e_status = ft_create_pipe(pipe, envp, tokens);
// 		i++;
// 	}
// 	return (e_status);
// }

// /* check for redir, then handles redir before exit */
// int	handle_builtin(t_command *cmd, t_infos *tokens, char ***envp, int *status)
// {
// 	if (is_builtin(cmd->name))
// 	{
// 		if (ft_strcmp("exit", cmd->name) == 0)
// 		{
// 			*status = -5;
// 			if (cmd->redir_count > 0)
// 			ft_execute(cmd, envp, tokens);
// 				handle_redirections(cmd, tokens);
// 			ft_execute(cmd, envp, tokens);
// 		}
// 		else
// 		{
// 			*status = 1;
// 			if (cmd->redir_count > 0)
// 				handle_redirections(cmd, tokens);
// 			ft_execute(cmd, envp, tokens);
// 		}
// 	}
// 	else
// 		*status = 0;
// 	return (*status);
// }

// /* helper for execute_command to handle the child process if created*/
// int	run_child(t_infos *tokens, char ***envp)
// {
// 	setup_signal_handlers_child();
// 	if (tokens->commands[0]->redir_count > 0)
// 	{
// 		handle_redirections(tokens->commands[0], tokens);
// 		if (tokens->e_code == 1)
// 			return (1);
// 	}
// 	tokens->e_code = ft_execute(tokens->commands[0], envp, tokens);
// 	return (tokens->e_code);
// }

// int	handle_forked_process(t_infos *tokens, char ***envp)
// {
// 	pid_t	pid;

// 	pid = fork_process();
// 	if (pid == 0)
// 	{
// 		setup_signal_handlers_child();
// 		tokens->e_code = run_child(tokens, envp);
// 		exit(tokens->e_code);
// 	}
// 	else if (pid > 0)
//         return (pid);
// 	else
// 		return (-1);
// }
// // Function to handle the parent process logic after fork
// int	handle_parent_process(pid_t pid, t_infos *tokens)
// {
// 	int	status;

// 	signal(SIGINT, SIG_IGN);
// 	waitpid(pid, &status, 0);
// 	signal(SIGINT, handle_sigint);
// 	if (status == 256)
// 	{
// 		tokens->e_code = -5;
// 		return (tokens->e_code);
//     }
// 	if (WIFEXITED(status))
//         tokens->e_code = WEXITSTATUS(status);
// 	else if (WIFSIGNALED(status))
// 	{
// 		if (WTERMSIG(status) == SIGINT)
// 			g_int = 0;  // Child exited due to Ctrl + C, clear g_int in parent
// 	}
// 	if (g_int)
// 	{
// 		tokens->e_code = 130;
// 		g_int = 0;
// 	}
//     return (tokens->e_code);
// }

// /* my data was stored in cmd , but if pipe exist then we store in
// pipe->cmd1(start < pipe(position) and cmd2(pipe(position + 1) < NULL || next_pipe)) 
// sso if (pipe exist), we use pipe to process the cmds and exectute but if(!pipe exist)
// we use the copy of cmd and then set up child fork is necessary and then execute */
// int	execute_command(t_infos *tokens, char ***envp) {
//     pid_t	pid;
// 	int		status;

// 	if (tokens->pipe_index > 0)
// 		tokens->e_code = iterate_pipe_index(tokens, envp);
// 	else
// 	{
// 		handle_builtin(tokens->commands[0], tokens, envp, &status);
// 		if ((status == -5) || (status == 1))
//             return (status);
//         pid = handle_forked_process(tokens, envp);
//         if (pid > 0)
// 		{
// 			return (handle_parent_process(pid, tokens));
// 		}
// 	}
// 	return (tokens->e_code);
// }

/* my data was stored in cmd , but if pipe exist then we store in
pipe->cmd1(start < pipe(position) and cmd2(pipe(position + 1) < NULL || next_pipe)) 
sso if (pipe exist), we use pipe to process the cmds and exectute but if(!pipe exist)
we use the copy of cmd and then set up child fork is necessary and then execute */
// int	execute_command(t_infos *tokens, char ***envp)
// {
// 	pid_t	pid;
// 	int		status;

// 	if (tokens->pipe_index > 0)
// 		tokens->e_code = iterate_pipe_index(tokens, envp);
// 	else
// 	{
// 		handle_builtin(tokens->commands[0], tokens, envp, &status);
// 		if (status == -5)
// 			return (status);
// 		else if (status == 1)
// 			return (status);
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			setup_signal_handlers_child();
// 			tokens->e_code = run_child(tokens, envp);
// 			exit (tokens->e_code);
// 		}
// 		else if (pid > 0)
// 		{
// 			signal(SIGINT, SIG_IGN);
// 			waitpid(pid, &status, 0);
// 			if (status == 256)
// 				return (-5);
// 			signal(SIGINT, handle_sigint);
			
// 			if (WIFEXITED(status)){
// 				tokens->e_code = WEXITSTATUS(status);}
// 			else if (WIFSIGNALED(status)) {
//                if (WTERMSIG(status) == SIGINT) {
//             	g_int = 0;  // Child exited due to Ctrl + C, clear g_int in parent
//         }
//             }
// 			if (g_int)
// 			{
//                 tokens->e_code = 130;
// 				g_int = 0;
//             }
// 			return (tokens->e_code);
// 		}
// 	}
// 	return (tokens->e_code);
// }

/* Checks if execution is builtin function and then handle it
if(!builtin) it check if path is in Path and then execute.*/
// int	ft_execute(t_command *command, char ***envp, t_infos *tokens)
// {
// 	char	*path;

// 	if (is_builtin(command->name))
// 		tokens->e_code= ft_check_builtin(command, envp);
// 	else
// 	{
// 		path = ft_access(command->name, (*envp));
// 		if (path == NULL)
// 		{
// 			ft_putstr_fd("command \'", STDERR_FILENO);
// 			ft_putstr_fd(command->name, STDERR_FILENO);
// 			ft_putstr_fd("\' not found\n", STDERR_FILENO);
// 			tokens->e_code = 127;
// 			return (tokens->e_code);
// 		}
// 		if (execve(path, command->args, (*envp)) == -1)
// 		{
// 			perror("EXECVE");
// 			free(path);
// 			tokens->e_code = 13;
// 			return (tokens->e_code);
// 		}
// 	}
// 	return (tokens->e_code);
// }
