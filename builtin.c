/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:36:34 by riporth           #+#    #+#             */
/*   Updated: 2024/08/12 00:22:12 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *type)
{
	if (ft_strcmp("echo", type) == 0 || ft_strcmp("cd", type) == 0 ||
		ft_strcmp("export", type) == 0 || ft_strcmp("pwd", type) == 0 ||
		ft_strcmp("unset", type) == 0 || ft_strcmp("env", type) == 0 )
		return (1);
	return (0);
}

void	builtin_echo(t_command *cmd)
{
	int	i;

	if (ft_strcmp(cmd->args[1], "-n") == 0)
	{
		i = 2;
		while (cmd->args[i])
		{
			ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
			i++;
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	else
	{
		i = 1;
		while (cmd->args[i])
		{
			ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
			i++;
		}
	}
}

void	builtin_env(t_env *env)
{
	while (env)
	{
		ft_putstr_fd(env->key, STDOUT_FILENO);
		ft_putstr_fd("=", STDOUT_FILENO);
		ft_putendl_fd(env->value, STDOUT_FILENO);
		env = env->next;
	}
}

void	builtin_export(t_env *envp, char *key, char *value)
{
	if (key == NULL || value == NULL)
		ft_putendl_fd("Error: Name and value must be non-null", STDERR_FILENO);
	set_env_var(&envp, key, value);
}

void	builtin_unset(t_env *envp, char *key)
{
	t_env	*current;
	t_env	*previous;

	current = envp;
	previous = NULL;
	while(current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (previous)
				previous->next = current->next;
			else
				envp = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return;
		}
		previous = current;
		current = current->next;
	}
}