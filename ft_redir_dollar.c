/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_dollar.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 03:33:47 by danevans          #+#    #+#             */
/*   Updated: 2024/09/17 15:29:43 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection_char(t_command *cmd, char *token_array[], int *start)
{
	t_redir	*redir_command;

	if (is_redir(token_array, *start))
	{
		if (token_array[*start + 1])
		{
			if (!is_filename(token_array, (*start) + 1))
			{
				printf("minishell: syntax error near unexpected token `%s'\n",
					token_array[(*start) + 1]);
				return (-1);
			}
			redir_command = ft_create_redir(token_array[*start],
					token_array[*start + 1]);
			cmd->redir_cmd[cmd->redir_count++] = redir_command;
			*start += 2;
			return (1);
		}
		else
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			return (-1);
		}
	}
	return (0);
}

char	*ft_strstr(char *haystack, char *needle)
{
	char	*h;
	char	*n;

	if (!*needle)
	{
		return ((char *)haystack);
	}
	while (*haystack)
	{
		h = haystack;
		n = needle;
		while (*h && *n && (*h == *n))
		{
			h++;
			n++;
		}
		if (!*n)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}

int	ft_isalnum(int c)
{
	return (((c > 96 && c < 123) || (c > 64 && c < 91))
		|| (c >= 48 && c <= 57));
}

int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

// void	redir_here_doc_helper(char *input, int pipefd[2], t_infos *tokens)
// {
// 	char	**new_input;
// 	char	*converted_str;

// 	if (tokens->save_fdin == -1)
// 		tokens->save_fdin = dup(STDIN_FILENO);
// 	new_input = ft_token_spliter(input, tokens);
// 	if (new_input)
// 	{
// 		converted_str = convert_str(new_input);
// 		write(pipefd[1], converted_str, ft_strlen(converted_str));
// 		free (input);
// 		free (new_input);
// 		free (converted_str);
// 	}
// 	else
// 	{
// 		write(pipefd[1], input, ft_strlen(input));
// 		free(input);
// 	}
// 	close_fd(pipefd[1]);
// 	dup2(pipefd[0], STDIN_FILENO);
// 	close_fd(pipefd[0]);
// }
