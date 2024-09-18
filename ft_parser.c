/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 02:57:05 by danevans          #+#    #+#             */
/*   Updated: 2024/09/18 12:22:05 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_read_input(char *prompt, t_infos *tokens)
{
	char	*input_read;
	char	**tokens_array;

	input_read = readline(prompt);
	if (g_exit == 130)
	{
		tokens->e_code = 130;
		g_exit = -1;
	}
	if (input_read == NULL)
	{
		free (input_read);
		return (NULL);
	}
	add_history(input_read);
	tokens_array = ft_token_spliter(input_read, tokens);
	free (input_read);
	return (tokens_array);
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

int	save_name_args(t_command *cmd, int *flag,
			int *start, char *tokens_array[])
{
	char	*str;

	if (*flag)
	{
		str = tokens_array[*start];
		if (str[0] == '"' || str[0] == '\'')
			str++;
		if (str && ft_strlen(str) == 0)
			return (0);
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
	return (1);
}

t_command	*ft_create_cmd(int start, int end, char *tokens_array[],
				t_infos *tokens)
{
	t_command	*cmd;
	int			redir_status;
	int			flag;

	cmd = init_cmd(&flag);
	redir_status = 0;
	while (start <= end)
	{
		redir_status = is_redirection_char(cmd, tokens_array, &start);
		if (redir_status > 0)
			continue ;
		else if (redir_status < 0)
			break ;
		if (!save_name_args(cmd, &flag, &start, tokens_array))
		{
			invalid_name_args(tokens, cmd);
			return (NULL);
		}
	}
	if (!ft_redir_status(cmd, redir_status, tokens))
		return (NULL);
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
		skip_until_pipe_end(token_array, &i);
		command = ft_create_cmd(start, i - 1, token_array, tokens);
		if (command == NULL)
			break ;
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
