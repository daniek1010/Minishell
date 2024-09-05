/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 02:57:05 by danevans          #+#    #+#             */
/*   Updated: 2024/09/05 21:17:54 by danevans         ###   ########.fr       */
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
	else if (ft_strcmp(str, ">|") == 0)
		redir->type = TRUNC;
	else
		return (NULL);
	redir->file = ft_strdup(file);
	return (redir);
}

void	save_name_args(t_command *cmd, int *flag,
			int *start, char *tokens_array[])
{
	char	*str;

	if (*flag)
	{
		str = tokens_array[*start];
		if (str[0] == '"' || str[0] == '\'')
			str++;
		cmd->name = ft_strdup(str);
		(*flag) = 0;
	}
	else
	{
		str = tokens_array[*start];
		if (str[0] == '"' || str[0] == '\'')
			str++;
		cmd->args[cmd->i++] = ft_strdup(str);
		(*start)++;
	}
}

t_command	*ft_create_cmd(int start, int end, char *tokens_array[],
	t_infos *tokens)
{
	int			redir_status;
	t_command	*cmd;
	int			flag;

	cmd = init_cmd(&flag);
	while (start <= end)
	{
		if (is_dollar_char(cmd, tokens_array[start], &start, tokens))
			continue ;
		redir_status = is_redirection_char(cmd, tokens_array, &start);
		if (redir_status > 0)
			continue ;
		else if (redir_status < 0)
			break ;
		save_name_args(cmd, &flag, &start, tokens_array);
	}
	cmd->args[cmd->i] = NULL;
	cmd->redir_cmd[cmd->redir_count] = NULL;
	return (cmd);
}

/* this sorrt the token_array checking for the pipe and commands, it writes 
into the cmd until a pipe is found and then it writes into a pipe->cmd1 and
 cmd->2 and return tokens*/
int	ft_sort(t_infos *tokens, char **token_array)
{
	int			i;
	int			start;
	t_command	*command;

	ft_init(tokens);
	i = 0;
	while (token_array[i] != NULL)
	{
		start = i;
		while (token_array[i] && ft_strcmp(token_array[i],
				"|") != 0)
			i++;
		command = ft_create_cmd(start, i - 1, token_array, tokens);
		if (!command)
			return (0);
		tokens->commands[tokens->cmd_index++] = command;
		if (ft_strcmp(token_array[i], "|") == 0)
		{
			tokens->pipe_index++;
			i++;
		}
	}
	tokens->commands[tokens->cmd_index] = NULL;
	ft_cleaner(token_array);
	return (1);
}
