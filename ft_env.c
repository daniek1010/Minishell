/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:27:39 by danevans          #+#    #+#             */
/*   Updated: 2024/08/12 01:41:23 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env_var(t_env **env, char *key, char *value)
{
	t_env	*current;
	t_env	*new_node;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free (current->value);
			current->value = ft_strdup(value);
			return;
		}
		current = current->next;
	}
	new_node = (t_env *)ft_malloc(sizeof(t_env));
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = *env;
	*env = new_node;
}

char	*get_env_var(t_env *env, char *key, char *value)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	**convert_env(t_env *env)
{
	int		count;
	int		len;
	t_env	*temp;
	char	**env_array;
	char	*str;
	int		i;

	temp = env;
	count = 0;
	i = 0;
	while(temp)
	{
		count++;
		temp = temp->next;
	}
	env_array = (char **)ft_malloc(sizeof(char *) * count + 1);
	i = 0;
	temp = env;
	while(temp)
	{
		len = ft_strlen(temp->key) + ft_strlen(temp->value) + 2;
		env_array[temp->i] = (char *)ft_malloc(len);
		str = ft_strjoin(temp->key, "=");
		env_array[i] = ft_strjoin(str, temp->value);
		free(str);
		temp = temp->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

void	builtin_cd(t_env *env, const char *path)
{
	const char *home;

	if (!path)
	{
		home = get_env_var(env, "HOME", NULL);
		if (!home)
			errors("HOME path not set");
		path = home;
	}
	if (chdir(path) != 0)
		errors("chdir failed");
}

void	builtin_pwd(void)
{
	char	buffer[1024];

	if (getcwd(buffer, sizeof(buffer)) != NULL)
		ft_putendl_fd(buffer, STDOUT_FILENO);
	else
		errors("getcwd failed");
}