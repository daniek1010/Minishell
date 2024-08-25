/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:12:50 by danevans          #+#    #+#             */
/*   Updated: 2024/08/25 04:38:02 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_sigint_child(int sig) {
    (void)sig;
	rl_replace_line("", 0);
	// ft_putstr_fd("\n", STDOUT_FILENO);
	// rl_on_new_line();
	rl_redisplay();
    exit(130);  // Exit code 130 indicates termination by SIGINT
}

void setup_signal_handlers_child() {
    signal(SIGINT, handle_sigint_child);
    // signal(SIGQUIT, SIG_IGN);  // Ignore SIGQUIT in child if not needed
}


// char	*ft_read_input_here_doc(char *prompt, char *delimeter)
// {
// 	char	*input_read;
// 	char	*str = NULL;
// 	// int		e_status = 0;

// 	str = NULL;
// 	while (1)
// 	{
// 		if (g_int)
// 		{
// 			if (str)
// 				free (str);
// 			return NULL;
// 		}
// 		input_read = readline(prompt);
// 		if (!input_read)
// 		{
// 			if (str)
// 				free (str);
// 			ft_putendl_fd("execpts delimiter", STDOUT_FILENO);
// 			// return NULL;
// 			exit(0);
// 		}
// 		if (ft_strcmp(input_read, delimeter) == 0)
// 			break ;
// 		add_history(input_read);
// 		str = ft_strjoin_new_line(str, input_read);
// 		free (input_read);
// 	}
// 	if (input_read)
// 		free (input_read);
// 	return (str);
// }

char *ft_read_input_here_doc(char *prompt, char *delimiter) {
    char *input_read;
    char *str = NULL;

    while (1) {
        if (g_int) {  // Check for interruption
            if (str)
                free(str);
            return NULL;
        }

        input_read = readline(prompt);
        if (!input_read) {
            if (str)
                free(str);
            ft_putendl_fd("EOF detected", STDOUT_FILENO);
            return NULL;  // Handle EOF
        }

        if (ft_strcmp(input_read, delimiter) == 0)
            break;

        add_history(input_read);
        str = ft_strjoin_new_line(str, input_read);
        free(input_read);
    }

    if (input_read)
        free(input_read);
    return str;
}


void	redir_here_docs(char *prompt, char *delimeter)
{
	char	*input;
	int		pipefd[2];

	pipe_create(pipefd);
	input = ft_read_input_here_doc(prompt, delimeter);
	if (!input)
	{
		free (input);
		close(pipefd[0]);
		close(pipefd[1]);
		return ;
	}
	write(pipefd[1], input, ft_strlen(input));
	close(pipefd[1]);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
}

int	handle_redirections(t_command *cmd, t_infos *tokens)
{
	int	i;

	if (cmd->redir_count > 0)
	{
		i = 0;
		while (i < cmd->redir_count)
		{
			if (cmd->redir_cmd[i]->type == TRUNC
				|| cmd->redir_cmd[i]->type == APPEND)
			{
				if (!redir_append_trunc(tokens, cmd->redir_cmd[i]->type,
					cmd->redir_cmd[i]->file))
						break ;
			}
			else if (cmd->redir_cmd[i]->type == INPUT)
			{
				if (!redir_input(tokens, cmd->redir_cmd[i]->file))
						break ;
			}
			else
				redir_here_docs("> ", cmd->redir_cmd[i]->file);
			i++;
		}
	}
	return (tokens->e_code);
}

int	redir_append_trunc(t_infos *tokens, int type, char *file)
{
	int	fdout;

	fdout = 0;
	if (type == TRUNC)
		fdout = open(file, O_CREAT | O_WRONLY
				| O_TRUNC, S_IRUSR | S_IWUSR);
	else
		fdout = open(file, O_CREAT | O_WRONLY
				| O_APPEND, S_IRUSR | S_IWUSR);
	if (fdout == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		tokens->e_code = 1;
		return (0);
	}
	dup2(fdout, STDOUT_FILENO);
	tokens->e_code = 0;
	return (1);
}

int	redir_input(t_infos *tokens, char *file)
{
	int	fdin;

	fdin = 0;
	fdin = open(file, O_RDONLY);
	if (fdin == -1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		tokens->e_code = 1;
		return (0);
	}
	dup2(fdin, STDIN_FILENO);
	tokens->e_code = 0;
	return (1);

}
