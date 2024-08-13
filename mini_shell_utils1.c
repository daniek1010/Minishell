/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 08:50:30 by danevans          #+#    #+#             */
/*   Updated: 2024/08/13 16:12:55 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_errors(char *str, t_command *command, char *env[], t_infos *tokens)
{
	perror(str);
	if (tokens){
	free_tokens(tokens);
	tokens = NULL;
	}
	if (env)
		ft_cleaner(env);
	ft_putendl_fd("got heere ? \n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

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

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

t_infos	*ft_init(void)
{
	t_infos	*data;

	data = (t_infos *)ft_malloc(sizeof(t_infos));
	data->commands = (t_command **)ft_malloc(sizeof(t_command) * INIT_SIZE);
	data->pipes = (t_pipe **)ft_malloc(sizeof(t_pipe) * INIT_SIZE);
	data->cmd_index = 0;
	data->pipe_index = 0;
	data->red_index = 0;
	return (data);
}
