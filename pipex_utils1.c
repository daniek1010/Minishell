/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 08:50:30 by danevans          #+#    #+#             */
/*   Updated: 2024/08/06 02:52:33 by danevans         ###   ########.fr       */
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

t_infos *ft_init(void) {
    t_infos *data = malloc(sizeof(t_infos));
    if (!data) return NULL;
    
    data->pipes = malloc(sizeof(t_pipe *) * 42);
    data->commands = malloc(sizeof(t_command *) * 42);
    data->redirs = malloc(sizeof(t_redir *) * 42);
    
    if (!data->pipes || !data->commands || !data->redirs) {
        // Handle allocation failure
        free(data);
        return NULL;
    }
    
    data->pipe_index = 0;
    data->cmd_index = 0;
    data->red_index = 0;
    
    return data;
}



// t_infos	*ft_init(void)
// {
// 	t_infos	*data;

// 	data = (t_infos *)ft_malloc(sizeof(t_infos));
// 	data->commands = (t_command **)ft_malloc(sizeof(t_command) * INIT_SIZE);
// 	data->pipes = (t_pipe **)ft_malloc(sizeof(t_pipe) * INIT_SIZE);
// 	data->redirs = (t_redir **)ft_malloc(sizeof(t_redir) * INIT_SIZE);
// 	data->cmd_index = 0;
// 	data->pipe_index = 0;
// 	data->red_index = 0;
// 	return (data);
// }

void	ft_null(t_infos *data)
{
	data->pipes[data->pipe_index] = NULL;
	data->redirs[data->red_index] = NULL;
	data->commands[data->cmd_index] = NULL;
}

void	ft_file_error(int file_fd)
{
	if (file_fd == -1)
		perror("Couldnt open file");
	return ;
	
}

int	ft_file(char *file, int mode)
{
	int	file_fd;

	if (mode == INPUT)
	{
		file_fd = open(file, O_RDONLY);
		ft_file_error(file_fd);
	}
	else if (mode == OUTPUT)
	{
		file_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		ft_file_error(file_fd);

	}
	else if (mode == APPEND)
	{
		file_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		ft_file_error(file_fd);

	}
	// else if (mode == DELIMETER)
	// {
	// 	ft_file_error(file_fd);
	// }
	else 
	{
		error();
		return (-1);
	}
	return (file_fd);
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

int main(int ac, char *av[], char *envp[])
{
    char **tester;
	tester = ft_read_input("Minishell> ");
   

	t_infos *tokens ;

	tokens = ft_sort(tester);
	
		
	ft_check_path(envp);
	ft_execute(tokens, envp, 0);

	free(tokens->commands);
    free(tokens);

    for (int i = 0; tester[i]; i++) {
        free(tester[i]);
    }
    free(tester);
    return 0;
}

void	execute_command(char *av[], char *envp[], int pipefd[], int process)
{
	int	infile;
	int	outfile;

	if (process == 1)
	{
		infile = ft_file(av[1], 0);
		redirect_input_output(infile, 0, pipefd, 1);
		close(infile);
		ft_execute(av, envp, 2);
	}
	else if (process == 2)
	{
		outfile = ft_file(av[4], 1);
		redirect_input_output(0, outfile, pipefd, 2);
		close(outfile);
		ft_execute(av, envp, 3);
	}
}

int	redirect_input_output(int infile, int outfile, int pipefd[2], int x)
{
	if (x == 1)
	{
		if (dup2(infile, STDIN_FILENO) == -1)
			error();
		close(infile);
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			error();
		close(pipefd[1]);
	}
	else if (x == 2)
	{
		close(pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
			error();
		close(pipefd[0]);
		if (dup2(outfile, STDOUT_FILENO) == -1)
			error();
		close(outfile);
	}
	return (0);
}

void	ft_execute(t_infos *data, char *envp[], int x)
{
	char	*path;

	path = ft_access(data->commands[0]->name, envp);
	if (path == NULL){
		errors("Couldn't find the executable");
		}
	if (execve(path, data->commands[0]->args, envp) == -1)
	{
		free(path);
		errors("Couldnt execute the cmd");
	}
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
