/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:33:05 by danevans          #+#    #+#             */
/*   Updated: 2024/08/09 15:16:34 by danevans         ###   ########.fr       */
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
#define TRUNC		1
#define APPEND		2
#define DELIMETER	3
#define	INIT_SIZE	64

typedef struct s_redir{
	int		type;
	int		fd;
	char	*file;
}t_redir;

typedef struct s_command{
	char 	*name;
	char 	**args;
	t_redir	**redir_cmd;
	int		redir_count;
}t_command;

typedef struct s_pipe{
	t_command *cmd1;
	t_command *cmd2;
}t_pipe;

typedef struct s_infos{
	t_command	**commands;
	t_pipe		**pipes;
	// t_redir		**redirs;
	int			pipe_index; 
	int			cmd_index; 
	int			red_index;
	int			pipin;
	int			pipout;
	int			fdin;
	int			fdout;
	
}t_infos;


char	**ft_read_input(char *prompt);
void	errors(char *str);
char	**ft_split(char const *s, char *delimeter);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_malloc(size_t size);
t_infos	*ft_init(void);
void	ft_null(t_infos *data);
char	**ft_check_path(char *envp[]);
t_infos	*ft_sort(char *tokens[]);
char	*ft_strdup(const char *s);
void	ft_execute(t_command *command, char *envp[]);
int		ft_create_pipe(t_pipe *pipe, char *envp[], t_infos *tokens);
void	ft_putstr_fd(char *s, int fd);


void handle_redirections(t_command *cmd, t_infos *tokens);
void	redir_input(t_infos *tokens, char *file);
void	redir_append_trunc(t_infos *tokens, int type, char *file);
void	execute_command(t_infos *tokens, char *envp[]);
t_redir	*ft_create_redir(char *str, char *file);
void	ft_putendl_fd(char *s, int fd);

void	ft_close(int fd);

void exec_cmmd(t_command *cmd, t_infos *tokens, char *envp[]);



// char	**ft_splittest(char const *s, char c);





void	error();
char	*join(char *str, char *av);
void	bad_arg(int x);
char	*ft_access(char *av, char *envp[]);
void	ft_cleaner(char *str[]);
int		ft_file(char *file, int mode);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		redirect_input_output(int infile, int outfile, int pipefd[2], int x);
void	close_fd(int pipefd[2], int x);
void	pipe_create(int pipefd[2]);
int		less_args(void);
pid_t	fork_process(void);


#endif