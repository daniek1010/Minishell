/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:36:34 by riporth           #+#    #+#             */
/*   Updated: 2024/08/21 17:22:47 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *type)
{
	if (ft_strcmp("echo", type) == 0 || ft_strcmp("cd", type) == 0
		|| ft_strcmp("export", type) == 0 || ft_strcmp("pwd", type) == 0
		|| ft_strcmp("unset", type) == 0 || ft_strcmp("env", type) == 0
		|| ft_strcmp("exit", type) == 0)
		return (1);
	return (0);
}

int	not_env(t_command *cmd, int i, int x)
{
	if (ft_strcmp(cmd->args[i], "404") == 0)
	{
		if (x == 1)
			ft_putstr_fd("\n", STDOUT_FILENO);
		return (1);
	}
	return (0);
}

int	builtin_echo(t_command *cmd)
{
	int	i;

	if (ft_strcmp(cmd->args[1], "-n") == 0)
	{
		i = 2;
		if (not_env(cmd, i, 0))
			return (0);
		while (cmd->args[i])
		{
			ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
			if (cmd->args[i + 1] != NULL)
				ft_putstr_fd(" ", STDOUT_FILENO);
			i++;
		}
	}
	else
	{
		i = 1;
		while (cmd->args[i])
		{
			if (not_env(cmd, i, 1))
				return (0);
			ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
			if (cmd->args[i + 1] != NULL)
				ft_putstr_fd(" ", STDOUT_FILENO);
			i++;
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	return (0);
}

int	builtin_env(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		ft_putendl_fd(envp[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}

int	builtin_export(char *envp[], char *key, char *value)
{
	if (key == NULL || value == NULL)
	{
		ft_putendl_fd("Error: Name and value must be non-null", STDERR_FILENO);
		return (0);
	}
	set_env_var(&envp, key, value);
	// for (int i = 0; envp[i]; i++)
	// {
	// 	printf("%s\n", envp[i]);
	// }
	return (0);
}

int	builtin_unset(char ***envp, char *key)
{
	int		i;
	int		j;
	int		k;
	int		l;
	char	**new_envp;

	i = 0;
	j = 0;
	l = 0;
	while ((*envp)[j])
		j++;
	while ((*envp)[i])
	{
		if (compare_key(envp, key, i))
		{
			free ((*envp)[i]);
			new_envp = (char **)ft_malloc(sizeof(char *) * (j));
			break ;
		}
		i++;
	}
	k = 0;
	if (new_envp)
	{
		while (k < j)
		{
			if (k != i)
				new_envp[l++] = (*envp)[k];
			k++;
		}
		new_envp[j - 1] = NULL;
		free ((*envp));
		*envp = new_envp;
	}
	return (0);
}
