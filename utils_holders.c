/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_holders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 14:49:30 by danevans          #+#    #+#             */
/*   Updated: 2024/09/08 20:36:19 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	create_new(char ***envp, char *str, int i, int j)
{
	char	**new_envp;

	if (compare_key(envp, str, i))
	{
		free ((*envp)[i]);
		new_envp = (char **)ft_malloc(sizeof(char *) * (j));
		builtin_unset_helper(&new_envp, envp, j, i);
		return (1);
	}
	return (0);
}

const char	*builtin_cd_helper(char ***envp, const char *path)
{
	const char	*home;

	if (!path)
	{
		home = get_env_var((*envp), "HOME");
		if (!home)
			errors("HOME path not set");
		path = home;
	}
	return (path);
}

void	redir_here_doc_helper(char *input, int pipefd[2], t_infos *tokens)
{
	char	*new_input;

	new_input = ft_extract_variables(input, tokens);
	if (new_input)
	{
		write(pipefd[1], new_input, ft_strlen(new_input));
		free (new_input);
	}
	else
	{
		write(pipefd[1], input, ft_strlen(input));
		free(input);
	}
	close_fd(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close_fd(pipefd[0]);
}

void	wait_for_child(pid_t pid, t_infos *tokens, int is_last_command)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	waitpid(pid, &status, 0);
	signal(SIGINT, handle_sig_parent);
	signal(SIGQUIT, SIG_IGN);
	if (WIFEXITED(status))
		tokens->e_code = WEXITSTATUS(status);
	if (tokens->prev_pipefd[0] != -1)
		close_pipe(tokens, 1);
	if (!is_last_command)
		close_fd (tokens->pipefd[1]);
}
