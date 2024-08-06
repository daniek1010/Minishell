/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 20:43:49 by danevans          #+#    #+#             */
/*   Updated: 2024/08/06 02:52:02 by danevans         ###   ########.fr       */
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
