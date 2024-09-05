/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_holders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:49:30 by danevans          #+#    #+#             */
/*   Updated: 2024/09/05 21:14:40 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	if (!g_int)
	{
		g_int = 1;
		rl_replace_line("", 0);
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_sigquit(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
}

void	signal_handlers(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
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

t_command	*init_cmd(int *flag)
{
	t_command	*cmd;

	cmd = (t_command *)ft_malloc(sizeof(t_command));
	cmd->redir_cmd = (t_redir **)ft_malloc(sizeof(t_redir *) * INIT_SIZE);
	cmd->args = (char **)ft_malloc(sizeof(char *) * INIT_SIZE);
	cmd->i = 0;
	cmd->redir_count = 0;
	*flag = 1;
	return (cmd);
}