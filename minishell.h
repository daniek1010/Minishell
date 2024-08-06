/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:33:05 by danevans          #+#    #+#             */
/*   Updated: 2024/08/06 02:11:48 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H

# define MINI_SHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

#define INPUT		0
#define OUTPUT		1
#define APPEND		2
#define DELIMETER	3
#define	INIT_SIZE	64


typedef struct s_command{
	char *name;
	char **args;
}t_command;

typedef struct s_pipe{
	t_command *cmd1;
	t_command *cmd2;
}t_pipe;

typedef struct s_redir{
	int		type;
	int		fd;
	char	*file;
}t_redir;

typedef struct s_infos{
	t_command	**commands;
	t_pipe		**pipes;
	t_redir		**redirs;
	int			pipe_index; 
	int			cmd_index; 
	int			red_index;
	
}t_infos;


char	**ft_read_input(char *prompt);
void	errors(char *str);
char	**ft_split(char const *s, char *delimeter);
int	ft_strcmp(const char *s1, const char *s2);
void	*ft_malloc(size_t size);
t_infos	*ft_init(void);
void	ft_null(t_infos *data);
char	**ft_check_path(char *envp[]);
t_infos	*ft_sort(char *tokens[]);
char	*ft_strdup(const char *s);









// char	**ft_splittest(char const *s, char c);





void	error();
char	*join(char *str, char *av);
void	bad_arg(int x);
char	*ft_access(char *av, char *envp[]);
void	ft_cleaner(char *str[]);
int		ft_file(char *file, int mode);
void	ft_execute(t_infos *data, char *envp[], int x);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	execute_command(char *av[], char *envp[], int pipefd[], int process);
int		redirect_input_output(int infile, int outfile, int pipefd[2], int x);
void	close_fd(int pipefd[2], int x);
void	create_pipe(int pipefd[2]);
int		less_args(void);
pid_t	fork_process(void);

#endif
