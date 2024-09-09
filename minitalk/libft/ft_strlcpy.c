/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:46:49 by riporth           #+#    #+#             */
/*   Updated: 2023/11/13 16:48:47 by riporth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	ind;

	ind = 0;
	if (!dst || !src)
		return (0);
	if (!size)
		return (ft_strlen(src));
	while (src[ind] != '\0' && ind < size - 1)
	{
		dst[ind] = src[ind];
		ind++;
	}
	dst[ind] = '\0';
	return (ft_strlen(src));
}
