/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 02:57:05 by danevans          #+#    #+#             */
/*   Updated: 2024/08/19 09:36:26 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_read_input(char *prompt)
{
	char	*input_read;
	// char	*delimter;
	char	**tokens;

	// delimter = " \t\r\n\a";
	input_read = readline(prompt);
	if (input_read)
		add_history(input_read);
	else
	{
		free (input_read);
		errors("No input read");
	}
	printf("%s\n", input_read);
	// tokens = ft_split(input_read, delimter);
	tokens = ft_spliter(input_read, ' ');
	free (input_read);
	return (tokens);
}

int	is_redir(char *tokens[], int start)
{
	if (ft_strcmp(tokens[start], "<") == 0
			|| ft_strcmp(tokens[start], ">") == 0
			|| ft_strcmp(tokens[start], ">>") == 0
			|| ft_strcmp(tokens[start], "<<") == 0)
		return (1);
	return (0);
}

char	*ft_strchr(const char *str, char c)
{
	if (!str)
		return (NULL);
	while(*str)
	{
		if (*str == c)
			return ((char *) str);
		str++;
	}
	return (NULL);
}



char	*ft_special_char(char *envp[], const char *str)
{
	int		i;
	char	*value;
	char	*new_value;
	char	*get_env;
	char	env_key[256] = {0};

	i = 0;
	value = ft_strchr(str, '$');
	if (value)
	{
		value++;
		if (ft_strncmp(value, "?", 1) == 0)
		{
			printf("what do i do ??\n");
		}
		else
		{
			while (*value != ' ' && *value != '\0')
				env_key[i++] = *value++;
			env_key[i] = '\0';
			get_env = get_env_var(envp, env_key);
			if (get_env == NULL)
				return (NULL);
			new_value = ft_strdup(get_env);
		}
		return (new_value);
	}
	return (NULL);
}


t_command	*ft_create_cmd(int start, int end, char *tokens[], char *envp[])
{
	int			i;
	char		*value;
	t_command	*commands;
	t_redir		*redir_command;

	commands = (t_command *)ft_malloc(sizeof(t_command));
	commands->redir_cmd = (t_redir **)ft_malloc(sizeof(t_redir *) * INIT_SIZE);
	commands->name = ft_strdup(tokens[start]);
	commands->args = (char **)ft_malloc(sizeof(char *) * (end - start + 2));
	i = 0;
	commands->redir_count = 0;
	while (start <= end)
	{
		value = ft_special_char(envp, tokens[start]);
		if (value)
		{
			printf("****value***** %s\n",value);
			commands->args[i++] = value;
			start++;
			continue ;
		}
		if (is_redir(tokens, start))
		{
			if (tokens[start + 1])
			{
				redir_command = ft_create_redir(tokens[start],
						tokens[start + 1]);
				commands->redir_cmd[commands->redir_count++] = redir_command;
				start += 2;
				continue ;
			}
			else
				break ;
		}
		commands->args[i++] = ft_strdup(tokens[start++]);
	}
	commands->args[i] = NULL;
	commands->redir_cmd[commands->redir_count] = NULL;
	return (commands);
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

t_infos	*ft_sort(char *tokens[], char *envp[])
{
	int			i;
	int			j = 0;
	int			end = 0;
	int			start;
	t_infos		*data;
	t_pipe		*pipe;
	t_command	*command;
	data = ft_init();
	i = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "$") == 0)
		{
			
		}
		else if (ft_strcmp(tokens[i], "|") == 0)
		{
			pipe = (t_pipe *)ft_malloc(sizeof(t_pipe));
			pipe->cmd1 = ft_create_cmd(j, i - 1, tokens, envp);
			end = i + 1;
			while (tokens[end] && (ft_strcmp(tokens[end], "|") != 0))
				end++;
			pipe->cmd2 = ft_create_cmd(i + 1, end - 1, tokens, envp);
			data->pipes[data->pipe_index++] = pipe;
			j = i + 1;
		}
		else
		{
			start = i;
			while (tokens[i] && ft_strcmp(tokens[i], "|") != 0)
				i++;
			command = ft_create_cmd(start, i - 1, tokens, envp);
			data->commands[data->cmd_index++] = command;
			i--;
		}
		i++;
	}
	ft_null(data);
	ft_cleaner(tokens);
	return (data);
}

