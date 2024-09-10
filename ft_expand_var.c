/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:41:40 by danevans          #+#    #+#             */
/*   Updated: 2024/09/10 14:31:07 by riporth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_helper_2(char **key_value, char ***envp, char *key, char *value)
{
	if (alpha_numeric(key))
	{
		set_env_var(envp, key, value);
		return (0);
	}
	else
	{
		printf("%s:\'%s\': not a valid identifier\n", key_value[0], key);
		return (1);
	}
}

int	builtin_export_helper(char **key_value, char ***envp)
{
	int		i;
	char	*str;
	int		result;

	i = 1;
	while (key_value[i] != NULL)
	{
		str = ft_strchr(key_value[i], '=');
		if (str)
		{
			*str = '\0';
			result = export_helper_2(key_value, envp, key_value[i], str + 1);
			*str = '=';
			if (result != 0)
				return (result);
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

void	restore_stdout(t_infos *tokens)
{
	if (tokens->save_fdout != -1)
	{
		dup2(tokens->save_fdout, STDOUT_FILENO);
		close(tokens->save_fdout);
		tokens->save_fdout = -1;
	}
}
