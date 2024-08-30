/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 20:43:49 by danevans          #+#    #+#             */
/*   Updated: 2024/08/30 00:56:03 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_quoted_content(char *input, int *pos, int end)
{
	char	quote_char;
	int		start;

	quote_char = input[*pos];
	start = ++(*pos);
	while (*pos < end && input[*pos] != quote_char)
		(*pos)++;
	return (ft_substr(input, start, *pos - start));
}

static char	*extract_unquoted_content(char *input, int *pos, int end)
{
	int	start;

	start = *pos;
	while (*pos < end && input[*pos] != ' ' && input[*pos] != '<' &&
		input[*pos] != '>' && input[*pos] != '"' && input[*pos] != '\'')
		(*pos)++;
	return (ft_substr(input, start, *pos - start));
}

static char	*join_and_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}

static char	*extract_argument(char *input, int *pos, int end)
{
	char	*arg;
	char	*temp;

	arg = NULL;
	while (*pos < end)
	{
		if (input[*pos] == '"' || input[*pos] == '\'')
			temp = extract_quoted_content(input, pos, end);
		else
			temp = extract_unquoted_content(input, pos, end);
		if (arg == NULL)
			arg = temp;
		else
			arg = join_and_free(arg, temp);
		if (*pos < end && (input[*pos] == '"' || input[*pos] == '\''))
			continue;
		else
			break;
	}
	return (arg);
}

void	get_cmd_name_args(int start, int end, char *input_read, t_command *cmd)
{
	int		i;
	char	*arg;

	i = skip_redir(input_read, start, end);
	cmd->args_count = 0;
	cmd->name = extract_argument(input_read, &i, end);
	cmd->args = (char **)malloc(sizeof(char *) * (end - start + 2));
	cmd->args[cmd->args_count++] = ft_strdup(cmd->name);
	while (i < end)
	{
		i = skip_redir(input_read, i, end);
		if (i >= end)
			break;
		arg = extract_argument(input_read, &i, end);
		if (arg && *arg)
			cmd->args[cmd->args_count++] = arg;
		else
			free(arg);
	}
	cmd->args[cmd->args_count] = NULL;
}