/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:33:05 by danevans          #+#    #+#             */
/*   Updated: 2024/09/05 21:17:18 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

#include <string.h> // used it for strcat

# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>

# define INPUT		0
# define TRUNC		1
# define APPEND		2
# define HEREDOC		3
# define INIT_SIZE	64

extern volatile sig_atomic_t	g_int;

typedef struct s_redir
{
	int		type;
	int		fd;
	char	*file;
}	t_redir;

typedef struct s_command
{
	char	*name;
	char	**args;
	t_redir	**redir_cmd;
	int		redir_count;
	int		i;
}	t_command;

typedef struct s_infos
{
	t_command	**commands;
	char		***envp;
	int			pipe_index;
	int			cmd_index;
	int			red_index;
	int			e_code;
	int			save_fdin;
	int			save_fdout;
	int			pipefd[2];
	int			prev_pipefd[2];

}	t_infos;

/* builtin.c .... not formated ... unset*/
int		builtin_export(char ***envp, char *key_value[]);
int		builtin_unset(char ***envp, char *key[]);
int		builtin_env(char ***envp);
int		builtin_echo(t_command *cmd);
int		builtin_cd(char ***envp, const char *path);

/* ft_parser.c .... not formatted*/
int		ft_sort(t_infos *tokens, char **token_array);
char	**ft_read_input(char *prompt);
t_redir	*ft_create_redir(char *str, char *file);
t_command	*ft_create_cmd(int start, int end, char *tokens_array[],
			t_infos *tokens);

/* utils_holders.c .... not formatted*/
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	signal_handlers(void);
int		builtin_export_helper(char **key_value, char ***envp); //too large
t_command	*init_cmd(int *flag);

/* ft_toke_utils.c not formatted*/
char	*list_length_create(const char *str, const int *i);
char	*fill_qoute_case(const char *str, char *list, int *i, char a);
char	*fill_word(const char *str, char *list, int *i);
char	**ft_token_fill(const char *str, char **list);

/* ft_token_split.c formatted */
int		count_qoute_f(const char *str, int i);
int		token_count_words(const char *str);
char	**ft_token_split(char const *s);
char	*fill_direct(const char *str, char *list, int *i);

/* norm.c ...file name should be renamed*/
void	redirect_io(int is_last_command, t_infos *tokens);
void	exec_cmd_builtin(t_command *cmd, int is_last_command,
			t_infos *tokens, int flag);
void	exec_cmd(t_command *cmd, int is_last_command,
			t_infos *tokens, int flag);
int		execute_commander(t_infos *tokens);
int		exec_builtin_path(t_command *command, t_infos *tokens);

// ***********done formated ************
/* ft_expand_var.c .... formatted*/
char	*replace_substring(char *str, char *to_replace, char *replacement);
char	*isolate_variable(char *str, int i);
char	*add_var(char *str, int *i, t_infos *tokens);
char	*expand_var(t_infos *tokens, char *str, int x, int *flag);
char	*ft_extract_variables(char *str, t_infos *tokens);

/*ft_redir_dollar.c.... formatted*/
int		is_redirection_char(t_command *cmd, char *token_array[], int *start);
char	*ft_strstr(char *haystack, char *needle);
int		is_dollar_char(t_command *cmd, char *token_array, int *start, t_infos *tokens);
int		ft_isalnum(int c);
int		is_valid_var_char(char c);

/* ft_env.c ....formated*/
int		compare_key(char ***envp, char *key, int i);
void	set_env_var(char ***envp, char *key, char *value);
char	*get_env_var(char **envp, char *key);
int		set_env_var_helper(char *key, char *value, char ***envp, int i);
char	**write_envp(int *j, int i, char **new_envp, char ***envp);

/*ft_itoa.c ....  formatted*/
char	*ft_itoa(int n);
void	ft_check_builtin(t_command *command, t_infos *tokens);
int		alpha_numeric(char *str);
int		is_filename(char *token_array[], int start);

/*ft_split_minishell.c ....formatted*/
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c);

/* ft_pipe.c .... formated*/
void	close_pipe(t_infos *tokens, int flag);
void	init_pipe(t_infos *tokens);
void	pipe_create(int pipefd[2]);
void	setup_pipes(t_infos *tokens, int is_last_command, int *flag);
void	builtin_handler(t_command *cmd, t_infos *tokens);

/* ft_redir.c .... formatted*/
char	*ft_read_input_here_doc(char *prompt, char *delimeter);
int		handle_redirections(t_command *cmd, t_infos *tokens);
int		redir_input(t_infos *tokens, char *file);
int		redir_append_trunc(t_infos *tokens, int type, char *file);
void	redir_here_docs(char *prompt, char *delimeter, t_infos *tokens);

/*mini_shell_utils1.c ....formated*/
void	errors(char *str);
char	*ft_strdup(const char *s);
void	*ft_malloc(size_t size);
void	close_fd(int fd);
void	ft_init(t_infos *tokens);

/*mini_shell_utils2.c ....formated*/
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
pid_t	fork_process(void);
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
char	**copy_env(char *envp[]);
size_t	ft_strlen(const char *s);
void	ft_cleaner(char *str[]);
int		is_redir(char *tokens[], int start);

/*mini_shell_utils5.c....not full formated*/
void	free_command(t_command *cmd);
void	free_tokens(t_infos *tokens);
void	free_name_args(t_command *cmd);
char	*ft_strchr(const char *str, char c);
void	add_shlvl(t_infos *tokens);

/* mini_shell_utils6 .... formated*/
int		is_builtin(char *type);
int		builtin_pwd(void);
int		not_env_path(t_command *cmd, int i, int x);
int		echo_new_line(t_command *cmd);
int		builtin_unset_helper(char ***new_envp, char ***envp, int j, int i);

#endif