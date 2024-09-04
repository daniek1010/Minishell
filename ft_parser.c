/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 02:57:05 by danevans          #+#    #+#             */
/*   Updated: 2024/09/03 18:53:03 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_read_input(char *prompt)
{
	char	*input_read;
	char	**tokens;
	char	**empty_input;

	input_read = readline(prompt);
	if (input_read == NULL)
	{
		free (input_read);
		return (NULL);
	}
	if (input_read[0] == '\0')
	{
		empty_input = malloc(sizeof(char *) * 2);
		empty_input[0] = ft_strdup("");
		empty_input[1] = NULL;
		free(input_read);
		return (empty_input);
	}
	add_history(input_read);
	tokens = ft_token_split(input_read);
	free (input_read);
	return (tokens);
}

/* checks for redir and simply return a value if found*/
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

/* creates the cmd, checks if $, redir and strdup the str found into
the cmd->args every str is kept in cmd->args and the cmd struct is returned*/
// t_command	*ft_create_cmd(int start, int end, char *tokens[], char *envp[], t_var *var)
// {
// 	int			redir_status;
// 	t_command	*cmd;

// 	cmd = (t_command *)ft_malloc(sizeof(t_command));
// 	cmd->redir_cmd = (t_redir **)ft_malloc(sizeof(t_redir *) * INIT_SIZE);
// 	cmd->name = ft_strdup(tokens[start]);
// 	cmd->args = (char **)ft_malloc(sizeof(char *) * (end - start + 2));
// 	cmd->i = 0;
// 	cmd->redir_count = 0;
// 	while (start <= end)
// 	{
// 		if (is_dollar_char(cmd, tokens, &start, envp))
// 			continue ;
// 		redir_status = is_redirection_char(cmd, tokens, &start);
// 		if (redir_status > 0)
// 			continue ;
// 		else if (redir_status < 0)
// 			break ;
// 		cmd->args[cmd->i++] = ft_strdup(tokens[start++]);
// 		cmd->e_status = 0;
// 	}
// 	cmd->args[cmd->i] = NULL;
// 	cmd->redir_cmd[cmd->redir_count] = NULL;
// 	return (cmd);
// }

t_command	*ft_create_cmd(int start, int end, char *tokens_array[], t_infos *tokens)
{
	int			redir_status;
	t_command	*cmd;
	int flag = 1;

	cmd = (t_command *)ft_malloc(sizeof(t_command));
	cmd->redir_cmd = (t_redir **)ft_malloc(sizeof(t_redir *) * INIT_SIZE);
	cmd->args = (char **)ft_malloc(sizeof(char *) * INIT_SIZE);
	cmd->i = 0;
	cmd->redir_count = 0;
	while (start <= end)
	{
		if (is_dollar_char(cmd, tokens_array[start], &start, tokens))
			continue ;
		redir_status = is_redirection_char(cmd, tokens_array, &start);
		if (redir_status > 0)
			continue ;
		else if (redir_status < 0)
			break ;
		if (flag)
		{
			char *str = tokens_array[start];
			if (str[0] == '"' || str[0] == '\'')
				str++;
			cmd->name = ft_strdup(str);
			flag = 0;
		}
		else
		{
			char *str = tokens_array[start];
			if (str[0] == '"' || str[0] == '\'')
				str++;
			cmd->args[cmd->i++] = ft_strdup(str);
			start++;
		}
	}
	cmd->args[cmd->i] = NULL;
	cmd->redir_cmd[cmd->redir_count] = NULL;
	return (cmd);
}


/* this creates the pipe struct which have the cmd1 and cmd2,
the cmd1 keeps all cmd created from the start until a pipe and
cmd2 keep all cmd after the pipe till the next pipe or NULL*/
// void	is_pipe_char(char *token_array[], char *envp[],
// 		t_infos *tokens, t_var *var)
// {
// 	t_pipe		*pipe;

// 	pipe = (t_pipe *)ft_malloc(sizeof(t_pipe));
// 	pipe->cmd1 = ft_create_cmd(var->j, var->i - 1, token_array, envp, tokens);
// 	var->end = var->i + 1;
// 	while (token_array[var->end] && (ft_strcmp(token_array[var->end],
// 				"|") != 0))
// 		var->end++;
// 	pipe->cmd2 = ft_create_cmd(var->i + 1, var->end - 1, token_array, envp, tokens);
// 	tokens->pipes[tokens->pipe_index++] = pipe;
// 	var->j = var->i + 1;
// 	return ;
// }

/* this sorrt the token_array checking for the pipe and commands, it writes 
into the cmd until a pipe is found and then it writes into a pipe->cmd1 and
 cmd->2 and return tokens*/
void	*ft_sort(t_infos *tokens, char **token_array)
{
	t_var		var;
	t_command	*command;

	if (!token_array)
		return (NULL);
	ft_init(&var, tokens);
	while (token_array[var.i] != NULL)
	{
		var.start = var.i;
		while (token_array[var.i] && ft_strcmp(token_array[var.i],
				"|") != 0)
			var.i++;
		command = ft_create_cmd(var.start, var.i - 1, token_array, tokens);
		tokens->commands[tokens->cmd_index++] = command;
		if (ft_strcmp(token_array[var.i], "|") == 0)
		{
			tokens->pipe_index++;
			var.i++;
		}
	}
	ft_null(tokens);
	// ft_cleaner(token_array);
	return (tokens);
}
