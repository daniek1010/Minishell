/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:27:39 by danevans          #+#    #+#             */
/*   Updated: 2024/08/16 18:38:43 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	compare_key(char ***envp, char *key, int i)
{
	if ((ft_strncmp((*envp)[i], key, ft_strlen(key)) == 0)
		&& (*envp)[i][ft_strlen(key)] == '=')
		return (1);
	return (0);
}

void	set_env_var(char ***envp, char *key, char *value)
{
	int	i;
	int	j;
	char *str;
	char **new_envp;

	i = 0;
	while ((*envp)[i] != NULL)
	{
		if (compare_key(envp, key, i))
		{
			free ((*envp)[i]);
			str = ft_strjoin(key, "=");
			(*envp)[i] = ft_strjoin(str, value);
			free (str);
			return ;
		}
		i++;
	}
	new_envp = (char **)ft_malloc(sizeof(char *) * (i + 2));
	j = 0;
	while (j < i)
	{
		new_envp[j] = (*envp)[j];
		j++;
	}
	str = ft_strjoin(key, "=");
	new_envp[j] = ft_strjoin(str, value);
	free (str);
	new_envp[j + 1] = NULL;
	free (*envp);
	*envp = new_envp;
	return ;
}

char	*get_env_var(char *envp[], char *key)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if ((ft_strncmp(envp[i], key, ft_strlen(key)) == 0)
			&& envp[i][ft_strlen(key)] == '=')
			return (envp[i] + (ft_strlen(key) + 1));
		i++;
	}
	return (NULL);
}

int	builtin_cd(char *envp[], const char *path)
{
	const char	*home;

	if (!path)
	{
		home = get_env_var(envp, "HOME");
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
