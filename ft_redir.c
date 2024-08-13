/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:12:50 by danevans          #+#    #+#             */
/*   Updated: 2024/08/13 14:30:16 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_read_input_here_doc(char *prompt, char *delimeter)
{
	char	*input_read;
	char	*str;

	str = NULL;
	while (1)
	{
		input_read = readline(prompt);
		if (!input_read || ft_strcmp(input_read, delimeter) == 0)
			break ;
		add_history(input_read);
		str = ft_strjoin_new_line(str, input_read);
		free (input_read);
	}
	if (input_read)
		free (input_read);
	return (str);
}

void	handle_redirections(t_command *cmd, t_infos *tokens)
{
	int	i;

	if (cmd->redir_count > 0)
	{
		i = 0;
		while (i < cmd->redir_count)
		{
			if (cmd->redir_cmd[i]->type == TRUNC
				|| cmd->redir_cmd[i]->type == APPEND)
				redir_append_trunc(tokens, cmd->redir_cmd[i]->type,
					cmd->redir_cmd[i]->file);
			else if (cmd->redir_cmd[i]->type == INPUT)
				redir_input(tokens, cmd->redir_cmd[i]->file);
			else
				redir_here_docs("heredoc> ", cmd->redir_cmd[i]->file);
			i++;
		}
	}
}

void	redir_here_docs(char *prompt, char *delimeter)
{
	char	*input;
	int		pipefd[2];

	pipe_create(pipefd);
	input = ft_read_input_here_doc(prompt, delimeter);
	if (!input)
	{
		free (input);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	write(pipefd[1], input, ft_strlen(input));
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
}

void	redir_append_trunc(t_infos *tokens, int type, char *file)
{
	int	fdout;

	fdout = 0;
	if (type == TRUNC)
		fdout = open(file, O_CREAT | O_WRONLY
				| O_TRUNC, S_IRUSR | S_IWUSR);
	else
		fdout = open(file, O_CREAT | O_WRONLY
				| O_APPEND, S_IRUSR | S_IWUSR);
	if (fdout == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	}
	dup2(fdout, STDOUT_FILENO);
}

void	redir_input(t_infos *tokens, char *file)
{
	int	fdin;

	fdin = 0;
	fdin = open(file, O_RDONLY);
	if (fdin == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	}
	dup2(fdin, STDIN_FILENO);
}
