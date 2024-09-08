/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell_utils6.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 12:51:33 by danevans          #+#    #+#             */
/*   Updated: 2024/09/06 12:34:15 by danevans         ###   ########.fr       */
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

int	not_env_path(t_command *cmd, int i, int x)
{
	if (ft_strcmp(cmd->args[i], "404") == 0)
		return (1);
	return (0);
}

int	echo_new_line(t_command *cmd)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		if (not_env_path(cmd, i, 1))
		{
			i++;
			continue ;
		}
		ft_putstr_fd(cmd->args[i], STDOUT_FILENO);
		if (cmd->args[i + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}

int	builtin_unset_helper(char ***new_envp, char ***envp, int j, int i)
{
	int	k;
	int	l;

	k = 0;
	l = 0;
	if ((*new_envp))
	{
		while (k < j)
		{
			if (k != i)
			{
				(*new_envp)[l++] = (*envp)[k];
			}
			k++;
		}
		(*new_envp)[j - 1] = NULL;
		free ((*envp));
		*envp = (*new_envp);
		return (0);
	}
	return (0);
}

int	builtin_pwd(void)
{
	char	buffer[1024];

	if (getcwd(buffer, sizeof(buffer)) != NULL)
		ft_putendl_fd(buffer, STDOUT_FILENO);
	else
	{
		perror("GETCWD");
		return (22);
	}
	return (0);
}
