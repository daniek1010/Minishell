/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 05:22:05 by danevans          #+#    #+#             */
/*   Updated: 2024/09/11 18:45:38 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit = -1;

int	mini_shell(t_infos *tokens)
{
	char	**token_array;

	while (1)
	{
		token_array = ft_read_input("Minishell> ", tokens);
		if (token_array == NULL)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		if (!ft_sort(tokens, token_array))
		{
			free_tokens(tokens);
			continue ;
		}
		execute_commander(tokens);
		if (tokens->exit_flag)
		{
			free_tokens(tokens);
			break ;
		}
		free_tokens(tokens);
	}
	return (tokens->e_code);
}

void	handle_sig_parent(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_redisplay();
	g_exit = 130;
}

void	signal_handlers(void)
{
	signal(SIGINT, handle_sig_parent);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int ac, char *av[], char *envp[])
{
	char	**env;
	t_infos	*tokens;
	int		status;

	(void)ac;
	(void)av;
	signal_handlers();
	env = copy_env(envp);
	tokens = (t_infos *)ft_malloc(sizeof (t_infos));
	tokens->envp = &env;
	tokens->e_code = 0;
	add_shlvl(tokens);
	status = mini_shell(tokens);
	ft_cleaner(*(tokens->envp));
	free(tokens);
	tokens = NULL;
	return (status);
}
