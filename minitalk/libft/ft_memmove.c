/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 16:45:37 by riporth           #+#    #+#             */
/*   Updated: 2023/11/13 16:46:03 by riporth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*dest_ptr;
	char	*src_ptr;

	dest_ptr = (char *)dest;
	src_ptr = (char *)src;
	if (n && dest != src)
	{
		if (src_ptr < dest_ptr)
		{
			while (n--)
				*(dest_ptr + n) = *(src_ptr + n);
			return (dest);
		}
		while (n--)
			*dest_ptr++ = *src_ptr++;
		return (dest);
	}
	return (dest);
}
