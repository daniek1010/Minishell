/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell_utils7.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:04:18 by danevans          #+#    #+#             */
/*   Updated: 2024/09/09 20:01:43 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_count_2(const char *str, int i, int *count, int *in_word)
{
	*count += 1;
	*in_word = 1;
	if (str[i] == '>' && str[i + 1] == '>')
		i++;
	else if (str[i] == '<' && str[i + 1] == '<')
		i++;
	else if (str[i] == '>' && str[i + 1] == '|')
		i++;
	i++;
	return (i);
}

int	count_qoute_2(const char *str, int i, int *count, int	*in_word)
{
	char	a;

	a = str[i];
	i++;
	if (*in_word == 1)
		*count += 1;
	*in_word = 0;
	while (str[i] != '\0')
	{
		if (str[i] == a)
		{
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

int	count_word_2(const char *str, int i, int *count, int	*in_word)
{
	i++;
	if (*in_word == 1)
		*count += 1;
	*in_word = 0;
	while (str[i] != '\0')
	{
		if (strchr("|><\'\"", str[i]))
			break ;
		else if ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
			break ;
		i++;
	}
	return (i);
}

int	token_count_words_2(const char *str)
{
	int	count;
	int	in_word;
	int	i;

	count = 0;
	in_word = 1;
	i = 0;
	while (str[i] != '\0')
	{
		if (strchr("|><", str[i]))
			i = pipe_count_2(str, i, &count, &in_word);
		else if (strchr("\'\"", str[i]))
			i = count_qoute_2(str, i, &count, &in_word);
		else if (!((str[i] <= 13 && str[i] >= 9) || str[i] == 32))
			i = count_word_2(str, i, &count, &in_word);
		else
		{
			in_word = 1;
			i++;
		}
	}
	return (count);
}

//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------

int	count_string_length(const char *str, int i)
{
	int in_word;
	int	count;

	in_word = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (strchr("|><", str[i]))
			break ;
		else if (strchr("\'\"", str[i]))
			i = count_qoute_2(str, i, &count, &in_word);
		else if (!((str[i] <= 13 && str[i] >= 9) || str[i] == 32))
			i = count_word_2(str, i, &count, &in_word);
		else
			break ;
	}
	return (i);
}

char	*fill_word_2(const char *str, char *list, int *i)
{
	int	j;
	int	x;

	j = 0;
	x = 0;
	j = count_string_length(str, *i);
	j = j - *i;
	list = (char *)malloc(sizeof(char) * (j + 1));
	printf("addres list %p -------------------\n", &list);
	list[j] = '\0';
	while (x < j)
	{
		list[x] = str[*i];
		x++;
		*i += 1;
	}
	return (list);
}

char	*fill_direct_2(const char *str, char *list, int *i)
{
	int	x;

	x = 1;
	if (str[*i] == '>' && str[*i + 1] == '>')
		x++;
	else if (str[*i] == '<' && str[*i + 1] == '<')
		x++;
	else if (str[*i] == '>' && str[*i + 1] == '|')
		x++;
	list = (char *)malloc(sizeof(char) * (x + 1));
	printf("addres list_2 %p -------------------\n", &list);
	if (!list)
		return (NULL);
	list[x] = '\0';
	list[0] = str[*i];
	if (x == 2)
	{
		(*i)++;
		list[1] = str[*i];
	}
	(*i)++;
	return (list);
}

char	**ft_token_fill_2(const char *str, char **list)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (((str[i] <= 13 && str[i] >= 9) || str[i] == 32))
		{
			i++;
			j--;
		}
		else if (strchr("|><", str[i]))
			list[j] = fill_direct_2(str, list[j], &i);
		else
			list[j] = fill_word_2(str, list[j], &i);
		j++;
	}
	return (list);
}

//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
char	*fill_part_one (const char *str, int *j, int i)
{
	char	*new_str;
	int		len;

	len = ft_strlen(str);
	new_str = (char *)malloc((len + 1) * sizeof(char));
	printf("addres new_str %p -------------------\n", &new_str);
	new_str[len] = '\0';
	if (!new_str)
		return (NULL);
	while (*j < i)
	{
		new_str[*j] = str[*j];
		*j += 1;
	}
	return (new_str);
}

char	*fill_part_two (const char *str, char *new_str, int j, int i)
{
	while (str[i] != '\0')
	{
		new_str[j] = str[i];
		j++;
		i++;
	}
	return (new_str);
}

char	*remove_char( char *str, char to_remove, int i)
{
	char	*new_str;
	int		j;

	j = 0;
	new_str = fill_part_one(str, &j, i);
	if (!new_str)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] != to_remove)
		{
			new_str[j] = str[i];
			j++;
		}
		else
			break ;
		i++;
	}
	if (str[i] != '\0')
		new_str = fill_part_two(str, new_str, j, i);
	free(str);
	return (new_str);
}

char	*replace_substring_2(char *str, char *to_replace, char *replacement)
{
	char	*pos;
	char	*new_str;
	int		new_len;
	int		prefix_len;

	pos = ft_strstr(str, to_replace);
	if (!pos)
		return (str);
	new_len = ft_strlen(str) - ft_strlen(to_replace) + ft_strlen(replacement);
	if (new_len == 0)
		return (str);
	new_str = malloc((new_len + 1) * sizeof(char));
	// new_str[new_len] = '\0';
	printf("addres new_str_2 %p -------------------\n", &new_str);
	if (!new_str)
		return (str);
	prefix_len = pos - str;
	ft_strcpy(new_str, str);
	new_str[prefix_len] = '\0';
	strcat(new_str, replacement);
	strcat(new_str, pos + ft_strlen(to_replace));
	return (new_str);
}

char	*isolate_variable_2(char *str, int i)
{
	int		length;
	int		start;
	char	*var;

	if (str[i] != '$')
		return (NULL);
	i++;
	start = i;
	while (is_valid_var_char(str[i]))
		i++;
	length = i - start;
	if (length == 0)
		return (NULL);
	var = malloc((length + 1) * sizeof(char));
	printf("addres var %p -------------------\n", &var);
	if (!var)
		return (NULL);
	strncpy(var, str + start, length);
	var[length] = '\0';
	return (var);
}

char	*expand_var_2(t_infos *tokens, char *str, int x, int *flag)
{
	char	*var;
	char	*replace;

	var = isolate_variable_2(str, x);
	x++;
	if (str[x] == '?')
	{
		replace = ft_itoa(tokens->e_code);
		*flag = 1;
		return (replace);
	}
	replace = get_env_var(*(tokens->envp), var);
	if (!replace)
		return (replace);
	replace = ft_strdup(get_env_var(*(tokens->envp), var));
	return (replace);
	
}
char *remove_char_at_position(char *str, int pos)
{
	int		len;
	char	*new_str;

	len = ft_strlen(str);
	new_str = (char *)malloc((len) * sizeof(char));
	printf("addres newstr_2 %p -------------------\n", &new_str);
	if (!new_str)
		return (NULL);
	strncpy(new_str, str, pos);
	strcpy(new_str + pos, str + pos + 1);
	free (str);
	return (new_str);
}

char	*add_var_2(char *str, int *i, t_infos *tokens)
{
	char	*new;
	char	*var;
	char	*replace;
	int		flag;
	char	*new_var;

	flag = 0;
	var = isolate_variable_2(str, *i);
	replace = expand_var_2(tokens, str, *i, &flag);
	if (var == NULL)
		new_var = ft_strjoin("$", "?");
	else
		new_var = ft_strjoin("$", var);
	if (!replace)
	{
		new = replace_substring_2(str, new_var, "" );
		// free (replace);
		// write an function that removes a worrd at the x point of the array
	}
	else
	{
		new = replace_substring_2(str, new_var, replace);
		*i += ft_strlen(replace);
		// free (replace);
	}
	if (replace)
		free (replace);
	free (var);
	free (new_var);
	free(str);
	return (new);
}

char	*ft_extract_variables_2(char *str, t_infos *tokens)
{
	int	i;
	int	in_single_qoute;
	int	in_double_qoute;

	i = 0;
	in_single_qoute = 0;
	in_double_qoute = 0;
	while (str[i] != '\0')
	{
		// handel singel $ case
		if (str[i] == '\"' && in_single_qoute == 0)
			in_double_qoute = !in_double_qoute;
		else if (str[i] == '\'' && in_double_qoute == 0)
			in_single_qoute = !in_single_qoute;
		if (str[i] == '$' && in_single_qoute == 0)
			str = add_var_2(str, &i, tokens);
		else
			i++;
	}
	return (str);
}
//----------------------



// char *remove_qoute(char *str)
// {
// 	int	i;
// 	int	in_single_qoute;
// 	int	in_double_qoute;

// 	i = 1;
// 	in_single_qoute = 2;
// 	in_double_qoute = 2;
// 	if (str[0] == '\'')
// 		in_single_qoute += 1;
// 	else if (str[0] == '\"')
// 		in_double_qoute += 1;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '\"' && in_single_qoute % 2 != 0)
// 		{
// 			str = remove_char_at_position(str, i);
// 			in_double_qoute += 1;
// 		}
// 		if (str[i] == '\'' && in_double_qoute % 2 != 0)
// 		{
// 			str = remove_char_at_position(str,i);
// 			in_single_qoute += 1;
// 		}
// 		i++;
// 	}
// 	return (str);
// }

char *remove_qoute(char *str)
{
	int i;
	int in_single_qoute = 0;
	int in_double_qoute = 0;

	i = 1;
	if (str[0] == '\"')
		in_double_qoute = !in_double_qoute;
	else if (str[0] == '\'')
		in_single_qoute = !in_single_qoute;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' && in_single_qoute == 0)
		{
			str = remove_char_at_position(str, i);
			in_double_qoute = !in_double_qoute;
		}
		else if (str[i] == '\'' && in_double_qoute == 0)
		{
			str = remove_char_at_position(str, i);
			in_single_qoute = !in_single_qoute;
		}
		else
		{
			i++;
		}
	}
	return str;
}


//------------------------------------------------------------------

char	**ft_var_up(char **list, int count, t_infos *tokens)
{
	int	x;

	x = 0;
	while (x != count)
	{
		list[x] = ft_extract_variables_2(list[x], tokens);
		list[x] = remove_qoute(list[x]);
		x++;
	}
	return (list);
}

//-------------------------------------------------------------------------------------------------
char	**ft_token_spliter_2(char const *s, t_infos *tokens)
{
	int		word;
	char	**list;

	word = token_count_words_2(s);
	list = (char **)malloc(sizeof(char *) * (word + 1));
	printf("addres list_super %p -------------------\n", &list);
	if (!list)
		return (NULL);
	list[word] = NULL;
	list = ft_token_fill_2(s, list);
	list = ft_var_up(list, word, tokens);
	return (list);
}