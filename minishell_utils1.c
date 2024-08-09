/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 08:50:30 by danevans          #+#    #+#             */
/*   Updated: 2024/08/09 15:20:25 by danevans         ###   ########.fr       */
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
		errors("Malloc Failed");
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

void	ft_null(t_infos *data)
{
	data->pipes[data->pipe_index] = NULL;
	data->commands[data->cmd_index] = NULL;
}

char	**ft_check_path(char *envp[])
{
	int		i;
	char	**splitted;
	char *delimter = ":,:,:,:,:";
	

	i = 0;
	splitted = NULL;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			splitted = ft_split(envp[i] + 5, delimter);
			break ;
		}
		i++;
	}
	return (splitted);
}

void	ft_cleaner(char *str[])
{
	int		i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL)
		return ;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
	write(fd, "\n", 1);
}

char	*ft_access(char *av, char *envp[])
{
	char	**splitted;
	char	*path;
	int		i;

	splitted = ft_check_path(envp);
	i = -1;
	while (splitted[++i] != NULL)
	{
		path = join(splitted[i], av);
		if (access(path, X_OK) == 0)
			break ;
		free(path);
	}
	if (splitted[i] == NULL)
	{
		ft_cleaner(splitted);
		return (NULL);
	}
	return (path);
}

char	*join(char *str, char *av)
{
	char	*path;
	char	**cmd;

	cmd = ft_split(av, "     ");
	str = ft_strjoin(str, "/");
	path = ft_strjoin(str, cmd[0]);
	free(str);
	ft_cleaner(cmd);
	return (path);
}