/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:03:47 by danevans          #+#    #+#             */
/*   Updated: 2024/08/19 16:30:23 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	index;
	char			*str;

	if (start >= ft_strlen(s) || len <= 0)
	{
		str = (char *)malloc(sizeof(char));
		if (str == NULL)
			return (NULL);
		*str = '\0';
		return (str);
	}
	if ((ft_strlen(s) - start) < len)
		len = ft_strlen(s) - start;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	index = 0;
	while (index < len && s[start + index] != '\0')
	{
		str[index] = s[start + index];
		index++;
	}
	str[index] = '\0';
	return (str);
}

static int	count_words(char const *s, char *delimter)
{
	int	i;
	int	count;
	int	control;

	i = 0;
	count = 0;
	control = 0;
	while (s[i] != '\0')
	{
		if ((s[i] != delimter[0] || s[i] != delimter[1] || s[i] != delimter[2]
				|| s[i] != delimter[3] || s[i] != delimter[4]
				|| s[i] != delimter[5]) && control == 0)
		{
			count++;
			control = 1;
		}
		else if (s[i] == delimter[0] || s[i] == delimter[1]
			|| s[i] == delimter[2] || s[i] == delimter[3]
			|| s[i] == delimter[4])
			control = 0;
		i++;
	}
	return (count);
}

static void	*free_str(char **result)
{
	int	i;

	i = 0;
	while (result[i])
	{
		free (result[i]);
		i++;
	}
	free (result);
	return (NULL);
}

static char	**write_str(char const *s, char *c, char **result, int start)
{
	size_t	i;
	int		j;	

	i = 0;
	j = 0;
	while (i <= ft_strlen(s))
	{
		if ((s[i] != c[0] || s[i] != c[1]
				|| s[i] != c[2] || s[i] != c[3]) && start < 0)
			start = i;
		else if (is_type(s, c, start, i))
		{
			result[j++] = ft_substr(s, start, i - start);
			if (result[j - 1] == NULL)
			{
				free_str (result);
				return (NULL);
			}
			start = -1;
		}
		i++;
	}
	result[j] = NULL;
	return (result);
}

char	**ft_split(char const *s, char *delimeter)
{
	int		size;
	int		start;
	char	**result;

	size = count_words(s, delimeter);
	if (!s || size == 0)
	{
		result = (char **)malloc(sizeof(char *) * (size + 1));
		if (!result)
			return (NULL);
		*result = NULL;
	}
	else
	{
		result = (char **)malloc(sizeof(char *) * (size + 1));
		if (!result)
			return (NULL);
		start = -1;
		result = write_str(s, delimeter, result, start);
	}
	return (result);
}

static int	count_wordsss(char const *s, char c)
{
	int	i;
	int	count;
	int	in_word;
	int	single_quote;
	int	double_quote;

	i = 0;
	count = 0;
	in_word = 0;
	single_quote = 0;
	double_quote = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '"')
			double_quote = !double_quote;
		else if (s[i] == '\'')
			single_quote = !single_quote;
		else if (s[i] != c && !single_quote && !double_quote)
		{
			if (!in_word)
			{
				printf("******** from first string %c\n", s[i]);
				count++;
				in_word = 1;
			}
		}
		else if (s[i] == c && !single_quote && !double_quote)
		{
			in_word = 0;
		}
		// else if (s[i] == c && (single_quote || double_quote))
		// {
		// 	// in_word = 0;
		// }
		else if (s[i] != c && (single_quote || double_quote))
		{
			if (!in_word)
			{
				printf("******** %c\n", s[i]);
				count++;
				in_word = 1;
			}
		}
		i++;
	}
	printf("****what is count ******* %d\n", count);
	return (count);
}

// static void	*free_strss(char **result)
// {
// 	int	i;

// 	i = 0;
// 	while (result[i])
// 	{
// 		free (result[i]);
// 		i++;
// 	}
// 	free (result);
// 	return (NULL);
// }

static char	**write_strss(char const *s, char c, char **result, int start)
{
	size_t	i;
	int		j;	

	i = 0;
	j = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && start < 0) 
			start = i;
		else if ((s[i] == c || i == ft_strlen(s)) && start >= 0)
		{
			result[j++] = ft_substr(s, start, i - start);
			if (result[j - 1] == NULL)
			{
				free_str (result);
				return (NULL);
			}
			start = -1;
		}
		i++;
	}
	result[j] = NULL;
	return (result);
}

char	**ft_spliter(char const *s, char c)
{
	int		size;
	int		start;
	char	**result;

	size = count_wordsss(s, c);
	if (!s || size == 0)
	{
		result = (char **)malloc(sizeof(char *) * (size + 1));
		if (!result)
			return (NULL);
		*result = NULL;
	}
	else
	{
		printf("count ======== %d\n", size);
		result = (char **)malloc(sizeof(char *) * (size + 1));
		if (!result)
			return (NULL);
		start = -1;
		result = write_strss(s, c, result, start);
	}
	return (result);
}
