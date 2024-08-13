/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:25:24 by danevans          #+#    #+#             */
/*   Updated: 2024/08/13 15:40:44 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command(t_command *cmd)
{
	int	i;

	if (cmd)
	{
		if (cmd->name)
			free(cmd->name);
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
			{
				free (cmd->args[i]);
				i++;
			}
			free(cmd->args);
        }
        if (cmd->redir_cmd)
		{
			i = 0;
			while (cmd->redir_cmd[i])
			{
				free (cmd->redir_cmd[i]);
				i++;
			}
			free(cmd->redir_cmd);
		}
		free(cmd);
	}
}

void	free_tokens(t_infos *tokens)
{
	int	i = 0;
	if (!tokens)
		return ;
	if (tokens->pipe_index > 0)
	{
		i = 0;
		while (i < tokens->pipe_index)
		{
			free_command(tokens->pipes[i]->cmd1);
			free_command(tokens->pipes[i]->cmd2);
			free(tokens->pipes[i]);
			i++;
		}
		free(tokens->pipes);
	}
	else
	{
		i = 0;
		while (i < tokens->cmd_index)
		{
			printf("what are you here else %d	%d\n", i, tokens->cmd_index);
			free_command(tokens->commands[i]);
			i++;
		}
		free(tokens->commands);
	}
	
	free(tokens);
}

void	free_env(t_env *env)
{
	t_env *temp;

	if (env)
	{
		while (env)
		{
			temp = env;
			free(env->key);
			free(env->value);
			env = env->next;
			free(temp);
        }
    }
}
// cat args1 args2 | ls args3 args






// void	bad_arg(int x)
// {
// 	if (x == 2)
// 	{
// 		write(2, "cmd1 not found\n", ft_strlen("cmd1 not found\n"));
// 		write(2, "FMT > infile.txt cmd1 cmd2 outfile.txt \n", 41);
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (x == 3)
// 	{
// 		write(2, "cmd2 not found\n", ft_strlen("cmd2 not found\n"));
// 		write(2, "FMT > infile.txt cmd1 cmd2 outfile.txt \n", 41);
// 		exit(EXIT_FAILURE);
// 	}
// }

// void	error(void)
// {
// 	perror("Error");
// 	exit(EXIT_FAILURE);
// }
