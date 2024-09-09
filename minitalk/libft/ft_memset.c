/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:37:27 by riporth           #+#    #+#             */
/*   Updated: 2023/11/13 16:48:38 by riporth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*s_ptr;

	s_ptr = s;
	while (n)
	{
		*s_ptr = c;
		s_ptr++;
		n--;
	}
	return (s);
}
