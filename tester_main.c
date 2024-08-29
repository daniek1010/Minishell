#include <stdio.h>
#include <string.h>
#include "minishell.h"

char	*get_cmd_name(int start, int end, char *input_read);
int main()
{
	char *input = "        <this<   here    < is    >the <input        impressed ?";
	size_t len = strlen(input);
	(int)len;
	int start = 0;
	char *name = get_cmd_name(start, len, input);
	printf("%s\n", name);
}

void	rm_whitespace(char *str, int *start, int end)
{
	while (*start < end && str[*start] == ' ' || (str[*start] >= 9 && str[*start] <= 13))
		(*start)++;
}

int	skip_redir(char *input_read, int start, int end)
{
	int	i;

	i = 0;
	rm_whitespace(input_read, &start, end);
	while ((input_read[start] == '<' && input_read[start + 1] != '<')
		||(input_read[start] == '>' && input_read[start + 1] != '>') 
		||(input_read[start] == '<' && input_read[start + 1] == '<')
		||(input_read[start] == '>' && input_read[start + 1] == '>'))
	{
		if (input_read[start + 1] == '<' || input_read[start + 1] == '>')
			start += 2;
		else
			start++;
		rm_whitespace(input_read, &start, end);
		while (start < end && input_read[start] != ' ' && !(input_read[start] >= 9
				&& input_read[start] <= 13) && input_read[start] != '<'
				&& input_read[start] != '>')
			start++;
		rm_whitespace(input_read, &start, end);
	}
	return (start);
}

char	*get_cmd_name(int start, int end, char *input_read)
{
	int		i;
	char	*name;

	start = skip_redir(input_read, start, end);
	i = start;
	while (start < end && input_read[start] != ' ' && !(input_read[start] >= 9
			&& input_read[start] <= 13) && input_read[start] != '<'
			&& input_read[start] != '>')
		start++;
	name = ft_substr(input_read, i, start - i);
	return name;
}