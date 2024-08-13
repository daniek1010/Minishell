/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:41:40 by danevans          #+#    #+#             */
/*   Updated: 2024/08/13 16:46:13 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command(t_infos *tokens, t_env *env)
{
	int		i;
	char	**envp;
	pid_t	pid;
	t_pipe	*pipe;

	i = 0;
	envp = convert_env(env);
	if (!envp)
		ft_execute_errors("couldnt convert env", NULL, envp, tokens);
	if (tokens->pipe_index > 0)
	{
		int k = 0;
		while (k < tokens->cmd_index)
		{
			free_command(tokens->commands[k]);
			k++;
		}
		free(tokens->commands);
		while (i < tokens->pipe_index)
		{
			pipe = tokens->pipes[i];
			ft_create_pipe(pipe, envp, tokens, env);
			i++;
		}
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (tokens->commands[0]->redir_count > 0)
				handle_redirections(tokens->commands[0], tokens);
			ft_execute(tokens->commands[0], envp, env, tokens);
		}
		else if (pid > 0)
		{
		int status;
			waitpid(pid, &status, 0);
			if (WIFEXITED(status) && WEXITSTATUS(status) != 0){
				ft_execute_errors("Exit here  ", tokens->commands[0], envp, tokens);
			// waitpid(pid, NULL, 0);
			}
			}
		else
			ft_execute_errors("Fork failed", tokens->commands[0],envp, tokens);
	}
}

void	ft_check_builtin(t_command *command, t_env *env)
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
	else if (ft_strcmp("exit", command->name) == 0)
	{
			ft_putendl_fd("not yet assigned\n", STDERR_FILENO);
	}
}

void	ft_execute(t_command *command, char *envp[], t_env *env, t_infos *tokens)
{
	char	*path;

	if (is_builtin(command->name))
		ft_check_builtin(command, env);
	else
	{
		path = ft_access(command->name, envp);
		if (path == NULL)
		{
			if (env) {
        		t_env *temp;
        		while (env) {
            		temp = env;
            		free(env->key);
            		free(env->value);
            		env = env->next;
            		free(temp);
        		}
    		}
			ft_execute_errors("Couldn't find the executable", command, envp, tokens);
		}
		if (execve(path, command->args, envp) == -1)
		{
			free(path);
			if (env) {
        		t_env *temp;
        		while (env) {
            		temp = env;
            		free(env->key);
            		free(env->value);
            		env = env->next;
            		free(temp);
        		}
    		}
			ft_execute_errors("Couldnt execute the cmd", command, envp, tokens);
		}
	}
}
