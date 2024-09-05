/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell_utils3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 00:27:06 by danevans          #+#    #+#             */
/*   Updated: 2024/09/05 19:57:40 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_check_path(char *envp[])
{
	int		i;
	char	**splitted;

	i = 0;
	splitted = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			splitted = ft_split(envp[i] + 5, ':');
			break ;
		}
		i++;
	}
	return (splitted);
}

char	*ft_access(char *av, char *envp[])
{
	char	**splitted;
	char	*path;
	int		i;

	splitted = ft_check_path(envp);
	i = -1;
	if (access(av, X_OK) == 0)
		return (av);
	while (splitted[++i] != NULL)
	{
		path = join(splitted[i], av);
		if (access(path, X_OK) == 0)
			break ;
		free(path);
	}
	if (splitted[i] == NULL)
	{
		ft_cleaner(splitted);
		return (NULL);
	}
	return (path);
}

char	*join(char *str, char *av)
{
	char	*path;
	char	**cmd;

	cmd = ft_split(av, ' ');
	str = ft_strjoin(str, "/");
	path = ft_strjoin(str, cmd[0]);
	free(str);
	ft_cleaner(cmd);
	return (path);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	index;

	index = 0;
	if (n == 0)
		return (0);
	while (((s1[index] != '\0') || (s2[index] != '\0')) && index < n)
	{
		if (s1[index] != s2[index])
			return ((unsigned char)s1[index] - (unsigned char) s2[index]);
		index++;
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	index;

	index = 0;
	if (!s1)
		return (1);
	while ((s1[index] != '\0') || (s2[index] != '\0'))
	{
		if (s1[index] != s2[index])
			return ((unsigned char)s1[index] - (unsigned char) s2[index]);
		index++;
	}
	return (0);
}
