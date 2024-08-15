/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_cmds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:41:40 by danevans          #+#    #+#             */
/*   Updated: 2024/08/15 02:07:39 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_builtin(t_command *command, t_env **env)
{
	if (ft_strcmp("echo", command->name) == 0)
			builtin_echo(command);
	else if (ft_strcmp("env", command->name) == 0)
		builtin_env(*env);
	else if (ft_strcmp("export", command->name) == 0){
		printf("Exporting key: %s, value: %s\n", command->args[1], command->args[2]);
		builtin_export(env, command->args[1], command->args[2]);}
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

void	execute_error(char *str, char *envp[], t_infos *tokens, t_env *env)
{
	perror(str);
	// if (tokens)
	// 	free_tokens(tokens);
	if (envp)
		ft_cleaner(envp);
	return ;
}

char	**check_envp_error(t_env **env, t_infos *tokens)
{
	char	**envp;

	envp = convert_env(*env);
	if (!envp)
		execute_error("envp_array Failed ", envp, tokens, *env);
	return (envp);
}

void	destroy_cmd_use_pipe_cmd(t_infos *tokens)
{
	int	k;

	k = 0;
	while (k < tokens->cmd_index)
	{
		free_command(tokens->commands[k]);
		k++;
	}
	free(tokens->commands);
}

void	iterate_pipe_index(t_infos *tokens, char *envp[], t_env **env)
{
	int 	i;
	t_pipe	*pipe;

	i = 0;
	while (i < tokens->pipe_index)
	{
		pipe = tokens->pipes[i];
		ft_create_pipe(pipe, envp, tokens, env);
		i++;
	}
}

// void	ft_execute_errors(char *str, char *envp[], t_infos *tokens, t_env *env)
// {
// 	perror(str);
// 	if (tokens)
// 	{
// 		free_tokens(tokens);
// 		ft_putendl_fd("token free child", STDERR_FILENO);
// 	}gi
// 	tokens->commands = NULL;
// 	tokens->pipes = NULL;
// 	tokens = NULL;
// 	if (envp)
// 		ft_cleaner(envp);
// 	if (env)
// 	{
// 		t_env	*temp;
// 		while (env)
// 		{
// 			temp = env;
// 			free(env->key);
// 			free(env->value);
// 			env = env->next;
// 			free(temp);
//         }
// 	}
// 	exit (EXIT_FAILURE);
// }

void	execute_command(t_infos *tokens, t_env **env)
{
	char	**envp;
	pid_t	pid;

	envp = check_envp_error(env, tokens);
	if (!envp)
		return ;
	if (tokens->pipe_index > 0)
	{
		destroy_cmd_use_pipe_cmd(tokens);
		iterate_pipe_index(tokens, envp, env);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (tokens->commands[0]->redir_count > 0)
				handle_redirections(tokens->commands[0], tokens);
			ft_execute(tokens->commands[0], envp, env, tokens);
			exit (EXIT_FAILURE);
		}
		else if (pid > 0)
		{
			waitpid(pid, NULL, 0);
			if (envp)
					ft_cleaner(envp);
			return ;
		}
	}
}


void	ft_execute(t_command *command, char *envp[], t_env **env, t_infos *tokens)
{
	char	*path;

	if (is_builtin(command->name))
		ft_check_builtin(command, env);
	else
	{
		path = ft_access(command->name, envp);
		if (path == NULL)
		{
			perror("PATH failed ");
			return ;
		}
		if (execve(path, command->args, envp) == -1)
		{
			perror("EXECVE FAILED ");
			free(path);
			return ;
		}
	}
}
