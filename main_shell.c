/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 05:22:05 by danevans          #+#    #+#             */
/*   Updated: 2024/08/22 13:15:48 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_builtin(t_command *command, char **envp[])
{
	int	e_status;

	e_status = 0;
	if (ft_strcmp("echo", command->name) == 0)
		e_status = builtin_echo(command);
	else if (ft_strcmp("env", command->name) == 0)
		e_status = builtin_env(envp);
	else if (ft_strcmp("export", command->name) == 0)
		e_status = builtin_export(envp, command->args[1], command->args[2]);
	else if (ft_strcmp("unset", command->name) == 0)
		e_status = builtin_unset(envp, command->args[1]);
	else if (ft_strcmp("cd", command->name) == 0)
		e_status = builtin_cd(envp, command->args[1]);
	else if (ft_strcmp("pwd", command->name) == 0)
		e_status = builtin_pwd();
	else if (ft_strcmp("exit", command->name) == 0)
		exit (0);
	return (e_status);
}

char	**copy_env(char *envp[])
{
	int		i;
	int		len;
	char	**new_envp;

	len = 0;
	i = 0;
	while (envp[len])
		len++;
	new_envp = (char **)malloc(sizeof(char *) * (len + 1));
	if (!new_envp)
		return (NULL);
	while(i < len)
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[len] = NULL;
	return (new_envp);	
}

int mini_shell(char **envp[])
{
    char	**token_array;
	t_infos	*tokens;
	int		e_status;

	e_status = 0;
	/* ONLY CTRL D breaks this loop or exit keyword*/
	while (e_status != -5)
	{
		token_array = ft_read_input("Minishell> ");
		if (token_array == NULL)
			continue ;
		tokens = ft_sort(token_array, envp);
		e_status = execute_command(tokens, envp);
		free_tokens(tokens);
    }
	return (e_status);
}


int main(int ac, char *av[], char *envp[])
{
	int	status;
	char	**env;

	env = copy_env(envp);
	status = 0;
	(void)ac;
	(void)av;
	status = mini_shell(&env);
	ft_cleaner(env);
    return (status);
}
