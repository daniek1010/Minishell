/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft__new_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:50:03 by riporth           #+#    #+#             */
/*   Updated: 2024/09/09 12:58:09 by riporth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_count(const char *str, int i, int *count, int *in_word)
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

int	count_qoute(const char *str, int i, int *count, int	*in_word)
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

int	count_word(const char *str, int i, int *count, int	*in_word)
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

int	token_count_words(const char *str)
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
			i = pipe_count(str, i, &count, &in_word);
		else if (strchr("\'\"", str[i]))
			i = count_qoute(str, i, &count, &in_word);
		else if (!((str[i] <= 13 && str[i] >= 9) || str[i] == 32))
			i = count_word(str, i, &count, &in_word);
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
			i = count_qoute(str, i, &count, &in_word);
		else if (!((str[i] <= 13 && str[i] >= 9) || str[i] == 32))
			i = count_word(str, i, &count, &in_word);
		else
			break ;
	}
	return (i);
}

char	*fill_word(const char *str, char *list, int *i)
{
	int	j;
	int	x;

	j = 0;
	x = 0;
	j = count_string_length(str, *i);
	j = j - *i;
	list = (char *)malloc(sizeof(char) * (j + 1));
	list[j] = '\0';
	while (x < j)
	{
		list[x] = str[*i];
		x++;
		*i += 1;
	}
	return (list);
}

char	*fill_direct(const char *str, char *list, int *i)
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

char	**ft_token_fill(const char *str, char **list)
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
			list[j] = fill_direct(str, list[j], &i);
		else
			list[j] = fill_word(str, list[j], &i);
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

char	*replace_substring(char *str, char *to_replace, char *replacement)
{
	char	*pos;
	char	*new_str;
	int		new_len;
	int		prefix_len;

	pos = ft_strstr(str, to_replace);
	if (!pos)
		return (str);
	new_len = ft_strlen(str) - ft_strlen(to_replace) + ft_strlen(replacement);
	new_str = malloc((new_len + 1) * sizeof(char));
	if (!new_str)
		return (str);
	prefix_len = pos - str;
	ft_strcpy(new_str, str);
	new_str[prefix_len] = '\0';
	ft_strcat(new_str, replacement);
	ft_strcat(new_str, pos + ft_strlen(to_replace));
	return (new_str);
}

char	*isolate_variable(char *str, int i)
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
	if (!var)
		return (NULL);
	strncpy(var, str + start, length);
	var[length] = '\0';
	return (var);
}

char	*expand_var(t_infos *tokens, char *str, int x, int *flag)
{
	char	*var;
	char	*replace;

	var = isolate_variable(str, x);
	x++;
	if (str[x] == '?')
	{
		replace = ft_strdup(ft_itoa(tokens->e_code));
		*flag = 1;
	}
	else
		replace = get_env_var(*(tokens->envp), var);
	return (replace);
}

char	*add_var(char *str, int *i, t_infos *tokens)
{
	char	*new;
	char	*var;
	char	*replace;
	int		flag;
	char	*new_var;

	flag = 0;
	var = isolate_variable(str, *i);
	replace = expand_var(tokens, str, *i, &flag);
	new_var = ft_strjoin("$", var);
	if (!replace)
	{
		*i += ft_strlen(var);
		return (str);
	}
	new = replace_substring(str, new_var, replace);
	free (var);
	free (new_var);
	*i += ft_strlen(replace);
	free (replace);
	free(str);
	return (new);
}

char	*ft_extract_variables(char *str, t_infos *tokens)
{
	int	i;
	int	in_qoute_1;
	int	in_qoute_2;

	i = 0;
	in_qoute_1 = 2;
	in_qoute_2 = 2;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && in_qoute_1 % 2 == 0)
			in_qoute_2 += 1;
		else if (str[i] == '\"' && in_qoute_2 % 2 == 0)
			in_qoute_1 += 1;
		if (str[i] == '$' && in_qoute_2 % 2 == 0)
			str = add_var(str, &i, tokens);
		else
			i++;
	}
	return (str);
}
//----------------------

char *remove_char_at_position(char *str, int pos)
{
	int		len;
	char	*new_str;

	len = ft_strlen(str);
	*new_str = (char *)malloc((len) * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_strncpy(new_str, str, pos);
	ft_strcpy(new_str + pos, str + pos + 1);
	free (str);
	return (new_str);
}

char *remove_qoute(char *str)
{
	int	i;
	int	in_qoute_1;
	int	in_qoute_2;

	i = 1;
	in_qoute_1 = 2;
	in_qoute_2 = 2;
	if (str[0] == '\'' && in_qoute_1 % 2 == 0)
		in_qoute_2 += 1;
	else if (str[0] == '\"' && in_qoute_2 % 2 == 0)
		in_qoute_1 += 1;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && in_qoute_1 % 2 == 0)
			in_qoute_2 += 1;
		else if (str[i] == '\"' && in_qoute_2 % 2 == 0)
			in_qoute_1 += 1;
		else if (str[i] == '$' && in_qoute_2 % 2 == 0)
			str = remove_char_at_position(str, i);
		else if (str[i] == '\'' && in_qoute_1 % 2 == 0)
			str = remove_char_at_position(str,i);
		i++;
	}
	return (str);
}

//------------------------------------------------------------------

char	**ft_var_up(char **list, int count, t_infos *tokens)
{
	int	x;

	x = 0;
	while (x != count)
	{
		list[x] = ft_extract_variables(list[x], tokens);
		list[x] = ft_remove_qoutation();
		x++;
	}
	return (list);
}

//-------------------------------------------------------------------------------------------------
char	**ft_token_split(char const *s, t_infos *tokens)
{
	int		word;
	char	**list;

	word = token_count_words(s);
	list = (char **)malloc(sizeof(char *) * (word + 1));
	if (!list)
		return (NULL);
	list[word] = NULL;
	list = ft_token_fill(s, list);
	list = ft_var_up(list, word);
	return (list);
}
