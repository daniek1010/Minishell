/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:27:39 by danevans          #+#    #+#             */
/*   Updated: 2024/09/11 18:07:55 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*bool comparison to check if key was found */
int	compare_key(char ***envp, char *key, int i)
{
	if ((ft_strncmp((*envp)[i], key, ft_strlen(key)) == 0))
		return (1);
	return (0);
}

/*bool to checks if key is found and then join the key + value*/
int	set_env_var_helper(char *key, char *value, char ***envp, int i)
{
	char	*str;

	if (compare_key(envp, key, i))
	{
		free ((*envp)[i]);
		str = ft_strjoin(key, "=");
		(*envp)[i] = ft_strjoin(str, value);
		free (str);
		return (1);
	}
	return (0);
}

/* copies envp into the new_envp, helper for set_env_var */
char	**write_envp(int *j, int i, char **new_envp, char ***envp)
{
	while (*j < i)
	{
		new_envp[*j] = ft_strdup((*envp)[*j]);
		(*j)++;
	}
	return (new_envp);
}

/* checks if key already exist,counts the envp found , creates 
space with malloc for new_envp write into new_envp, free the envp
 and then a pointer to new_envp  */
void	set_env_var(char ***envp, char *key, char *value)
{
	int		i;
	int		j;
	char	*str;
	char	**new_envp;

	i = 0;
	while ((*envp)[i] != NULL)
	{
		if (set_env_var_helper(key, value, envp, i))
			return ;
		i++;
	}
	new_envp = (char **)ft_malloc(sizeof(char *) * (i + 2));
	j = 0;
	new_envp = write_envp(&j, i, new_envp, envp);
	if (value == NULL)
	{
		new_envp[j] = ft_strdup(key);
		new_envp[j + 1] = NULL;
		ft_cleaner(*envp);
		(*envp) = new_envp;
	}
	else
	{
		str = ft_strjoin(key, "=");
		new_envp[j] = ft_strjoin(str, value);
		free (str);
		new_envp[j + 1] = NULL;
		ft_cleaner(*envp);
		(*envp) = new_envp;
	}
	return ;
}

/* loop tru the envp to get the key and then skip key and return value*/
char	*get_env_var(char **envp, char *key)
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
