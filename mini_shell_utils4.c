/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell_utils4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:40:31 by danevans          #+#    #+#             */
/*   Updated: 2024/09/05 20:12:39 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s2 || !s1)
		return ;
	while (s2[i] != '\0')
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
}

size_t	ft_strlen(const char *s)
{
	int	index;

	index = 0;
	if (!s)
		return (0);
	while (s[index] != '\0')
		index++;
	return (index);
}

void	ft_cleaner(char *str[])
{
	int		i;

	if (!str)
		return ;
	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return ;
}

int	is_redir(char *tokens[], int start)
{
	if (ft_strcmp(tokens[start], "<") == 0
		|| ft_strcmp(tokens[start], ">") == 0
		|| ft_strcmp(tokens[start], ">>") == 0
		|| ft_strcmp(tokens[start], "<<") == 0
		|| ft_strcmp(tokens[start], ">|") == 0)
		return (1);
	return (0);
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
	while (i < len)
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[len] = NULL;
	return (new_envp);
}
