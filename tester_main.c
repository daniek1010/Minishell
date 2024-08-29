// #include <stdio.h>
// #include <string.h>
// #include "minishell.h"

// void	get_cmd_name_args(int start, int end, char *input_read, t_command *cmd);
// void	get_cmd_redir(int start, int end, char * input_read, t_command *cmd);
// int main()
// {
// 	t_command *cmd;
// 	cmd = (t_command *)malloc(sizeof(t_command));
// 	cmd->redir_cmd = malloc(sizeof(t_redir *) * 64);
// 	char *input = "  <echo \"$PATH     'this\' \" <ano<this  ther <one <   here    <<    is    >the <input        impressed <another one ?";
// 	size_t len = strlen(input);
// 	(int)len;
// 	int start = 0;
// 	get_cmd_name_args(start, len, input, cmd);
// 	for (int i = 0; cmd->args[i]; i++)
// 	{
// 		printf("cmd.name = %s      cmd.args = %s\n", cmd->name, cmd->args[i]);
// 	}

// 	printf("\n\n");
// 	start = 0;
// 	get_cmd_redir(start, len, input, cmd);
// 	for (int i = 0; cmd->redir_cmd[i]; i++)
// 	{
// 		printf("redir.ype = %d    redir.file = %s\n", cmd->redir_cmd[i]->type, cmd->redir_cmd[i]->file);
// 	}
// }

// void	rm_whitespace(char *str, int *start, int end)
// {
// 	while (*start < end && (str[*start] == ' '
// 			|| (str[*start] >= 9 && str[*start] <= 13)))
// 		(*start)++;
// }

// int	skip_redir(char *input_read, int start, int end)
// {
// 	int	i;

// 	i = 0;
// 	rm_whitespace(input_read, &start, end);
// 	while ((input_read[start] == '<' && input_read[start + 1] != '<')
// 		|| (input_read[start] == '>' && input_read[start + 1] != '>')
// 		|| (input_read[start] == '<' && input_read[start + 1] == '<')
// 		|| (input_read[start] == '>' && input_read[start + 1] == '>'))
// 	{
// 		if (input_read[start + 1] == '<' || input_read[start + 1] == '>')
// 			start += 2;
// 		else
// 			start++;
// 		rm_whitespace(input_read, &start, end);
// 		while (start < end && input_read[start] != ' '
// 			&& !(input_read[start] >= 9 && input_read[start] <= 13) 
// 			&& input_read[start] != '<' && input_read[start] != '>')
// 			start++;
// 		rm_whitespace(input_read, &start, end);
// 	}
// 	return (start);
// }


// int	check_balanced_quotes(const char *str, int start, int end)
// {
// 	char quote = 0;
//     int has_opening_quote = 0;

// 	while (start < end)
// 	{
// 		if ((str[start] == '"' || str[start] == '\'') && quote == 0)
// 		{
// 			quote = str[start];
// 	    	has_opening_quote = 1;
// 	    } 
// 		else if (str[start] == quote)
// 		{
// 			quote = 0;
// 			has_opening_quote = 0;
// 	    }
// 		start++;
// 	}
//     return (has_opening_quote == 0);
// }

// // int	skip_name_args(char *input_read, int start, int end)
// // {
// // 	int	i;

// // 	i = 0;
// // 	while (start < end)
// // 	{
// // 		rm_whitespace(input_read, &start, end);
// // 		if ((input_read[start] == '<' && input_read[start + 1] != '<')
// // 			|| (input_read[start] == '>' && input_read[start + 1] != '>')
// // 			|| (input_read[start] == '<' && input_read[start + 1] == '<')
// // 			|| (input_read[start] == '>' && input_read[start + 1] == '>'))
// // 			return (start);
// // 		start++;
// // 	}
// // 	return (-1);
// // }

// int skip_name_args(char *input_read, int start, int end) {
//     int i = 0;
//     char quote = 0;

//     while (start < end) {
//         rm_whitespace(input_read, &start, end);

//         // Handle quoted strings
//         if (input_read[start] == '"' || input_read[start] == '\'') {
//             quote = input_read[start];
//             start++;
//             while (start < end && input_read[start] != quote)
//                 start++;
//             if (start < end)
//                 start++; // Skip closing quote
//         }

//         // If we encounter a redirection outside of quotes, return the position
//         if ((input_read[start] == '<' && input_read[start + 1] != '<')
//             || (input_read[start] == '>' && input_read[start + 1] != '>')
//             || (input_read[start] == '<' && input_read[start + 1] == '<')
//             || (input_read[start] == '>' && input_read[start + 1] == '>')) {
//             return start;
//         }

//         start++;
//     }

//     return -1;
// }


// int	get_redir_type(int *start, char *input_read)
// {
// 	int	type;

// 	if (input_read[*start] == '<' && input_read[*start + 1] != '<')
// 	{
// 		type = INPUT;
// 		(*start)++;
// 	}
// 	else if (input_read[*start] == '>' && input_read[*start + 1] != '>')
// 	{
// 		type = TRUNC;
// 		(*start)++;
// 	}
// 	else if (input_read[*start] == '<' && input_read[*start + 1] == '<')
// 	{
// 		type = HEREDOC;
// 		(*start) += 2;
// 	}
// 	else if (input_read[*start] == '>' && input_read[*start + 1] == '>')
// 	{
// 		type = APPEND;
// 		(*start) += 2;
// 	}
// 	else
// 		type = -1;
// 	return (type);
// }

// void	get_cmd_redir(int start, int end, char *input_read, t_command *cmd)
// {
// 	int	i;

// 	cmd->redir_cmd = (t_redir **)malloc(sizeof(t_redir *) * (end - start + 1));
// 	cmd->redir_count = 0;
// 	while (start < end)
// 	{
// 		start = skip_name_args(input_read, start, end);
// 		if (start == -1 || start >= end)
// 			break ;
// 		cmd->redir_cmd[cmd->redir_count] = (t_redir *)malloc(sizeof(t_redir));
// 		cmd->redir_cmd[cmd->redir_count]->type = get_redir_type
// 			(&start, input_read);
// 		if (cmd->redir_cmd[cmd->redir_count]->type == -1)
// 			exit (1); //invalid redir
// 		rm_whitespace(input_read, &start, end);
// 		i = start;
// 		while (start < end && input_read[start] != ' ' 
// 			&& !(input_read[start] >= 9 && input_read[start] <= 13)
// 			&& input_read[start] != '<' && input_read[start] != '>')
// 			start++;
// 		cmd->redir_cmd[cmd->redir_count]->file
// 			= ft_substr(input_read, i, start - i); 
// 		cmd->redir_count++;
// 	}
// 	cmd->redir_cmd[cmd->redir_count] = NULL;
// }

// void	get_cmd_name_args(int start, int end, char *input_read, t_command *cmd)
// {
// 	int		i;
// 	int		quote;
// 	char	*name;

// 	cmd->args_count = 0;
// 	start = skip_redir(input_read, start, end);
// 	i = start;
// 	while (start < end && input_read[start] != ' ' && !(input_read[start] >= 9
// 			&& input_read[start] <= 13) && input_read[start] != '<'
// 		&& input_read[start] != '>')
// 		start++;
// 	cmd->name = ft_substr(input_read, i, start - i);
// 	cmd->args = (char **)malloc(sizeof(char *) * (end - start + 2));
// 	while (start < end)
// 	{
// 		start = skip_redir(input_read, start, end);
// 		i = start;
// 		quote = 0;
//         // Check for quoted strings
//         if (input_read[start] == '"' || input_read[start] == '\'')
// 		{
//             if (!check_balanced_quotes(input_read, start, end))
// 			{
//                 fprintf(stderr, "Error: Unbalanced quotes in input.\n");
//                 exit(1);
//             }
//             quote = input_read[start++];
//             while (start < end && input_read[start] != quote)
//                 start++;
//             if (start < end)
//                 start++; // Skip closing quote
//         }
// 		else
// 		{
// 			while (start < end && input_read[start] != ' '
// 				&& !(input_read[start] >= 9 && input_read[start] <= 13)
// 				&& input_read[start] != '<' && input_read[start] != '>')
// 			start++;
// 		}
// 		cmd->args[cmd->args_count++] = ft_substr(input_read, i, start - i);
// 	}
// 	cmd->args[cmd->args_count] = NULL;
// }

// // void get_cmd_name_args(int start, int end, char *input_read, t_command *cmd) {
// //     int i;
// //     char quote;

// //     cmd->args_count = 0;
// //     start = skip_redir(input_read, start, end);
// //     i = start;

// //     // Skip command name
// //     while (start < end && input_read[start] != ' ' && !(input_read[start] >= 9
// //             && input_read[start] <= 13) && input_read[start] != '<'
// //             && input_read[start] != '>') {
// //         start++;
// //     }

// //     cmd->name = ft_substr(input_read, i, start - i);
// //     cmd->args = (char **)malloc(sizeof(char *) * (end - start + 2));

// //     while (start < end) {
// //         start = skip_redir(input_read, start, end);
// //         i = start;
// //         quote = 0;

// //         // Handle quoted strings
// //         if (input_read[start] == '"' || input_read[start] == '\'') {
// //             quote = input_read[start++];
// //             while (start < end && input_read[start] != quote)
// //                 start++;
// //             if (start < end)
// //                 start++; // Skip closing quote
// //         } else {
// //             // Normal argument parsing
// //             while (start < end && input_read[start] != ' ' && !(input_read[start] >= 9
// //                     && input_read[start] <= 13) && input_read[start] != '<'
// //                     && input_read[start] != '>') {
// //                 start++;
// //             }
// //         }

// //         cmd->args[cmd->args_count++] = ft_substr(input_read, i, start - i);
// //     }

// //     cmd->args[cmd->args_count] = NULL;
// // }

