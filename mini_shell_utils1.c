/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 08:50:30 by danevans          #+#    #+#             */
/*   Updated: 2024/09/09 23:19:25 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	errors(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

char	*ft_strdup(const char *s)
{
	char	*result;
	size_t	len;
	int		i;

	len = ft_strlen(s);
	result = malloc((len + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

void	*ft_malloc(size_t n_size)
{
	void	*ptr;

	ptr = malloc(n_size);
	if (!ptr)
		perror("Malloc Failed");
	return (ptr);
}

void	close_fd(int fd)
{
	if (fd >= 0)
	{
		close (fd);
	}
	fd = -1;
}

void	ft_init(t_infos *tokens)
{
	tokens->commands = (t_command **)ft_malloc(sizeof(t_command) * INIT_SIZE);
	tokens->cmd_index = 0;
	tokens->pipe_index = 0;
	tokens->red_index = 0;
	tokens->save_fdin = -1;
	tokens->save_fdout = -1;
}
