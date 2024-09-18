/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:49:02 by danevans          #+#    #+#             */
/*   Updated: 2024/09/18 12:22:16 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*change_pipe(char *list)
{
	char	*new;

	new = (char *)malloc(sizeof(char) * 3);
	if (!new)
		return (NULL);
	free (list);
	new[0] = '"';
	new[1] = '|';
	new[2] = '\0';
	return (new);
}

int	path_not_found(t_command *command)
{
	ft_putstr_fd("command \'", STDERR_FILENO);
	ft_putstr_fd(command->name, STDERR_FILENO);
	ft_putstr_fd("\' not found\n", STDERR_FILENO);
	return (127);
}

int	pipe_start_error(void)
{
	ft_putstr_fd("minishell ", STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token `|'\n", STDERR_FILENO);
	return (2);
}

int	empty_str_error(void)
{
	ft_putstr_fd("Command \'\'", STDERR_FILENO);
	ft_putendl_fd("not found, but you can fuck off", STDERR_FILENO);
	return (127);
}

void	invalid_name_args(t_infos *tokens, t_command *cmd)
{
	empty_str_error();
	tokens->e_code = 127;
	cmd->name = NULL;
	free (cmd->args);
	free (cmd->redir_cmd);
	free (cmd);
	cmd = NULL;
}
