/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 02:57:05 by danevans          #+#    #+#             */
/*   Updated: 2024/08/06 02:44:25 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_read_input(char *prompt)
{
	char	*input_read;
	char	*delimter;
	char	**tokens;

	delimter = " \t\r\n\a";
	input_read =  readline(prompt);
	if (input_read)
	{
		add_history(input_read);
	}
	else
	{
		free (input_read);
		errors("No input read");
	}
	tokens =  ft_split(input_read, delimter);
	free (input_read);
	return (tokens);
}

t_command	*ft_create_cmd(int start, int end, char *tokens[])
{
	int			i;
	t_command	*commands;

	commands = malloc(sizeof(t_command));
	if (!commands)
		errors("Failed to allocate memory for command");
	commands->name = ft_strdup(tokens[start]);
	commands->args = malloc(sizeof(char *) * (end - start + 1));
	if (!commands->args)
		errors("Failed to allocate memory for command arguments");
	i = 0;
	while (start <= end)
	{
		commands->args[i] = malloc(sizeof (commands->args[i]));
		commands->args[i] = ft_strdup(tokens[start]);
		i++;
		start++;
	}
	commands->args[i] = NULL;
	return (commands);
}

t_redir	*ft_create_redir(char *tokens, char *file)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (ft_strcmp(tokens, "<") == 0)
		redir->type = INPUT;
	else if (ft_strcmp(tokens, ">") == 0)
		redir->type = OUTPUT;
	else if (ft_strcmp(tokens, ">>") == 0)
		redir->type = APPEND;
	else if (ft_strcmp(tokens, "<<") == 0)
		redir->type = DELIMETER;
	else
		return (NULL);
	redir->file = ft_strdup(file);
	return (redir);
}

t_infos	*ft_sort(char *tokens[])
{
	int			i;
	int			j = 0;
	int			end = 0;
	int			start;
	t_infos		*data;
	t_pipe		*pipe;
	t_command	*command;
	t_redir		*redir;
	data = ft_init();
	i = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "|") == 0)
		{
			pipe = (t_pipe *)ft_malloc(sizeof(t_pipe));
			if (!pipe)
				return NULL;
			pipe->cmd1 = ft_create_cmd(j, i - 1, tokens);
			end = i + 1;
			while (tokens[end] && (ft_strcmp(tokens[end], "|") != 0))
				end++;
			pipe->cmd2 = ft_create_cmd(i + 1, end - 1, tokens);
			data->pipes[data->pipe_index++] = pipe;
			j = i + 1;
			printf("\n\n\n\n");

		}
		else if (ft_strcmp(tokens[i], "<") == 0 || ft_strcmp(tokens[i], ">")
			== 0 || ft_strcmp(tokens[i], ">>") == 0 || ft_strcmp(tokens[i], "<<") == 0)
		{
			redir = (t_redir *)malloc(sizeof(t_redir));
			if (tokens[i + 1] == NULL)
			{
				//need to check if no two character are followed
				return NULL;
			}
			redir = ft_create_redir(tokens[i], tokens[i + 1]);
			data->redirs[data->red_index++] = redir;
			printf("\n\n\n\n");

		}
		else
		{
			start = i;
			command = (t_command *)ft_malloc(sizeof(t_command));
			while (tokens[i] && ft_strcmp(tokens[i], "|") != 0
				&& ft_strcmp(tokens[i], "<") != 0 && ft_strcmp(tokens[i], ">") != 0
				&& ft_strcmp(tokens[i], "<<") != 0 && ft_strcmp(tokens[i], ">>") != 0)
				i++;
			command = ft_create_cmd(start, i - 1, tokens);
			data->commands[data->cmd_index++] = command;
			i--;
		}
		i++;
	}
	ft_null(data);
	return (data);
}

