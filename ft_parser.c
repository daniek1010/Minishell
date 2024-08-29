/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 02:57:05 by danevans          #+#    #+#             */
/*   Updated: 2024/08/29 06:02:21 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_read_input(char *prompt)
{
	char	*input_read;

	input_read = readline(prompt);
	if (!input_read)
	{
		free (input_read);
		return (NULL);
	}
	add_history(input_read);
	return (input_read);
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

void	rm_whitespace(char *str, int *start, int end)
{
	while (*start < end && str[*start] == ' ' || (str[*start] >= 9 && str[*start] <= 13))
		(*start)++;
}

int	skip_redir(char *input_read, int start, int end)
{
	int	i;

	i = 0;
	rm_whitespace(input_read, &start, end);
	while ((input_read[start] == '<' && input_read[start + 1] != '<')
		||(input_read[start] == '>' && input_read[start + 1] != '>') 
		||(input_read[start] == '<' && input_read[start + 1] == '<')
		||(input_read[start] == '>' && input_read[start + 1] == '>'))
	{
		if (input_read[start + 1] == '<' || input_read[start + 1] == '>')
			start += 2;
		else
			start++;
		rm_whitespace(input_read, &start, end);
		while (start < end && input_read[start] != ' ' && !(input_read[start] >= 9
				&& input_read[start] <= 13) && input_read[start] != '<'
				&& input_read[start] != '>')
			start++;
		rm_whitespace(input_read, &start, end);
	}
	return (start);
}

char	*get_cmd_name(int start, int end, char *input_read, t_command *cmd)
{
	int		i;
	char	*name;

	start = skip_redir(input_read, start, end);
	i = start;
	while (start < end && input_read[start] != ' ' && !(input_read[start] >= 9
			&& input_read[start] <= 13) && input_read[start] != '<'
			&& input_read[start] != '>')
		start++;
	cmd->name = ft_substr(input_read, i, start - i);
	
}

t_command	*ft_create_cmd(int start, int end, char *input_read, t_infos *tokens)
{
	int			redir_status;
	t_command	*cmd;

	cmd = (t_command *)ft_malloc(sizeof(t_command));
	cmd->redir_cmd = (t_redir **)ft_malloc(sizeof(t_redir *) * INIT_SIZE);
	cmd->name = get_cmd_name(start, end, input_read);
	cmd->args = (char **)ft_malloc(sizeof(char *) * (end - start + 2));
	cmd->i = 0;
	cmd->redir_count = 0;
	while (start <= end)
	{
		if (is_dollar_char(cmd, tokens_array, &start, tokens))
			continue ;
		redir_status = is_redirection_char(cmd, tokens_array, &start);
		if (redir_status > 0)
			continue ;
		else if (redir_status < 0)
			break ;
		cmd->args[cmd->i++] = ft_strdup(tokens_array[start++]);
	}
	cmd->args[cmd->i] = NULL;
	cmd->redir_cmd[cmd->redir_count] = NULL;
	return (cmd);
}

/* this creates the pipe struct which have the cmd1 and cmd2,
the cmd1 keeps all cmd created from the start until a pipe and
cmd2 keep all cmd after the pipe till the next pipe or NULL*/
void	is_pipe_char(char *token_array[], char *envp[],
		t_infos *tokens, t_var *var)
{
	t_pipe		*pipe;

	pipe = (t_pipe *)ft_malloc(sizeof(t_pipe));
	pipe->cmd1 = ft_create_cmd(var->j, var->i - 1, token_array, envp, tokens);
	var->end = var->i + 1;
	while (token_array[var->end] && (ft_strcmp(token_array[var->end],
				"|") != 0))
		var->end++;
	pipe->cmd2 = ft_create_cmd(var->i + 1, var->end - 1, token_array, envp, tokens);
	tokens->pipes[tokens->pipe_index++] = pipe;
	var->j = var->i + 1;
	return ;
}

/* this sorrt the token_array checking for the pipe and commands, it writes 
into the cmd until a pipe is found and then it writes into a pipe->cmd1 and
 cmd->2 and return tokens*/
t_infos	*ft_sort(char *input_read, t_infos *tokens)
{
	t_var		var;
	t_command	*command;

	ft_init(&var, tokens);
	while (input_read[var.i] != '\0')
	{
		var.start = var.i;
		while ((input_read[var.i] != '\0') && (input_read[var.i] != '|'))
			var.i++;
		command = ft_create_cmd(var.start, var.i - 1, input_read, tokens);
		tokens->commands[tokens->cmd_count++] = command;
		if (input_read[var.i] == '|')
			tokens->pipe_count++;
		var.i++;
	}
	ft_null(tokens);
	ft_cleaner(token_array);
	return (tokens);
}
