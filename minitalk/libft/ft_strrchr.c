/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:51:13 by riporth           #+#    #+#             */
/*   Updated: 2023/11/14 15:53:50 by riporth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	ind;

	ind = ft_strlen(s);
	if (c == '\0')
		return ((char *)s + ind);
	else
	{
		while (ind >= 0)
		{
			if (s[ind] == (char)c)
				return ((char *)(s + ind));
			ind--;
		}
	}
	return (0);
}
