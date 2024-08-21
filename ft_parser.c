/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 02:57:05 by danevans          #+#    #+#             */
/*   Updated: 2024/08/21 13:59:51 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_read_input(char *prompt)
{
	char	*input_read;
	char	*delimter;
	char	**tokens;

	delimter = " \t\r\n\a";
	tokens = NULL;
	input_read = readline(prompt);
	if (input_read == NULL || input_read[0] == '\0')
	{
		free (input_read);
		return (tokens);
	}
	add_history(input_read);
	tokens = ft_split(input_read, delimter);
	free (input_read);
	return (tokens);
}

t_redir	*ft_create_redir(char *str, char *file)
{
	t_redir	*redir;

	redir = (t_redir *)ft_malloc(sizeof(t_redir));
	if (ft_strcmp(str, "<") == 0)
		redir->type = INPUT;
	else if (ft_strcmp(str, ">") == 0)
		redir->type = TRUNC;
	else if (ft_strcmp(str, ">>") == 0)
		redir->type = APPEND;
	else if (ft_strcmp(str, "<<") == 0)
		redir->type = HEREDOC;
	else
		return (NULL);
	redir->file = ft_strdup(file);
	return (redir);
}

t_command	*ft_create_cmd(int start, int end, char *tokens[], char *envp[])
{
	int			redir_status;
	t_command	*cmd;

	cmd = (t_command *)ft_malloc(sizeof(t_command));
	cmd->redir_cmd = (t_redir **)ft_malloc(sizeof(t_redir *) * INIT_SIZE);
	cmd->name = ft_strdup(tokens[start]);
	cmd->args = (char **)ft_malloc(sizeof(char *) * (end - start + 2));
	cmd->i = 0;
	cmd->redir_count = 0;
	while (start <= end)
	{
		if (is_dollar_char(cmd, tokens, &start, envp))
			continue ;
		redir_status = is_redirection_char(cmd, tokens, &start);
		if (redir_status > 0)
			continue ;
		else if (redir_status < 0)
			break ;
		cmd->args[cmd->i++] = ft_strdup(tokens[start++]);
	}
	cmd->args[cmd->i] = NULL;
	cmd->redir_cmd[cmd->redir_count] = NULL;
	return (cmd);
}

void	is_pipe_char(char *token_array[], char *envp[],
		t_infos *tokens, t_var *var)
{
	t_pipe		*pipe;

	pipe = (t_pipe *)ft_malloc(sizeof(t_pipe));
	pipe->cmd1 = ft_create_cmd(var->j, var->i - 1, token_array, envp);
	var->end = var->i + 1;
	while (token_array[var->end] && (ft_strcmp(token_array[var->end],
				"|") != 0))
		var->end++;
	pipe->cmd2 = ft_create_cmd(var->i + 1, var->end - 1, token_array, envp);
	tokens->pipes[tokens->pipe_index++] = pipe;
	var->j = var->i + 1;
	return ;
}

t_infos	*ft_sort(char *token_array[], char *envp[])
{
	t_var		var;
	t_infos		*tokens;
	t_command	*command;

	if (!token_array)
		return (NULL);
	tokens = ft_init(&var);
	while (token_array[var.i])
	{
		if (ft_strcmp(token_array[var.i], "|") == 0)
			is_pipe_char(token_array, envp, tokens, &var);
		else
		{
			var.start = var.i;
			while (token_array[var.i] && ft_strcmp(token_array[var.i],
					"|") != 0)
				var.i++;
			command = ft_create_cmd(var.start, var.i - 1, token_array, envp);
			tokens->commands[tokens->cmd_index++] = command;
			var.i--;
		}
		var.i++;
	}
	ft_null(tokens);
	ft_cleaner(token_array);
	return (tokens);
}
