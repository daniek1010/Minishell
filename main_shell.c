/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 05:22:05 by danevans          #+#    #+#             */
/*   Updated: 2024/08/16 20:35:59 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while(i < len)
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[len] = NULL;
	return (new_envp);	
}

int mini_shell(char *envp[])
{
    char	**token_array;
	t_infos	*tokens;
	int		e_status;

	e_status = 0;
	while (e_status >= -1)
	{
		token_array = ft_read_input("Minishell> ");
		tokens = ft_sort(token_array);
		e_status = execute_command(tokens, envp);
		free_tokens(tokens);
    }
	return (e_status);
}

int main(int ac, char *av[], char *envp[])
{
	int	status;
	char	**env;

	env = copy_env(envp);
	status = 0;
	(void)ac;
	(void)av;
	status = mini_shell(env);
	ft_cleaner(env);
    return (status);
}
