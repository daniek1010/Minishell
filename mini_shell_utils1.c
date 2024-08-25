/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 08:50:30 by danevans          #+#    #+#             */
/*   Updated: 2024/08/25 00:24:56 by danevans         ###   ########.fr       */
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

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}

t_infos	*ft_init(t_var *var)
{
	t_infos	*data;

	data = (t_infos *)ft_malloc(sizeof(t_infos));
	data->commands = (t_command **)ft_malloc(sizeof(t_command) * INIT_SIZE);
	data->pipes = (t_pipe **)ft_malloc(sizeof(t_pipe) * INIT_SIZE);
	data->cmd_index = 0;
	data->pipe_index = 0;
	data->red_index = 0;
	// data->e_code = 0;
	var->i = 0;
	var->j = 0;
	var->end = 0;
	return (data);
}
