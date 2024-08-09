/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:12:50 by danevans          #+#    #+#             */
/*   Updated: 2024/08/09 05:26:02 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redirections(t_command *cmd, t_infos *tokens)
{
	int	i;

	i = 0;
	while (i < tokens->red_index)
    {
        t_redir *redir = tokens->redirs[i];
        if (redir->type == TRUNC || redir->type == APPEND)
            redir_append_trunc(tokens, redir->type, i);
        else if (redir->type == INPUT)
            redir_input(tokens, i);
		// else
        // Handle other redirection types like HEREDOC if needed
		i++;
    }
}

void	redir_append_trunc(t_infos *tokens, int type, int i)
{
	ft_close(tokens->fdout);
	if (type == TRUNC)
		tokens->fdout = open(tokens->redirs[i]->file, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
	else
		tokens->fdout = open(tokens->redirs[i]->file, O_CREAT | O_WRONLY | O_APPEND, S_IRUSR | S_IWUSR);
	if (tokens->fdout == -1)		
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(tokens->redirs[i]->file, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	}
	dup2(tokens->fdout, STDOUT_FILENO);
}

void	redir_input(t_infos *tokens, int i)
{
	ft_close(tokens->fdin);
	tokens->fdin = open(tokens->redirs[i]->file, O_RDONLY);
	if (tokens->fdin == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(tokens->redirs[i]->file, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
	}
	dup2(tokens->fdin, STDIN_FILENO);
}

