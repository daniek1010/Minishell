/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 16:11:04 by riporth           #+#    #+#             */
/*   Updated: 2023/11/14 16:12:20 by riporth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	ind;

	ind = 0;
	if (n == 0 || !s1 || !s2)
		return (0);
	while (s1[ind] != '\0' && s1[ind] == s2[ind] && (ind + 1 < n))
		ind++;
	return ((unsigned char)s1[ind] - (unsigned char)s2[ind]);
}
