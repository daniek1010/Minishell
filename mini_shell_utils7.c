/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell_utils7.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:04:18 by danevans          #+#    #+#             */
/*   Updated: 2024/09/18 12:21:40 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_qoute(char *str)
{
	int	i[3];

	i[0] = 1;
	i[1] = 0;
	i[2] = 0;
	if (str[0] == '\"')
		i[1] = !i[1];
	else if (str[0] == '\'')
		i[2] = !i[2];
	while (str[i[0]] != '\0')
	{
		if (str[i[0]] == '\"' && i[2] == 0)
		{
			str = remove_char_at_position(str, i[0]);
			i[1] = !i[1];
		}
		else if (str[i[0]] == '\'' && i[1] == 0)
		{
			str = remove_char_at_position(str, i[0]);
			i[2] = !i[2];
		}
		else
			i[0]++;
	}
	return (str);
}

char	**ft_var_up(char **list, int count, t_infos *tokens)
{
	int	x;

	x = 0;
	while (x != count)
	{
		list[x] = ft_extract_variables(list[x], tokens);
		if (list[x][0] != '\0')
			list[x] = remove_qoute(list[x]);
		x++;
	}
	return (list);
}

void	remove_empty_strings(char **list)
{
	int	i;
	int	j;

	i = 0;
	while (list[i] != NULL)
	{
		if (list[i][0] == '\0')
		{
			free(list[i]);
			j = i;
			while (list[j] != NULL)
			{
				list[j] = list[j + 1];
				j++;
			}
			i--;
		}
		i++;
	}
}

char	**ft_token_spliter(char const *s, t_infos *tokens)
{
	int		word;
	char	**list;

	word = token_count_words(s);
	list = (char **)malloc(sizeof(char *) * (word + 1));
	if (!list)
		return (NULL);
	list[word] = NULL;
	list = ft_token_fill(s, list);
	list = ft_var_up(list, word, tokens);
	remove_empty_strings(list);
	if (list[0] != NULL)
	{
		if (list[0][0] == '|' && list[0][1] == '\0')
			list[0] = change_pipe(list[0]);
	}
	return (list);
}

int	ft_redir_status(t_command *cmd, int redir_status, t_infos *tokens)
{
	if (cmd->i == 0)
		cmd->name = NULL;
	cmd->args[cmd->i] = NULL;
	cmd->redir_cmd[cmd->redir_count] = NULL;
	if (redir_status < 0)
	{
		tokens->e_code = 2;
		free_command(cmd);
		return (0);
	}
	return (1);
}
