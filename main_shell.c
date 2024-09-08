/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 05:22:05 by danevans          #+#    #+#             */
/*   Updated: 2024/09/08 20:36:08 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	handle_sig_child(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	exit (130);
}

void	signal_handlers_child(void)
{
	signal(SIGINT, handle_sig_child);
	signal(SIGQUIT, SIG_IGN);
}

int	mini_shell(t_infos *tokens)
{
	char	**token_array;

	while (1)
	{
		token_array = ft_read_input("Minishell> "); //pass token here
		if (token_array == NULL)
		{
			ft_putendl_fd("exiter", STDOUT_FILENO);
			break ;
		}
		if (!ft_sort(tokens, token_array))
		{
			free_tokens(tokens);
			continue ;
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

void	handle_sig_parent(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_redisplay();
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

int	builtin_export_helper(char **key_value, char ***envp)
{
	int		i;
	char	*str;

	i = 1;
	while (key_value[i] != NULL)
	{
		str = ft_strchr(key_value[i], '=');
		if (str)
		{
			*str = '\0';
			if (alpha_numeric(key_value[i]))
				set_env_var(envp, key_value[i], str + 1);
			else
			{
				*str = '=';
				printf("%s:\'%s\': not a valid identifier\n",
					key_value[0], key_value[i]);
				return (1);
			}
		}
		else
		{
			printf("%s:\'%s\': not a valid identifier\n",
				key_value[0], key_value[i]);
			return (1);
		}
		i++;
	}
	return (0);
}