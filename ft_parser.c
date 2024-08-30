/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 02:57:05 by danevans          #+#    #+#             */
/*   Updated: 2024/08/30 03:42:22 by danevans         ###   ########.fr       */
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
	printf("got here ***************?    %s\n", input_read);
	add_history(input_read);
	return (input_read);
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

void	rm_whitespace(char *str, int *start, int end)
{
	while (*start < end && (str[*start] == ' '
			|| (str[*start] >= 9 && str[*start] <= 13)))
	{
		(*start)++;
	}
}

int	skip_redir(char *input_read, int start, int end)
{
	rm_whitespace(input_read, &start, end);
	while ((input_read[start] == '<' && input_read[start + 1] != '<')
		|| (input_read[start] == '>' && input_read[start + 1] != '>')
		|| (input_read[start] == '<' && input_read[start + 1] == '<')
		|| (input_read[start] == '>' && input_read[start + 1] == '>'))
	{
		if (input_read[start + 1] == '<' || input_read[start + 1] == '>')
			start += 2;
		else
			start++;
		rm_whitespace(input_read, &start, end);
		while (start < end && input_read[start] != ' '
			&& !(input_read[start] >= 9 && input_read[start] <= 13) 
			&& input_read[start] != '<' && input_read[start] != '>')
		{
			start++;
		}
		rm_whitespace(input_read, &start, end);
	}
	return (start);
}

int	skip_name_args(char *input_read, int start, int end)
{
	while (start < end)
	{
		rm_whitespace(input_read, &start, end);
		if ((input_read[start] == '<' && input_read[start + 1] != '<')
			|| (input_read[start] == '>' && input_read[start + 1] != '>')
			|| (input_read[start] == '<' && input_read[start + 1] == '<')
			|| (input_read[start] == '>' && input_read[start + 1] == '>'))
		{
			return (start);
		}
		start++;
	}
	return (-1);
}

int	get_redir_type(int *start, char *input_read)
{
	int	type;

	if (input_read[*start] == '<' && input_read[*start + 1] != '<')
	{
		type = INPUT;
		(*start)++;
	}
	else if (input_read[*start] == '>' && input_read[*start + 1] != '>')
	{
		type = TRUNC;
		(*start)++;
	}
	else if (input_read[*start] == '<' && input_read[*start + 1] == '<')
	{
		type = HEREDOC;
		(*start) += 2;
	}
	else if (input_read[*start] == '>' && input_read[*start + 1] == '>')
	{
		type = APPEND;
		(*start) += 2;
	}
	else
	{
		type = -1;
	}
	return (type);
}

void	get_cmd_redir(int start, int end, char *input_read, t_command *cmd)
{
	int	i;

	cmd->redir_count = 0;
	while (start < end)
	{
		start = skip_name_args(input_read, start, end);
		if (start == -1 || start >= end)
			break ;
		cmd->redir_cmd[cmd->redir_count] = (t_redir *)malloc(sizeof(t_redir));
		cmd->redir_cmd[cmd->redir_count]->type = get_redir_type
			(&start, input_read);
		if (cmd->redir_cmd[cmd->redir_count]->type == -1)
			exit (1);
		rm_whitespace(input_read, &start, end);
		i = start;
		while (start < end && input_read[start] != ' ' 
			&& !(input_read[start] >= 9 && input_read[start] <= 13)
			&& input_read[start] != '<' && input_read[start] != '>')
		{
			start++;
		}
		cmd->redir_cmd[cmd->redir_count]->file
			= ft_substr(input_read, i, start - i); 
		cmd->redir_count++;
	}
	cmd->redir_cmd[cmd->redir_count] = NULL;
}

t_command	*ft_create_cmd(int start, int end, char *input_read, t_infos *tokens)
{
	int			i;
	t_command	*cmd;

	cmd = (t_command *)ft_malloc(sizeof(t_command));
	cmd->redir_cmd = (t_redir **)ft_malloc(sizeof(t_redir *) * INIT_SIZE);
	get_cmd_name_args(start, end, input_read, cmd);
	get_cmd_redir(start, end, input_read, cmd);
	i = 0;
	while (cmd->args[i])
	{
		is_dollar_char(cmd, i, tokens);
		i++;
	}
	
	return (cmd);
}

t_infos	*ft_sort(char *input_read, t_infos *tokens)
{
	t_var		var;
	t_command	*command;

	ft_init(&var, tokens);
	while (input_read[var.i] != '\0')
	{
		var.start = var.i;
		while ((input_read[var.i] != '\0') && (input_read[var.i] != '|'))
		{
			var.i++;
		}
		command = ft_create_cmd(var.start, var.i, input_read, tokens);
		tokens->commands[tokens->cmd_count++] = command;
		if (input_read[var.i] == '|')
		{
			tokens->pipe_count++;
			var.i++;
		}
	}
	return (tokens);
}
