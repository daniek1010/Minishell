/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 05:22:05 by danevans          #+#    #+#             */
/*   Updated: 2024/08/09 05:22:28 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char *av[], char *envp[])
{
    char		**tester;
	t_infos		*tokens ;
	(void)ac;
	(void)av;
	
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