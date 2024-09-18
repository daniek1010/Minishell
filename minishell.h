/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:33:05 by danevans          #+#    #+#             */
/*   Updated: 2024/09/18 15:49:20 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <string.h>
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
# define HEREDOC	3
# define INIT_SIZE	64

extern int	g_exit;

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
	int			exit_flag;
	int			is_heredoc;
	int			save_fdin;
	int			save_fdout;
	int			pipefd[2];
	int			prev_pipefd[2];

}	t_infos;

void		handle_sig_parent(int sig);
void		signal_handlers(void);
void		redir_here_doc_helper(char *input, int pipefd[2], t_infos *tokens);

/* ft_parser.c .... formatted*/
char		**ft_read_input(char *prompt, t_infos *tokens);
t_redir		*ft_create_redir(char *str, char *file);
int			save_name_args(t_command *cmd, int *flag,
				int *start, char *tokens_array[]);
t_command	*ft_create_cmd(int start, int end, char *tokens_array[],
				t_infos *tokens);
int			ft_sort(t_infos *tokens, char **token_array);

/* norm.c ...file name should be renamed*/
void		redirect_io(int is_last_command, t_infos *tokens);
void		exec_cmd_builtin(t_command *cmd, int is_last_command,
				t_infos *tokens, int flag);
void		exec_cmd(t_command *cmd, int is_last_command,
				t_infos *tokens, int flag);
int			execute_commander(t_infos *tokens);
int			exec_builtin_path(t_command *command, t_infos *tokens);

// ***********done formated ************
/* builtin.c .... not formated ... unset*/
int			builtin_export(char ***envp, char *key_value[]);
int			builtin_unset(char ***envp, char *key[]);
int			builtin_env(char ***envp);
int			builtin_echo(t_command *cmd);
int			builtin_cd(char ***envp, char **args);

/*ft_redir_dollar.c.... formatted*/
int			is_redirection_char(t_command *cmd, char *token_array[],
				int *start);
char		*ft_strstr(char *haystack, char *needle);
int			ft_isalnum(int c);
int			is_valid_var_char(char c);

/* ft_env.c ....formated*/
int			compare_key(char ***envp, char *key, int i);
void		set_env_var(char ***envp, char *key, char *value);
char		*get_env_var(char **envp, char *key);
int			set_env_var_helper(char *key, char *value, char ***envp, int i);
char		**write_envp(int *j, int i, char **new_envp, char ***envp);

/*ft_itoa.c ....  formatted*/
char		*ft_itoa(int n);
void		ft_check_builtin(t_command *command, t_infos *tokens);
int			alpha_numeric(char *str);
int			is_filename(char *token_array[], int start);

/*ft_split_minishell.c ....formatted*/
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		**ft_split(char const *s, char c);

/* ft_pipe.c .... formated*/
void		close_pipe(t_infos *tokens, int flag);
void		init_pipe(t_infos *tokens);
void		pipe_create(int pipefd[2]);
void		setup_pipes(t_infos *tokens, int is_last_command, int *flag);
void		builtin_handler(t_command *cmd, t_infos *tokens,
				int is_last_command);

/* ft_redir.c .... formatted*/
char		*ft_read_input_here_doc(char *prompt, char *delimeter);
int			handle_redirections(t_command *cmd, t_infos *tokens);
int			redir_input(t_infos *tokens, char *file);
int			redir_append_trunc(t_infos *tokens, int type, char *file);
void		redir_here_docs(char *delimeter, t_infos *tokens, t_command *cmd,
				int pos);

/* minishell_utils0.c */
int			echo_n_handeler(char *str);
int			handle_heredoc(t_command *cmd, t_infos *tokens);
int			count_heredoc(t_command *cmd);
void		close_pipefd(int pipefd[2]);
void		exec_child_process(t_infos *tokens, t_command *cmd,
				int is_last_command);

/*mini_shell_utils1.c ....formated*/
void		errors(char *str);
char		*ft_strdup(const char *s);
void		*ft_malloc(size_t size);
void		close_fd(int fd);
void		ft_init(t_infos *tokens);

/*mini_shell_utils2.c ....formated*/
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
pid_t		fork_process(void);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strjoin_new_line(char const *s1, char const *s2);

/*mini_shell_utils3.c ....formated*/
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strcmp(const char *s1, const char *s2);
char		*join(char *str, char *av);
char		*ft_access(char *av, char *envp[]);
char		**ft_check_path(char *envp[]);

/*mini_shell_utils4.c ....formated*/
void		ft_strcpy(char *s1, char *s2);
char		**copy_env(char *envp[]);
size_t		ft_strlen(const char *s);
void		ft_cleaner(char *str[]);
int			is_redir(char *tokens[], int start);

/*mini_shell_utils5.c....not full formated*/
void		free_command(t_command *cmd);
void		free_tokens(t_infos *tokens);
void		free_name_args(t_command *cmd);
char		*ft_strchr(const char *str, char c);
void		add_shlvl(t_infos *tokens);

/* mini_shell_utils6 .... formated*/
int			is_builtin(char *type);
int			builtin_pwd(void);
int			echo_new_line(t_command *cmd);
int			builtin_unset_helper(char ***new_envp, char ***envp, int j, int i);
void		skip_until_pipe_end(char **token_array, int *i);

/* mini_shell_utils7 .... formated*/
char		**ft_var_up(char **list, int count, t_infos *tokens);
int			ft_redir_status(t_command *cmd, int redir_status, t_infos *tokens);
void		remove_empty_strings(char **list);
char		*remove_qoute(char *str);
char		**ft_token_spliter(char const *s, t_infos *tokens);

/* minishell_utils8.c */
int			ft_atoi(const char *str);
int			ft_isdigit(int c);
int			print_error(char *str_i, char *str_0);

/*mini_shell_utils9.c*/
char		*convert_str(char **input);
const char	*builtin_cd_helper(char ***envp, char **args);
void		wait_for_child(pid_t pid, t_infos *tokens, int is_last_command);
int			create_new(char ***envp, char *str, int i, int j);
t_command	*init_cmd(int *flag);

/* mini_shell_utils10.c */
int			export_helper_2(char **key_value, char ***envp, char *key,
				char *value);
int			builtin_export_helper(char **key_value, char ***envp);
void		handle_sig_child(int sig);
void		signal_handlers_child(void);
void		restore_std(t_infos *tokens, int flag);

/* split_utils.c */
char		*ft_strncpy(char *dest, const char *src, size_t n);
char		*ft_strcat(char *dest, const char *src);
int			pipe_count(const char *str, int i, int *count, int *in_word);
int			count_qoute(const char *str, int i, int *count, int	*in_word);
int			count_word_2(const char *str, int i, int *count, int	*in_word);

/* split_utils1.c */
char		*ft_var_up_2(char *list, t_infos *tokens);
char		*ft_token_fill_2(const char *str, char *list);
char		**ft_token_spliter_2(char const *s, t_infos *tokens);

/* split_utils2.c */
int			token_count_words(const char *str);
int			count_string_length(const char *str, int i);
char		*fill_word(const char *str, char *list, int *i);
char		*fill_direct(const char *str, char *list, int *i);
char		**ft_token_fill(const char *str, char **list);

/* split_utils3.c */
char		*fill_part_one(const char *str, int *j, int i);
char		*fill_part_two(const char *str, char *new_str, int j, int i);
char		*remove_char( char *str, char to_remove, int i);
char		*replace_substring(char *str, char *to_rep, char *repment, int *i);
char		*isolate_variable(char *str, int i);

/* split_utils4.c */
char		*expand_var(t_infos *tokens, char *str, int x);
char		*remove_char_at_position(char *str, int pos);
char		*remove_substring(const char *str, const char *to_rep, int *i);
char		*add_var(char *str, int *i, t_infos *tokens);
char		*ft_extract_variables(char *str, t_infos *tokens);

/* split_utils5.c */
char		*change_pipe(char *list);
int			path_not_found(t_command *command);
int			pipe_start_error(void);
int			empty_str_error(void);
void		invalid_name_args(t_infos *tokens, t_command *cmd);

#endif