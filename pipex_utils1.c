/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 08:50:30 by danevans          #+#    #+#             */
/*   Updated: 2024/08/06 14:20:16 by danevans         ###   ########.fr       */
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
		// ft_file_error(file_fd);
	}
	else if (mode == OUTPUT)
	{
		file_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		// ft_file_error(file_fd);

	}
	else if (mode == APPEND)
	{
		file_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		// ft_file_error(file_fd);

	}
	// else if (mode == DELIMETER)
	// {
	// 	ft_file_error(file_fd);
	// }
	else 
	{
		// error();
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
printf("values of %d	%d\n", tokens->cmd_index, tokens->pipe_index);
	if (tokens->pipe_index > 0)
	{
	for (int i = 0; i < tokens->pipe_index; i++) {
        ft_execute_pipe(tokens->pipes[i], envp, tokens);
    }
	}
	else
	{
    for (int i = 0; i < tokens->cmd_index; i++) {
        if (fork() == 0) {
            ft_execute(tokens->commands[i], envp, tokens);
        }
        wait(NULL);
    }
	}

	free(tokens->commands);
    free(tokens);

    for (int i = 0; tester[i]; i++) {
        free(tester[i]);
    }
    free(tester);
    return 0;
}

void	execute_command(t_infos *tokens, char *envp[], int pipefd[])
{
	int	infile;
	int	outfile;
	int	append;
	int	i;

	i = 0;
	while(i < tokens->red_index)
	{
		if (tokens->redirs[i]->type == INPUT)
		{
			infile = ft_file(tokens->redirs[i]->file, 0);
			if (infile == -1)
				errors("couldnt open file");
			redirect_input_output(infile, 0, pipefd, 1);
			close(infile);
		}
		else if (tokens->redirs[i]->type == OUTPUT)
		{
			outfile = ft_file(tokens->redirs[i]->file, 1);
			redirect_input_output(0, outfile, pipefd, 2);
			close(outfile);
		}
		else if (tokens->redirs[i]->type == APPEND)
		{
			append = ft_file(tokens->redirs[i]->file, 2);
			redirect_input_output(0, outfile, pipefd, 2);
			close(outfile);
		}
		i++;
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

