/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:12:40 by riporth           #+#    #+#             */
/*   Updated: 2023/11/13 17:12:59 by riporth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem_adr;

	mem_adr = malloc(nmemb * size);
	if (!mem_adr)
		return (NULL);
	ft_bzero(mem_adr, nmemb * size);
	return (mem_adr);
}
