/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 05:22:05 by danevans          #+#    #+#             */
/*   Updated: 2024/08/14 13:38:21 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_ultimate_free_pipes(char *env[], t_infos *tokens, t_env *envp)
{
	for (int i = 0; tokens->pipes[i]; i++)
	{
		free_command(tokens->pipes[i]->cmd1);
		free_command(tokens->pipes[i]->cmd2);
	}
	if (envp)
    {
        t_env *temp;
        while (envp)
        {
            temp = envp;
            free(envp->key);
            free(envp->value);
            envp = envp->next;
            free(temp);
        }
    }
	if (env)
		ft_cleaner(env);
}

void	clean_env(t_env *env)
{
	if (env)
	{
		t_env	*temp;
		while (env)
		{
			temp = env;
			free(env->key);
			free(env->value);
			env = env->next;
			free(temp);
		}
		exit (EXIT_SUCCESS);
	}
}

int main(int ac, char *av[])
{
    char	**token_array;
    t_infos	*tokens;
    t_env	*envp;

    envp = NULL;
	(void)ac;
	(void)av;
	set_env_var(&envp, "PATH", "/usr/bin:/bin");
	while (1)
	{
		// ft_putendl_fd("*********** start here ******************", STDERR_FILENO);
		token_array = ft_read_input("Minishell> ");
        // ft_putendl_fd("*********** after input recvied ***************", STDERR_FILENO);

		tokens = ft_sort(token_array);
        // ft_putendl_fd("*********** after input broken into token ***************", STDERR_FILENO);

		execute_command(tokens, &envp);
		// ft_putendl_fd("**********  end hhere after execution *********", STDERR_FILENO);
		free_tokens(tokens);
    }
	clean_env(envp);
    return 0;
}
