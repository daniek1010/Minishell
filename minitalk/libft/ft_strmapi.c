/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:51:03 by riporth           #+#    #+#             */
/*   Updated: 2023/11/20 10:54:51 by riporth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	ind;
	char			*new;

	new = malloc(sizeof(char *) * ft_strlen(s) + 1);
	if (!new)
		return (NULL);
	ind = 0;
	while (s[ind])
	{
		new[ind] = (*f)(ind, s[ind]);
		ind++;
	}
	new[ind] = '\0';
	return (new);
}
