/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:58:01 by riporth           #+#    #+#             */
/*   Updated: 2024/09/03 18:01:40 by riporth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	char	*h;
	char	*n;

	if (!*needle)
	{
		return ((char *)haystack);
	}

	while (*haystack)
	{
		h = haystack;
		n = needle;
		while (*h && *n && (*h == *n)) 
		{
			h++;
			n++;
		}
		if (!*n)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
