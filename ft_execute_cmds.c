/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:41:40 by danevans          #+#    #+#             */
/*   Updated: 2024/08/25 04:46:57 by danevans         ###   ########.fr       */
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
	int	status;

	if (is_builtin(cmd->name))
	{
		status = -5;
		if (cmd->redir_count > 0)
			handle_redirections(cmd, tokens);
		status = ft_execute(cmd, envp, tokens);
	}
	else
		status = 0;
	return (status);
}

/* helper for execute_command to handle the child process if created*/
int	run_child(t_infos *tokens, char **envp[])
{
	setup_signal_handlers_child();
	if (tokens->commands[0]->redir_count > 0)
	{
		handle_redirections(tokens->commands[0], tokens);
		if (tokens->e_code == 1)
			return (1);
	}
	tokens->e_code = ft_execute(tokens->commands[0], envp, tokens);
	return (tokens->e_code);
}

/* my data was stored in cmd , but if pipe exist then we store in
pipe->cmd1(start < pipe(position) and cmd2(pipe(position + 1) < NULL || next_pipe)) 
sso if (pipe exist), we use pipe to process the cmds and exectute but if(!pipe exist)
we use the copy of cmd and then set up child fork is necessary and then execute */
// int	execute_command(t_infos *tokens, char **envp[])
// {
// 	pid_t	pid;
// 	int		status;

// 	if (tokens->pipe_index > 0)
// 		tokens->e_code = iterate_pipe_index(tokens, envp);
// 	else
// 	{
// 		if (ft_strcmp("exit", tokens->commands[0]->name) == 0){
// 			status = handle_builtin_exit(tokens->commands[0], tokens, envp);
// 		if (status == -5)
// 			return (status);}
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			setup_signal_handlers_child();
// 			tokens->e_code = run_child(tokens, envp);
// 			exit (tokens->e_code);
// 		}
// 		else if (pid > 0)
// 		{
// 			waitpid(pid, &status, 0);
// 			if (WIFEXITED(status))
// 				tokens->e_code = WEXITSTATUS(status);
// 			if (g_int) {  // Check if interrupted
//                 tokens->e_code = 130;  // Exit code for interrupted by SIGINT
//             }
// 			return (tokens->e_code);
// 		}
// 	}
// 	return (tokens->e_code);
// }

int execute_command(t_infos *tokens, char **envp[]) {
    pid_t pid;
    int status;

    if (tokens->pipe_index > 0) {
        tokens->e_code = iterate_pipe_index(tokens, envp);
    } else {
        if (ft_strcmp("exit", tokens->commands[0]->name) == 0) {
            status = handle_builtin_exit(tokens->commands[0], tokens, envp);
            if (status == -5) return status;
        }

        pid = fork();
        if (pid == 0) {
            // Child process
            setup_signal_handlers_child();
            tokens->e_code = run_child(tokens, envp);
            exit(tokens->e_code);
        } else if (pid > 0) {
            // Parent process
            waitpid(pid, &status, 0);
            if (WIFEXITED(status)) {
                tokens->e_code = WEXITSTATUS(status);
            } else if (WIFSIGNALED(status)) {
                tokens->e_code = 128 + WTERMSIG(status);  // Capture signal exit status
            }

            if (g_int) {  // Check if interrupted
                tokens->e_code = 130;  // Exit code for SIGINT
            }
            return tokens->e_code;
        }
    }
    return tokens->e_code;
}


/* Checks if execution is builtin function and then handle it
if(!builtin) it check if path is in Path and then execute.*/
int	ft_execute(t_command *command, char **envp[], t_infos *tokens)
{
	char	*path;

	if (is_builtin(command->name))
		tokens->e_code= ft_check_builtin(command, envp);
	else
	{
		path = ft_access(command->name, (*envp));
		if (path == NULL)
		{
			ft_putstr_fd("command \'", STDERR_FILENO);
			ft_putstr_fd(command->name, STDERR_FILENO);
			ft_putstr_fd("\' not found\n", STDERR_FILENO);
			tokens->e_code = 127;
			return (tokens->e_code);
		}
		if (execve(path, command->args, (*envp)) == -1)
		{
			perror("EXECVE");
			free(path);
			tokens->e_code = 13;
			return (tokens->e_code);
		}
	}
	return (tokens->e_code);
}
