/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:33:05 by danevans          #+#    #+#             */
/*   Updated: 2024/08/23 15:07:10 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H

# define MINI_SHELL_H

#include <signal.h>
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
	int		i;
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
	int			e_code;

}t_infos;

typedef struct s_var{
	int	i;
	int	j;
	int	start;
	int	end;
	
}t_var;

int	builtin_export_helper(char **key_value, char **envp[]);
int	alpha_numeric(char *str);

int	ft_check_builtin(t_command *command, char **envp[]);
/*ft_split_minishell.c ....formatted*/
char	**ft_split(char const *s, char *delimeter);
char	*ft_substr(char const *s, unsigned int start, size_t len);




/* builtin.c .... formated*/
int		builtin_export(char **envp[], char *key_value[]);
int		builtin_unset(char **envp[], char *key[]);
int		builtin_env(char **envp[]);
int		builtin_echo(t_command *cmd);
int		builtin_cd(char **envp[], const char *path);

/* ft_env.c ....formated*/
int		compare_key(char **envp[], char *key, int i);
void	set_env_var(char **envp[], char *key, char *value);
char	*get_env_var(char *envp[], char *key);
int		set_env_var_helper(char *key, char *value, char **envp[], int i);
char	**write_envp(int *j, int i, char **new_envp, char **envp[]);

/* ft_pipe.c .... formated*/
int		ft_create_pipe(t_pipe *pipe, char **envp[], t_infos *tokens);
void	pipe_create(int pipefd[2]);
pid_t	fork_process(void);
void	ft_dup(int pipefd[2], int fd);
void	handle_pid1(int pipefd[2], t_pipe *pipe, t_infos *tokens, char **envp[]);

/* ft_parser.c .... not formatted*/
t_infos		*ft_sort(char *token_array[], char **envp[]);
t_redir		*ft_create_redir(char *str, char *file);
char		**ft_read_input(char *prompt);
t_command	*ft_create_cmd(int start, int end, char *tokens[], char *envp[]);
void		is_pipe_char(char *token_array[], char *envp[],
			t_infos *tokens, t_var *var);

/* ft_execute_cmds.c .... formatted*/
int	ft_execute(t_command *command, char **envp[], t_infos *tokens);
int	execute_command(t_infos *tokens, char **envp[]);
int	iterate_pipe_index(t_infos *tokens, char **envp[]);
int	handle_builtin_exit(t_command *cmd, t_infos *tokens, char **envp[]);
int	run_child(t_infos *tokens, char **envp[]);

/* ft_redir.c .... formatted*/
char	*ft_read_input_here_doc(char *prompt, char *delimeter);
void	handle_redirections(t_command *cmd, t_infos *tokens);
void	redir_input(t_infos *tokens, char *file);
void	redir_append_trunc(t_infos *tokens, int type, char *file);
void	redir_here_docs(char *prompt, char *delimeter);

/*mini_shell_utils0.c....formated*/
char	*ft_write_env(char *value);
char	*ft_special_char(char *envp[], const char *str);
int		is_dollar_char(t_command *cmd, char *token_array[], int *start, 
		char *envp[]);
int		is_redirection_char(t_command *cmd, char *token_array[], int *start);
void	destroy_cmd_use_pipe_cmd(t_infos *tokens);

/*mini_shell_utils1.c ....formated*/
void	errors(char *str);
char	*ft_strdup(const char *s);
void	*ft_malloc(size_t size);
void	ft_close(int fd);
t_infos	*ft_init(t_var *var);

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
void	ft_cleaner(char *str[]);
int		is_redir(char *tokens[], int start);

/*mini_shell_utils5.c....formated*/ 
void	free_command(t_command *cmd);
void	free_tokens(t_infos *tokens);
void	free_pipes(t_infos *tokens);
void	free_name_args(t_command *cmd);
char	*ft_strchr(const char *str, char c);

/* mini_shell_utils6 .... formated*/
int		is_builtin(char *type);
int		builtin_pwd(void);
int		not_env_path(t_command *cmd, int i, int x);
int		echo_new_line(t_command *cmd);
int		builtin_unset_helper(char **new_envp, char **envp[], int j, int i);







void	error();
void	bad_arg(int x);
int		ft_file(char *file, int mode);
int		redirect_input_output(int infile, int outfile, int pipefd[2], int x);
void	close_fd(int pipefd[2], int x);
int		less_args(void);


#endif