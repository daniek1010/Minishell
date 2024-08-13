/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 05:22:05 by danevans          #+#    #+#             */
/*   Updated: 2024/08/13 14:26:58 by danevans         ###   ########.fr       */
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

// void	ft_ultimate_free_cmd(char *env[], t_infos *tokens, t_env *envp)
// {
// 	for (int i = 0; tokens->commands[i]; i++)
// 	{
// 		free_command(tokens->commands[i]);
// 	}
// 	free(tokens->commands);
// 	if (envp)
//     {
//         t_env *temp;
//         while (envp)
//         {
//             temp = envp;
//             free(envp->key);
//             free(envp->value);
//             envp = envp->next;
//             free(temp);
//         }
//     }
// 	if (env)
// 		ft_cleaner(env);
// 	free (tokens);
// }

void free_env_array(char **envp) {
    for (int i = 0; envp[i]; i++) {
        free(envp[i]);
    }
    free(envp);
}


void ft_ultimate_free_cmd(char *env[], t_infos *tokens, t_env *envp) {
    // Free commands
    for (int i = 0; tokens->commands[i]; i++) {
        free_command(tokens->commands[i]);
    }
    free(tokens->commands);

    // Free envp
    if (envp) {
        t_env *temp;
        while (envp) {
            temp = envp;
            free(envp->key);
            free(envp->value);
            envp = envp->next;
            free(temp);
        }
    }

    // Free env array if dynamically allocated
    if (env)
        free_env_array(env);
    
    // Free tokens structure
    free(tokens);
}


// int main(int ac, char *av[])
// {
//     char		**tester;
// 	t_infos		*tokens;
// 	t_env		*envp;

// 	envp = NULL;
// 	(void)ac;
// 	(void)av;
// 	set_env_var(&envp, "PATH", "/usr/bin:/bin");
// 	while (1){
// 		tester = ft_read_input("Minishell> ");
// 		tokens = ft_sort(tester);
// 		execute_command(tokens, envp);
// 	for (int i = 0; tester[i]; i++) {
//         free(tester[i]);
//     	}
//     	free(tester);
// 	}
// 	if (tokens->pipe_index > 0)
// 		ft_ultimate_free_pipes(NULL, tokens, envp);
// 	else
// 		ft_ultimate_free_cmd(NULL, tokens, envp);
	
//     return 0;
// }

int main(int ac, char *av[])
{
    char	**token_array;
    t_infos	*tokens;
    t_env	*envp;

    envp = NULL;
    (void)ac;
    (void)av;
    
    // Initialize environment variables once
    set_env_var(&envp, "PATH", "/usr/bin:/bin");
	while (1)
	{
		token_array = ft_read_input("Minishell> ");
		tokens = ft_sort(token_array);
		execute_command(tokens, envp);
		// if (token_array)
		// 	ft_cleaner(token_array);
		free_tokens(tokens);
    }
	free_env(envp);
    return 0;
}
