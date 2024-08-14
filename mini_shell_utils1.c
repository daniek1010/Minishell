/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 08:50:30 by danevans          #+#    #+#             */
/*   Updated: 2024/08/14 11:57:24 by danevans         ###   ########.fr       */
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

// t_infos	*ft_init(void)
// {
// 	t_infos	*data;
// 	t_pipe	*pipe;

// 	data = (t_infos *)ft_malloc(sizeof(t_infos));
// 	data->commands = (t_command **)ft_malloc(sizeof(t_command) * INIT_SIZE);
// 	data->pipes = (t_pipe **)ft_malloc(sizeof(t_pipe) * INIT_SIZE);
// 	pipe->cmd1 = (t_pipe *)ft_malloc(sizeof(t_pipe) * INIT_SIZE);
// 	pipe->cmd2 = (t_pipe *)ft_malloc(sizeof(t_pipe) * INIT_SIZE);
// 	data = NULL;
// 	data->commands = NULL;
// 	data->pipes = NULL;
// 	pipe->cmd1 = NULL;
// 	pipe->cmd2 = NULL;
// 	data->cmd_index = 0;
// 	data->pipe_index = 0;
// 	data->red_index = 0;
// 	return (data);
// }

t_infos *ft_init(void)
{
    t_infos *data;

    data = (t_infos *)ft_malloc(sizeof(t_infos));
    if (data == NULL) {
        // Handle allocation failure
        return NULL;
    }

    // Allocate memory for command pointers
    data->commands = (t_command **)ft_malloc(sizeof(t_command *) * INIT_SIZE);
    if (data->commands == NULL) {
        free(data);
        // Handle allocation failure
        return NULL;
    }

    // Allocate memory for pipe pointers
    data->pipes = (t_pipe **)ft_malloc(sizeof(t_pipe *) * INIT_SIZE);
    if (data->pipes == NULL) {
        free(data->commands);
        free(data);
        // Handle allocation failure
        return NULL;
    }

    // Initialize fields
    data->cmd_index = 0;
    data->pipe_index = 0;
    data->red_index = 0;

    // Initialize pointers to NULL
    for (int i = 0; i < INIT_SIZE; i++) {
        data->commands[i] = NULL;
        data->pipes[i] = NULL;
    }

    return data;
}
