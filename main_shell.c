/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 05:22:05 by danevans          #+#    #+#             */
/*   Updated: 2024/09/05 19:32:05 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile	sig_atomic_t	g_int = 0;

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

int	mini_shell(t_infos *tokens)
{
	char	**token_array;

	while (1)
	{
		token_array = ft_read_input("Minishell> ");
		if (token_array == NULL)
		{
			ft_putendl_fd("exiter", STDOUT_FILENO);
			break ;
		}
		if (token_array[0][0] == '\0')
		{
			ft_cleaner(token_array);
			continue ;
		}
		if (!ft_sort(tokens, token_array))
		{
			free_tokens(tokens);
			break ;
		}
		execute_commander(tokens);
		if (tokens->e_code == -5)
		{
			tokens->e_code = 0;
			free_tokens(tokens);
			break ;
		}
		free_tokens(tokens);
	}
	return (0);
}

void	add_shlvl(t_infos *tokens)
{
	char	*shlvl_get;
	char	*shlvl_set;
	int		shlvl_i;

	shlvl_get = get_env_var(*(tokens->envp), "SHLVL");
	shlvl_i = atoi(shlvl_get);
	shlvl_i += 1;
	shlvl_set = ft_itoa(shlvl_i);
	set_env_var(tokens->envp, "SHLVL", shlvl_set);
	free(shlvl_set);
}

int	main(int ac, char *av[], char *envp[])
{
	char	**env;
	t_infos	*tokens;

	(void)ac;
	(void)av;
	signal_handlers();
	env = copy_env(envp);
	tokens = (t_infos *)ft_malloc(sizeof (t_infos));
	tokens->envp = &env;
	tokens->e_code = 0;
	add_shlvl(tokens);
	mini_shell(tokens);
	ft_cleaner(*(tokens->envp));
	free(tokens);
	tokens = NULL;
	return (0);
}
