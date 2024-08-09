/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:12:50 by danevans          #+#    #+#             */
/*   Updated: 2024/08/09 15:08:53 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirections(t_command *cmd, t_infos *tokens)
{
	int	i;

	i = 0;
	if (cmd->redir_count > 0)
	{
		while (i < cmd->redir_count)
		{
			if (cmd->redir_cmd[i]->type == TRUNC ||cmd->redir_cmd[i]->type == APPEND)
				redir_append_trunc(tokens, cmd->redir_cmd[i]->type, cmd->redir_cmd[i]->file);
			else if (cmd->redir_cmd[i]->type == INPUT)
				redir_input(tokens, cmd->redir_cmd[i]->file);
			// else
			// Handle other redirection types like HEREDOC if needed
			i++;
		}
	}
}

void	redir_append_trunc(t_infos *tokens, int type, char *file)
{
	ft_close(tokens->fdout);
	if (type == TRUNC)
		tokens->fdout = open(file, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	else
		tokens->fdout = open(file, O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);
	if (tokens->fdout == -1)		
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	}
	dup2(tokens->fdout, STDOUT_FILENO);
}

void	redir_input(t_infos *tokens, char *file)
{
	ft_close(tokens->fdin);
	tokens->fdin = open(file, O_RDONLY);
	if (tokens->fdin == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	}
	dup2(tokens->fdin, STDIN_FILENO);
}

