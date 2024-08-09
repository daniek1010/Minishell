/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:41:40 by danevans          #+#    #+#             */
/*   Updated: 2024/08/09 06:26:23 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void execute_command(t_infos *tokens, char *envp[])
{
	// int	status;
	int	i;

	i = 0;
    if (tokens->pipe_index > 0)
    {
		while (i < tokens->pipe_index)
        {
            t_pipe *pipe = tokens->pipes[i];
            ft_create_pipe(pipe, envp, tokens);
			i++;
		}
    }
    // 2. Handle Built-ins
    // else if (is_builtin(tokens->commands[0]->name))
    // {
    //     execute_builtin(tokens->commands[0], tokens);  // Execute built-in command
    // }
    else
    {
        pid_t pid = fork();
        if (pid == 0)  // Child process
        {
            handle_redirections(tokens->commands[0], tokens);
            ft_execute(tokens->commands[0], envp);
        }
        else if (pid > 0)
			waitpid(pid, NULL, 0);
        else
			errors("Fork failed");
    }
}

void	ft_execute(t_command *command, char *envp[])
{
	char	*path;

	path = ft_access(command->name, envp);
	if (path == NULL)
		errors("Couldn't find the executable");
	if (execve(path, command->args, envp) == -1)
	{
		free(path);
		errors("Couldnt execute the cmd");
	}
}
