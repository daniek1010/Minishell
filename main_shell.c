/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 05:22:05 by danevans          #+#    #+#             */
/*   Updated: 2024/09/04 22:36:12 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_int = 0;

void	handle_sigint(int sig)
{
	(void)sig;
	g_int = 1;
	rl_replace_line("", 0);
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_handlers(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
}

void	handle_sigquit(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
}


int	alpha_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')
		|| (str[i] >= '0' && str[i] <= '9'))
		{
			if ((str[0] >= '0' && str[0] <= '9'))
				return (0);
			i++;
		}
		else
			return (0);
	}
	return (1);
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
				printf("%s:\'%s\': not a valid identifier\n", key_value[0], key_value[i]);
				return (1);
			}
		}
		else
		{
			printf("%s:\'%s\': not a valid identifier\n", key_value[0], key_value[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_check_builtin(t_command *command, t_infos *tokens)
{
	tokens->e_code = 0;
	if (ft_strcmp("echo", command->name) == 0)
		tokens->e_code = builtin_echo(command);
	else if (ft_strcmp("env", command->name) == 0)
		tokens->e_code = builtin_env(tokens->envp);
	else if (ft_strcmp("export", command->name) == 0)
		tokens->e_code = builtin_export(tokens->envp, command->args);
	else if (ft_strcmp("unset", command->name) == 0)
		tokens->e_code = builtin_unset(tokens->envp, command->args);
	else if (ft_strcmp("cd", command->name) == 0)
		tokens->e_code = builtin_cd(tokens->envp, command->args[1]);
	else if (ft_strcmp("pwd", command->name) == 0)
		tokens->e_code = builtin_pwd();
	else if (ft_strcmp("exit", command->name) == 0)
	{
		ft_putendl_fd("exiting", STDOUT_FILENO);
		tokens->e_code = -5;
	}
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
	while(i < len)
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[len] = NULL;
	return (new_envp);	
}

void	destroy_cmd_use_pipe_cmd(t_infos *tokens)
{
	int	k;

	k = 0;
	while (k < tokens->cmd_index)
	{
		free_command(tokens->commands[k]);
		k++;
	}
	free(tokens->commands);
}


int mini_shell(t_infos *tokens)
{
	char	**token_array;

	while (1)
	{
		token_array = ft_read_input("Minishell> ");
		if (token_array == NULL)
		{
			ft_putendl_fd("exiter", STDOUT_FILENO);
			exit (EXIT_SUCCESS);
		}
		if (token_array[0][0] == '\0')
		{
			ft_cleaner(token_array);
			continue ;
		}
		ft_sort(tokens, token_array);
		execute_commander(tokens);
		if (tokens->e_code == -5)
		{
			tokens->e_code = 0;
			free_tokens(tokens);
			break;
		}
		// free_tokens(tokens);
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
}

int main(int ac, char *av[], char *envp[])
{
	char	**env;
	t_infos	*tokens;

	(void)ac;
	(void)av;
	signal_handlers();
	env = copy_env(envp);
	tokens = (t_infos *)ft_malloc(sizeof (t_infos));
	tokens->envp = &env;
	add_shlvl(tokens);
	tokens->e_code = mini_shell(tokens);
	ft_cleaner(env);
	free (tokens);
	tokens = NULL;
    return (0);
}
