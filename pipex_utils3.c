/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 20:43:49 by danevans          #+#    #+#             */
/*   Updated: 2024/09/04 12:29:56 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	redirect_input_output(int infile, int outfile, int pipefd[2], int x)
// {
// 	if (x == 1)
// 	{
// 		if (dup2(infile, STDIN_FILENO) == -1)
// 			error();
// 		close(infile);
// 		close(pipefd[0]);
// 		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
// 			error();
// 		close(pipefd[1]);
// 	}
// 	else if (x == 2)
// 	{
// 		close(pipefd[1]);
// 		if (dup2(pipefd[0], STDIN_FILENO) == -1)
// 			error();
// 		close(pipefd[0]);
// 		if (dup2(outfile, STDOUT_FILENO) == -1)
// 			error();
// 		close(outfile);
// 	}
// 	return (0);
// }

// void	execute_command(char *av[], char *envp[], int pipefd[], int process)
// {
// 	int	infile;
// 	int	outfile;

// 	if (process == 1)
// 	{
// 		infile = ft_file(av[1], 0);
// 		redirect_input_output(infile, 0, pipefd, 1);
// 		close(infile);
// 		ft_execute(av, envp, 2);
// 	}
// 	else if (process == 2)
// 	{
// 		outfile = ft_file(av[4], 1);
// 		redirect_input_output(0, outfile, pipefd, 2);
// 		close(outfile);
// 		ft_execute(av, envp, 3);
// 	}
// }

// void	ft_execute(char *av[], char *envp[], int x)
// {
// 	char	*path;
// 	char	**cmd;

// 	path = ft_access(av[x], envp);
// 	if (path == NULL)
// 		bad_arg(x);
// 	cmd = ft_split(av[x], ' ');
// 	if (execve(path, cmd, envp) == -1)
// 	{
// 		free(cmd);
// 		free(path);
// 		error();
// 	}
// }

// char	*ft_access(char *av, char *envp[])
// {
// 	char	**splitted;
// 	char	*path;
// 	int		i;

// 	splitted = check_path(envp);
// 	i = -1;
// 	while (splitted[++i] != NULL)
// 	{
// 		path = join(splitted[i], av);
// 		if (access(path, X_OK) == 0)
// 			break ;
// 		free(path);
// 	}
// 	if (splitted[i] == NULL)
// 	{
// 		ft_cleaner(splitted);
// 		return (NULL);
// 	}
// 	return (path);
// }

// char	*join(char *str, char *av)
// {
// 	char	*path;
// 	char	**cmd;

// 	cmd = ft_split(av, ' ');
// 	str = ft_strjoin(str, "/");
// 	path = ft_strjoin(str, cmd[0]);
// 	free(str);
// 	ft_cleaner(cmd);
// 	return (path);
// }


pid_t	fork_process(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_putendl_fd("couldn't fork",STDERR_FILENO);
	return (pid);
}

// void	ft_dup(int pipefd[2], int fd)
// {
// 	if (fd == STDOUT_FILENO)
// 	{
// 		close(pipefd[0]);
// 		if (dup2(pipefd[1], fd) == -1)
// 			errors("dup2 failed\n");
// 		close(pipefd[1]);
// 	}
// 	else if (fd == STDIN_FILENO)
// 	{
// 		close(pipefd[1]);
// 		if (dup2(pipefd[0], fd) == -1)
// 			errors("dup2 failed\n");
// 		close(pipefd[0]);
// 	}
// }

// void	handle_pid(int pipefd[2], t_command *cmd, t_infos *tokens, char ***envp, int stdio)
// {
// 	char *str1 = ft_itoa(cmd->redir_count);
// 	ft_putendl_fd(str1, STDERR_FILENO);
// 	if (cmd->redir_count == 0)
// 		ft_dup(pipefd, stdio);
// 	handle_redirections(cmd, tokens);
// 	if (tokens->e_code == 1)
// 		exit (tokens->e_code);
// 	tokens->e_code = ft_execute(cmd, envp, tokens);
// 	exit (tokens->e_code);
// }

// int	ft_create_pipe(t_pipe *pipe, char ***envp, t_infos *tokens)
// {
// 	int		pipefd[2];
// 	pid_t	pid1;
// 	pid_t	pid2;
// 	int status;

// 	pipe_create(pipefd);
// 	if (pipe->cmd1->name)
// 	{
// 		if (is_builtin(pipe->cmd1->name))
// 		{
// 			if (tokens->save_fdout > 0)
// 				close (tokens->save_fdout);
// 			tokens->save_fdout = dup(STDOUT_FILENO);
// 			char *str = ft_itoa(pipe->cmd1->redir_count);
// 			ft_putendl_fd(str, STDERR_FILENO);
// 			if (pipe->cmd1->redir_count == 0)
// 				dup2(pipefd[1], STDOUT_FILENO);
// 			handle_builtin(pipe->cmd1, tokens, envp, &status);
// 			dup2(tokens->save_fdout, STDOUT_FILENO);
// 		}
// 		else
// 		{
// 			pid1 = fork_process();
// 			if (pid1 == 0)
// 			{
				
// 				handle_pid(pipefd, pipe->cmd1, tokens, envp, STDOUT_FILENO);
				
// 			}
// 		}
//     }
// 	ft_putendl_fd("fuck here", STDERR_FILENO);
// 	if (pipe->cmd2->name)
// 	{
// 		if (is_builtin(pipe->cmd2->name))
// 		{
// 			if (tokens->save_fdin > 0)
// 				close (tokens->save_fdin);
// 			tokens->save_fdin = dup(STDIN_FILENO);
// 			if (pipe->cmd2->redir_count == 0)
// 				dup2(pipefd[0], STDIN_FILENO);
// 			handle_builtin(pipe->cmd2, tokens, envp, &status);
// 			dup2(tokens->save_fdin, STDIN_FILENO);
// 		}
// 		else
// 		{
// 			pid2 = fork_process();
// 			if (pid2 == 0)
// 				handle_pid(pipefd, pipe->cmd2, tokens, envp, STDIN_FILENO);
// 		}
// 	}
// 	close(pipefd[1]);
// 	close(pipefd[0]);
// 	if (!is_builtin(pipe->cmd1->name))
// 		waitpid(pid1, NULL, 0);
// 	if (!is_builtin(pipe->cmd2->name))
// 		waitpid(pid2, NULL, 0);
// 	return (tokens->e_code);
// }



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




//  signals shold be checked howto

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