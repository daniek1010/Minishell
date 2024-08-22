/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:36:34 by riporth           #+#    #+#             */
/*   Updated: 2024/08/22 12:53:11 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_echo(t_command *cmd)
{
	int	i;
	int	e_status;

	if (ft_strcmp(cmd->args[1], "-n") == 0)
	{
		i = 2;
		if (not_env_path(cmd, i, 0))
			return (-1);
		while (cmd->args[i])
		{
			ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
			if (cmd->args[i + 1] != NULL)
				ft_putstr_fd(" ", STDOUT_FILENO);
			i++;
		}
		e_status = 0;
	}
	else
		e_status = echo_new_line(cmd);
	return (e_status);
}

int	builtin_env(char **envp[])
{
	int	i;

	i = 0;
	while ((*envp)[i] != NULL)
	{
		ft_putendl_fd((*envp)[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}

int	builtin_export(char **envp[], char *key, char *value)
{
	if (key == NULL || value == NULL)
	{
		ft_putendl_fd("Error: Name and value must be non-null", STDERR_FILENO);
		return (-1);
	}
	set_env_var(envp, key, value);
	printf("varaible works here\n");
	return (0);
}

int	builtin_unset(char **envp[], char *key)
{
	int		i;
	int		j;
	int		e_status;
	char	**new_envp;

	i = 0;
	j = 0;
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
	e_status = builtin_unset_helper(new_envp, envp, j, i);
	return (e_status);
}

int	builtin_cd(char **envp[], const char *path)
{
	const char	*home;

	if (!path)
	{
		home = get_env_var((*envp), "HOME");
		if (!home)
			errors("HOME path not set");
		path = home;
	}
	if (chdir(path) != 0)
	{
		perror("CHDIR");
		return (2);
	}
	else
		builtin_pwd();
	return (0);
}
