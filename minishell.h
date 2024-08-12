/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:33:05 by danevans          #+#    #+#             */
/*   Updated: 2024/08/12 15:11:13 by danevans         ###   ########.fr       */
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
#define HEREDOC		3
#define	INIT_SIZE	64

typedef struct s_env
{
	int				i;
	char			*key;
	char			*value;
	struct s_env	*next;
}t_env;


typedef struct s_redir{
	int		type;
	int		fd;
	char	*file;
	char	*delimeter;
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
	int			pipe_index; 
	int			cmd_index; 
	int			red_index;
	int			pipin;
	int			pipout;
	int			fdin;
	int			fdout;
	
}t_infos;



// char	**ft_splittest(char const *s, char c);
// void exec_cmmd(t_command *cmd, t_infos *tokens, char *envp[]);


/* ft_parser.c .... not formatted*/
t_infos		*ft_sort(char *tokens[]);
t_redir		*ft_create_redir(char *str, char *file);
char		**ft_read_input(char *prompt);
t_command	*ft_create_cmd(int start, int end, char *tokens[]);

/* ft_execute_cmds.c .... not formatted*/
void	ft_execute(t_command *command, char *envp[], t_env *env);
void	execute_command(t_infos *tokens, t_env *env);
void	ft_check_builtin(t_command *command, t_env *env);




/* ft_pipe.c ....*/
int		ft_create_pipe(t_pipe *pipe, char *envp[], t_infos *tokens, t_env *env);
void	pipe_create(int pipefd[2]);
pid_t	fork_process(void);
void	ft_close_pipe(int pipefd[2]);
void	ft_dup(int pipefd[2], int fd);

/* ft_redir.c .... formatted*/
char	*ft_read_input_here_doc(char *prompt, char *delimeter);
void	handle_redirections(t_command *cmd, t_infos *tokens);
void	redir_input(t_infos *tokens, char *file);
void	redir_append_trunc(t_infos *tokens, int type, char *file);
void	redir_here_docs(char *prompt, char *delimeter);

/* builtin.c .... formated*/
void	builtin_export(t_env *envp, char *key, char *value);
void	builtin_unset(t_env *envp, char *key);
void	builtin_env(t_env *envp);
void	builtin_echo(t_command *cmd);
int		is_builtin(char *type);

/* ft_env.c ....formated*/
char	**convert_env(t_env *env);
void	set_env_var(t_env **env, char *key, char *value);
char	*get_env_var(t_env *env, char *key, char *value);
void	builtin_cd(t_env *env,const char *path);
void	builtin_pwd(void);

/*mini_shell_utils1.c ....formated*/
void	errors(char *str);
char	*ft_strdup(const char *s);
void	*ft_malloc(size_t size);
void	ft_close(int fd);
t_infos	*ft_init(void);

/*mini_shell_utils2.c ....formated*/
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_null(t_infos *data);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_new_line(char const *s1, char const *s2);

/*mini_shell_utils3.c ....formated*/
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*join(char *str, char *av);
char	*ft_access(char *av, char *envp[]);
char	**ft_check_path(char *envp[]);

/*mini_shell_utils4.c ....formated*/
void	ft_strcpy(char *s1, char *s2);
int		is_type(const char *s, char *c, int start, int i);
size_t	ft_strlen(const char *s);
char	*helper_convert_env(t_env *temp, int i);
void	ft_cleaner(char *str[]);

/*ft_split_minishell.c ....formatted*/
char	**ft_split(char const *s, char *delimeter);
char	*ft_substr(char const *s, unsigned int start, size_t len);





void	error();
void	bad_arg(int x);
int		ft_file(char *file, int mode);
int		redirect_input_output(int infile, int outfile, int pipefd[2], int x);
void	close_fd(int pipefd[2], int x);
int		less_args(void);


#endif