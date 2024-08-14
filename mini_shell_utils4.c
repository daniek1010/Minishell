/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell_utils4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:40:31 by danevans          #+#    #+#             */
/*   Updated: 2024/08/13 17:49:34 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s2)
		return ;
	while (s2[i] != '\0')
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
}

int	is_type(const char *s, char *c, int start, int i)
{
	if (((s[i] == c[0] || s[i] == c[1] || s[i] == c[2]
				|| s[i] == c[3] || s[i] == c[4] || s[i] == c[5])
			|| i == ft_strlen(s)) && start >= 0)
		return (1);
	return (0);
}

char	*helper_convert_env(t_env *temp)
{
	char	*str;
	char	*env;

	str = ft_strjoin(temp->key, "=");
	if (!str)
		return (NULL);
	env = ft_strjoin(str, temp->value);
	free(str);
	return (env);
}

size_t	ft_strlen(const char *s)
{
	int	index;

	index = 0;
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
