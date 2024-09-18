/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:12:50 by danevans          #+#    #+#             */
/*   Updated: 2024/09/18 09:15:03 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_read_input_here_doc(char *prompt, char *delimeter)
{
	char	*input_read;
	char	*str;
	char	*temp;

	str = NULL;
	while (1)
	{
		input_read = readline(prompt);
		if (!input_read)
		{
			ft_putstr_fd("minishell: warning: here-document: ", STDERR_FILENO);
			ft_putendl_fd(delimeter, STDERR_FILENO);
			return (str);
		}
		if (ft_strcmp(input_read, delimeter) == 0)
			break ;
		temp = ft_strjoin_new_line(str, input_read);
		free (str);
		str = temp;
		free (input_read);
	}
	if (input_read)
		free (input_read);
	return (str);
}

void	redir_here_docs(char *delimeter, t_infos *tokens, t_command *cmd,
			int pos)
{
	char	*input;
	int		pipefd[2];
	int		last_heredoc;

	last_heredoc = count_heredoc(cmd);
	input = ft_read_input_here_doc("> ", delimeter);
	if (last_heredoc == pos)
	{
		if (cmd->name == NULL)
		{
			free (input);
			return ;
		}
		pipe_create(pipefd);
		if (!input)
		{
			write(pipefd[1], "", STDOUT_FILENO);
			dup2(pipefd[0], STDIN_FILENO);
			return ;
		}
		redir_here_doc_helper(input, pipefd, tokens);
	}
	else
		free (input);
}

int	handle_redirections(t_command *cmd, t_infos *tokens)
{
	int	i;

	if (cmd->redir_count > 0)
	{
		i = 0;
		while (i < cmd->redir_count)
		{
			if (cmd->redir_cmd[i]->type == TRUNC
				|| cmd->redir_cmd[i]->type == APPEND)
			{
				if (!redir_append_trunc(tokens, cmd->redir_cmd[i]->type,
						cmd->redir_cmd[i]->file))
					return (0);
			}
			else if (cmd->redir_cmd[i]->type == INPUT)
			{
				if (!redir_input(tokens, cmd->redir_cmd[i]->file))
					return (0);
			}
			i++;
		}
	}
	return (tokens->e_code);
}

int	redir_append_trunc(t_infos *tokens, int type, char *file)
{
	int	fdout;

	fdout = 0;
	tokens->save_fdout = dup(STDOUT_FILENO);
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
		tokens->e_code = 1;
		return (0);
	}
	dup2(fdout, STDOUT_FILENO);
	close (fdout);
	tokens->e_code = 0;
	return (1);
}

int	redir_input(t_infos *tokens, char *file)
{
	int	fdin;

	fdin = 0;
	tokens->save_fdin = dup(STDIN_FILENO);
	fdin = open(file, O_RDONLY);
	if (fdin == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		tokens->e_code = 1;
		return (0);
	}
	dup2(fdin, STDIN_FILENO);
	close (fdin);
	tokens->e_code = 0;
	return (1);
}
