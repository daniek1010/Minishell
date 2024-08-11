/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:41:40 by danevans          #+#    #+#             */
/*   Updated: 2024/08/12 01:36:04 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void execute_command(t_infos *tokens, t_env *env)
{
	int	i;
	char **envp;
	
	i = 0;
	envp = convert_env(env);
	if (!envp)
		errors("couldnt create envp array");
    if (tokens->pipe_index > 0)
    {
		while (i < tokens->pipe_index)
        {
            t_pipe *pipe = tokens->pipes[i];
            ft_create_pipe(pipe, envp, tokens, env);
			i++;
		}
    }
    else
    {
        pid_t pid = fork();
        if (pid == 0)
        {
			if (tokens->commands[0]->redir_count > 0)
            	handle_redirections(tokens->commands[0], tokens);
            ft_execute(tokens->commands[0], envp, env);
        }
        else if (pid > 0)
			waitpid(pid, NULL, 0);
        else
			errors("Fork failed");
    }
}

void	ft_execute(t_command *command, char *envp[], t_env *env)
{
	char	*path;

	if (is_builtin(command->name))
	{
		if (ft_strcmp("echo", command->name) == 0)
			builtin_echo(command);
		else if (ft_strcmp("env", command->name) == 0)
			builtin_env(env);
		else if (ft_strcmp("export", command->name) == 0)
			builtin_export(env, command->args[1], command->args[2]);
		else if (ft_strcmp("unset", command->name) == 0)
			builtin_unset(env, command->args[1]);
		else if (ft_strcmp("cd", command->name) == 0)
			builtin_cd(env, command->args[1]);
		else if (ft_strcmp("pwd", command->name) == 0)
			builtin_pwd();
		// else if (ft_strcmp("exit", command->name) == 0 )
		// 	builtin_pwd();
	}
	else
	{
		path = ft_access(command->name, envp);
		if (path == NULL)
			errors("Couldn't find the executable");
		if (execve(path, command->args, envp) == -1)
		{
			free(path);
			errors("Couldnt execute the cmd");
		}
	}
}
