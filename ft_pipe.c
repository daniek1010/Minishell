/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:39:57 by danevans          #+#    #+#             */
/*   Updated: 2024/08/09 06:25:43 by danevans         ###   ########.fr       */
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

int	ft_create_pipe(t_pipe *pipe, char *envp[], t_infos *tokens)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	pipe_create(pipefd);
	pid1 = fork_process();
	if (pid1 == 0)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			errors("dup2 failed\n");
		handle_redirections(pipe->cmd1, tokens);
		ft_execute(pipe->cmd1, envp);
		close(pipefd[1]);
		exit (1);
	}
	pid2 = fork_process();
	if (pid2 == 0)
	{
		close(pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			errors("dup2 failed\n");
		// tokens->pipout = pipefd[1];
		handle_redirections(pipe->cmd2, tokens);
		ft_execute(pipe->cmd2, envp);
		close(pipefd[0]);
		exit (1);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
