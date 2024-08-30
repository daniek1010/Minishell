/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 05:22:05 by danevans          #+#    #+#             */
/*   Updated: 2024/08/30 03:41:21 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_int = 0;

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


int	ft_check_builtin(t_command *command, char ***envp)
{
	int	e_status;

	e_status = 0;
	if (ft_strcmp("echo", command->name) == 0)
		e_status = builtin_echo(command);
	else if (ft_strcmp("env", command->name) == 0)
		e_status = builtin_env(envp);
	else if (ft_strcmp("export", command->name) == 0)
		e_status = builtin_export(envp, command->args);
	else if (ft_strcmp("unset", command->name) == 0)
		e_status = builtin_unset(envp, command->args);
	else if (ft_strcmp("cd", command->name) == 0)
		e_status = builtin_cd(envp, command->args[1]);
	else if (ft_strcmp("pwd", command->name) == 0)
		e_status = builtin_pwd();
	else if (ft_strcmp("exit", command->name) == 0)
		exit (0);
	return (e_status);
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

int mini_shell(t_infos *tokens)
{
    char	*input_read;

	while (1)
	{
		if (g_int)
		{
			tokens->e_code = 130;
			g_int = 0;
			continue ;
		}
		input_read = ft_read_input("Minishell> ");
		if (input_read == NULL)
		{
			printf("what are  up here? %d\n", tokens->e_code);
			ft_putendl_fd("exiter", STDOUT_FILENO);
			exit (EXIT_SUCCESS);
		}
		if (input_read[0] == '\0')
		{
			free (input_read);
			continue ;
		}
		ft_sort(input_read, tokens);
		tokens->e_code = execute_commander(tokens);
		// free_tokens(tokens);

    }
	return (0);
}


int main(int ac, char *av[], char *envp[])
{
	int		status;
	char	**env;
	t_infos	*tokens;
	char	*shlvl_get;
	char	*shlvl_set;
	int		shlvl_i;
	// t_var	*var;
	
	signal_handlers();
	env = copy_env(envp);
	tokens = (t_infos *)ft_malloc(sizeof (t_infos));
	tokens->envp = &env;

	status = 0;
	(void)ac;
	(void)av;
	shlvl_get = get_env_var((env), "SHLVL");
	shlvl_i = atoi(shlvl_get);
	shlvl_i += 1;
	shlvl_set = ft_itoa(shlvl_i);
	set_env_var(&env, "SHLVL", shlvl_set);
	status = mini_shell(tokens);
	ft_cleaner(*(tokens->envp));
	free (tokens);
	tokens = NULL;
	ft_cleaner(env);
    return (status);
}
