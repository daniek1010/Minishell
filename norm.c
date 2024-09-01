/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 00:53:50 by danevans          #+#    #+#             */
/*   Updated: 2024/09/01 05:22:27 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:41:40 by danevans          #+#    #+#             */
/*   Updated: 2024/08/30 03:39:57 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* cchek and create the number of pipes we have in our token*/
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

/* check for redir, then handles redir before exit */
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



/* helper for execute_command to handle the child process if created*/
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

/* my data was stored in cmd , but if pipe exist then we store in
pipe->cmd1(start < pipe(position) and cmd2(pipe(position + 1) < NULL || next_pipe)) 
sso if (pipe exist), we use pipe to process the cmds and exectute but if(!pipe exist)
we use the copy of cmd and then set up child fork is necessary and then execute */
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
// int	execute_command(t_infos *tokens)
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


// void	handle_redirections(t_command *cmd)
// {
// 	int	i;
// 	int	fd;

// 	i = 0;
// 	while (i < cmd->redir_count)
// 	{
// 		if (cmd->redir_cmd[i]->type == INPUT_REDIR)
// 		{
// 			fd = open(cmd->redir_cmd[i]->file, O_RDONLY);
// 			if (fd == -1)
// 			{
// 				errors("Error opening file for input redirection\n");
// 			}
// 			dup2(fd, STDIN_FILENO);
// 		}
// 		else if (cmd->redir_cmd[i]->type == OUTPUT_REDIR)
// 		{
// 			fd = open(cmd->redir_cmd[i]->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 			if (fd == -1)
// 			{
// 				errors("Error opening file for output redirection\n");
// 			}
// 			dup2(fd, STDOUT_FILENO);
// 		}
// 		close(fd);
// 		i++;
// 	}
// }

int	handle_builtiner(t_command *cmd, t_infos *tokens, int *status)
{
	if (is_builtin(cmd->name))
	{
		if (ft_strcmp("exit", cmd->name) == 0)
		{
			ft_putendl_fd("first exit", STDERR_FILENO);
			*status = -5;
			if (cmd->redir_count > 0)
				handle_redirections(cmd, tokens);
			if (tokens->e_code == 1)
				return (tokens->e_code);
			ft_executer(cmd, tokens);
		}
		else
		{
			ft_putendl_fd("else statement ", STDERR_FILENO);
			*status = 1;
			if (cmd->redir_count > 0)
				handle_redirections(cmd, tokens);
			if (tokens->e_code == 1)
				return (tokens->e_code);
			ft_executer(cmd, tokens);
		}
			ft_putendl_fd("next one", STDERR_FILENO);
	}
	else
		*status = 0;
	return (*status);
}

void	setup_pipes(int pipefd[2], int prev_pipefd[2], int is_last_command)
{
	if (!is_last_command)
	{
		pipe(pipefd);
	}
	if (prev_pipefd[0] != -1)
	{
		close(prev_pipefd[0]);
		close(prev_pipefd[1]);
	}
}

void	redirect_io(int prev_pipefd[2], int pipefd[2], int is_last_command)
{
	if (prev_pipefd[0] != -1)
	{
		ft_putendl_fd("***********", STDERR_FILENO);
		dup2(prev_pipefd[0], STDIN_FILENO);
		close(prev_pipefd[0]);
		close(prev_pipefd[1]);
	}
	if (!is_last_command)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

void	exec_builtin_or_external(t_command *cmd, int pipefd[2], int prev_pipefd[2], int is_last_command, t_infos *tokens)
{
	int		status;

	if (is_builtin(cmd->name))
	{
		if (is_last_command)
		{
			// Last command in pipeline: execute directly in the parent process
			if (prev_pipefd[0] != -1)
			{
				dup2(prev_pipefd[0], STDIN_FILENO);
				close(prev_pipefd[0]);
				close(prev_pipefd[1]);
			}
			handle_builtiner(cmd, tokens, &status);
			// if (status == -5 || status == 1)
			// 	return ;
		}
		else
		{
			// Built-in in the middle of a pipeline: execute in the parent with output redirected
			if (pipefd[1] != -1)
			{
				close (pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				ft_putendl_fd("first here??", STDERR_FILENO);
				close(pipefd[1]);
			}
			if (prev_pipefd[0] != -1)
			{
				ft_putendl_fd("here??", STDERR_FILENO);	
				dup2(prev_pipefd[0], STDIN_FILENO);
				close(prev_pipefd[0]);
				close(prev_pipefd[1]);
			}
			handle_builtiner(cmd, tokens, &status);
			ft_putendl_fd("success", STDERR_FILENO);
		}
	}
	else {
        // External commands run in a child process
        pid_t pid = fork();
        if (pid == 0) {  // Child process
            redirect_io(prev_pipefd, pipefd, is_last_command);
            handle_redirections(cmd, tokens);  // Handle I/O redirections for the command
            ft_executer(cmd, tokens);  // Execute the command
            exit(tokens->e_code);  // Exit with the status code
        } else if (pid > 0) {  // Parent process
            if (pipefd[1] != -1) {
                close(pipefd[1]);  // Close the write end of the pipe
            }
            if (prev_pipefd[0] != -1) {
                close(prev_pipefd[0]);
                close(prev_pipefd[1]);
            }
            waitpid(pid, &status, 0);  // Wait for the child process to finish
        } else {
            perror("fork");
            exit(EXIT_FAILURE);
        }
    }
}

int	execute_commander(t_infos *tokens)
{
	int		pipefd[2];
	int		prev_pipefd[2];
	int		i;
	int		is_last_command;

	prev_pipefd[0] = -1;
	prev_pipefd[1] = -1;
	i = 0;
	while (i < tokens->cmd_index)
	{
		is_last_command = (i == tokens->cmd_index - 1);
		setup_pipes(pipefd, prev_pipefd, is_last_command);
		exec_builtin_or_external(tokens->commands[i], pipefd, prev_pipefd, is_last_command, tokens);
		prev_pipefd[0] = pipefd[0];
		prev_pipefd[1] = pipefd[1];
		char buff[10000];
		size_t byte_read = read(prev_pipefd[0], buff, sizeof(buff));
		buff[byte_read] = '\0';
		ft_putendl_fd(buff, STDERR_FILENO);
		ft_putendl_fd("after the first cmd", STDERR_FILENO);
		i++;
	}
	close(prev_pipefd[0]);
	close(prev_pipefd[1]);
	close(pipefd[0]);
	close(pipefd[1]);
	i = 0;
	while (i < tokens->cmd_index)
	{
		wait(NULL);
		i++;
	}
	return (tokens->e_code);
}


/* Checks if execution is builtin function and then handle it
if(!builtin) it check if path is in Path and then execute.*/
int	ft_executer(t_command *command, t_infos *tokens)
{
	char	*path;

	if (is_builtin(command->name))
	{
		ft_putendl_fd("inside buitin before ", STDERR_FILENO);
		tokens->e_code= ft_check_builtin(command, tokens->envp);
		ft_putendl_fd("inside buitin after ", STDERR_FILENO);
	}
	else
	{
		path = ft_access(command->name, *(tokens->envp));
		if (path == NULL)
		{
			ft_putstr_fd("command \'", STDERR_FILENO);
			ft_putstr_fd(command->name, STDERR_FILENO);
			ft_putstr_fd("\' not found\n", STDERR_FILENO);
			tokens->e_code = 127;
			return (tokens->e_code);
		}
		if (execve(path, command->args, *(tokens->envp)) == -1)
		{
			perror("EXECVE");
			free(path);
			tokens->e_code = 13;
			return (tokens->e_code);
		}
	}
	ft_putendl_fd("builtin end", STDERR_FILENO);
	return (tokens->e_code);
}