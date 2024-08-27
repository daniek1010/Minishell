/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:39:57 by danevans          #+#    #+#             */
/*   Updated: 2024/08/27 21:46:27 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_create(int pipefd[2])
{
	if (pipe(pipefd) == -1)
		errors("Couldnt create pipe\n");
}

pid_t	fork_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_putendl_fd("couldn't fork",STDERR_FILENO);
	return (pid);
}

void	ft_dup(int pipefd[2], int fd)
{
	if (fd == STDOUT_FILENO)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], fd) == -1)
			errors("dup2 failed\n");
		close(pipefd[1]);
	}
	else if (fd == STDIN_FILENO)
	{
		close(pipefd[1]);
		if (dup2(pipefd[0], fd) == -1)
			errors("dup2 failed\n");
		close(pipefd[0]);
	}
}

void	handle_pid(int pipefd[2], t_command *cmd, t_infos *tokens, char ***envp, int stdio)
{
	char *str1 = ft_itoa(cmd->redir_count);
	ft_putendl_fd(str1, STDERR_FILENO);
	if (cmd->redir_count == 0)
		ft_dup(pipefd, stdio);
	handle_redirections(cmd, tokens);
	if (tokens->e_code == 1)
		exit (tokens->e_code);
	tokens->e_code = ft_execute(cmd, envp, tokens);
	exit (tokens->e_code);
}

int	ft_create_pipe(t_pipe *pipe, char ***envp, t_infos *tokens)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;
	int status;

	pipe_create(pipefd);
	if (pipe->cmd1->name)
	{
		if (is_builtin(pipe->cmd1->name))
		{
			if (tokens->save_fdout > 0)
				close (tokens->save_fdout);
			tokens->save_fdout = dup(STDOUT_FILENO);
			char *str = ft_itoa(pipe->cmd1->redir_count);
			ft_putendl_fd(str, STDERR_FILENO);
			if (pipe->cmd1->redir_count == 0)
				dup2(pipefd[1], STDOUT_FILENO);
			handle_builtin(pipe->cmd1, tokens, envp, &status);
			dup2(tokens->save_fdout, STDOUT_FILENO);
		}
		else
		{
			pid1 = fork_process();
			if (pid1 == 0)
			{
				
				handle_pid(pipefd, pipe->cmd1, tokens, envp, STDOUT_FILENO);
				
			}
		}
    }
	ft_putendl_fd("fuck here", STDERR_FILENO);
	if (pipe->cmd2->name)
	{
		if (is_builtin(pipe->cmd2->name))
		{
			if (tokens->save_fdin > 0)
				close (tokens->save_fdin);
			tokens->save_fdin = dup(STDIN_FILENO);
			if (pipe->cmd2->redir_count == 0)
				dup2(pipefd[0], STDIN_FILENO);
			handle_builtin(pipe->cmd2, tokens, envp, &status);
			dup2(tokens->save_fdin, STDIN_FILENO);
		}
		else
		{
			pid2 = fork_process();
			if (pid2 == 0)
				handle_pid(pipefd, pipe->cmd2, tokens, envp, STDIN_FILENO);
		}
	}
	close(pipefd[1]);
	close(pipefd[0]);
	if (!is_builtin(pipe->cmd1->name))
		waitpid(pid1, NULL, 0);
	if (!is_builtin(pipe->cmd2->name))
		waitpid(pid2, NULL, 0);
	return (tokens->e_code);
}



// void	handle_pid1(int pipefd[2], t_pipe *pipe, t_infos *tokens, char **envp[]) {
//     // Set up signal handlers for the first child
//     setup_signal_handlers_child();

//     ft_dup(pipefd, STDOUT_FILENO);
//     handle_redirections(pipe->cmd1, tokens);
//     if (tokens->e_code == 1)
//         exit(tokens->e_code);
//     tokens->e_code = ft_execute(pipe->cmd1, envp, tokens);
//     exit(tokens->e_code);
// }

// void	handle_pid2(int pipefd[2], t_pipe *pipe, t_infos *tokens, char **envp[]) {
//     // Set up signal handlers for the second child
// 	// int	i = 0;
//     setup_signal_handlers_child();

//     ft_dup(pipefd, STDIN_FILENO);
// 	handle_redirections(pipe->cmd2, tokens);
//     if (tokens->e_code == 1)
//         exit(tokens->e_code);
//     tokens->e_code = ft_execute(pipe->cmd2, envp, tokens);
//     exit(tokens->e_code);
// }

// int	ft_create_pipe(t_pipe *pipe, char **envp[], t_infos *tokens) {
//     int pipefd[2];
//     pid_t pid1, pid2;
//     int status;

//     pipe_create(pipefd);
//     pid1 = fork_process();
//     if (pid1 == 0) {
//         handle_pid1(pipefd, pipe, tokens, envp);
//     }

//     pid2 = fork_process();
//     if (pid2 == 0) {
//         handle_pid2(pipefd, pipe, tokens, envp);
//     }

//     close(pipefd[0]);
//     close(pipefd[1]);

//     // Parent process waits for both child processes to complete
//     waitpid(pid1, &status, 0);
//     if (WIFSIGNALED(status)) {
//         tokens->e_code = 128 + WTERMSIG(status); // Handle signal-based termination
//     }

//     waitpid(pid2, &status, 0);
//     if (WIFSIGNALED(status)) {
//         tokens->e_code = 128 + WTERMSIG(status); // Handle signal-based termination
//     }

//     return tokens->e_code;
// }
