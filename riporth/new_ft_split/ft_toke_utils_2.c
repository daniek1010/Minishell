/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toke_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riporth <riporth@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:47:59 by riporth           #+#    #+#             */
/*   Updated: 2024/08/30 15:08:13 by riporth          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "change_the_file.h"

int	count_qoute(const char *str, int i, char a)
{
	i++;
	while (str[i] != '\0')
	{
		if (str[i] == a)
		{
			break ;
		}
		i++;
	}
	return (i);
}
