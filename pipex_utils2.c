/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.f>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 10:25:24 by danevans          #+#    #+#             */
/*   Updated: 2024/08/02 04:27:37 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// cat args1 args2 | ls args3 args

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*str;
	size_t		s1_len;
	size_t		s2_len;
	size_t		i;
	size_t		j;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

size_t	ft_strlen(const char *s)
{
	int	index;

	index = 0;
	while (s[index] != '\0')
		index++;
	return (index);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	index;

	index = 0;
	if (n == 0)
		return (0);
	while (((s1[index] != '\0') || (s2[index] != '\0')) && index < n)
	{
		if (s1[index] != s2[index])
			return ((unsigned char)s1[index] - (unsigned char) s2[index]);
		index++;
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	index;

	index = 0;
	while ((s1[index] != '\0') || (s2[index] != '\0'))
	{
		if (s1[index] != s2[index])
			return ((unsigned char)s1[index] - (unsigned char) s2[index]);
		index++;
	}
	return (0);
}

void	bad_arg(int x)
{
	if (x == 2)
	{
		write(2, "cmd1 not found\n", ft_strlen("cmd1 not found\n"));
		write(2, "FMT > infile.txt cmd1 cmd2 outfile.txt \n", 41);
		exit(EXIT_FAILURE);
	}
	else if (x == 3)
	{
		write(2, "cmd2 not found\n", ft_strlen("cmd2 not found\n"));
		write(2, "FMT > infile.txt cmd1 cmd2 outfile.txt \n", 41);
		exit(EXIT_FAILURE);
	}
}

// void	error(void)
// {
// 	perror("Error");
// 	exit(EXIT_FAILURE);
// }
