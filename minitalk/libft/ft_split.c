/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:12:29 by riporth           #+#    #+#             */
/*   Updated: 2023/11/20 18:10:09 by riporth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_substrnum(char const *s, char c)
{
	int		count;

	count = 0;
	if (*s != c && *s)
		count++;
	while (*s)
	{
		while (*s == c)
		{
			s++;
			if (!*s)
				return (count);
			else if (*s != c)
				count++;
		}
		s++;
	}
	return (count);
}

static int	ft_substrlen(const char *s, char c)
{
	int		len;

	len = 0;
	while (*s)
	{
		if (*s == c)
			return (len);
		len++;
		s++;
	}
	return (len);
}

char const	*ft_loop(char const *s, char c)
{
	while (*s == c)
		s++;
	return (s);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	int		num;
	int		len;
	int		ind;

	if (!s)
		return (NULL);
	num = ft_substrnum(s, c);
	ptr = (char **)malloc(sizeof(char *) * (num + 1));
	if (!ptr)
		return (NULL);
	ptr[num] = NULL;
	ind = 0;
	while (ind < num)
	{
		s = ft_loop(s, c);
		len = ft_substrlen(s, c);
		ptr[ind] = (char *)malloc(sizeof(char) * (len + 1));
		if (!ptr[ind])
			return (NULL);
		ft_strlcpy(ptr[ind], s, len + 1);
		s = s + len;
		ind++;
	}
	return (ptr);
}
