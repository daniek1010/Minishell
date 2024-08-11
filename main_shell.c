/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 05:22:05 by danevans          #+#    #+#             */
/*   Updated: 2024/08/12 01:09:10 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char *av[])
{
    char		**tester;
	t_infos		*tokens;
	t_env		*envp;

	envp = NULL;
	(void)ac;
	(void)av;
	set_env_var(&envp, "PATH", "/usr/bin:/bin");
	while (1){
		tester = ft_read_input("Minishell> ");
		tokens = ft_sort(tester);
		execute_command(tokens, envp);
	}

	free(tokens->commands);
    free(tokens);

    for (int i = 0; tester[i]; i++) {
        free(tester[i]);
    }
    free(tester);
    return 0;
}