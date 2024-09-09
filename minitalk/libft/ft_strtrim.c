/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 16:13:09 by riporth           #+#    #+#             */
/*   Updated: 2023/11/20 14:07:21 by riporth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	size_t	len;
	size_t	ind;

	ind = 0;
	len = ft_strlen(s1);
	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup((char *)s1));
	while (s1[ind] && ft_strchr(set, s1[ind]))
		ind++;
	if (len > ind)
		while (s1[len - 1] && ft_strchr(set, s1[len - 1]))
			len--;
	trimmed = (char *)malloc(sizeof(char) * (len - ind + 1));
	if (!trimmed)
		return (NULL);
	if (trimmed)
		ft_strlcpy(trimmed, &s1[ind], len - ind + 1);
	return (trimmed);
}
