/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:45:26 by riporth           #+#    #+#             */
/*   Updated: 2024/09/17 17:59:26 by riporth          ###   ########.fr       */
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

