/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:39:57 by danevans          #+#    #+#             */
/*   Updated: 2024/08/25 03:32:39 by danevans         ###   ########.fr       */
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
		errors("couldn't fork");
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

void	handle_pid1(int pipefd[2], t_pipe *pipe, t_infos *tokens, char **envp[])
{
	ft_dup(pipefd, STDOUT_FILENO);
	handle_redirections(pipe->cmd1, tokens);
	if (tokens->e_code == 1)
		exit (tokens->e_code);
	tokens->e_code = ft_execute(pipe->cmd1, envp, tokens);
	exit (tokens->e_code);
}

int	ft_create_pipe(t_pipe *pipe, char **envp[], t_infos *tokens)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	pipe_create(pipefd);
	pid1 = fork_process();
	if (pid1 == 0)
		handle_pid1(pipefd, pipe, tokens, envp);
	pid2 = fork_process();
	if (pid2 == 0)
	{
		ft_dup(pipefd, STDIN_FILENO);
		handle_redirections(pipe->cmd2, tokens);
		if (tokens->e_code == 1)
			exit (tokens->e_code);
		tokens->e_code = ft_execute(pipe->cmd2, envp, tokens);
		exit (tokens->e_code);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (tokens->e_code);
}
