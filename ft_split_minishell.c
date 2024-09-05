/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_minishell.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 19:03:47 by danevans          #+#    #+#             */
/*   Updated: 2024/09/05 19:55:18 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	unsigned int	index;
// 	char			*str;

// 	if (start >= ft_strlen(s) || len <= 0)
// 	{
// 		str = (char *)malloc(sizeof(char));
// 		if (str == NULL)
// 			return (NULL);
// 		*str = '\0';
// 		return (str);
// 	}
// 	if ((ft_strlen(s) - start) < len)
// 		len = ft_strlen(s) - start;
// 	str = (char *)malloc(sizeof(char) * (len + 1));
// 	if (str == NULL)
// 		return (NULL);
// 	index = 0;
// 	while (index < len && s[start + index] != '\0')
// 	{
// 		str[index] = s[start + index];
// 		index++;
// 	}
// 	str[index] = '\0';
// 	return (str);
// }

// static int	count_words(char const *s, char delimter)
// {
// 	int	i;
// 	int	count;
// 	int	control;

// 	i = 0;
// 	count = 0;
// 	control = 0;
// 	while (s[i] != '\0')
// 	{
// 		if (s[i] != delimter && control == 0)
// 		{
// 			count++;
// 			control = 1;
// 		}
// 		else if (s[i] == delimter)
// 			control = 0;
// 		i++;
// 	}
// 	return (count);
// }

// static void	*free_str(char **result)
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

// static char	**write_str(char const *s, char c, char **result, int start)
// {
// 	size_t	i;
// 	int		j;	

// 	i = 0;
// 	j = 0;
// 	while (i <= ft_strlen(s))
// 	{
// 		if (s[i] != c && start < 0)
// 			start = i;
// 		else if (is_type(s, c, start, i))
// 		{
// 			result[j++] = ft_substr(s, start, i - start);
// 			if (result[j - 1] == NULL)
// 			{
// 				free_str (result);
// 				return (NULL);
// 			}
// 			start = -1;
// 		}
// 		i++;
// 	}
// 	result[j] = NULL;
// 	return (result);
// }

// char	**ft_split(char const *s, char delimeter)
// {
// 	int		size;
// 	int		start;
// 	char	**result;

// 	size = count_words(s, delimeter);
// 	if (!s || size == 0)
// 	{
// 		result = (char **)malloc(sizeof(char *) * (size + 1));
// 		if (!result)
// 			return (NULL);
// 		*result = NULL;
// 	}
// 	else
// 	{
// 		result = (char **)malloc(sizeof(char *) * (size + 1));
// 		if (!result)
// 			return (NULL);
// 		start = -1;
// 		result = write_str(s, delimeter, result, start);
// 	}
// 	return (result);
// }
