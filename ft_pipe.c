/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:39:57 by danevans          #+#    #+#             */
/*   Updated: 2024/08/06 14:02:10 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipe(int pipefd[2])
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

void	ft_execute_pipe(t_pipe *pipe, char *envp[], t_infos *tokens)
{
	int		pipefd[2];
	pid_t	pid1;
	pid_t	pid2;

	create_pipe(pipefd);
	pid1 = fork_process();
	if (pid1 == 0)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			errors("dup2 failed\n");
		close(pipefd[1]);
		ft_execute(pipe->cmd1, envp, tokens);
	}
	pid2 = fork_process();
	if (pid2 == 0)
	{
		close(pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			errors("dup2 failed\n");
		close(pipefd[0]);
		ft_execute(pipe->cmd2, envp, tokens);
	}
	close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}

