/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:37:48 by riporth           #+#    #+#             */
/*   Updated: 2023/11/16 11:43:56 by riporth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	ind;

	if (!s)
		return (NULL);
	if ((size_t)start >= ft_strlen(s))
		return (ft_strdup(""));
	substr = malloc((sizeof(char) * len) + 1);
	if (!substr)
		return (NULL);
	ind = 0;
	while (s[start] != '\0' && len > ind)
	{
		substr[ind] = s[start];
		start++;
		ind++;
	}
	substr[ind] = '\0';
	return (substr);
}
